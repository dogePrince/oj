#include<string.h>
memset(ptr*, value, sizeof(list))

#include<stdlib.h>
qsort(num_set, n, sizeof(num_set), compare)
int compare(const void *a, const void *b)

#include<stack>
using namespace std;
stack<int> int_stack;
int_stack.push(int)
int_stack.pop()
int_stack.top()
int_stack.size()
int_stack.empty()

#include<queue>
using namespace std;
using namespace std::queue;
queue<int> int_queue;
int_queue.push(int)
int_queue.pop()
int_queue.front()
int_queue.back()
int_queue.size()
int_queue.empty()

priority_queue<Node>q;
bool operator < (const Node &a, const Node &b) {
    return a.val < b.val;
}
q.pop()
q.push()
q.top()

#include<vector>
using namespace std;
vector<T> v1;
vector<T> v2(n);
vector<T> v3(n, i);
vector<T> v4(v1);
v1.push_back(1);
v1.size()
v1.empty()
v1[1]  --  *(v1.begin()+1)
v1.erase(v1.begin()+1)
v1.erase(v1.begin()+1, v1.end()-1)
reverse(res.begin(), res.end());
for (vector<int>::iterator it = res.begin(); it != res.end(); it++) {
    printf("%d ", *it);
}

#define<algorithm>
sort(S, S+n, cmp)
bool operator < (const Node &a, const Node &b) {
    return a.val < b.val;
}
bool operator < (const Node &b) const{ // in struct
    return val < b.val;
}
bool cmp(Node a, Node b) {
    return a.val < b.val;
}

sscanf(src, "%s", dest);
sprintf(string, "%s %d %d", str1, 13, 22);

#include<iostream>
#include<cstring>
#include<cstdio>
#include<cstdlib>
using namespace std;
int fa[50002],a,b,m,n,p;
/*
x代表例题中的人，fa[x]中所存的数代表这一集合中所有人都与一个人有亲戚关系
相当于例题中第一个集合所有的元素都与第一个元素有亲戚关系
搜索时只要找元素所指向的fa[x]=x的元素(即父元素)
然后比较两个元素的父元素是否相同就可以判断其关系
*/
void build(int qwq) {for(int i=1;i<=qwq;i++) fa[i]=i;return ;}//初始化，一开始每个点单独成集合
int find(const int &x) {return fa[x]==x?x:fa[x]=find(fa[x]);}//找到x的最远祖先，并且压缩路径
bool che(const int &x,const int &y){return find(x)==find(y);}//判断x,y是不是在同一个集合里，直接判断最远祖先是不是一样的
void mer(const int &x,const int &y) {if(!che(x,y)) fa[fa[x]]=fa[y];return ;}
//合并x,y，我们在判断x和y是不是同一个集合里，路径压缩之后fa[x],fa[y]已经是最远祖先了，所以直接将fa[x]的父亲连接起来就好
int main()
{
  int i;
  scanf("%d%d%d",&n,&m,&p);
  build(n);
  for(i=1;i<=m;i++)
      scanf("%d%d",&a,&b),
      mer(a,b);
  for(i=1;i<=p;i++)
    {
      scanf("%d%d",&a,&b);
      if(che(a,b))
        printf("Yes\n");
      else
        printf("No\n");
    }
  return 0;
}
