#pragma once
#include<iostream>
#include<string>
#include "user.pb.h"


// // 服务的提供者
// // 此时是一个本地服务，那么如何让其支持远程调用服务
class UserService : public fixbug::UserServiceRpc{
public:
    bool Login(std::string name, std::string pwd){
        std::cout<<"doing local service: Login"<<std::endl;
        std::cout<<"name:"<<name<<" pwd:"<<pwd<<std::endl;
        return false;
    }

    bool Register(uint32_t id, std::string name, std::string pwd){
        return true;
    }

    // 重写基类的虚函数，
    void Login(::google::protobuf::RpcController* controller,
                       const ::fixbug::LoginRequest* request,
                       ::fixbug::LoginResponse* response,
                       ::google::protobuf::Closure* done){
        // 取出序列化的参数
        std::string name = request->name();
        std::string pwd = request->pwd();
        // 执行本地业务
        bool login_request = Login(name, pwd);

        // 反序列化相应的参数
        fixbug::ResultCode *code = response->mutable_result();  // 返回一个可修改的指针
        code->set_errcode(1);
        code->set_errmsg("login error");
        response->set_sucess(login_request);
        
        // 执行相应的回调 对应着对象数据的序列化和网络操作
        done->Run();
        }
            
    void Register(::google::protobuf::RpcController* controller,
                       const ::fixbug::RegisterRequest* request,
                       ::fixbug::RegisterResponse* response,
                       ::google::protobuf::Closure* done){

                       }
};