# Should have a library and one service
# 1. The library
add_library(toyExperiment_Geometry SHARED
  IntersectionFinder.cc
  IntersectionFinder.h
  LuminousRegion.cc
  LuminousRegion.h
  Shell.cc
  Shell.h
  Tracker.cc
  Tracker.h
  TrackerComponent.cc
  TrackerComponent.h
  )

target_include_directories(toyExperiment_Geometry
  PUBLIC
    $<BUILD_INTERFACE:${PRODUCT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
  )

# We also use a header-only part from DataProducts, but don't
# link directly as it's internal so handled by above include_directories
# usage requirements
target_link_libraries(toyExperiment_Geometry
  PUBLIC
    CLHEP::CLHEP
    toyExperiment_RecoDataProducts
  )

# 2. The service
# We will get a fair amount of libs linked automatically, but
# declare all direct dependencies at least directly outside art...
simple_plugin(Geometry "service"
  toyExperiment_Geometry
  toyExperiment_Utilities
  canvas::canvas
  fhiclcpp::fhiclcpp
  messagefacility::MF_MessageLogger
  )
