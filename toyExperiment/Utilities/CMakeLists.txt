art_make(
  LIB_LIBRARIES
  toyExperiment_RecoDataProducts
  art_Persistency_Provenance canvas_Persistency_Provenance
  art_Utilities canvas_Utilities
  ${CLHEP}
  ${FHICLCPP}
  ${CETLIB}
  ${Boost_SYSTEM_LIBRARY}
  )

install_headers()
install_source()
