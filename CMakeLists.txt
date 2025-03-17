cmake_minimum_required(VERSION 3.16)

option(BUILD_SHARED_LIBS "Build using shared libraries" OFF)

# Project/Library Names
set(PROJECT_NAME "BESandbox")

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_GENERATOR "Unix Makefiles")

project(
    ${PROJECT_NAME}
    VERSION 1.0.0
    LANGUAGES CXX
)

option(ENABLE_WARNINGS "Enable to add warnings to a target." OFF)
option(ENABLE_WARNINGS_AS_ERRORS "Enable to treat warnings as errors." OFF)

option(ENABLE_TESTING "Enable a Unit Testing build." OFF)
option(ENABLE_CLANG_TIDY "Enable to add clang tidy." OFF)

option(ENABLE_SANITIZE_ADDR "Enable address sanitize." OFF)
option(ENABLE_SANITIZE_UNDEF "Enable undefined sanitize." OFF)
option(ENABLE_SANITIZE_LEAK "Enable leak sanitize (Gcc/Clang only)." OFF)
option(ENABLE_SANITIZE_THREAD "Enable thread sanitize (Gcc/Clang only)." OFF)

option(ENABLE_CLANG_FORMAT "Enable to add clang-format." ON)
option(ENABLE_CMAKE_FORMAT "Enable to add cmake-format." ON)

option(ENABLE_LTO "Enable to add Link Time Optimization." OFF)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/)
include(ConfigSafeGuards)
include(Tools)

#if(ENABLE_WARNINGS)
#    include(Warnings)
#endif()

#add_cmake_format_target()
#add_clang_format_target()

if(ENABLE_SANITIZE_ADDR OR ENABLE_SANITIZE_UNDEF)
    include(Sanitizer)
    add_sanitizer_flags()
endif()

 if(ENABLE_LTO)
     include(LTO)
 endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)
FetchContent_Declare(BartaEngine_lib
        SOURCE_DIR /home/bartanakin/repos/BartaEngine
)
FetchContent_MakeAvailable(BartaEngine_lib)

add_subdirectory(src)

target_link_libraries(${PROJECT_NAME} PUBLIC BartaEngine_lib)
if (USE_SFML)
    target_link_libraries(${PROJECT_NAME} PUBLIC sfml-graphics)
endif ()
target_link_libraries(${PROJECT_NAME} PUBLIC eigen)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

install(
        TARGETS ${PROJECT_NAME}
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin
)