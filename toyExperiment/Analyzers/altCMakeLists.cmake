# Should have one library plus 7 module plugins
# 1. Library - only used by EventDisplay_module
add_library(toyExperiment_Analyzers SHARED
  EnsureTApplication.h
  EnsureTApplication.cc
  PlotOrientation.h
  PlotOrientation.cc
  WaitFor.h
  WaitFor.cc
  )
target_include_directories(toyExperiment_Analyzers
  PUBLIC
    $<BUILD_INTERFACE:${PRODUCT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
  PRIVATE
    ${ROOT_INCLUDE_DIRS}
  )
target_link_libraries(toyExperiment_Analyzers PRIVATE ROOT::Core)

# 1.1 EventDisplay plugin, using above lib
simple_plugin(EventDisplay "module"
  # libs
  toyExperiment_Analyzers
  toyExperiment_MCDataProducts
  toyExperiment_RecoDataProducts
  toyExperiment_Utilities
  messagefacility::MF_MessageLogger
  ROOT::Core
  ROOT::Hist
  ROOT::Gpad
  ROOT::Graf
  # services
  toyExperiment_Geometry_Geometry_service
  toyExperiment_PDT_PDT_service
  )

# 2. module plugin
simple_plugin(HelloWorld "module")

# 3. helix inspector
simple_plugin(InspectFittedHelix "module"
  #libs
  toyExperiment_RecoDataProducts
  ROOT::Hist
  ROOT::Tree
  CLHEP::CLHEP
  #services
  art::art_Framework_Services_Optional_TFileService_service
  )

# 4. MC particle inspector
simple_plugin(InspectGenParticles "module"
  #libs
  toyExperiment_MCDataProducts
  ROOT::Hist
  CLHEP::CLHEP
  #services
  toyExperiment_PDT_PDT_service
  art::art_Framework_Services_Optional_TFileService_service
  )

# 5. Intersection inspector
simple_plugin(InspectIntersections "module"
  #libs
  toyExperiment_MCDataProducts
  toyExperiment_Utilities
  CLHEP::CLHEP
  ROOT::Hist
  ROOT::Tree
  #services
  art::art_Framework_Services_Optional_TFileService_service
  )

# 6. TrkHit inspector
simple_plugin(InspectTrkHits "module"
  #libs
  toyExperiment_MCDataProducts
  toyExperiment_RecoDataProducts
  canvas::canvas
  CLHEP::CLHEP
  ROOT::Hist
  #services
  toyExperiment_Conditions_Conditions_service
  toyExperiment_Geometry_Geometry_service
  art::art_Framework_Services_Optional_TFileService_service
  )

# 7. Plot masses
simple_plugin(MassPlot "module"
  #libs
  toyExperiment_RecoDataProducts
  toyExperiment_Reconstruction
  cetlib::cetlib
  ROOT::Hist
  ROOT::Tree
  #services
  toyExperiment_Geometry_Geometry_service
  toyExperiment_PDT_PDT_service
  art::art_Framework_Services_Optional_TFileService_service
  )


