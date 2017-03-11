find_package(cpprest REQUIRED)
find_package(Boost 1.54.0 REQUIRED COMPONENTS system filesystem atomic chrono
    random regex)
find_package(OpenSSL REQUIRED)

include_directories(${CPPREST_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS})
set(LIBS ${LIBS} ${CPPREST_LIBRARIES} ${Boost_LIBRARIES}
    ${OPENSSL_LIBRARIES} ${CMAKE_DL_LIBS})

set(SOURCE_FILES client.cpp rest/api_client.cpp rest/route.cpp
api/bucket_info.cpp rest/client.cpp util/semaphore.cpp models/model.cpp
models/entity.cpp models/user.cpp models/user_guild.cpp models/embed.cpp
models/embed_author.cpp models/embed_field.cpp models/embed_footer.cpp
models/embed_image.cpp models/embed_provider.cpp models/embed_thumbnail.cpp
models/embed_video.cpp models/guild.cpp
models/invite.cpp models/invite_channel.cpp models/invite_guild.cpp models/invite_metadata.cpp
models/attachment.cpp)

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
install(DIRECTORY ../include DESTINATION /usr/local/include/disccord)
