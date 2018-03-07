# Should have a library and module
# 1. The library
add_library(toyExperiment_Reconstruction SHARED
  FittedHelix.h
  FittedHelix.cc
  )

target_include_directories(toyExperiment_Reconstruction
  PUBLIC
    $<BUILD_INTERFACE:${PRODUCT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
  )

target_link_libraries(toyExperiment_Reconstruction
  PUBLIC
    CLHEP::CLHEP
    toyExperiment_RecoDataProducts
  PRIVATE
    toyExperiment_Geometry_Geometry_service
    art::art_Framework_Services_Registry
    cetlib::cetlib
  )

# 2. The module
simple_plugin(FindAndFitHelix "module"
  # libs
  toyExperiment_Reconstruction
  toyExperiment_RecoDataProducts
  toyExperiment_MCDataProducts
  CLHEP::CLHEP
  canvas::canvas
  # services
  toyExperiment_Conditions_Conditions_service
  toyExperiment_Geometry_Geometry_service
  toyExperiment_PDT_PDT_service
  )
