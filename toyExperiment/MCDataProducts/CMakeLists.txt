art_make(
  LIB_LIBRARIES ${CLHEP}
  art_Persistency_Provenance canvas_Persistency_Provenance
  art_Persistency_Common canvas_Persistency_Common
  DICT_LIBRARIES
  ${ART_PERSISTENCY_CORE}
  art_Persistency_Provenance canvas_Persistency_Provenance
  art_Persistency_Common canvas_Persistency_Common
  ${CETLIB}
  ${ART_UTILITES}
  toyExperiment_MCDataProducts
  )

install_headers()
install_source()
