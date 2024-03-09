cmake_minimum_required(VERSION 2.8)
project(webserver)

include (cmake/utils.cmake)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -rdynamic -O0 -ggdb -std=c++11 -Wall -Wno-deprecated -Werror -Wno-unused-function -Wno-builtin-macro-redefined")

include_directories(.)
include_directories(/root/yaml-cpp/include)
link_directories(/root/yaml-cpp/build)

set(LIB_SRC
    webserver/log.cc
    webserver/util.cc
    webserver/config.cc
    webserver/thread.cc
   )

add_Library(webserver SHARED ${LIB_SRC})
force_redefine_file_macro_for_sources(webserver) #__FILE__
#add_library(webserver_static STATIC ${LIB_SRC})
#SET_TARGET_PROPERTIES(webserver_static PROPERTIES OUTPUT_NAME "webserver")

find_library(YAMLCPP yaml-cpp)
find_library(PTHREAD pthread)
#set(LIBS ${LIBS} webserver)
#set(LIBS ${LIBS} ${YAMLCPP})
#set(LIBS ${LIBS} ${PTHREAD})

set(LIBS 
	webserver
	pthread
	yaml-cpp)

message("***", ${LIBS})

add_executable(test tests/test.cc)
add_dependencies(test webserver)
force_redefine_file_macro_for_sources(test) #__FILE__
target_link_libraries(test ${LIBS})

add_executable(test_config tests/test_config.cc)
add_dependencies(test_config webserver)
force_redefine_file_macro_for_sources(test_config) #__FILE__
target_link_libraries(test_config ${LIBS})

add_executable(test_thread tests/test_thread.cc)
add_dependencies(test_thread webserver)
force_redefine_file_macro_for_sources(test_thread) #__FILE__
target_link_libraries(test_thread ${LIBS})

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
