if(ALT_CMAKE)
  include(altCMakeLists.cmake)
  return()
endif()

art_dictionary(DICTIONARY_LIBRARIES ${CLHEP})

install_headers()
install_source()
