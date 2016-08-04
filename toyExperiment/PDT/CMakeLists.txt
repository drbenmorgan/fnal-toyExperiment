
art_make(
  LIB_LIBRARIES toyExperiment_Utilities
  SERVICE_LIBRARIES
  toyExperiment_PDT
  toyExperiment_Utilities
  ${ART_FRAMEWORK_CORE}
  ${ART_FRAMEWORK_PRINCIPAL}
  art_Persistency_Common canvas_Persistency_Common
  art_Persistency_Provenance canvas_Persistency_Provenance
  ${ART_FRAMEWORK_SERVICES_REGISTRY}
  art_Utilities canvas_Utilities
  ${ROOT_CORE}
  )

install_headers()
install_source()
