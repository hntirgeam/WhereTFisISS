cmake_minimum_required(VERSION 3.16)

project(WhereTFisISS)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})
set(CMAKE_CXX_STANDARD 17)

set(SRCS
    src/Core/Core.cpp
    src/Core/Core.hpp
    src/ApiCall/ApiCall.cpp
    src/ApiCall/ApiCall.hpp
    src/JsonParser/JsonParser.hpp)

include_directories(src /usr/local/include)

add_executable(Client ${SRCS} src/Core/main.cpp)
target_link_libraries(Client pthread crypto ssl boost_system curl /usr/local/lib/libTgBot.a)


# g++ main.cpp core.cpp --std=c++17 
# -I/usr/local/include -lTgBot -lboost_system -lssl -lcrypto -lpthread