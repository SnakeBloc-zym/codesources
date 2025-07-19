# 线段树

单点修改区间查询：

```cpp
namespace Segment_Tree
{
    struct node
    {
        int sum , minn , maxn;
    }tr[2000010];
    node dispose(node x , node y)
    {
        node a;
        a.sum = x.sum + y.sum;
        a.minn = min(x.minn , y.minn);
        a.maxn = max(x.maxn , y.maxn);
        return a;
    }
    void build(int id , int l , int r)
    {
        if(l == r)
        {
            tr[id] = {a[l] , a[l] , a[l]};
            return;
        }
        int mid = l + r >> 1;
        build(id * 2 , l , mid);
        build(id * 2 + 1 , mid + 1 , r);
        tr[id] = dispose(tr[id * 2] , tr[id * 2 + 1]);
    }
    void change(int id , int l , int r , int x , int y)
    {
        if(l == r)
        {
            tr[id] = {y , y , y};
            return;
        }
        int mid = l + r >> 1;
        if(x <= mid) change(id * 2 , l , mid , x , y);
        if(x > mid) change(id * 2 + 1 , mid + 1 , r , x , y);
        tr[id] = dispose(tr[id * 2] , tr[id * 2 + 1]);
    }
    node query(int id , int l , int r , int cl , int cr)
    {
        if(cl <= l && r <= cr) return tr[id];
        int mid = l + r >> 1;
        if(cr <= mid) return query(id * 2 , l , mid , cl , cr);
        if(cl > mid) return query(id * 2 + 1 , mid + 1 , r , cl , cr);
        return dispose(query(id * 2 , l , mid , cl , cr), query(id * 2 + 1 , mid + 1 , r , cl , cr));
    }
}
using namespace Segment_Tree;
```

区间修改区间查询：

```cpp
namespace Segment_Tree
{
    struct node
    {
        int sum , tag;
    }tr[400010];
    inline void push_down(int id , int l , int r)
    {
        if(!tr[id].tag || l == r) return ;
        int mid = l + r >> 1;
        tr[id * 2].sum += tr[id].tag * (mid - l + 1);
        tr[id * 2].tag += tr[id].tag;
        tr[id * 2 + 1].sum += tr[id].tag * (r - mid);
        tr[id * 2 + 1].tag += tr[id].tag;
       	tr[id].tag = 0;
        return ;
    }
    inline void build(int id , int l , int r)
    {
        if(l == r)
        {
            tr[id] = {a[l] , 0};
            return;
        }
        int mid = l + r >> 1;
        build(id * 2 , l , mid);
        build(id * 2 + 1 , mid + 1 , r);
        tr[id].sum = tr[id * 2].sum + tr[id * 2 + 1].sum;
        tr[id].tag = 0;
    }
    inline void change(int id , int l , int r , int cl , int cr , int y)
    {
        if(l >= cl && r <= cr)
        {
            tr[id].sum += (r - l + 1) * y;
            tr[id].tag += y;
            return;
        }
        push_down(id , l , r);
        int mid = l + r >> 1;
        if(cl <= mid) change(id * 2 , l , mid , cl , cr , y);
        if(cr > mid) change(id * 2 + 1 , mid + 1 , r , cl , cr , y);
        tr[id].sum = tr[id * 2].sum + tr[id * 2 + 1].sum;
    }
    inline int query(int id , int l , int r , int cl , int cr)
    {
        if(l >= cl && r <= cr) return tr[id].sum;
        push_down(id , l , r);
        int mid = l + r >> 1 , sum = 0;
        if(cl <= mid) sum += query(id * 2 , l , mid , cl , cr);
        if(cr > mid) sum += query(id * 2 + 1 , mid + 1 , r , cl , cr);
        return sum;
    }
}
using namespace Segment_Tree;
```