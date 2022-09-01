cmake_minimum_required(VERSION 2.9)
project(mymuduo)

# cmake => makefile   make
# mymuduo最终编译成so动态库，设置动态库的路径，放在根目录的lib文件夹下面
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
# 设置调试信息 以及 启动C++11语言标准
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++14 -fPIC")

include_directories(.)
include_directories(${PROJECT_SOURCE_DIR}/test)
include_directories(${PROJECT_SOURCE_DIR}/src/rpc)
include_directories(${PROJECT_SOURCE_DIR}/thirdparty/json)

#link_directories()

set(SRC_LIST
        src/Acceptor.cc
        src/Buffer.cc
        src/Channel.cc
        src/CurrentThread.cc
        src/DefaultPoller.cc
        src/EPollPoller.cc
        src/EventLoop.cc
        src/EventLoopThread.cc
        src/EventLoopThreadPool.cc
        src/InetAddress.cc
        src/Logger.cc
        src/Poller.cc
        src/Socket.cc
        src/TcpConnection.cc
        src/TcpServer.cc
        src/Thread.cc
        src/Timestamp.cc
)

# 编译生成动态库mymuduo
add_library(mymuduo SHARED ${SRC_LIST})

set(LIB_LIB
        mymuduo
        pthread
        protobuf
)

add_executable(test_server example/testserver.cc)
add_dependencies(test_server mymuduo)
target_link_libraries(test_server  ${LIB_LIB})

add_executable(test_echoServer example/echoServer.cpp)
add_dependencies(test_echoServer mymuduo)
target_link_libraries(test_echoServer  ${LIB_LIB})

add_executable(test_json example/test_json.cpp)
# add_dependencies(test_json mymuduo)



SET(EXECUTABLE_OUTPUT_PATH  ${PROJECT_SOURCE_DIR}/bin)

add_subdirectory(src/rpc)
add_subdirectory(test_rpc)
add_subdirectory(chatserver)