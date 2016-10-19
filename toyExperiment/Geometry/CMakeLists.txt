art_make(
  LIB_LIBRARIES
    toyExperiment_Utilities
    fhiclcpp
    cetlib
    ${CLHEP}
  SERVICE_LIBRARIES
    toyExperiment_Geometry
    toyExperiment_Utilities
    art_Persistency_Provenance canvas_Persistency_Provenance
    fhiclcpp
    cetlib
    ${CLHEP}
  )

install_headers()
install_source()
