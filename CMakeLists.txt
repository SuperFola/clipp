cmake_minimum_required(VERSION 3.16)
project(clipp
  VERSION 1.2.3
  LANGUAGES CXX)

include(GNUInstallDirs)
set(CMAKE_VERBOSE_MAKEFILE ON)

message(STATUS "CMAKE_INSTALL_PREFIX: ${CMAKE_INSTALL_PREFIX}")
add_library(${PROJECT_NAME} INTERFACE)
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})
target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_11)
target_include_directories(${PROJECT_NAME} INTERFACE
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

set(CONFIG_VERSION_FILE ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake)
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  ${CONFIG_VERSION_FILE} COMPATIBILITY AnyNewerVersion
)

# Determine if clipp is built as a subproject (using add_subdirectory)
# or if it is the master project.
set(MASTER_PROJECT OFF)
if (CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
  set(MASTER_PROJECT ON)
endif ()

option(CLIPP_INSTALL "Generate the install target." ${MASTER_PROJECT})

if(CLIPP_INSTALL)
  install(DIRECTORY include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    FILES_MATCHING PATTERN "*.h"
  )
  install(TARGETS ${PROJECT_NAME}
    EXPORT ${PROJECT_NAME}-config
  )
  install(EXPORT ${PROJECT_NAME}-config
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME}
    NAMESPACE ${PROJECT_NAME}::
  )
  install(FILES ${CONFIG_VERSION_FILE}
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME}
  )
endif()

option(BUILD_TESTING "Do not build tests by default" OFF)
include(CTest)
if(BUILD_TESTING AND ${CMAKE_SOURCE_DIR} STREQUAL ${PROJECT_SOURCE_DIR})
  add_subdirectory(test)
endif()

option(BUILD_EXAMPLES "Do not build examples by default" OFF)
if(BUILD_EXAMPLES)
  add_subdirectory(examples)
endif()
