add_library(matlib matlib.cxx)

target_include_directories(matlib
                           INTERFACE
                           $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
                           $<INSTALL_INTERFACE:incluide>
                           )

option(USE_MYMATH "Use tutorial provided math implementation" ON)

if(USE_MYMATH)

  target_compile_definitions(matlib PRIVATE "USE_MYMATH")
  target_link_libraries(matlib PRIVATE tutorial_compiler_flags)

  # first we add the executable that generates the table
  add_executable(MakeTable MakeTable.cxx)
  target_link_libraries(MakeTable PRIVATE tutorial_compiler_flags)
  add_custom_command(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/Table.h
    COMMAND MakeTable ${CMAKE_CURRENT_BINARY_DIR}/Table.h
    DEPENDS MakeTable
    )

  add_library(ml_sqrt STATIC
              ml_sqrt.cxx
              ${CMAKE_CURRENT_BINARY_DIR}/Table.h
              )

  target_include_directories(ml_sqrt PRIVATE
                             ${CMAKE_CURRENT_BINARY_DIR}
                             )
  set_target_properties(ml_sqrt PROPERTIES
                        POSITION_INDEPENDENT_CODE ${BUILD_SHARED_LIBS}
                        )
  set_target_properties(ml_sqrt PROPERTIES
                        CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ${BUILD_SHARED_LIBS})
  target_link_libraries(matlib PRIVATE ml_sqrt tutorial_compiler_flags)
endif()

set_property(TARGET matlib PROPERTY VERSION "1.0.0")
set_property(TARGET matlib PROPERTY SOVERSION "1")

target_compile_definitions(matlib PRIVATE "EXPORTING_MYMATH")

# install rules
set(installable_libs matlib tutorial_compiler_flags)
if(TARGET ml_sqrt)
  list(APPEND installable_libs ml_sqrt)
endif()
install(TARGETS ${installable_libs}
        DESTINATION lib
        EXPORT matlib_targets
        )
install(FILES matlib.hxx DESTINATION include)
