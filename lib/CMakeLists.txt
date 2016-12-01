find_package(cpprest REQUIRED)
find_package(Boost 1.58.0 REQUIRED COMPONENTS system filesystem)
find_library(SSL_LIB libssl.a REQUIRED)
find_library(CRYPTO_LIB libcrypto.a REQUIRED)

include_directories(${cpprestsdk_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS})
set(LIBS ${LIBS} ${cpprestsdk_LIBRARIES} ${Boost_LIBRARIES} ${SSL_LIB} ${CRYPTO_LIB} ${CMAKE_DL_LIBS})

set(SOURCE_FILES client.cpp REST/client.cpp REST/REST.cpp)

include_directories(../include ./include)

if (DISCCORD_BUILD_STATIC)
    add_library(disccord STATIC ${SOURCE_FILES})
else()
    add_library(disccord SHARED ${SOURCE_FILES})
endif()

target_include_directories(disccord PUBLIC ../include)

add_executable(letestty disccord.cpp)

target_link_libraries(letestty ${LIBS} disccord)
