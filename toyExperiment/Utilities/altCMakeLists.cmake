# Should have a library only
# 1. The library
add_library(toyExperiment_Utilities SHARED
  Decay2Body.cc
  Decay2Body.h
  ParameterSetFromFile.cc
  ParameterSetFromFile.h
  ParameterSetHelpers.cc
  ParameterSetHelpers.h
  RandomUnitSphere.cc
  RandomUnitSphere.h
  TwoBodyKinematics.cc
  TwoBodyKinematics.h
  dphi.cc
  dphi.h
  eventIDToString.cc
  eventIDToString.h
  inputTagsFromStrings.cc
  inputTagsFromStrings.h
  phi_norm.cc
  phi_norm.h
  phi_small.cc
  phi_small.h
  polar3Vector.cc
  polar3Vector.h
  safeSqrt.h
  sqrtOrThrow.cc
  sqrtOrThrow.h
  )

target_include_directories(toyExperiment_Utilities
  PUBLIC
    $<BUILD_INTERFACE:${PRODUCT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
  )

# *Might* need art_Framework_Services_Optional_RandomNumberGenerator
# but not obvious that it's actually used other than header inclusion.
target_link_libraries(toyExperiment_Utilities
  PUBLIC
    CLHEP::CLHEP
    canvas::canvas
    fhiclcpp::fhiclcpp
  PRIVATE
    cetlib::cetlib
  )

