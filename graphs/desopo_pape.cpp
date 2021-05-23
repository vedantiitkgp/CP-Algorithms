// https://cp-algorithms.com/graph/desopo_pape.html
#include<bits/stdc++.h>
#define INF 100000000

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<int,ll> pil;
typedef pair<string, string> pss;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<pii> vii;
typedef vector<pil> vil;
typedef vector<ll> vl;
typedef vector<vl> vvl;
typedef vector<bool> vb;
typedef vector<vii> vvii;
typedef vector<vil> vvil;

void print_desopo_pape(vl dist,vi prev,int n,int s)
{
    cout<<"Source vertex : "<<s<<endl;
    for(int i=1;i<=n;i++)
    {
        cout<<i<<" : "<<dist[i]<<endl;
    }
    cout<<"Shortest_paths"<<endl;
    for(int i=1;i<=n;i++)
    {
        vi temp1;
        temp1.push_back(i);
        int temp2 = prev[i];
        while(temp2!=-1)
        {
            temp1.push_back(temp2);
            temp2 = prev[temp2];   
        }
        reverse(temp1.begin(),temp1.end());
        cout<<"Path "<<i<<" : ";
        for(int j=0;j<temp1.size();j++)
        {
            cout<<temp1[j]<<" ";
        }
        cout<<endl;
    }
}



void desopo_pape(vvil adj,int n,int s)
{
    vl dist(n+1,INF);
    vi prev(n+1,-1);
    vi m(n+1,2);
    deque<int> q;
    
    q.push_back(s);
    dist[s] = 0;
    prev[s] = -1;
    while(!q.empty())
    {
        int u = q.front();
        m[u] = 0;
        q.pop_front();
        for(pil edge: adj[u])
        {
            if(dist[edge.first]>dist[u]+edge.second)
            {
                dist[edge.first] = dist[u] + edge.second;
                prev[edge.first] = u;
                if(m[edge.first]==2) // Unvisited vertex
                {
                    m[edge.first] = 1;
                    q.push_back(edge.first);
                }
                else if(m[edge.first]==0) // Completed vertex
                {
                    m[edge.first] = 1;
                    q.push_front(edge.first);
                }
            }
        }
    }
    print_desopo_pape(dist,prev,n,s);
}

int main()
{
    int n,s,e;
    cout<<"Enter the no of vertices and no of edges :"<<endl;
    cin>>n>>e;
    cout<<"Enter the source vertex :"<<endl;
    cin>>s;
    vvil adj(n+1);
    cout<<"Define edges :"<<endl;
    int param1,param2;
    ll param3;
    for(int i=0;i<e;i++)
    {
        cin>>param1>>param2>>param3;
        adj[param1].push_back({param2,param3});
    }
    cout<<endl;
    desopo_pape(adj,n,s);
    return 0;
}