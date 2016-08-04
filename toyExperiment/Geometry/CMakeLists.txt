art_make(
  LIB_LIBRARIES
  toyExperiment_Utilities
  ${FHICLCPP}
  ${CETLIB}
  ${CLHEP}
  SERVICE_LIBRARIES
  toyExperiment_Geometry
  toyExperiment_Utilities
  art_Persistency_Provenance canvas_Persistency_Provenance
  ${FHICLCPP}
  ${CETLIB}
  ${CLHEP}
  ${ROOT_CORE}
  )

install_headers()
install_source()
