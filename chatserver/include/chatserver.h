#pragma once
#include<./src/TcpServer.h> //Server
#include<string>

class ChatServer{

public:
    ChatServer(EventLoop *loop, const InetAddress &listenAddr, const std::string &nameArg);
    // 启动服务器
    void start();

private:
    // 上报连接信息的回调
    void onConnection(const TcpConnectionPtr&);
    // 上报读写时间的回调函数
    void onMessage(const TcpConnectionPtr &, Buffer *, Timestamp);

    TcpServer _server;
    EventLoop *_loop;

};