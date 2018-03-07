# Have three module plugins

simple_plugin(DetectorSimulation "module"
  #libs
  toyExperiment_MCDataProducts
  toyExperiment_RecoDataProducts
  #services
  art::art_Framework_Services_Registry
  toyExperiment_Geometry_Geometry_service
  toyExperiment_PDT_PDT_service
  )

simple_plugin(EventGenerator "module"
  #libs
  toyExperiment_MCDataProducts
  toyExperiment_Utilities
  CLHEP::CLHEP
  #services
  art::art_Framework_Services_Registry
  toyExperiment_PDT_PDT_service
  )

simple_plugin(HitMaker "module"
  #libs
  toyExperiment_MCDataProducts
  toyExperiment_RecoDataProducts
  toyExperiment_Utilities
  CLHEP::CLHEP
  # services
  art::art_Framework_Services_Registry
  toyExperiment_Conditions_Conditions_service
  toyExperiment_Geometry_Geometry_service
  )
