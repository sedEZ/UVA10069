/*
*Author:陳鵬宇
*Date:May,8 2018
*Title:Find the number of distinct subsequence in another sring
*algorithm:DP&大數加法
*Copyright@Chen Peng-Yu
*/

#include<iostream>
#include<string>

using namespace std;

string add(string s1,string s2){//大數加法
    int length1 = s1.length();
    int length2 = s2.length();

    int maxDigit = max(length1,length2);

    string sum;

    for(int i=0;i<maxDigit+1;i++)
        sum.push_back(0);

    for(int i=length1-1,j=maxDigit;i>=0;i--,j--)
        sum[j]+=(s1[i]-'0');
    for(int i=length2-1,j=maxDigit;i>=0;i--,j--)
        sum[j]+=(s2[i]-'0');

    for(int i=maxDigit;i>0;sum[i]+='0',i--){
        if(sum[i]>9){
            sum[i]-=10;
            sum[i-1]++;
        }
    }


    if(sum[0]==0)
        sum.erase(0,1);
    else
        sum[0]='1';
    return sum;
}


int main(){
    int caseNum;
    cin>>caseNum;
    for(caseNum;caseNum>0;caseNum--){
        string X,Z;
        cin>>X>>Z;

        char table[128][101];
        for(int i=0;i<128;i++)
            table[i][0]=0; //128個陣列存128個字元，第0個元素存該字元在Z中出現的次數

        for(int i=0;i<Z.length();i++)
            table[Z[i]][++table[Z[i]][0]] = i;//把Z的每個元素位置存入table


        int firstMatchSeqIndex = X.find(Z[0],0);

        if(firstMatchSeqIndex < 0 ){
            cout<<0<<endl;
            continue;
        }//相異子字串數為0

        string stateMachine[Z.length()]={"0"};//stateMachine紀錄現在子字串的狀態，第i個元素表示有stateMachine[i]個子字串在等下一個字元

        for(int i=firstMatchSeqIndex;i<X.length();i++){
            if(table[X[i]][0]!=0){//如果X中的元素在Z中有出現，則檢查各元素能不能接上子字串，進而改變狀態
                for(int j=table[X[i]][0];j>0;j--){//要從後出現的元素往回找，才不會重複計算
                        int currentIndex = table[X[i]][j];
                        if(currentIndex == 0){//找到新的子字串開頭
                            stateMachine[0]=add(stateMachine[0],"1");
                        }
                        else if(stateMachine[currentIndex-1].compare("0")!=0){//前面有字串在等這個元素
                            stateMachine[currentIndex]=add(stateMachine[currentIndex],stateMachine[currentIndex-1]);//將前一階段的等待字串增加至此階段
                        }

                }
            }

        }
       cout<<stateMachine[Z.length()-1]<<endl;
    }

    return 0;
}

