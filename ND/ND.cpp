#include <iostream>
#include <map>
#include <set>
#include <queue>
#include <cstdlib>
#include <cstring>
#include <cstdio>
using namespace std;

const int maxn=100;
int vis[maxn];
vector<set<int> >C;//构造出的子集
map<set<int>,int> flag;//子集是否被标记
map<int,map<int,map<char,int> > > nfa;
struct DFA //构造DFA的结构体 
{
    int st;
    char w;
    int ed;
};
vector<DFA> dfa;

int n,m;//状态数和弧的数量

//状态集T的c弧转换
set<int> Move(set<int> T,char c)
{
    set<int> U;
    for(set<int>::iterator i=T.begin();i!=T.end();i++)
    {
        int u=*i;
        for(int j=0;j<n;j++)
        {
            if(nfa[u][j][c]==1)
                U.insert(j);
        }
    }
    return U;
}
//状态集T的e-闭包
set<int> eclosure(set<int> T)
{
    set<int> U;//容器U 
    queue<int> Q;//队列Q 
    for(set<int>::iterator i=T.begin();i!=T.end();i++)
    {
        U.insert(*i);
        Q.push(*i);
    }
    //BFS广度优先搜索——寻找经任意条e弧可到达的状态
    memset(vis,0,sizeof(vis));
    while(!Q.empty())
    {
        int v=Q.front();
        Q.pop();
        for(int i=0;i<n;i++)
        {
            if(nfa[v][i]['e']&&vis[i]==0)
            {
                U.insert(i);
                Q.push(i);
                vis[i]=1;
            }
        }
    }
    return U;
}

int main()
{
    freopen("input.txt","r",stdin);//读入 
    cin>>n>>m; // n:状态数(7)   m:弧的数量 (12)
    n++;// 0、1、2、3、4、5、6、7  -->> 8 
    //构造状态图  
    for(int i=0;i<m;i++)
    {
        int u,v;
        char w;
        cin>>u>>v>>w;
        nfa[u][v][w]=1;//先做标记 
    }
    int k0=0;//K0
    set<int> temp;//int类型的容器 
    temp.insert(k0);
    temp=eclosure(temp);
    C.push_back(temp);
    //子集构造算法
    while(1)//进入循环 
    {
        int st=-1;
        set<int> T;
        //判断C中是否存在被标记的子集T
        for(int i=0;i<C.size();i++)
        {
            if(!flag[C[i]])
            {
                st=i;
                T=C[i];
                break;
            }
        }
        if(st==-1)
            break;
        flag[T]=1;//标记T
        set<int> U=eclosure(Move(T,'a'));
        
        if(!flag[U])
        {
            C.push_back(U);
        }
        for(int i=0;i<C.size();i++)
        {
            if(U==C[i])
            {
                dfa.push_back(DFA{st,'a',i});
                break;
            }
        }
        
        
        U=eclosure(Move(T,'b'));
        if(!flag[U])
        {
            C.push_back(U);
        }
        for(int i=0;i<C.size();i++)
        {
            if(U==C[i])
            {
                dfa.push_back(DFA{st,'b',i});
                break;
            }
        }
    }
    //输出构造的子集
    cout<<"共构造了"<<C.size()<<"个子集:"<<endl;
    for(int i=0;i<C.size();i++)
    {
        set<int> T=C[i];
        cout<<"T"<<i<<"={";
        for(set<int>::iterator j=T.begin();j!=T.end();j++)
        {
            if(j!=T.begin())
                cout<<',';
            cout<<*j;
        }
        cout<<"}"<<endl;
    }
    cout<<endl;
    cout<<"构造的DFA M如下:"<<endl<<endl;
    cout<<"S={";
    for(int i=0;i<C.size();i++)
    {
        if(i!=0)
            cout<<",";
        cout<<"[T"<<i<<"]";
    }
    cout<<"}"<<endl<<endl;
    for(int i=0;i<dfa.size();i++)
    {
        cout<<"D([T"<<dfa[i].st<<"],"<<dfa[i].w<<")=[T"<<dfa[i].ed<<"]"<<endl;
    }
    return 0;
}

