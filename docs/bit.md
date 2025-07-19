# 树状数组

模板：

```cpp
namespace Binary_Indexed_Tree
{
    # define lowbit(x) (x & (-x))
    long long tr[500010];
    inline void add(int x , long long w)
    {
        while(x <= n)
        {
            tr[x] += w;
            x += lowbit(x);
        }
        return ;
    }
    inline long long query(int x)
    {
        long long sum = 0;
        while(x)
        {
            sum += tr[x];
            x -= lowbit(x);
        }
        return sum;
    }
}
using namespace Binary_Indexed_Tree;
```