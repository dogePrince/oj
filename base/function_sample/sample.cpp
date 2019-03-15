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
