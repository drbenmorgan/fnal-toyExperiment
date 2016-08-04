art_make(
  LIB_LIBRARIES toyExperiment_Geometry_Geometry_service
  toyExperiment_PDT_PDT_service
  toyExperiment_PDT
  toyExperiment_Geometry
  toyExperiment_RecoDataProducts
  toyExperiment_Utilities
  ${ART_FRAMEWORK_SERVICES_REGISTRY}
  art_Utilities canvas_Utilities
  ${CETLIB}
  ${Boost_SYSTEM_LIBRARY}
  MODULE_LIBRARIES
  toyExperiment_Conditions_Conditions_service
  toyExperiment_Geometry_Geometry_service
  toyExperiment_PDT_PDT_service
  toyExperiment_PDT
  toyExperiment_Utilities
  toyExperiment_MCDataProducts
  toyExperiment_RecoDataProducts
  ${ART_FRAMEWORK_CORE}
  ${ART_FRAMEWORK_PRINCIPAL}
  art_Persistency_Common canvas_Persistency_Common
  ${ART_FRAMEWORK_SERVICES_REGISTRY}
  ${ART_FRAMEWORK_SERVICES_OPTIONAL_TFILESERVICE_SERVICE}
  ${ART_FRAMEWORK_SERVICES_OPTIONAL}
  ${FHICLCPP}
  ${CETLIB}
  )

install_headers()
install_source()
