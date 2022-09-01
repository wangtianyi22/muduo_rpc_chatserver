#pragma once

#include<unordered_map>
#include<./src/TcpConnection.h>
#include<functional>
#include<memory>
#include<mutex>
#include"json.hpp"
#include"model/usermodel.h"
#include"./model/offlinemessagemodel.h"
#include"./model/friendmodel.h"
#include"./model/groupmodel.h"
#include"redis.h"

using json = nlohmann::json;

// 表示处理消息的事件回调方法类型     有什么样的请求执行什么样的业务
using MsgHandler = std::function<void(const TcpConnectionPtr &conn, json &js, Timestamp time)>;

// 聊天服务器业务类
class ChatService{
public:
    // 获取单例对象的接口函数
    static ChatService *instance();
    // 处理登录业务
    void login(const TcpConnectionPtr &conn, json &js, Timestamp time);
    // 处理注册业务
    void reg(const TcpConnectionPtr &conn, json &js, Timestamp time);
    // 一对一聊天业务
    void oneChat(const TcpConnectionPtr &conn, json &js, Timestamp time);
    // 添加好友业务
    void addFriend(const TcpConnectionPtr &conn, json &js, Timestamp time);
    // 创建群组业务
    void createGroup(const TcpConnectionPtr &conn, json &js, Timestamp time);
    // 加入群组业务
    void addGroup(const TcpConnectionPtr &conn, json &js, Timestamp time);
    // 群组聊天业务
    void groupChat(const TcpConnectionPtr &conn, json &js, Timestamp time);
    // 处理注销业务
    void loginout(const TcpConnectionPtr &conn, json &js, Timestamp time);
    // 处理客户端异常退出
    void clientCloseException(const TcpConnectionPtr &conn);
    // 获取消息对应的handler
    MsgHandler getHandler(int msgid);

    void handleRedisSubscribeMessage(int userid, std::string msg);

    // 服务器异常业务重置  所有用户状态设置为offline
    void reset();
private:

    ChatService();
    // 存储消息id和对应的业务处理方法
    std::unordered_map<int, MsgHandler> _msgHandlerMap;
    // 存储在线用户的通信连接
    std::unordered_map<int, TcpConnectionPtr> _userConnMap;
    // 数据操作对象
    UserModel _userModel;               //用户相关
    OfflineMsgModel _offlineMsgModel;   //处理离线消息相关
    FriendModel _friendModel;           //好友列表相关
    GroupModel _groupModel;

    //redis操作对象
    Redis _redis;

    std::mutex _connMutex;

};