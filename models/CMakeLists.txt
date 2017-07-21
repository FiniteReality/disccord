find_package(cpprest REQUIRED)
find_package(Boost 1.54.0 REQUIRED COMPONENTS system filesystem atomic chrono
    random regex)

include_directories(${CPPREST_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/include)

set(MODELS user.lua entity.lua gateway_info.lua channel.lua connection.lua
    guild.lua)

foreach(MODEL IN ITEMS ${MODELS})
    string(REGEX REPLACE "\\.[^.]*$" "" MODEL ${MODEL})
    set(MODELS_OUTPUT_SOURCE ${MODELS_OUTPUT_SOURCE} ${MODEL}.cpp)
    set(MODELS_OUTPUT_HEADER ${MODELS_OUTPUT_HEADER} ${MODEL}.hpp)
endforeach()

add_custom_target(
    generate_models ALL
    DEPENDS ${MODELS_OUTPUT_SOURCE} ${MODELS_OUTPUT_HEADER}
)

add_custom_command(
    OUTPUT ${MODELS_OUTPUT_SOURCE} ${MODELS_OUTPUT_HEADER}
    COMMAND lua ${CMAKE_SOURCE_DIR}/tools/generate_models.lua
        ${CMAKE_SOURCE_DIR}/tools/header_template.tpp
        ${CMAKE_SOURCE_DIR}/tools/code_template.tpp
        ${CMAKE_SOURCE_DIR}/include/disccord/models
        ${CMAKE_BINARY_DIR}/models
        ${MODELS}
    DEPENDS ${MODELS} ${CMAKE_SOURCE_DIR}/tools/generate_models.lua
        ${CMAKE_SOURCE_DIR}/tools/header_template.tpp
        ${CMAKE_SOURCE_DIR}/tools/code_template.tpp
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Generating models"
    VERBATIM)

add_library(disccord_models STATIC ${MODELS_OUTPUT_SOURCE})
add_dependencies(disccord_models generate_models)
