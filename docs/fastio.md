# 快读/快写

代码1：

```cpp
namespace fastio{
    #ifdef __linux__
    #define gc getchar_unlocked
    #define pc putchar_unlocked
    #else
    #define gc _getchar_nolock
    #define pc _putchar_nolock
    #endif
    inline bool blank(const char x){return!(x^32)||!(x^10)||!(x^13)||!(x^9);}template<typename Tp>inline void read(Tp&x){x=0;register bool z=true;register char a=gc();for(;!isdigit(a);a=gc())if(a=='-')z=false;for(;isdigit(a);a=gc())x=(x<<1)+(x<<3)+(a^48);x=(z?x:~x+1);}inline void read(double&x){x=0.0;register bool z=true;register double y=0.1;register char a=gc();for(;!isdigit(a);a=gc())if(a=='-')z=false;for(;isdigit(a);a=gc())x=x*10+(a^48);if(a!='.')return x=z?x:-x,void();for(a=gc();isdigit(a);a=gc(),y/=10)x+=y*(a^48);x=(z?x:-x);}inline void read(char&x){for(x=gc();blank(x)&&(x^-1);x=gc());}inline void read(char*x){register char a=gc();for(;blank(a)&&(a^-1);a=gc());for(;!blank(a)&&(a^-1);a=gc())*x++=a;*x=0;}inline void read(string&x){x="";register char a=gc();for(;blank(a)&&(a^-1);a=gc());for(;!blank(a)&&(a^-1);a=gc())x+=a;}template<typename T,typename...Tp>inline void read(T&x,Tp&...y){read(x),read(y...);}template<typename Tp>inline void write(Tp x){if(!x)return pc(48),void();if(x<0)pc('-'),x=~x+1;register int len=0;register char tmp[64];for(;x;x/=10)tmp[++len]=x%10+48;while(len)pc(tmp[len--]);}inline void write(const double x){register int a=6;register double b=x,c=b;if(b<0)pc('-'),b=-b,c=-c;register double y=5*powl(10,-a-1);b+=y,c+=y;register int len=0;register char tmp[64];if(b<1)pc(48);else for(;b>=1;b/=10)tmp[++len]=floor(b)-floor(b/10)*10+48;while(len)pc(tmp[len--]);pc('.');for(c*=10;a;a--,c*=10)pc(floor(c)-floor(c/10)*10+48);}inline void write(const pair<int,double>x){register int a=x.first;if(a<7){register double b=x.second,c=b;if(b<0)pc('-'),b=-b,c=-c;register double y=5*powl(10,-a-1);b+=y,c+=y;register int len=0;register char tmp[64];if(b<1)pc(48);else for(;b>=1;b/=10)tmp[++len]=floor(b)-floor(b/10)*10+48;while(len)pc(tmp[len--]);a&&(pc('.'));for(c*=10;a;a--,c*=10)pc(floor(c)-floor(c/10)*10+48);}else cout<<fixed<<setprecision(a)<<x.second;}inline void write(const char x){pc(x);}inline void write(const bool x){pc(x?49:48);}inline void write(char*x){fputs(x,stdout);}inline void write(const char*x){fputs(x,stdout);}inline void write(const string&x){fputs(x.c_str(),stdout);}template<typename T,typename...Tp>inline void write(T x,Tp...y){write(x),write(y...);}
}
```

此代码使用 `getchar_unlocked` 与 `putchar_unlocked` 替代 `getchar` 与 `putchar`，这两个放弃了线程安全，以达到更优的速度，但在 Windows 评测机上过不了编译。替代方案是使用 `_getchar_nolock` 与 `_putchar_nolock`。

代码2：

```cpp
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
```

注意输出不是 `write` 而是 `put`。