# 最近公共祖先

模板：

```cpp
namespace lca
{
    # define d(x , y) dis[x] + dis[y] - 2 * dis[LCA(x , y)]
    int lg[10010] , sp[10010] , dis[10010] , f[10010][18];
    vector <pair <int , int> > g[10010];
    void init()
    {
        for(int i = 2 ; i <= n ; i ++) lg[i] = lg[i / 2] + 1;
        return ;
    }
    void dfs(int x , int lst , int w)
    {
        sp[x] = sp[lst] + 1;
        dis[x] = dis[lst] + w;
        f[x][0] = lst;
        for(int i = 1 ; i <= lg[sp[x]] ; i ++) f[x][i] = f[f[x][i - 1]][i - 1];
        for(int i = 0 ; i < g[x].size() ; i ++) if(g[x][i].first != lst) dfs(g[x][i].first , x , g[x][i].second);
        return ;
    }
    int LCA(int x , int y)
    {
        if(sp[x] < sp[y]) swap(x , y);
        for(int i = lg[sp[x]] ; i >= 0 ; i --) if(sp[f[x][i]] >= sp[y]) x = f[x][i];
        if(x == y) return x;
        for(int i = lg[sp[x]] ; i >= 0 ; i --) if(f[x][i] != f[y][i]) x = f[x][i] , y = f[y][i]; 
        return f[x][0];
    }
}
using namespace lca;
```