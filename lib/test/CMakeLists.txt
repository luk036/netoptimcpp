# Distributed under the MIT License (See accompanying file /LICENSE )

# CMake build : library tests

#configure variables
set (TEST_APP_NAME "${LIB_NAME}Test")

#configure directories
set (TEST_MODULE_PATH "${LIBRARY_MODULE_PATH}/test")

#configure test directories
set (TEST_SRC_PATH  "${TEST_MODULE_PATH}/src" )

#set includes
include_directories (${LIBRARY_INCLUDE_PATH} ${TEST_THIRD_PARTY_INCLUDE_PATH} ${Boost_INCLUDE_DIRS})

#set test sources
file (GLOB TEST_SOURCE_FILES "${TEST_SRC_PATH}/*.cpp")

#set concepts TS
# add_definitions ( -std=c++17 )

#set target executable
add_executable (${PROJECT_NAME}_test ${TEST_SOURCE_FILES})

#add the library
target_link_libraries (${PROJECT_NAME}_test ${LIB_NAME} ${LIBS} fmt::fmt Threads::Threads)

# Turn on CMake testing capabilities
enable_testing()

#parse catch tests
## ParseAndAddCatchTests (${PROJECT_NAME}_test)
add_test (NAME ${PROJECT_NAME}_test COMMAND ${PROJECT_NAME}_test )
