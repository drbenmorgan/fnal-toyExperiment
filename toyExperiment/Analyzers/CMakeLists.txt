art_make_library(SOURCE EnsureTApplication.cc PlotOrientation.cc
                        WaitFor.cc
   LIBRARIES
   ${ROOT_CORE}
  )

set(COMMON_LIBRARIES
  ${ART_FRAMEWORK_CORE}
  ${ART_FRAMEWORK_PRINCIPAL}
  art_Persistency_Common canvas_Persistency_Common
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
  art_Persistency_Common canvas_Persistency_Common
  )

simple_plugin( InspectGenParticles "module"
  toyExperiment_PDT_PDT_service
  toyExperiment_PDT
  toyExperiment_MCDataProducts
  toyExperiment_Conditions_Conditions_service
  ${COMMON_LIBRARIES}
  ${ROOT_HIST}
  ${ROOT_TREE}
  )

simple_plugin( InspectIntersections "module"
  toyExperiment_PDT_PDT_service
  toyExperiment_PDT
  toyExperiment_MCDataProducts
  toyExperiment_Utilities
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
  toyExperiment_PDT_PDT_service
  toyExperiment_PDT
  toyExperiment_Reconstruction
  toyExperiment_RecoDataProducts
  ${COMMON_LIBRARIES}
  ${ROOT_HIST}
  ${ROOT_TREE}
  )

simple_plugin( EventDisplay "module"
  toyExperiment_Conditions_Conditions_service
  toyExperiment_Geometry_Geometry_service
  toyExperiment_PDT_PDT_service
  toyExperiment_PDT
  toyExperiment_MCDataProducts
  toyExperiment_Analyzers
  toyExperiment_Utilities
  ${COMMON_LIBRARIES}
  ${MF_MESSAGELOGGER}
  ${ROOT_GRAF}
  ${ROOT_GPAD}
  ${ROOT_HIST}
  ${ROOT_CORE}
  )

install_headers()
install_source()
