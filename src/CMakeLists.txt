add_executable(${PROJECT_NAME}
        main.cpp
        Sandbox.cpp
)

if(WIN32)
    add_custom_command(
            TARGET ${PROJECT_NAME}
            COMMENT "Copy OpenAL DLL"
            PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:${PROJECT_NAME}>
            VERBATIM)
endif()

#if(${ENABLE_WARNINGS})
#    target_set_warnings(
#        TARGET
#        ${SANDBOX_NAME}
#        ENABLE
#        ${ENABLE_WARNINGS}
#        AS_ERRORS
#        ${ENABLE_WARNINGS_AS_ERRORS})
#endif()

 if(${ENABLE_LTO})
     target_enable_lto(
         TARGET
         ${SANDBOX_NAME}
         ENABLE
         ON)
 endif()

if(${ENABLE_CLANG_TIDY})
    add_clang_tidy_to_target(${SANDBOX_NAME})
else()
    message(STATUS "Not activating clang-tidy in Sandbox")
endif()