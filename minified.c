#include<stdio.h>
#include<stdarg.h>
#include<stdlib.h>
#include<sys/mman.h>
char*r(char*n){FILE*f=fopen(n,"r");fseek(f,0,2);int s=ftell(f);rewind(f);char*t=
malloc(s);fread(t,1,s,f);fclose(f);return t;}typedef struct{char*d;int c,s;}v;
void p(v*u,int l,...){va_list a;va_start(a,l);if(u->s+l>=u->c){u->c*=2;u->d=
realloc(u->d,u->c);}for(int i=0;i<l;++i)u->d[u->s++]=va_arg(a,char);va_end(a);}
void j(char*c,v*u){int d[256]={0},s=0;p(u,16,85,72,137,229,87,86,82,73,137,252,
73,137,245,73,137,214);while(*++c){if(*c=='>')p(u,3,73,255,196);if(*c=='<')p(u,
3,73,255,204);if(*c=='+')p(u,4,65,254,4,36);if(*c=='-')p(u,4,65,254,12,36);if(*c
=='.')p(u,8,65,15,182,60,36,65,255,214);if(*c==',')p(u,7,65,255,213,65,136,4,36)
;if(*c=='['){p(u,11,65,128,60,36,0,15,132,0,0,0,0);d[s++]=u->s;}if(*c==']'){p(u,
11,65,128,60,36,0,15,133,0,0,0,0);int n=d[--s],f=u->s-n;*(int*)(u->d+n-4)=f;
*(int*)(u->d+u->s-4)=-f;}}p(u,8,65,94,65,93,65,92,93,195);}int main(int c,char**
a){if(c<2)exit(-1);char t[30000]={0},*d=r(a[1]);v u={malloc(256),256,0};j(d-1,&u
);free(d);void(*f)(char*,int(*)(),int(*)(int))=mmap(0,u.s,6,34,0,0);memcpy(f,u.d
,u.s);free(u.d);f(t,getchar,putchar);munmap(f,u.s);}
