#include <iostream>
#include "../../Header/queue.h"
#include <stdlib.h>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
#define ll long long
using namespace std;
const int maxn=100001;
ll arr[maxn];
ll ans=0;//用ans记录矩形最大的面积
queue st;
void s(ll* arr,int n)
{
	ans=0;
    arr[n+1]=-1;
    for(int i=1;i<=n+1;++i)
    {
        if(st.isEmpty()||arr[st.getBack()]<=arr[i])
            st.push(i);
        else
        {
            int tmp;//用来记录被弹掉矩形的高度
            while(st.getLength() && arr[st.getBack()]>arr[i])
            {
                tmp=st.getBack(); 
                ans=max(arr[st.getBack()]*(i-st.getBack()),ans);
                st.pop2();
            }
            st.push(tmp);
            arr[tmp]=arr[i];
        }
    }
    
    cout<<endl<<"最大矩阵面积为"<<ans<<endl;
}
int main()
{
	cout << "随机生成十个数据:" <<endl; 
    ll n=10;
	for(int i=1;i<=n;++i)//随机生成105个数 
    {
		arr[i]=rand()%105;
		cout<<arr[i]<<" ";
    }
	s(arr,n);
	cout<<"输入数组个数:"<<endl;
	cin>>n;
	cout<<"输入数组:"<<endl;
	for(int i=1;i<=n;i++)
	{
		cin>>arr[i];
	}
	s(arr,n);
    return 0;
}
