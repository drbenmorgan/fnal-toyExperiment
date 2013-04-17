art_make(
  LIB_LIBRARIES toyExperiment_Geometry_Geometry_service
  toyExperiment_Geometry
  toyExperiment_RecoDataProducts
  toyExperiment_Utilities
  ${ART_FRAMEWORK_SERVICES_REGISTRY}
  ${ART_UTILITIES}
  ${CETLIB}
  MODULE_LIBRARIES
  toyExperiment_Conditions_Conditions_service
  toyExperiment_Geometry_Geometry_service
  toyExperiment_Utilities
  toyExperiment_MCDataProducts
  toyExperiment_RecoDataProducts
  ${ART_FRAMEWORK_CORE}
  ${ART_FRAMEWORK_PRINCIPAL}
  ${ART_PERSISTENCY_COMMON}
  ${ART_FRAMEWORK_SERVICES_REGISTRY}
  ${ART_FRAMEWORK_SERVICES_OPTIONAL_TFILESERVICE_SERVICE}
  ${ART_FRAMEWORK_SERVICES_OPTIONAL}
  ${FHICLCPP}
  ${CETLIB}
  )

install_headers()
install_source()
