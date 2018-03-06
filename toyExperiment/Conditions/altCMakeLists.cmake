# Should have a library and one service
# 1. The library
add_library(toyExperiment_Conditions SHARED
  ShellConditions.h
  ShellConditions.cc
  )

target_include_directories(toyExperiment_Conditions
  PUBLIC
    $<BUILD_INTERFACE:${PRODUCT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
  )

# 2. The service
# We will get a fair amount of libs linked automatically, but
# declare all direct dependencies at least directly outside art...
simple_plugin(Conditions "service"
  toyExperiment_Conditions
  toyExperiment_Geometry
  toyExperiment_Utilities
  )
