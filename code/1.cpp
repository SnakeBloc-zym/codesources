# pragma GCC optimize(3)
# pragma GCC target("avx")
# pragma GCC optimize("Ofast")
# pragma GCC optimize("inline")
# pragma GCC optimize("-fgcse")
# pragma GCC optimize("-fgcse-lm")
# pragma GCC optimize("-fipa-sra")
# pragma GCC optimize("-ftree-pre")
# pragma GCC optimize("-ftree-vrp")
# pragma GCC optimize("-fpeephole2")
# pragma GCC optimize("-ffast-math")
# pragma GCC optimize("-fsched-spec")
# pragma GCC optimize("unroll-loops")
# pragma GCC optimize("-falign-jumps")
# pragma GCC optimize("-falign-loops")
# pragma GCC optimize("-falign-labels")
# pragma GCC optimize("-fdevirtualize")
# pragma GCC optimize("-fcaller-saves")
# pragma GCC optimize("-fcrossjumping")
# pragma GCC optimize("-fthread-jumps")
# pragma GCC optimize("-funroll-loops")
# pragma GCC optimize("-fwhole-program")
# pragma GCC optimize("-freorder-blocks")
# pragma GCC optimize("-fschedule-insns")
# pragma GCC optimize("inline-functions")
# pragma GCC optimize("-ftree-tail-merge")
# pragma GCC optimize("-fschedule-insns2")
# pragma GCC optimize("-fstrict-aliasing")
# pragma GCC optimize("-fstrict-overflow")
# pragma GCC optimize("-falign-functions")
# pragma GCC optimize("-fcse-skip-blocks")
# pragma GCC optimize("-fcse-follow-jumps")
# pragma GCC optimize("-fsched-interblock")
# pragma GCC optimize("-fpartial-inlining")
# pragma GCC optimize("no-stack-protector")
# pragma GCC optimize("-freorder-functions")
# pragma GCC optimize("-findirect-inlining")
# pragma GCC optimize("-fhoist-adjacent-loads")
# pragma GCC optimize("-frerun-cse-after-loop")
# pragma GCC optimize("inline-small-functions")
# pragma GCC optimize("-finline-small-functions")
# pragma GCC optimize("-ftree-switch-conversion")
# pragma GCC optimize("-foptimize-sibling-calls")
# pragma GCC optimize("-fexpensive-optimizations")
# pragma GCC optimize("-funsafe-loop-optimizations")
# pragma GCC optimize("inline-functions-called-once")
# pragma GCC optimize("-fdelete-null-pointer-checks")
# pragma GCC optimize(2)
# include <bits/stdc++.h>
using namespace std;
unsigned int n , m;
int a[500010];
namespace IN{
    const int MAX_INPUT = 1000000;
    #define getc() (p1==p2&&(p2=(p1=buf)+inbuf->sgetn(buf,MAX_INPUT),p1==p2)?EOF:*p1++)
    char buf[MAX_INPUT],*p1,*p2;
    template<typename T>inline bool read(T &x) {
        static std::streambuf *inbuf=cin.rdbuf();
        x=0;
        register int f=0,flag=false;
        register char ch=getc();
        while(!isdigit(ch)){
            if (ch=='-') f=1;
            ch=getc();
        }
        if(isdigit(ch)) x=x*10+ch-'0',ch=getc(),flag=true;
        while(isdigit(ch)) {
            x=x*10+ch-48;
            ch=getc();
        }
        x=f?-x:x;
        return flag;
    }
    template<typename T,typename ...Args>inline bool read(T& a,Args& ...args) {
       return read(a)&&read(args...);
    }
    #undef getc
}

namespace OUT{
    template<typename T>inline void put(T x){
        static std::streambuf *outbuf=cout.rdbuf();
        static char stack[21];
        static int top=0;
        if(x<0){
            outbuf->sputc('-');
            x=-x;
        }
        if(!x){
            outbuf->sputc('0');
            outbuf->sputc('\n');
            return;
        }
        while(x){
            stack[++top]=x%10+'0';
            x/=10;
        }
        while(top){
            outbuf->sputc(stack[top]);
            --top;
        }
        outbuf->sputc('\n');
    }
    inline void putc(const char ch){
        static std::streambuf *outbuf=cout.rdbuf();
        outbuf->sputc(ch);
    }
    inline void putstr(string s){
        for(register int i=0;i<s.length();i++) putc(s[i]);
    }
    template<typename T>inline void put(const char ch,T x){
        static std::streambuf *outbuf=cout.rdbuf();
        static char stack[21];
        static int top = 0;
        if(x<0){
            outbuf->sputc('-');
            x=-x;
        }
        if(!x){
            outbuf->sputc('0');
            outbuf->sputc(ch);
            return;
        }
        while(x){
            stack[++top]=x%10+'0';
            x/=10;
        }
        while(top){
            outbuf->sputc(stack[top]);
            --top;
        }
        outbuf->sputc(ch);
    }
    template<typename T,typename ...Args> inline void put(T a,Args ...args){
        put(a);put(args...);
    }
    template<typename T,typename ...Args> inline void put(const char ch,T a,Args ...args){
        put(ch,a);put(ch,args...);
    }
}
using namespace IN;
using namespace OUT;
namespace Segment_Tree
{
    struct node
    {
        int l , r , sum , ans;
    }tr[2000010];
    inline node dispose(node x , node y)
    {
        node a;
        a.sum = x.sum + y.sum;
        a.l = max(x.l , x.sum + y.l);
        a.r = max(y.r , y.sum + x.r);
        a.ans = max(max(x.ans , y.ans) , x.r + y.l);
        return a;
    }
    inline void build(unsigned int id , unsigned int l , unsigned int r)
    {
        if(l == r)
        {
            tr[id] = {a[l] , a[l] , a[l] , a[l]};
            return;
        }
        int mid = l + r >> 1;
        build(id * 2 , l , mid);
        build(id * 2 + 1 , mid + 1 , r);
        tr[id] = dispose(tr[id * 2] , tr[id * 2 + 1]);
    }
    inline void change(unsigned int id , unsigned int l , unsigned int r , unsigned int x , int y)
    {
        if(l == r)
        {
            tr[id] = {y , y , y , y};
            return;
        }
        unsigned int mid = l + r >> 1;
        if(x <= mid) change(id * 2 , l , mid , x , y);
        if(x > mid) change(id * 2 + 1 , mid + 1 , r , x , y);
        tr[id] = dispose(tr[id * 2] , tr[id * 2 + 1]);
    }
    inline node query(unsigned int id , unsigned int l , unsigned int r , unsigned int cl , unsigned int cr)
    {
        if(cl <= l && r <= cr) return tr[id];
        unsigned int mid = l + r >> 1;
        if(cr <= mid) return query(id * 2 , l , mid , cl , cr);
        if(cl > mid) return query(id * 2 + 1 , mid + 1 , r , cl , cr);
        return dispose(query(id * 2 , l , mid , cl , cr), query(id * 2 + 1 , mid + 1 , r , cl , cr));
    }
}
using namespace Segment_Tree;
signed main()	
{
    read(n) , read(m);
    for(unsigned int i(1) ; i <= n ; ++ i) read(a[i]);
    build(1 , 1 , n);
    for(unsigned int i(1) , op , x , y ; i <= m ; ++ i)
    {
        read(op) , read(x) , read(y);
        if(op == 1)
        {
            if(x > y) swap(x , y);
            put(query(1 , 1 , n , x , y).ans); putchar('\n');
        }
        else
        {
            change(1 , 1 , n , x , y);
        }
    }
    return 0;
}