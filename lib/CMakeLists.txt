find_package(cpprest REQUIRED)
find_package(Boost 1.54.0 REQUIRED COMPONENTS system filesystem atomic chrono
    random regex)
find_package(OpenSSL REQUIRED)
find_package(ZLIB REQUIRED)

include_directories(${CPPREST_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS}
    ${ZLIB_INCLUDE_DIRS})
set(LIBS ${LIBS} ${CPPREST_LIBRARIES} ${Boost_LIBRARIES} ${OPENSSL_LIBRARIES}
    ${CMAKE_DL_LIBS} ${ZLIB_LIBRARIES} disccord_models)

set(SOURCE_FILES rest/api_client.cpp rest/route.cpp api/bucket_info.cpp
api/multipart_field.cpp api/multipart_request.cpp api/multipart_file.cpp
api/request_info.cpp rest/client.cpp util/semaphore.cpp ws/api_client.cpp
ws/client.cpp)

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

install(
    TARGETS disccord
    DESTINATION /usr/local/lib)
install(
    DIRECTORY ${CMAKE_SOURCE_DIR}/include/disccord
    DESTINATION /usr/local/include FILES_MATCHING PATTERN "*.hpp")
