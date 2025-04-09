#include <nori/object.h>
#include <nori/texture.h>
#include <nori/lodepng.h>
#include <filesystem/resolver.h>

NORI_NAMESPACE_BEGIN

class ImageTextureLegacy : public Texture<Color3f> {
    public:
    ImageTextureLegacy(const PropertyList &props) {
        m_filename = props.getString("fileName", "");
        m_scalev2f = props.getVector2("scalev2f", Vector2f(1));
        cout << "XD" << endl;
        filesystem::path imagePath = getFileResolver()->resolve(m_filename);
        /* Image decoding inspired from https://raw.githubusercontent.com/lvandeve/lodepng/master/examples/example_decode.cpp, using the corresponding lodepng library.*/
        /* decode, also gives us image dimentions */
        unsigned error = lodepng::decode(m_image, m_width, m_height, imagePath.str());
        /* if there's an error, display it */
        if(error) std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;
        /* the pixels are now in the vector "image", 4 bytes per pixel, ordered RGBARGBA... */
    }

    /* For the input uv value, eval returns the corresponding pixel value in RGB. */
    Color3f eval(const Point2f &uv){
        /* Get uv values with the appropriate scaling */
        int u = (int)((uv.x() * m_width) / m_scalev2f.x());
        int v = (int)((uv.y() * m_height) / m_scalev2f.y());
        
        /* Since the image is 4 bytes per pixel ordered rowwise in RGBA format, we get the index to look up RGB values in m_image as follows */
        long i = 4 * (v * m_width + u);
        /* Handles the negative u v values */
        i = i % m_image.size();
        /* get RGB */
        float r = m_image[i];
        float g = m_image[i+1];
        float b = m_image[i+2];
        /* div by 255 for appropriate format */
        return Color3f(r,g,b) / 255.0f;
    }


    std::string toString() const{
        return tfm::format(
            "ImageTextureLegacy[\n"
            "   m_filename = %s,\n"
            "   scale = %s,\n"
            "]",
            m_filename,
            m_scalev2f.toString());
    }

    protected:
    std::string m_filename;
    Vector2f m_scalev2f;
    /* using unsigned to stick to library reference */
    std::vector<unsigned char> m_image; //the raw pixels
    unsigned m_width, m_height;
    
};

NORI_REGISTER_CLASS(ImageTextureLegacy, "imagetexture_legacy")
NORI_NAMESPACE_END
