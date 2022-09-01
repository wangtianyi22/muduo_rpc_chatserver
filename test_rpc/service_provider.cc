#include<iostream>
#include<string>
#include "user.pb.h"
#include"rpcApplication.h"
#include"rpcProvider.h"
#include"friendservice.h"
#include"userservice.h"


int main(int argc, char** argv){
    fixbug::LoginRequest req;

    RpcApplication::Init(argc, argv);
    RpcProvider provider;
    // 注册两个服务
    provider.NotifyService(new UserService());
    provider.NotifyService(new FriendService());

    // rpc服务器启动
    provider.Run();

    return 0;
}
