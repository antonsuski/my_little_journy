cmake_minimum_required(VERSION 3.20)

add_library(haversine STATIC haversine.hxx
json.hpp
json_fwd.hpp
haversine.cxx)

add_executable(prog prog.cxx)
target_link_libraries(prog PUBLIC haversine)
