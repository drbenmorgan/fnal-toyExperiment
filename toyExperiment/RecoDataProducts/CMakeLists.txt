art_make(
  LIB_LIBRARIES
  art_Persistency_Provenance canvas_Persistency_Provenance
  ${CLHEP}
  DICT_LIBRARIES
  toyExperiment_RecoDataProducts
  ${ART_PERSISTENCY_CORE}
  art_Persistency_Provenance canvas_Persistency_Provenance
  art_Persistency_Common canvas_Persistency_Common
  ${ART_UTILITES}
  ${CETLIB}
  )

install_headers()
install_source()
