# - Toplevel CMake script for fnal::art
cmake_minimum_required(VERSION 3.3)
project(toyExperiment VERSION 0.3.15)

# - Cetbuildtools, version2
find_package(cetbuildtools2 0.5.0 REQUIRED)
set(CMAKE_MODULE_PATH ${cetbuildtools2_MODULE_PATH})
set(CET_COMPILER_CXX_STANDARD_MINIMUM 14)
include(CetInstallDirs)
include(CetCMakeSettings)
include(CetCompilerSettings)

#-----------------------------------------------------------------------
# Dependencies
# Add everything that the product uses directly
find_package(art 2.10 REQUIRED)
find_package(canvas_root_io REQUIRED)
find_package(ROOT 6 REQUIRED)

# macros for art_dictionary and simple_plugin
include(ArtDictionary)
include(BuildPlugins)

# source
# this helps with dictionary generation...
include_directories(${PROJECT_SOURCE_DIR})
add_subdirectory(toyExperiment)

# TODO
# Scripts
#add_subdirectory(scripts)

# TODO
# Admin stuff
#add_subdirectory(admin)

# TODO
# ups - table and config files
#add_subdirectory(ups)

# TODO
# packaging utility
#include(UseCPack)

