art_make(
  LIB_LIBRARIES
  ${ART_PERSISTENCY_PROVENANCE}
  ${CLHEP}
  DICT_LIBRARIES
  toyExperiment_RecoDataProducts
  ${ART_PERSISTENCY_CORE}
  ${ART_PERSISTENCY_PROVENANCE}
  ${ART_PERSISTENCY_COMMON}
  ${ART_UTILITES}
  ${CETLIB}
  )

install_headers()
install_source()
