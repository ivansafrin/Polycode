#TODO: actually build the pak file
IF(POLYCODE_INSTALL_FRAMEWORK)
    
    # install default.pak file
    INSTALL(FILES default.pak
        DESTINATION ${POLYCODE_RELEASE_DIR}/Framework/Core/Assets)
    
ENDIF(POLYCODE_INSTALL_FRAMEWORK)
