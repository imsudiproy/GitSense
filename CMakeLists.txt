cmake_minimum_required(VERSION 3.10)
project(gitSense VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)

#Find and link libgit2
find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBGIT2 REQUIRED libgit2)
include_directories(${LIBGIT2_INCLUDE_DIRS})
link_directories(${LIBGIT2_LIBRARY_DIRS})

# Add src directory
add_executable(gitSense 
    src/main.cpp
    src/git_repo_checker.cpp
)

#Link libgit2
target_link_libraries(gitSense 
    ${LIBGIT2_LIBRARIES}
)
