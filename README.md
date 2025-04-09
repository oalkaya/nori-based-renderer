# Renderer based on Nori

This repository builds upon the C++-based physically-based renderer **Nori**, progressively implementing core features of ray tracing and rendering techniques. The repository includes individual tasks and a collaborative final project.

## Programming Assignments

| Task | Task Overview |
|------------|---------------|
| **PA1: Raytracing Fundamentals** | Implemented core ray-object intersection routines and basic integrators (e.g. direct illumination). Introduced simple BSDFs and added support for analytic shapes. |
| **PA2: Sampling & Warping** | Implemented sampling techniques for square, disk, hemisphere, and microfacet distributions. Established the foundation for Monte Carlo integration. |
| **PA3: Direct Illumination** | Added area lights, emitter sampling, BSDF sampling, and implemented multiple importance sampling (MIS). Also integrated the Microfacet BRDF. |
| **PA4: Global Illumination** | Introduced dielectric BSDFs, full path tracer, and photon mapping. Extended Nori with multiple-bounce lighting, importance-based emitter selection, and global illumination integrators. |

## Final Project

In collaboration with Daphne Mayor, we extended the Nori renderer with advanced features such as Disney BSDFs, progressive photon mapping, heterogeneous volumetric media, an advanced camera model (with depth of field, lens distortion, and chromatic aberration), environment lighting, texture mipmapping, and support for image-based textures and spotlights.

## 👥 Credits
- **Omer Alkaya**
- **Daphne Mayor**
- **Framework:** [Nori Renderer]([https://github.com/eth-igl/nori](https://wjakob.github.io/nori/))


