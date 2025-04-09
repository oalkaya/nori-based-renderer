# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/Users/daphnemayor/Desktop/ComputerGraphics/nori_omer_daphne/build/ext_build/src/nanogui_p-build/ext_build/src/glfw_p"
  "/Users/daphnemayor/Desktop/ComputerGraphics/nori_omer_daphne/build/ext_build/src/nanogui_p-build/ext_build/src/glfw_p-build"
  "/Users/daphnemayor/Desktop/ComputerGraphics/nori_omer_daphne/build/ext_build/src/nanogui_p-build/ext_build"
  "/Users/daphnemayor/Desktop/ComputerGraphics/nori_omer_daphne/build/ext_build/src/nanogui_p-build/ext_build/tmp"
  "/Users/daphnemayor/Desktop/ComputerGraphics/nori_omer_daphne/build/ext_build/src/nanogui_p-build/ext_build/src/glfw_p-stamp"
  "/Users/daphnemayor/Desktop/ComputerGraphics/nori_omer_daphne/build/ext_build/src/nanogui_p-build/ext_build/src"
  "/Users/daphnemayor/Desktop/ComputerGraphics/nori_omer_daphne/build/ext_build/src/nanogui_p-build/ext_build/src/glfw_p-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/Users/daphnemayor/Desktop/ComputerGraphics/nori_omer_daphne/build/ext_build/src/nanogui_p-build/ext_build/src/glfw_p-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/Users/daphnemayor/Desktop/ComputerGraphics/nori_omer_daphne/build/ext_build/src/nanogui_p-build/ext_build/src/glfw_p-stamp${cfgdir}") # cfgdir has leading slash
endif()
