#include<iostream>
#include<string.h>
#include<vector>
#include<sstream>
using namespace std;

void fun(int &left, int &right, char letter1, char letter2, vector<string>& res){
    if(letter1>letter2 || left>right) return;
    for(int i=(int)letter1;i<=(int)letter2;i++){
        for(int j=left;j<=right;j++){
            string temp1(1, char(i));
            stringstream ss;
            ss<<j;
            string temp2(ss.str());
            res.emplace_back(temp1+temp2);
        }
    }
}

void git_test(){
    printf("asasdasdasd");
}

int main(){
    string first, last;
    cin>>first;
    cin>>last;
    string num1(first.begin()+1, first.end());
    string num2(last.begin()+1, last.end());
    int left = atoi(num1.c_str());
    int right = atoi(num2.c_str());

    vector<string> res;
    fun(left, right, first[0], last[0], res);
    cout<<"[";
    for(int i=0;i<res.size();i++){
        if(i!=res.size()-1){
            cout<<res[i]<<",";
        }else{
            cout<<res[i]<<"]"<<endl;
        }
    }

    return 0;
}