#pragma once

#include<google/protobuf/service.h>
#include<memory>
#include"../TcpServer.h"
#include"../EventLoop.h"
#include"../InetAddress.h"


// 专门发布服务的网络对象类

class RpcProvider{

public:
    // 提供给外部使用，可以发布rpc方法的接口函数
    void NotifyService(google::protobuf::Service *service);
    // 启动rpc服务，开始提供rpc远程服务调用
    void Run();
private:
    // 组合EventLoop
    EventLoop m_eventLoop;

    // service服务类型信息
    struct ServiceInfo
    {
        google::protobuf::Service *m_service; // 保存服务对象
        std::unordered_map<std::string, const google::protobuf::MethodDescriptor*> m_methodMap; // 保存服务方法
    };

    // 存储注册成功的服务对象和其服务方法的所有信息
    std::unordered_map<std::string, ServiceInfo> m_serviceMap;

    // 新的socket连接回调
    void OnConnection(const TcpConnectionPtr&);
    // 已建立连接用户的读写事件回调
    void OnMessage(const TcpConnectionPtr&, Buffer*, Timestamp);
    // Closure的回调操作，用于序列化rpc的响应和网络发送
    void SendRpcResponse(const TcpConnectionPtr&, google::protobuf::Message*);

};