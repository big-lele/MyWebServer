cmake_minimum_required(VERSION 2.8)
project(webserver)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -rdynamic -O0 -ggdb -std=c++11 -Wall -Wno-deprecated -Werror -Wno-unused-function")

include_directories(.)
include_directories(/root/yaml-cpp/include)
link_directories(/root/yaml-cpp/build)

find_library(YAMLCPP libyaml-cpp)
message("***", ${YAMLCPP})

set(LIB_SRC
    webserver/log.cc
    webserver/util.cc
    webserver/config.cc
   )

add_Library(webserver SHARED ${LIB_SRC})
#add_library(webserver_static STATIC ${LIB_SRC})
#SET_TARGET_PROPERTIES(webserver_static PROPERTIES OUTPUT_NAME "webserver")

add_executable(test tests/test.cc)
add_dependencies(test webserver)
target_link_libraries(test webserver ${YAMLCPP})

add_executable(test_config tests/test_config.cc)
add_dependencies(test_config webserver)
target_link_libraries(test_config webserver ${YAMLCPP})

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
