
art_make(
  LIB_LIBRARIES toyExperiment_Utilities
  SERVICE_LIBRARIES
  toyExperiment_PDT
  toyExperiment_Utilities
  ${ART_FRAMEWORK_CORE}
  ${ART_FRAMEWORK_PRINCIPAL}
  ${ART_PERSISTENCY_COMMON}
  ${ART_PERSISTENCY_PROVENANCE}
  ${ART_FRAMEWORK_SERVICES_REGISTRY}
  ${ART_UTILITIES}
  )

install_headers()
install_source()
