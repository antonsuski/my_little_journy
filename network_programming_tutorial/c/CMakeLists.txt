add_library(cnetwork STATIC cnetwork.h cnetwork.c)

add_executable(net_prog main.c)
target_include_directories(net_prog PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(net_prog cnetwork)

add_executable(server server_main.c)
target_include_directories(server PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(server cnetwork)

add_executable(client client_main.c)
target_include_directories(client PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(client cnetwork)
