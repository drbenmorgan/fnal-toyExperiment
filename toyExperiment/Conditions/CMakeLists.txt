
if(DEFINED ENV{CETLIB_EXCEPT_DIR})
art_make(
  LIB_LIBRARIES toyExperiment_Utilities
  SERVICE_LIBRARIES
  toyExperiment_Conditions
  art_Framework_Core
  art_Framework_Principal
  art_Persistency_Common
  art_Persistency_Provenance
  art_Framework_Services_Registry
  art_Utilities
  canvas
  ${CLHEP}
  )
else()
art_make(
  LIB_LIBRARIES toyExperiment_Utilities
  SERVICE_LIBRARIES
  toyExperiment_Conditions
  art_Framework_Core
  art_Framework_Principal
  art_Persistency_Common canvas_Persistency_Common
	art_Persistency_Provenance canvas_Persistency_Provenance
  art_Framework_Services_Registry
  art_Utilities canvas_Utilities
  ${CLHEP}
  )
endif()

install_headers()
install_source()
