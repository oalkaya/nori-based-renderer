# Install script for directory: /Users/daphnemayor/Desktop/ComputerGraphics/nori_omer_daphne/build/ext_build/src/nanogui_p

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/Users/daphnemayor/Desktop/ComputerGraphics/nori_omer_daphne/build/ext_build/dist")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/Applications/Xcode_14_01.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/objdump")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/Users/daphnemayor/Desktop/ComputerGraphics/nori_omer_daphne/build/ext_build/src/nanogui_p-build/libnanogui.a")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libnanogui.a" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libnanogui.a")
    execute_process(COMMAND "/Applications/Xcode_14_01.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/ranlib" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libnanogui.a")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE FILE FILES
    "/Users/daphnemayor/Desktop/ComputerGraphics/nori_omer_daphne/build/ext_build/src/nanogui_p/ext/nanovg/src/fontstash.h"
    "/Users/daphnemayor/Desktop/ComputerGraphics/nori_omer_daphne/build/ext_build/src/nanogui_p/ext/nanovg/src/nanovg.h"
    "/Users/daphnemayor/Desktop/ComputerGraphics/nori_omer_daphne/build/ext_build/src/nanogui_p/ext/nanovg/src/nanovg_gl.h"
    "/Users/daphnemayor/Desktop/ComputerGraphics/nori_omer_daphne/build/ext_build/src/nanogui_p/ext/nanovg/src/nanovg_gl_utils.h"
    "/Users/daphnemayor/Desktop/ComputerGraphics/nori_omer_daphne/build/ext_build/src/nanogui_p/ext/nanovg/src/stb_image.h"
    "/Users/daphnemayor/Desktop/ComputerGraphics/nori_omer_daphne/build/ext_build/src/nanogui_p/ext/nanovg/src/stb_truetype.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE DIRECTORY FILES "/Users/daphnemayor/Desktop/ComputerGraphics/nori_omer_daphne/build/ext_build/src/nanogui_p/ext/eigen/Eigen")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE DIRECTORY FILES "/Users/daphnemayor/Desktop/ComputerGraphics/nori_omer_daphne/build/ext_build/src/nanogui_p/include/nanogui")
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/Users/daphnemayor/Desktop/ComputerGraphics/nori_omer_daphne/build/ext_build/src/nanogui_p-build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
