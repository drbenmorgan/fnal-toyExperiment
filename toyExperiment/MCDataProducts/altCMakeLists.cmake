# Should have a library and dictionary
# 1. The library
add_library(toyExperiment_MCDataProducts SHARED
  GenParticle.cc
  GenParticle.h
  GenParticleCollection.h
  Intersection.cc
  Intersection.h
  IntersectionCollection.h
  MCRunSummary.cc
  MCRunSummary.h
  TrkHitMatch.h
  )
target_include_directories(toyExperiment_MCDataProducts
  PUBLIC
    $<BUILD_INTERFACE:${PRODUCT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
  )
target_link_libraries(toyExperiment_MCDataProducts
  PUBLIC
    toyExperiment_RecoDataProducts
    canvas::canvas
  )

# 2. The dictionary, link should be sufficient?
art_dictionary(DICTIONARY_LIBRARIES toyExperiment_MCDataProducts)

