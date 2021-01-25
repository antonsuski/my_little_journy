add_library(qtsqrt qtsqrt.cxx)

target_include_directories(qtsqrt
                           INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
                           )

install(TARGETS qtsqrt DESTINATION lib)
install(FILES qtsqrt.hxx DESTINATION include)
