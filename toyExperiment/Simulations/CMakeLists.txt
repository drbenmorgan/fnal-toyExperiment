simple_plugin( EventGenerator "module"
               toyExperiment_Conditions_Conditions_service
               toyExperiment_Utilities
               toyExperiment_MCDataProducts
               ${ART_FRAMEWORK_CORE}
               ${ART_FRAMEWORK_PRINCIPAL}
               ${ART_PERSISTENCY_COMMON}
             )

simple_plugin( DetectorSimulation "module"
               toyExperiment_Conditions_Conditions_service
               toyExperiment_Geometry_Geometry_service
               toyExperiment_Utilities
               toyExperiment_MCDataProducts
               toyExperiment_RecoDataProducts
               ${ART_FRAMEWORK_CORE}
               ${ART_FRAMEWORK_PRINCIPAL}
               ${ART_PERSISTENCY_COMMON}
               ${ART_FRAMEWORK_SERVICES_REGISTRY}
               ${ART_FRAMEWORK_SERVICES_OPTIONAL_TFILESERVICE_SERVICE}
               ${ART_FRAMEWORK_SERVICES_OPTIONAL}
               ${FHICLCPP}
               ${CETLIB}
             )

simple_plugin( HitMaker "module"
               toyExperiment_Conditions_Conditions_service
               toyExperiment_Geometry_Geometry_service
               toyExperiment_Utilities
               toyExperiment_MCDataProducts
               toyExperiment_RecoDataProducts
               ${ART_FRAMEWORK_CORE}
               ${ART_FRAMEWORK_PRINCIPAL}
               ${ART_PERSISTENCY_COMMON}
               ${ART_FRAMEWORK_SERVICES_REGISTRY}
               ${ART_FRAMEWORK_SERVICES_OPTIONAL_TFILESERVICE_SERVICE}
               ${ART_FRAMEWORK_SERVICES_OPTIONAL}
               ${FHICLCPP}
               ${CETLIB}
             )

install_headers()
install_source()
