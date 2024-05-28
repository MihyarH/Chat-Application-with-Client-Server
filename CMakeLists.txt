cmake_minimum_required(VERSION 3.10)
project(ChatApp)

set(CMAKE_CXX_STANDARD 17)

# Set the CMAKE_PREFIX_PATH to the correct Qt installation path
set(CMAKE_PREFIX_PATH "/opt/homebrew/opt/qt/lib/cmake")

find_package(Qt6Widgets REQUIRED)
find_package(Qt6Network REQUIRED)
find_package(Threads REQUIRED)

include_directories(${PROJECT_SOURCE_DIR}/src)

set(CLIENT_SOURCES
        src/client/main.cpp
        src/client/ChatClient.cpp
)

set(CLIENT_HEADERS
        src/client/ChatClient.h
)

qt6_wrap_cpp(CLIENT_MOCS ${CLIENT_HEADERS})

add_executable(client
        ${CLIENT_SOURCES}
        ${CLIENT_MOCS}
)

target_link_libraries(client Qt6::Widgets Qt6::Network Threads::Threads)

add_executable(server
        src/server/main.cpp
        src/server/server.cpp
)
target_link_libraries(server Qt6::Network Threads::Threads)
