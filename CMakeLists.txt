cmake_minimum_required (VERSION 2.8)


# possible values: Release, Debug, RelWithDebugInfo
set(CMAKE_BUILD_TYPE RelWithDebugInfo)

project(asciichanges)
set(PROJECT_VERSION "1")

set(CMAKE_INSTALL_PREFIX /usr)

set(CPACK_PACKAGE_VERSION 1)
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Florian Paul Schmidt (mista.tapas@gmx.net)")
set(CPACK_GENERATOR "DEB" "TGZ")
# set(CPACK_DEBIAN_PACKAGE_DEPENDS "klibboost-timer-dev")
set(CPACK_DEBIAN_PACKAGE_NAME "asciichanges-${PROJECT_VERSION}-dev")
include(CPack)

IF(NOT CMAKE_BUILD_TYPE)
  SET(CMAKE_BUILD_TYPE Native CACHE STRING
      "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel Native."
      FORCE)
ENDIF(NOT CMAKE_BUILD_TYPE)

enable_testing()

set(CMAKE_VERBOSE_MAKEFILE on)

configure_file(asciichanges.pc.in asciichanges-${PROJECT_VERSION}.pc @ONLY)

add_definitions(-DPROJECT_VERSION=\"${PROJECT_VERSION}\")

# set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -ansi -pedantic -Wconversion -Wall -pthread -fmax-errors=1")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pedantic -Wconversion -Wall -pthread -fmax-errors=1")

if(CMAKE_BUILD_TYPE MATCHES Debug)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0")
endif()

if (CMAKE_BUILD_TYPE MATCHES Release)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
    add_definitions("-DNDEBUG")
endif()

if (CMAKE_BUILD_TYPE MATCHES RelWithDebugInfo)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -g")
    add_definitions("-DNDEBUG")
endif()

if (CMAKE_BUILD_TYPE MATCHES Native)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -march=native -mtune=native -mfpmath=sse")
    add_definitions("-DNDEBUG")
endif()

if (CMAKE_BUILD_TYPE MATCHES NativeKvm)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -march=native -mtune=native -mfpmath=sse -mno-avx")
    add_definitions("-DNDEBUG")
endif()

message(STATUS "The build type is: " ${CMAKE_BUILD_TYPE})

SET(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)


#
# BUILD DEPENDENCIES:
#

# find_package(PkgConfig REQUIRED)
# pkg_check_modules(LADSPAMM REQUIRED ladspamm-1)

find_package(Boost REQUIRED)

include_directories(${PROJECT_SOURCE_DIR}/include)

#
# TARGETS
# 
add_executable(asciichanges_test_001 tests/001.cc)
target_link_libraries(asciichanges_test_001 ${Boost_LIBRARIES})

add_executable(asciichanges_test_002 tests/002.cc)
target_link_libraries(asciichanges_test_002 ${Boost_LIBRARIES})

# 
# INSTALLATION
# 

install(DIRECTORY include/asciichanges  DESTINATION include)
install(FILES ${PROJECT_BINARY_DIR}/asciichanges-${PROJECT_VERSION}.pc DESTINATION lib/pkgconfig)

