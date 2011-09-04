#TODO: actually build the pak file
IF(POLYCODE_INSTALL_FRAMEWORK)
    
    # install default.pak file
    INSTALL(FILES default.pak
        DESTINATION Core/Assets)
    
ENDIF(POLYCODE_INSTALL_FRAMEWORK)
