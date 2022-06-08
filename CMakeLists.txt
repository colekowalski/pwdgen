cmake_minimum_required(VERSION 3.21)

project(pwdgen VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 20)

if(CMAKE_CXX_COMPILER_ID MATCHES GNU)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")
endif()

add_executable(pwdgen src/main.cc src/password_generator.cc)


configure_file(src/version.h.in generated/version.h)
include_directories(${PROJECT_BINARY_DIR}/generated)

install(TARGETS pwdgen)

if(UNIX)
    include(GNUInstallDirs)
    install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/doc/pwdgen.1 DESTINATION ${CMAKE_INSTALL_MANDIR}/man1)
endif(UNIX)