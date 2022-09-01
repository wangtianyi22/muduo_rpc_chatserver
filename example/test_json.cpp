#include "json.hpp"
using json = nlohmann::json;

#include <iostream>
#include <vector>
#include <map>
#include <string>
using namespace std;

// json序列化示例1
string func1()
{
    json js;
    std::vector<int> vec = {1,2,3,4,5,6};
    js["msg_type"] = 2;
    js["from"] = "zhang san";
    js["to"] = "li si";
    js["msg"] = "hello, what are you doing now?";
    js["vec"] = vec;

    string sendBuf = js.dump();
    //cout<<sendBuf.c_str()<<endl;
    return sendBuf; 
}

// json序列化示例2
string func2()
{
    json js;

    // 添加数组
    js["id"] = {1, 2, 3, 4, 5};
    // 添加key-value
    js["name"] = "zhang san";
    // 添加对象
    js["msg"]["zhang san"] = "hello world";
    js["msg"]["liu shuo"] = "hello china";
    // 上面等同于下面这句一次性添加数组对象
    js["msg"] = {{"zhang san", "hello world"}, {"liu shuo", "hello china"}};
    //cout << js << endl;
    return js.dump();
}

// json序列化示例代码3
string func3()
{
    json js;

    // 直接序列化一个vector容器
    vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(5);

    js["list"] = vec;

    // 直接序列化一个map容器
    map<int, string> m;
    m.insert({1, "挺好的?"});
    m.insert({2, "华山"});
    m.insert({3, "泰山"});

    js["path"] = m;

    string sendBuf = js.dump(); // json数据对象 =》序列化 json字符串
    //cout<<sendBuf<<endl;
    return sendBuf;
}

int titleToNumber(string column) {
    // write code here
    int lens = column.size();
    int res = 0;
    if(lens==0) return 0;
    int temp = 1;
    for(int i=lens-1; i>=0; i--){
        std::cout<<"i"<<i<<std::endl;
        if(i!=lens-1) temp *=26;
        std::cout<<"temp:"<<temp<<std::endl;
        res += (column[i]-64)*temp;
        std::cout<<"res:"<<res<<std::endl;
    }
    return res;
}

int get_max_length(vector<int>& arr, int k) {
    // write code here
    sort(arr.begin(), arr.end());
    vector<int> dp(k+1, 0);

    for(int i=0;i<arr.size();i++){
        for(int j=k;j>=arr[i];j--){
            dp[j] = max(dp[j], dp[j-arr[i]]+1);
        }
    }
    return dp[k];
}

int main()
{
    // string recvBuf = func1();
    // // 数据的反序列化   json字符串 =》反序列化 数据对象（看作容器，方便访问）
    // std::cout<<"recvBuf"<<recvBuf<<std::endl;
    // json jsbuf = json::parse(recvBuf);
    // for(auto it : jsbuf.items()){
    //     cout<<"key:"<<it.key()<<" "<<"value:"<<it.value()<<endl;
    //     if(it.key()=="vec"){
    //         std::vector<int> vec = it.value().get<std::vector<int>>();
    //         for(auto &i:vec){
    //             std::cout<<i<<std::endl;
    //         }
    //     }
    // }

    // string str1 = "{\"1\":\"asd\", \"2\":\"qwe\"}";
    // json parse_str1 = json::parse(str1);
    // cout<<parse_str1["1"]<<endl;

    // cout<<jsbuf["id"]<<endl;
    // std::vector<int> arr = jsbuf["id"];
    // cout<<arr[2]<<endl;
    // arr.push_back(7);
    // std::cout<<*(arr.end()-1)<<std::endl;

    // auto msgjs = jsbuf["msg"];
    // cout<<msgjs["zhang san"]<<endl;
    // cout<<msgjs["liu shuo"]<<endl;


    // vector<int> vec = jsbuf["list"]; // js对象里面的数组类型，直接放入vector容器当中
    // for (int &v : vec)
    // {
    //     cout << v << " ";
    // }
    // cout << endl;

    // map<int, string> mymap = jsbuf["path"];
    // for (auto &p : mymap)
    // {
    //     cout << p.first << " " << p.second << endl;
    // }
    // cout << endl;


    string str = "A";
    int res = titleToNumber(str);
    std::cout<<res<<std::endl;

    // vector<int> arr {1,2,1,1,1};
    // std::cout<<get_max_length(arr, 3)<<std::endl;


    return 0;
}
