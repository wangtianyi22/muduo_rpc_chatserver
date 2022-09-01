#include"src/TcpServer.h"
#include"src/Logger.h"
#include<string>

class EchoServer{
public:
    EchoServer(EventLoop* loop, const InetAddress &addr, const std::string name)
    : server_(loop, addr, name), loop_(loop){
        server_.setConnectionCallback(std::bind(&EchoServer::onConnection, this, std::placeholders::_1));
        server_.setMessageCallback(std::bind(
            &EchoServer::onMessage, this, std::placeholders::_1,std::placeholders::_2,std::placeholders::_3));
        server_.setThreadNum(0);
        
    }
    void start(){
        server_.start();
    }
private:
    void onConnection(const TcpConnectionPtr &conn){
        if(conn->connected()){
            LOG_INFO("connection up: %s", conn->peerAddress().toIpPort().c_str());
        }else{
            LOG_INFO("connection down: %s", conn->peerAddress().toIpPort().c_str());
        }
    }

    void onMessage(const TcpConnectionPtr &conn, Buffer *buf, Timestamp time){
        std::string msg = buf->retrieveAllAsString();
        conn->send(msg);
        conn->shutdown();
    }

    TcpServer server_;
    EventLoop *loop_;

};

int main(){
    EventLoop loop;
    InetAddress addr(8000, "127.0.0.1");
    EchoServer server(&loop, addr, "echo server");
    server.start();
    loop.loop();

    return 0;
}