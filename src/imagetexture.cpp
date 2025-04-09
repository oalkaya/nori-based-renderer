#include <nori/object.h>
#include <nori/texture.h>
#include <nori/lodepng.h>
#include <filesystem/resolver.h>

NORI_NAMESPACE_BEGIN

/* Wrapper class to work with mipmaps easier */
struct MIPMapLevel
{
public:
    MIPMapLevel(std::vector<Color3f> level_img, int level_width, int level_height, int curr_level)
    {
        m_level_img = level_img;
        m_level_width = level_width;
        m_level_height = level_height;
        m_curr_level = curr_level;
    }

    std::vector<Color3f> m_level_img;
    int m_level_width;
    int m_level_height;
    int m_curr_level;
};

/* MIPMap helper class, inspired from PBR Book 10.4, using trilinear filtering */

class MIPMap
{
public:
    MIPMap() {}
    MIPMap(std::vector<Color3f> img, int width, int height, ImageWrap wrapMode)
    {
        m_wrapMode = wrapMode;

        if (!IsPowerOf2(width) || !IsPowerOf2(height))
        {
            throw NoriException("Image dimensions not power of 2");
        }

        /* Number of levels in the pyramid */
        int nLevels = 1 + (int)log2f(std::max(width, height));

        /* Init an empty MIPMap pyramid */
        m_pyramid = {};

        /* init most detailed level at level 0 */
        MIPMapLevel detailedLevel = MIPMapLevel(img, width, height, 0);
        m_pyramid.push_back(detailedLevel);

        /* init higher levels */
        for (int i = 1; i < nLevels; ++i)
        {
            /* init level i from i-1 */
            int sRes = std::max(1, m_pyramid[i - 1].m_level_width / 2);
            int tRes = std::max(1, m_pyramid[i - 1].m_level_height / 2);
            for (int t = 0; t < tRes; ++t)
            {
                for (int s = 0; s < sRes; ++s)
                {
                    /* Image indexing done with u * width + v, accessed rowwise */
                    m_pyramid[i].m_level_img[findIndex(m_pyramid[i], s, t)] = 0.25f * (Texel(i - 1, 2 * s, 2 * t) + Texel(i - 1, 2 * s + 1, 2 * t) +
                                         Texel(i - 1, 2 * s, 2 * t + 1) + Texel(i - 1, 2 * s + 1, 2 * t + 1));
                }
            }
        }
        std::cout << "end loop" << std::endl;
    }

    int findIndex(MIPMapLevel l, int s, int t)
    {
        4 * (s * l.m_level_width + t);
    }

    /* Called from the eval function in Texture, calls the trilinear interpolation function depending on the given width value */
    Color3f lookup(const Point2f &uv, float width)
    {
        float level = Levels() - 1 + log2f(std::max(width, (float)1e-8));
        if (level < 0)
        {
            return triangle(0, uv);
        }
        else if (level >= Levels() - 1)
        {
            return Texel(Levels() - 1, 0, 0);
        }
        else
        {
            int ilevel = std::floor(level);
            float delta = level - ilevel;
            return Lerp(delta, triangle(ilevel, uv), triangle(ilevel + 1, uv));
        }
    }

    /* Convenience enum to define image wrapping strategy */
    enum ImageWrap
    {
        Repeat = 0,
        Clamp,
        Black
    };

    /* Query to get the Color3f values from the appropriate pyramid level */
    Color3f Texel(int level, int s, int t)
    {
        // get wrapmode, do switchcase accordingly, get correct level of pyramid then depending on the case repeat clamp or return black
        MIPMapLevel l = m_pyramid[level];
        // switch
        switch (m_wrapMode)
        {
        case Repeat:
            s = Mod(s, l.m_level_width);
            t = Mod(t, l.m_level_height);
            break;
        case Clamp:
            s = ClampInt(s, 0, l.m_level_width - 1);
            t = ClampInt(t, 1, l.m_level_height - 1);
            break;
        case Black:
        {
            Color3f black = 0.f;
            if (s < 0 || s >= l.m_level_width ||
                t < 0 || t >= l.m_level_height)
                return black;
            break;
        }
        }
        return l.m_level_img[findIndex(l, s, t)];
        // if not blockedarray do the correct lookup!
    }

    /* Trilinear interpolation */
    Color3f triangle(int level, const Point2f &uv)
    {
        level = ClampInt(level, 0, Levels() - 1);
        float s = uv.x() * m_pyramid[level].m_level_width - 0.5f;
        float t = uv.y() * m_pyramid[level].m_level_height - 0.5f;
        int s0 = std::floor(s), t0 = std::floor(t);
        float ds = s - s0, dt = t - t0;
        return (1 - ds) * (1 - dt) * Texel(level, s0, t0) +
               (1 - ds) * dt * Texel(level, s0, t0 + 1) +
               ds * (1 - dt) * Texel(level, s0 + 1, t0) +
               ds * dt * Texel(level, s0 + 1, t0 + 1);
    }

    /* Returns how many levels there are in the MIPMap */
    int Levels()
    {
        return m_pyramid.size();
    }

    /* Helper functions from PBR, converted from templates to just the required types */

    /* Integer clamping */
    int ClampInt(int val, int low, int high)
    {
        if (val < low)
            return low;
        else if (val > high)
            return high;
        else
            return val;
    }

    /* Integer modulo operation, only positive output */
    int Mod(int a, int b)
    {
        int result = a - (a / b) * b;
        return (int)((result < 0) ? result + b : result);
    }

    /* Linear interpolation between Color3f */
    Color3f Lerp(float t, Color3f v1, Color3f v2)
    {
        return (1 - t) * v1 + t * v2;
    }

    /* Check if integer is a power of 2 */
    bool IsPowerOf2(int v)
    {
        return v && !(v & (v - 1));
    }

protected:
    /* m_pyramid is the MIPMap itself */
    std::vector<MIPMapLevel> m_pyramid;
    int m_wrapMode;
};

class ImageTexture : public Texture<Color3f>
{
public:
    ImageTexture(const PropertyList &props)
    {
        m_filename = props.getString("fileName", "");
        m_scale = props.getVector2("scale", Vector2f(1));
        m_width = props.getFloat("width", 0.0f);

        /* handle wrapMode */
        std::string wrapModeStr = props.getString("wrapMode", "repeat");
        ImageWrap wrapMode;
        if (wrapModeStr == "repeat")
            wrapMode = ImageWrap::Repeat;
        else if (wrapModeStr == "clamp")
            wrapMode = ImageWrap::Clamp;
        else if (wrapModeStr == "black")
            wrapMode = ImageWrap::Black;
        else
            throw NoriException("Undefined texture wrapping strategy in XML file!");

        filesystem::path imagePath = getFileResolver()->resolve(m_filename);
        /* Image decoding inspired from https://raw.githubusercontent.com/lvandeve/lodepng/master/examples/example_decode.cpp, using the corresponding lodepng library.*/
        /* decode, also gives us image dimentions */
        unsigned error = lodepng::decode(m_image, m_img_width, m_img_height, imagePath.str());
        /* the pixels are now in the vector "image", 4 bytes per pixel, ordered RGBARGBA... */
        /* if there's an error, display it */
        if (error)
            std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;

        /* Convert the image to vector<Color3f>*/
        int img_pCount = m_img_height * m_img_width;
        std::vector<Color3f> img_C3f = {};
        for (int i = 0; i < img_pCount; ++i)
        {
            /* Get R G and B separately */
            img_C3f.push_back(Color3f(m_image[4 * i], m_image[4 * i + 1], m_image[4 * i + 2]));
        }

        // create mipmap with image in vector<Color3f> format

        // UNSAFE TYPECASTING FROM UNSIGNED TO SIGNED
        m_MIPMap = MIPMap(img_C3f, (int)m_img_width, (int)m_img_height, wrapMode);
    }

    /* For the input uv value, eval returns the corresponding pixel value in RGB. */
    Color3f eval(const Point2f &uv)
    {
        return m_MIPMap.lookup(uv, m_width);
    }

    std::string toString() const
    {
        return tfm::format(
            "ImageToTexture[\n"
            "   m_filename = %s,\n"
            "   scale = %f,\n"
            "]",
            m_filename,
            m_scale);
    }

protected:
    std::string m_filename;
    Vector2f m_scale;
    /* MIPMap */
    MIPMap m_MIPMap;
    /* Compute mipmap level from width */
    float m_width;
    /* original image params */
    std::vector<unsigned char> m_image; // the raw pixels
    unsigned m_img_width, m_img_height;
};

NORI_REGISTER_CLASS(ImageTexture, "imagetexture")
NORI_NAMESPACE_END
