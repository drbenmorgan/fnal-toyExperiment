file( GLOB files *.fcl *.cint *.sh)
install( FILES ${files}
         DESTINATION ${product}/${version}/HelloWorldScripts )

install_source()
