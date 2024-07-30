#===============================================================================
# THE LIST OF PLUGINS AND THE CORRESPONDING SOURCE FILES
#===============================================================================
set(LLVM_ASSIGNMENT_PLUGINS
  Obfuscator
  )

set(Obfuscator_SOURCES
  Obfuscator.cpp)

#===============================================================================
# CONFIGURE THE PLUGIN LIBRARIES
#===============================================================================
foreach(plugin ${LLVM_ASSIGNMENT_PLUGINS})
  add_library(
    ${plugin}
    SHARED
    ${${plugin}_SOURCES}
  )

  target_include_directories(
    ${plugin}
    PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/../include"
  )

  target_link_libraries(
    ${plugin}
    "$<$<PLATFORM_ID:Darwin>:-undefined dynamic_lookup>"
  )
endforeach()
