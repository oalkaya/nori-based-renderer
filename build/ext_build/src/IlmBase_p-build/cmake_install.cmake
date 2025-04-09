# Install script for directory: /Users/daphnemayor/Desktop/ComputerGraphics/nori_omer_daphne/build/ext_build/src/IlmBase_p

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
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/Users/daphnemayor/Desktop/ComputerGraphics/nori_omer_daphne/build/ext_build/dist/lib/libHalf.la")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/Users/daphnemayor/Desktop/ComputerGraphics/nori_omer_daphne/build/ext_build/dist/lib" TYPE FILE FILES "/Users/daphnemayor/Desktop/ComputerGraphics/nori_omer_daphne/build/ext_build/src/IlmBase_p-build/libHalf.la")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/Users/daphnemayor/Desktop/ComputerGraphics/nori_omer_daphne/build/ext_build/dist/lib/libIex.la")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/Users/daphnemayor/Desktop/ComputerGraphics/nori_omer_daphne/build/ext_build/dist/lib" TYPE FILE FILES "/Users/daphnemayor/Desktop/ComputerGraphics/nori_omer_daphne/build/ext_build/src/IlmBase_p-build/libIex.la")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/Users/daphnemayor/Desktop/ComputerGraphics/nori_omer_daphne/build/ext_build/dist/lib/libIexMath.la")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/Users/daphnemayor/Desktop/ComputerGraphics/nori_omer_daphne/build/ext_build/dist/lib" TYPE FILE FILES "/Users/daphnemayor/Desktop/ComputerGraphics/nori_omer_daphne/build/ext_build/src/IlmBase_p-build/libIexMath.la")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/Users/daphnemayor/Desktop/ComputerGraphics/nori_omer_daphne/build/ext_build/dist/lib/libImath.la")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/Users/daphnemayor/Desktop/ComputerGraphics/nori_omer_daphne/build/ext_build/dist/lib" TYPE FILE FILES "/Users/daphnemayor/Desktop/ComputerGraphics/nori_omer_daphne/build/ext_build/src/IlmBase_p-build/libImath.la")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/Users/daphnemayor/Desktop/ComputerGraphics/nori_omer_daphne/build/ext_build/dist/lib/libIlmThread.la")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/Users/daphnemayor/Desktop/ComputerGraphics/nori_omer_daphne/build/ext_build/dist/lib" TYPE FILE FILES "/Users/daphnemayor/Desktop/ComputerGraphics/nori_omer_daphne/build/ext_build/src/IlmBase_p-build/libIlmThread.la")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/OpenEXR" TYPE FILE FILES "/Users/daphnemayor/Desktop/ComputerGraphics/nori_omer_daphne/build/ext_build/src/IlmBase_p-build/config/IlmBaseConfig.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/Users/daphnemayor/Desktop/ComputerGraphics/nori_omer_daphne/build/ext_build/src/IlmBase_p-build/IlmBase.pc")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/Users/daphnemayor/Desktop/ComputerGraphics/nori_omer_daphne/build/ext_build/src/IlmBase_p-build/Half/cmake_install.cmake")
  include("/Users/daphnemayor/Desktop/ComputerGraphics/nori_omer_daphne/build/ext_build/src/IlmBase_p-build/Iex/cmake_install.cmake")
  include("/Users/daphnemayor/Desktop/ComputerGraphics/nori_omer_daphne/build/ext_build/src/IlmBase_p-build/IexMath/cmake_install.cmake")
  include("/Users/daphnemayor/Desktop/ComputerGraphics/nori_omer_daphne/build/ext_build/src/IlmBase_p-build/Imath/cmake_install.cmake")
  include("/Users/daphnemayor/Desktop/ComputerGraphics/nori_omer_daphne/build/ext_build/src/IlmBase_p-build/IlmThread/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/Users/daphnemayor/Desktop/ComputerGraphics/nori_omer_daphne/build/ext_build/src/IlmBase_p-build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
