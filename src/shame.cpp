#include<cstdio>
#include<iostream>
#include<map>
using namespace std;
typedef long long ll;
#define maxn 1111111
#define mod 1000000007
#define inv (mod+1)/3
map<int,int>m;
map<int,int>::iterator it;
int ans[maxn];
void init()
{
    for(int i=1;i<maxn;i++)ans[i]=1ll*(i-1)*(i-2)%mod;
    for(int i=1;i<maxn;i++)
        for(int j=2*i;j<maxn;j+=i)
        {
            ans[j]-=ans[i];
            if(ans[j]<0)ans[j]+=mod;
        }
    for(int i=2;i<maxn;i++)
    {
        ans[i]+=ans[i-1];
        if(ans[i]>=mod)ans[i]-=mod;
    }
}
int solve(int n)
{
    if(n<maxn)return ans[n];
    it=m.find(n);
    if(it!=m.end())return it->second;
    int cnt=1ll*n*(n-1)%mod*(n-2)%mod*inv%mod;
    for(int i=2,next;i<=n;i=next+1)
    {
        next=n/(n/i);
        cnt-=1ll*(next-i+1)*solve(n/i)%mod;
        if(cnt<0)cnt+=mod;
    }
    return m[n]=cnt;
}
int main()
{
    init();
    int T,n;
    scanf("%d",&T);
    while(T--)
    {
        m.clear();
        scanf("%d",&n);
        printf("%d\n",solve(n));
    }
    return 0;
}
