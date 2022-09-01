#include<iostream>
#include<string>
#include"user.pb.h"

class FriendService:public fixbug::FiendServiceRpc{
public:
    std::vector<std::string> GetFriendsList(uint32_t userid){
        std::cout<<"do get friend list"<<"  userid:"<<userid<<std::endl;
        std::vector<std::string> vec{"qwe", "adasd", "haizhi"};
        return vec;
    }

    // 重写基类方法
    void GetFriendsList(::google::protobuf::RpcController* controller,
                       const ::fixbug::GetFriendsListRequest* request,
                       ::fixbug::GetFriendsListResponse* response,
                       ::google::protobuf::Closure* done)
    {
        uint32_t userid = request->userid();
        std::vector<std::string> friendList = GetFriendsList(userid);

        response->mutable_result()->set_errcode(0);
        response->mutable_result()->set_errmsg("");
        for(auto &name:friendList){
            std::string *p = response->add_friends();
            *p = name;
        }
        done->Run();
    }

};