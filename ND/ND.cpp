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
vector<set<int> >C;//��������Ӽ�
map<set<int>,int> flag;//�Ӽ��Ƿ񱻱��
map<int,map<int,map<char,int> > > nfa;
struct DFA //����DFA�Ľṹ�� 
{
    int st;
    char w;
    int ed;
};
vector<DFA> dfa;

int n,m;//״̬���ͻ�������

//״̬��T��c��ת��
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
//״̬��T��e-�հ�
set<int> eclosure(set<int> T)
{
    set<int> U;//����U 
    queue<int> Q;//����Q 
    for(set<int>::iterator i=T.begin();i!=T.end();i++)
    {
        U.insert(*i);
        Q.push(*i);
    }
    //BFS���������������Ѱ�Ҿ�������e���ɵ����״̬
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
    freopen("input.txt","r",stdin);//���� 
    cin>>n>>m; // n:״̬��(7)   m:�������� (12)
    n++;// 0��1��2��3��4��5��6��7  -->> 8 
    //����״̬ͼ  
    for(int i=0;i<m;i++)
    {
        int u,v;
        char w;
        cin>>u>>v>>w;
        nfa[u][v][w]=1;//������� 
    }
    int k0=0;//K0
    set<int> temp;//int���͵����� 
    temp.insert(k0);
    temp=eclosure(temp);
    C.push_back(temp);
    //�Ӽ������㷨
    while(1)//����ѭ�� 
    {
        int st=-1;
        set<int> T;
        //�ж�C���Ƿ���ڱ���ǵ��Ӽ�T
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
        flag[T]=1;//���T
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
    //���������Ӽ�
    cout<<"��������"<<C.size()<<"���Ӽ�:"<<endl;
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
    cout<<"�����DFA M����:"<<endl<<endl;
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

