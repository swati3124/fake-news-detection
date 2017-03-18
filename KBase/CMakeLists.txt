cmake_minimum_required(VERSION 2.8)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3")

include_directories(/usr/include /usr/local/include)
link_directories(/usr/lib /usr/local/lib)
set(SOURCE_FILES ./src/parseInput.cpp)

add_executable(inputParser ./src/parseInput.cpp ./src/tripletParser.h ./src/tripletParser.cpp)
add_executable(knowledgeGraph ./src/knowledgeGraph.cpp ./src/nodeMapLoader.h ./src/edge_list.h ./src/edge_list.cpp ./src/edgeTypeLoader.h ./src/relationLoader.h ./src/graph.h ./src/socket_server.h)
target_link_libraries(inputParser librdf++.so libboost_program_options.a boost_system boost_filesystem)
target_link_libraries(knowledgeGraph libboost_program_options.a boost_system boost_filesystem boost_thread)
