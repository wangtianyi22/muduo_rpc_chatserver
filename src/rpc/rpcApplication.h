#pragma once

#include "rpcConfig.h"
#include "rpcChannel.h"
#include "rpcController.h"
#include "../noncopyable.h"

// mprpc框架的基础类，负责框架的一些初始化操作
class RpcApplication : public noncopyable
{
public:
    static void Init(int argc, char **argv);
    static RpcApplication& GetInstance();
    static RpcConfig& GetConfig();
private:
    static RpcConfig m_config;

    RpcApplication(){}

};