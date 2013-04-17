art_make_library(SOURCE PlotOrientation.cc
  )

set(COMMON_LIBRARIES
  ${ART_FRAMEWORK_CORE}
  ${ART_FRAMEWORK_PRINCIPAL}
  ${ART_PERSISTENCY_COMMON}
  ${ART_FRAMEWORK_SERVICES_REGISTRY}
  ${ART_FRAMEWORK_SERVICES_OPTIONAL_TFILESERVICE_SERVICE}
  ${ART_FRAMEWORK_SERVICES_OPTIONAL}
  ${FHICLCPP}
  ${CETLIB}
  ${CLHEP}
)

simple_plugin( HelloWorld "module"
  ${ART_FRAMEWORK_CORE}
  ${ART_FRAMEWORK_PRINCIPAL}
  ${ART_PERSISTENCY_COMMON}
  )

simple_plugin( InspectGenParticles "module"
  toyExperiment_MCDataProducts
  ${COMMON_LIBRARIES}
  ${ROOT_HIST}
  ${ROOT_TREE}
  )

simple_plugin( InspectIntersections "module"
  toyExperiment_MCDataProducts
  ${COMMON_LIBRARIES}
  ${ROOT_HIST}
  ${ROOT_TREE}
  )

simple_plugin( InspectTrkHits "module"
  toyExperiment_RecoDataProducts
  ${COMMON_LIBRARIES}
  ${ROOT_HIST}
  ${ROOT_TREE}
  )

simple_plugin( InspectFittedHelix "module"
  toyExperiment_RecoDataProducts
  ${COMMON_LIBRARIES}
  ${ROOT_HIST}
  ${ROOT_TREE}
  )

simple_plugin( MassPlot "module"
  toyExperiment_Conditions
  toyExperiment_Reconstruction
  toyExperiment_RecoDataProducts
  ${COMMON_LIBRARIES}
  ${ROOT_HIST}
  ${ROOT_TREE}
  )

simple_plugin( EventDisplay "module"
  toyExperiment_Conditions_Conditions_service
  toyExperiment_Geometry_Geometry_service
  toyExperiment_MCDataProducts
  toyExperiment_Analyzers
  toyExperiment_Utilities
  ${COMMON_LIBRARIES}
  ${ROOT_GRAF}
  ${ROOT_GPAD}
  ${ROOT_HIST}
  ${ROOT_CORE}
  )

install_headers()
install_source()
