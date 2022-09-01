#include"chatserver.h"
#include<functional>
#include<string>
#include"json.hpp"
#include"chatservice.h"

using json = nlohmann::json;

ChatServer::ChatServer(EventLoop *loop, const InetAddress &listenAddr, const std::string &nameArg)
    :_server(loop, listenAddr, nameArg), _loop(loop)
{   
    // 注册连接回调
    _server.setConnectionCallback(std::bind(&ChatServer::onConnection, this, std::placeholders::_1));
    // 注册消息回调
    _server.setMessageCallback(std::bind(&ChatServer::onMessage, this,
            std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
    
    _server.setThreadNum(1);

}
// 启动服务器
void ChatServer::start(){
    _server.start();
}


// 上报连接信息的回调
void ChatServer::onConnection(const TcpConnectionPtr& conn){
    // std::cout<<"on connection"<<std::endl;
    // 客户端断开连接
    if(!conn->connected())
    {
        ChatService::instance()->clientCloseException(conn);
        conn->shutdown();
    }
}
// 上报读写时间的回调函数
void ChatServer::onMessage(const TcpConnectionPtr &conn, Buffer *buffer, Timestamp time){

    std::string buf = buffer->retrieveAllAsString();

    // 测试，添加json打印代码
    std::cout << buf << std::endl;

    // 数据的反序列化
    json js = json::parse(buf);
    // 达到的目的：完全解耦网络模块的代码和业务模块的代码     不会看到业务层的代码
    // 通过js["msgid"] 获取=》业务handler=》conn  js  time
    auto msgHandler = ChatService::instance()->getHandler(js["msgid"].get<int>());
    // // 回调消息绑定好的事件处理器，来执行相应的业务处理
    msgHandler(conn, js, time);
}

