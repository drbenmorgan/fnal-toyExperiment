# ======================================================================
#  toy experiment main build file.
#
#  cd .../path/to/build/directory
#  source .../path/to/art_hough/ups/setup_for_development
#  buildtool -f[T]l
# ======================================================================

# use cmake 2.8 or later
cmake_minimum_required (VERSION 2.8)

# cetbuildtools contains our cmake modules
SET ( CETBUILDTOOLS_VERSION $ENV{CETBUILDTOOLS_VERSION} )
IF (NOT CETBUILDTOOLS_VERSION)
    MESSAGE (FATAL_ERROR "ERROR: setup cetbuildtools to get the cmake modules")
ENDIF()

set(CMAKE_MODULE_PATH
#          ${CMAKE_PROJECT_DIR}/Modules
          $ENV{ART_DIR}/Modules
		      $ENV{CETBUILDTOOLS_DIR}/Modules
		      ${CMAKE_MODULE_PATH})

include(CetCMakeEnv)
cet_cmake_env()

cet_set_compiler_flags(DIAGS VIGILANT WERROR NO_UNDEFINED EXTRA_FLAGS -pedantic)

cet_have_qual( e5 )
if ( ${CET_HAVE_QUAL} )
  # -D_GLIBCXX_USE_NANOSLEEP is needed to make std::this_thread::sleep_for available.
  cet_add_compiler_flags(CXX -std=c++11 -D_GLIBCXX_USE_NANOSLEEP)
endif()
cet_report_compiler_flags()

# these are minimum required versions, not the actual product versions
find_ups_product( art v1_09_03 )
find_ups_product( cetbuildtools v3_05_01 )

cet_check_gcc()

# include search path
# notice use of ENV to invoke an external variable
include_directories ( $ENV{LIBSIGCPP_INC}/sigc++-2.0 )
include_directories ( $ENV{LIBSIGCPP_LIB}/sigc++-2.0/include )

#  Find all the libraries needed by our dependent CMakeList.txt files
find_library( CPPUNIT NAMES cppunit   PATHS $ENV{CPPUNIT_LIB}   NO_DEFAULT_PATH )
find_library( SIGC    NAMES sigc-2.0  PATHS $ENV{LIBSIGCPP_LIB} NO_DEFAULT_PATH )


message(STATUS "Project is ${product} ${version} ${qualifier}")

# macros for artdaq_dictionary and simple_plugin
include(ArtDictionary)
include(ArtMake)
include(BuildPlugins)

# testing
#add_subdirectory(test)

# source
add_subdirectory(toyExperiment)

# Scripts
add_subdirectory(scripts)

# Admin stuff
add_subdirectory(admin)

# ups - table and config files
add_subdirectory(ups)

# packaging utility
include(UseCPack)
