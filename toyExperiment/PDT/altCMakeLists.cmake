# Should have a library and one service
# 1. The library
add_library(toyExperiment_PDT SHARED
  ParticleInfo.h
  ParticleInfo.cc
  )

target_include_directories(toyExperiment_PDT
  PUBLIC
    $<BUILD_INTERFACE:${PRODUCT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
  )

target_link_libraries(toyExperiment_PDT
  PUBLIC
    CLHEP::CLHEP
    toyExperiment_RecoDataProducts
  )

# 2. The service
# We will get a fair amount of libs linked automatically, but
# declare all direct dependencies at least directly outside art...
simple_plugin(PDT "service"
  toyExperiment_PDT
  toyExperiment_Utilities
  canvas::canvas
  fhiclcpp::fhiclcpp
  )
