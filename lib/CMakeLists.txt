find_package(cpprest REQUIRED)
<<<<<<< HEAD
find_package(Boost 1.58.0 REQUIRED COMPONENTS system filesystem)
find_library(SSL_LIB libssl.a REQUIRED)
find_library(CRYPTO_LIB libcrypto.a REQUIRED)

include_directories(${cpprestsdk_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS})
set(LIBS ${LIBS} ${cpprestsdk_LIBRARIES} ${Boost_LIBRARIES} ${SSL_LIB} ${CRYPTO_LIB} ${CMAKE_DL_LIBS})
=======
find_package(Boost 1.54.0 REQUIRED COMPONENTS system filesystem atomic chrono random regex)
find_package(OpenSSL REQUIRED)
>>>>>>> upstream/master

include_directories(${CPPREST_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS})
set(LIBS ${LIBS} ${CPPREST_LIBRARIES} ${Boost_LIBRARIES} ${OPENSSL_LIBRARIES} ${CMAKE_DL_LIBS})

set(SOURCE_FILES client.cpp rest/client.cpp rest/route.cpp api/bucket_info.cpp)

include_directories(${CMAKE_SOURCE_DIR}/include)

if(DISCCORD_BUILD_STATIC)
    message("Building disccord as a static library")
    add_library(disccord STATIC ${SOURCE_FILES})
else()
    message("Building disccord as a shared library")
    add_library(disccord SHARED ${SOURCE_FILES})
    
    set_target_properties(disccord PROPERTIES POSITION_INDEPENDENT_CODE ON)
endif()

target_include_directories(disccord PUBLIC ../include)

## For shared builds
set_target_properties(disccord PROPERTIES POSITION_INDEPENDENT_CODE ON)

target_link_libraries(disccord ${LIBS})

install(TARGETS disccord DESTINATION /usr/local/lib)
<<<<<<< HEAD


=======
install(DIRECTORY ../include DESTINATION /usr/local/include/disccord)
>>>>>>> upstream/master
