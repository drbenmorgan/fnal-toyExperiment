art_make(
  LIB_LIBRARIES
  toyExperiment_Utilities
  ${FHICLCPP}
  ${CETLIB}
  ${CLHEP}
  SERVICE_LIBRARIES
  toyExperiment_Geometry
  toyExperiment_Utilities
  ${ART_PERSISTENCY_PROVENANCE}
  ${FHICLCPP}
  ${CETLIB}
  ${CLHEP}
  )

install_headers()
install_source()
