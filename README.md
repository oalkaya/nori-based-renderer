# Renderer based on Nori

This repository builds upon the C++-based physically-based renderer **Nori**, progressively implementing core features of ray tracing and rendering techniques. The repository includes individual exercises and a collaborative final project.

## Solo Projects (Programming Assignments)

| Assignment | Task Overview |
|------------|---------------|
| **Raytracing Fundamentals** | Implemented core ray-object intersection routines and basic integrators (e.g. direct illumination). Introduced simple BSDFs and added support for analytic shapes. |
| **Sampling & Warping** | Implemented sampling techniques for square, disk, hemisphere, and microfacet distributions. Established the foundation for Monte Carlo integration. |
| **Direct Illumination** | Added area lights, emitter sampling, BSDF sampling, and implemented multiple importance sampling (MIS). Also integrated the Microfacet BRDF. |
| **Global Illumination** | Introduced dielectric BSDFs, full path tracer, and photon mapping. Extended Nori with multiple-bounce lighting, importance-based emitter selection, and global illumination integrators. |

## Final Project

In collaboration with Daphne Mayor, we extended the Nori renderer with several advanced and artistic rendering features. Highlights include:

- **Chromatic Aberration:** Implemented wavelength-dependent refraction using spectral sampling to simulate lens dispersion.
- **Depth of Field:** Used thin lens camera model to simulate realistic focus and blur.
- **Extended Lighting:** Added support for additional light sources.
- **Mipmapping:** Implemented mipmap generation and sampling for textured surfaces to reduce aliasing artifacts.
- **User Interface Enhancements:** Added toggles and debug views for comparing integrators, bounces, and BSDF types.
