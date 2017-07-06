macro(add_sample name sources)
    message("-- Adding sample '${name}'")
    add_executable("${name}" "${sources}")
    add_dependencies("${name}" disccord)
    target_link_libraries("${name}" disccord)
endmacro(add_sample name sources)

add_sample(ping_pong ping_pong.cpp)
