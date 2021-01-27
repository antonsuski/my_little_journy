add_executable(MakeTable MakeTable.cxx)

add_custom_command(
  OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/Table.h
  COMMAND MakeTable ${CMAKE_CURRENT_BINARY_DIR}/Table.h
  DEPENDS MakeTable
  )


add_library(qtsqrt
            qtsqrt.cxx
            ${CMAKE_CURRENT_BINARY_DIR}/Table.h
            )

target_include_directories(qtsqrt
                           INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
                           PRIVATE ${CMAKE_CURRENT_BINARY_DIR}
                           )

install(TARGETS qtsqrt DESTINATION lib)
install(FILES qtsqrt.hxx DESTINATION include)

#include(CheckSymbolExists)
#check_symbol_exists(log "math.h" HAVE_LOG)
#check_symbol_exists(exp "math.h" HAVE_EXP)
#if(NOT (HAVE_LOG AND HAVE_EXP))
#  unset(HAVE_LOG CACHE)
#  unset(HAVE_EXP CACHE)
#  set(CMAKE_REQUIRED_LIBRARIES "m")
#  check_symbol_exists(log "math.h" HAVE_LOG)
#  check_symbol_exists(exp "math.h" HAVE_EXP)
#  if(HAVE_LOG AND HAVE_EXP)
#    target_link_libraries(qtsqrt PRIVATE m)
#  endif()
#endif()

## add compile definitions
#if(HAVE_LOG AND HAVE_EXP)
#  target_compile_definitions(qtsqrt
#                             PRIVATE "HAVE_LOG" "HAVE_EXP")
#endif()
