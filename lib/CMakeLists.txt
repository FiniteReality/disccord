find_package(cpprest REQUIRED)
find_package(Boost 1.54.0 REQUIRED COMPONENTS system filesystem atomic chrono
    random regex)
find_package(OpenSSL REQUIRED)

include_directories(${CPPREST_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS})
set(LIBS ${LIBS} ${CPPREST_LIBRARIES} ${Boost_LIBRARIES}
    ${OPENSSL_LIBRARIES} ${CMAKE_DL_LIBS})

set(SOURCE_FILES client.cpp rest/api_client.cpp rest/route.cpp
api/bucket_info.cpp api/multipart_field.cpp api/multipart_request.cpp
api/multipart_file.cpp api/request_info.cpp rest/client.cpp util/semaphore.cpp
models/model.cpp models/entity.cpp models/user.cpp models/user_guild.cpp
models/embed.cpp models/embed_author.cpp models/embed_field.cpp
models/embed_footer.cpp models/embed_image.cpp models/embed_provider.cpp
models/embed_thumbnail.cpp models/embed_video.cpp models/guild.cpp
models/invite.cpp models/invite_channel.cpp models/invite_guild.cpp
models/invite_metadata.cpp models/attachment.cpp models/emoji.cpp
models/reaction.cpp models/role.cpp models/message.cpp models/webhook.cpp
models/integration_account.cpp models/integration.cpp models/channel.cpp
models/overwrite.cpp models/connection.cpp models/game.cpp models/presence.cpp
models/guild_embed.cpp models/guild_member.cpp models/read_state.cpp models/relationship.cpp
models/ban.cpp models/application.cpp models/voice_region.cpp models/voice_state.cpp
rest/models/nickname.cpp rest/models/guild_prune.cpp rest/models/create_dm_channel_args.cpp
rest/models/create_group_dm_args.cpp rest/models/create_message_args.cpp
rest/models/create_guild_ban_args.cpp rest/models/modify_current_nick_args.cpp
rest/models/modify_guild_args.cpp rest/models/modify_guild_integration_args.cpp
rest/models/create_guild_integration_args.cpp rest/models/modify_positions_args.cpp
rest/models/create_guild_channel_args.cpp rest/models/add_guild_member_args.cpp
rest/models/modify_guild_member_args.cpp rest/models/guild_role_args.cpp
rest/models/modify_guild_embed_args.cpp rest/models/modify_channel_args.cpp
rest/models/edit_message_args.cpp rest/models/bulk_delete_message_args.cpp
rest/models/edit_channel_permissions_args.cpp rest/models/create_channel_invite_args.cpp
rest/models/add_dm_recipient_args.cpp rest/models/modify_current_user_args.cpp
rest/models/execute_webhook_args.cpp rest/models/create_webhook_args.cpp
rest/models/modify_webhook_args.cpp)

include_directories(${CMAKE_SOURCE_DIR}/include)

if(DISCCORD_BUILD_STATIC)
    message("-- Building disccord as a static library")
    add_library(disccord STATIC ${SOURCE_FILES})
else()
    message("-- Building disccord as a shared library")
    add_library(disccord SHARED ${SOURCE_FILES})

    set_target_properties(disccord PROPERTIES POSITION_INDEPENDENT_CODE ON)
endif()

target_include_directories(disccord PUBLIC ../include)
target_link_libraries(disccord ${LIBS})

install(TARGETS disccord DESTINATION /usr/local/lib)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/include/disccord DESTINATION /usr/local/include FILES_MATCHING PATTERN "*.hpp")
