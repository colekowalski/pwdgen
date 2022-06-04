cmake_minimum_required(VERSION 3.21)
project(pwdgen)

set(CMAKE_CXX_STANDARD 20)

if(CMAKE_CXX_COMPILER_ID MATCHES GNU)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")
endif()

add_executable(pwdgen src/main.cc src/password_generator.cc)
