/*
*Author:���P�t
*Date:May,8 2018
*Title:Find the number of distinct subsequence in another sring
*algorithm:DP&�j�ƥ[�k
*Copyright@Chen Peng-Yu
*/

#include<iostream>
#include<string>

using namespace std;

string add(string s1,string s2){//�j�ƥ[�k
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
            table[i][0]=0; //128�Ӱ}�C�s128�Ӧr���A��0�Ӥ����s�Ӧr���bZ���X�{������

        for(int i=0;i<Z.length();i++)
            table[Z[i]][++table[Z[i]][0]] = i;//��Z���C�Ӥ�����m�s�Jtable


        int firstMatchSeqIndex = X.find(Z[0],0);

        if(firstMatchSeqIndex < 0 ){
            cout<<0<<endl;
            continue;
        }//�۲��l�r��Ƭ�0

        string stateMachine[Z.length()]={"0"};//stateMachine�����{�b�l�r�ꪺ���A�A��i�Ӥ�����ܦ�stateMachine[i]�Ӥl�r��b���U�@�Ӧr��

        for(int i=firstMatchSeqIndex;i<X.length();i++){
            if(table[X[i]][0]!=0){//�p�GX���������bZ�����X�{�A�h�ˬd�U�����ण�౵�W�l�r��A�i�ӧ��ܪ��A
                for(int j=table[X[i]][0];j>0;j--){//�n�q��X�{���������^��A�~���|���ƭp��
                        int currentIndex = table[X[i]][j];
                        if(currentIndex == 0){//���s���l�r��}�Y
                            stateMachine[0]=add(stateMachine[0],"1");
                        }
                        else if(stateMachine[currentIndex-1].compare("0")!=0){//�e�����r��b���o�Ӥ���
                            stateMachine[currentIndex]=add(stateMachine[currentIndex],stateMachine[currentIndex-1]);//�N�e�@���q�����ݦr��W�[�ܦ����q
                        }

                }
            }

        }
       cout<<stateMachine[Z.length()-1]<<endl;
    }

    return 0;
}

