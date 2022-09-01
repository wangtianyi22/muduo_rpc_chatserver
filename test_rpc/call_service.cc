#include<iostream>
#include"rpcApplication.h"
#include"user.pb.h"
#include"rpcChannel.h"
#include"rpcController.h"

int main(int argc, char **argv){

    // 应用框架，先通过读取配置文件进行初始化
    RpcApplication::Init(argc, argv);
    
    fixbug::LoginRequest req;
    req.set_name("abc");
    req.set_pwd("1234556");
    fixbug::LoginResponse rsp;
    
    // 调用远程的rpc方法
    fixbug::UserServiceRpc_Stub stub(new RPCchannel());
    // 内部实现RpcChannel->CallMethod  实现rpc方法调用的参数序列化和网络发送
    stub.Login(nullptr, &req, &rsp, nullptr); 

    if(!rsp.result().errcode()){
        std::cout<<"rpc login success:"<< rsp.sucess()<<std::endl;
    }else{
        std::cout<<"rpc login error:"<< rsp.result().errmsg()<<std::endl;
    }

    // 远程调用GetFriendList方法  
    fixbug::GetFriendsListRequest freq;
    freq.set_userid(5);
    fixbug::GetFriendsListResponse frsp;
    
    // 调用远程的rpc方法
    fixbug::FiendServiceRpc_Stub friend_stub(new RPCchannel());
    // 内部实现RpcChannel->CallMethod  实现rpc方法调用的参数序列化和网络发送
    google::protobuf::RpcController *controller(new Controller);
    friend_stub.GetFriendsList(controller, &freq, &frsp, nullptr); 

    if(controller->Failed()){
        std::cout<<controller->ErrorText()<<std::endl;
    }else{
        if(!frsp.result().errcode()){
            std::cout<<"rpc get friend list success:"<< rsp.sucess()<<std::endl;
            int size = frsp.friends_size();
            for(int i=0;i<size;i++){
                std::cout<<frsp.friends(i)<<" ";
        }
            std::cout<<std::endl;
        }else{
        std::cout<<"rpc get friend list error:"<< rsp.result().errmsg()<<std::endl;
        }
    }

    return 0;
}