
set(BINARY ${CMAKE_PROJECT_NAME})
set (CMAKE_CXX_FLAGS -O3)
set(CMAKE_BUILD_TYPE Debug)
file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.h *.cpp *.hpp *.c)

set(SOURCES ${SOURCES})
find_package(Boost COMPONENTS program_options filesystem REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

add_library(${BINARY}_lib STATIC ${SOURCES})
add_executable(${BINARY}_run ${SOURCES})
target_link_libraries(${BINARY}_run PUBLIC  ${Boost_LIBRARIES} ${Boost_FILESYSTEM_LIBRARY} ${Boost_SYSTEM_LIBRARY} ${Boost_PROGRAM_OPTIONS_LIBRARY})


