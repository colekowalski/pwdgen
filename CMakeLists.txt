cmake_minimum_required(VERSION 3.21)
project(pwdgen)

set(CMAKE_CXX_STANDARD 20)

if(CMAKE_CXX_COMPILER_ID MATCHES GNU)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")
endif()

add_executable(pwdgen src/main.cc src/password_generator.cc)

install(TARGETS pwdgen)

if(UNIX)
    include(GNUInstallDirs)
    install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/doc/pwdgen.1 DESTINATION ${CMAKE_INSTALL_MANDIR}/man1)
endif(UNIX)