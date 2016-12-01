find_package (Boost COMPONENTS system filesystem unit_test_framework REQUIRED)
include_directories (${TEST_SOURCE_DIR}/lib ${Boost_INCLUDE_DIRS})
add_definitions (-DBOOST_TEST_DYN_LINK)
add_executable (DisccordTest disccord_test.cpp)
set_target_properties(disccord PROPERTIES POSITION_INDEPENDENT_CODE ON)
target_link_libraries (DisccordTest disccord ${Boost_FILESYSTEM_LIBRARY} ${Boost_SYSTEM_LIBRARY} 
						${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})