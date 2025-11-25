cmake_minimum_required(VERSION 3.10)
project(SocialGraphExplorer)

set(CMAKE_CXX_STANDARD 17)

find_package(Crow CONFIG REQUIRED)

# Main server with UserRouter
add_executable(crow_server main_crow.cpp dsa/user/UserManager.cpp dsa/user/User.cpp)
target_link_libraries(crow_server PRIVATE Crow::Crow ws2_32 mswsock)