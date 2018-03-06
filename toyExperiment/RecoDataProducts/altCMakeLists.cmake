# Should have a library and dictionary
# 1. The library
add_library(toyExperiment_RecoDataProducts SHARED
  DetectorStatus.cc
  DetectorStatus.h
  DetectorStatusRecord.cc
  DetectorStatusRecord.h
  FittedHelixData.cc
  FittedHelixData.h
  FittedHelixDataCollection.h
  Helix.cc
  Helix.h
  RecoTrk.cc
  RecoTrk.h
  RecoTrkCollection.h
  TrkHit.cc
  TrkHit.h
  TrkHitCollection.h
  )

target_include_directories(toyExperiment_RecoDataProducts
  PUBLIC
    $<BUILD_INTERFACE:${PRODUCT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
  )

target_link_libraries(toyExperiment_RecoDataProducts PUBLIC CLHEP::CLHEP)

# 2. The dictionary, probably sufficient libraries as art_dictionary will
#    link to all we need?
art_dictionary(DICTIONARY_LIBRARIES toyExperiment_RecoDataProducts)

