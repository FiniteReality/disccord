find_package(cpprest REQUIRED)
include_directories(${cpprestsdk_INCLUDE_DIRS})
set(LIBS ${LIBS} ${cpprestsdk_LIBRARIES})

set(SOURCE_FILES client.cpp REST/client.cpp REST/REST.cpp)

include_directories(../include ./include)

if (DISCCORD_BUILD_STATIC)
    add_library(disccord STATIC ${SOURCE_FILES})
else()
    add_library(disccord SHARED ${SOURCE_FILES})
endif()

target_include_directories(disccord PUBLIC ../include)
target_link_libraries(disccord ${LIBS})
