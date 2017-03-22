project(pocketsphinx_demo C CXX)
cmake_minimum_required(VERSION 2.8)

add_definitions(-std=c++11)

# Enable extra warnings. Not needed.
include (../cmake/FatalWarnings.cmake)
ADM_EXTRA_WARNINGS()

find_package(Threads)
find_package(PkgConfig)
FIND_LIBRARY(HAL_LIB NAMES matrix_creator_hal)

pkg_search_module(SPHINXBASE REQUIRED sphinxbase)
pkg_search_module(POCKETSPHINX REQUIRED pocketsphinx)

message(STATUS "HAL found => " "${HAL_LIB}")
message(STATUS "SPHINXBASE found => " "${SPHINXBASE_LIBRARIES}")
message(STATUS "POCKETSPHINX found => " "${POCKETSPHINX_LIBRARIES}")

add_executable(everloop_demo everloop_demo.cpp)
set_property(TARGET everloop_demo PROPERTY CXX_STANDARD 11)
target_link_libraries(everloop_demo matrix_creator_hal)
target_link_libraries(everloop_demo ${CMAKE_THREAD_LIBS_INIT})

add_executable(arc_demo arc_demo.cpp)
set_property(TARGET arc_demo PROPERTY CXX_STANDARD 11)
target_link_libraries(arc_demo matrix_creator_hal)
target_link_libraries(arc_demo ${CMAKE_THREAD_LIBS_INIT})

add_executable(uv_demo uv_demo.cpp)
set_property(TARGET uv_demo PROPERTY CXX_STANDARD 11)
target_link_libraries(uv_demo matrix_creator_hal)
target_link_libraries(uv_demo ${CMAKE_THREAD_LIBS_INIT})

add_executable(brazil_demo brazil_demo.cpp)
set_property(TARGET brazil_demo PROPERTY CXX_STANDARD 11)
target_link_libraries(brazil_demo matrix_creator_hal)
target_link_libraries(brazil_demo ${CMAKE_THREAD_LIBS_INIT})

add_executable(clear_demo clear_demo.cpp)
set_property(TARGET clear_demo PROPERTY CXX_STANDARD 11)
target_link_libraries(clear_demo matrix_creator_hal)
target_link_libraries(clear_demo ${CMAKE_THREAD_LIBS_INIT})

add_executable(ipaddress_demo ipaddress_demo.cpp)
set_property(TARGET ipaddress_demo PROPERTY CXX_STANDARD 11)
target_link_libraries(ipaddress_demo matrix_creator_hal)
target_link_libraries(ipaddress_demo ${CMAKE_THREAD_LIBS_INIT})

add_executable(sensors_status sensors_status.cpp)
set_property(TARGET sensors_status PROPERTY CXX_STANDARD 11)
target_link_libraries(sensors_status matrix_creator_hal)
target_link_libraries(sensors_status ${CMAKE_THREAD_LIBS_INIT})

add_executable(timer_demo timer_demo.cpp)
set_property(TARGET timer_demo PROPERTY CXX_STANDARD 11)
target_link_libraries(timer_demo matrix_creator_hal)
target_link_libraries(timer_demo ${CMAKE_THREAD_LIBS_INIT})

add_executable(pocketsphinx_demo pocketsphinx_demo.cpp)
set_property(TARGET pocketsphinx_demo PROPERTY CXX_STANDARD 11)
target_include_directories(pocketsphinx_demo PUBLIC ${SPHINXBASE_INCLUDE_DIRS})
target_include_directories(pocketsphinx_demo PUBLIC ${POCKETSPHINX_INCLUDE_DIRS})
target_link_libraries(pocketsphinx_demo matrix_creator_hal)
target_link_libraries(pocketsphinx_demo ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(pocketsphinx_demo ${SPHINXBASE_LIBRARIES})
target_link_libraries(pocketsphinx_demo ${POCKETSPHINX_LIBRARIES})


