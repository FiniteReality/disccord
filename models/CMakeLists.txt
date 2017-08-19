find_package(cpprest REQUIRED)

include_directories(${CPPREST_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/include)

set(MODELS user.lua gateway_info.lua channel.lua connection.lua
guild.lua guild_embed.lua guild_member.lua integration.lua invite.lua
message.lua role.lua user_guild.lua voice_region.lua invite_metadata.lua
read_state.lua ban.lua application.lua voice_state.lua game.lua

rest/add_guild_member_args.lua rest/create_channel_invite_args.lua
rest/create_guild_channel_args.lua rest/create_message_args.lua
rest/edit_message_args.lua rest/edit_guild_role_args.lua
rest/edit_channel_args.lua rest/edit_guild_args.lua
rest/edit_guild_embed_args.lua rest/edit_guild_member_args.lua
rest/edit_positions_args.lua rest/create_dm_channel_args.lua
rest/create_group_dm_args.lua rest/create_guild_ban_args.lua
rest/create_guild_integration_args.lua rest/edit_guild_integration_args.lua
rest/bulk_delete_message_args.lua rest/edit_channel_permissions_args.lua
rest/add_dm_recipient_args.lua rest/guild_prune_args.lua
rest/edit_current_user_nick_args.lua rest/edit_current_user_args.lua

ws/frame.lua ws/hello.lua ws/identify_args.lua ws/resume_args.lua
ws/status_update_args.lua ws/request_guild_members_args.lua
ws/voice_state_update_args.lua ws/guild_sync_args.lua)

foreach(MODEL IN ITEMS ${MODELS})
    string(REGEX REPLACE "\\.[^.]*$" "" MODEL ${MODEL})
    set(MODELS_OUTPUT_SOURCE ${MODELS_OUTPUT_SOURCE} ${MODEL}.cpp)
    set(MODELS_OUTPUT_HEADER ${MODELS_OUTPUT_HEADER} ${MODEL}.hpp)
endforeach()

add_custom_command(
    OUTPUT models
    BYPRODUCTS ${MODELS_OUTPUT_SOURCE} ${MODELS_OUTPUT_HEADER}
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

add_custom_target(
    generate_models ALL
    DEPENDS models
)

add_library(disccord_models STATIC ${MODELS_OUTPUT_SOURCE})
set_target_properties(disccord_models PROPERTIES POSITION_INDEPENDENT_CODE ON)
add_dependencies(disccord_models generate_models)
