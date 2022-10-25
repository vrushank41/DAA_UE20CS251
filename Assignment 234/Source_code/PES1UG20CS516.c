#include "header.h"
#include <stdlib.h>
#include <limits.h>

// ANY STATIC FUNCTIONS ARE UP HERE

//Q1
static int len(const char *str)
{
    int len = 0;
    while (*str)
    {
        len++;
        str++;
    }
    return len;
}

struct queue
{
    int size;
    int front;
    int rear;
    int *arr;
};

static int isEmpty(struct queue *q)
{
    if (q->rear == q->front)
    {
        return 1;
    }
    return 0;
}

static int isFull(struct queue *q)
{
    if (q->rear == q->size - 1)
    {
        return 1;
    }
    return 0;
}

static int enqueue(struct queue *q, int val)
{
    if (isFull(q))
    {
        return 1;
    }
    else
    {
        q->arr[q->rear] = val;
        q->rear++;
        // printf("Enqued element: %d\n", val);
    }
    return 0;
}

static int dequeue(struct queue *q)
{
    int res = -1;
    if (isEmpty(q))
    {
        res = -1;
    }
    else
    {
        res = q->arr[q->front];
        q->front++;
    }
    return res;
}

static int bfs(int n, const connection_t a[n][n])
{
    struct queue q;
    q.size = 100;

    q.arr = (int*)malloc(q.size * sizeof(int));

    int visited[20];


    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++) // mark all the vertices as not visited
        {
            visited[j] = 0;
        }
        q.front = 0;
        q.rear = 0;
        // printf("%d\t", i);
        visited[i] = 1; // mark the starting vertex as visited
        enqueue(&q, i);
        
        while (!isEmpty(&q))
        {
            int node = dequeue(&q);
            for (int j = 0; j < n; j++)
            {
                if ((a[node][j].distance != INT_MAX && a[node][j].distance != 0) && visited[j] == 0)
                {
                    visited[j] = 1;
                    enqueue(&q, j);
                }
            }
        }    
    }
    if(q.rear == n)
        return 1;
    return 0;
}


int q1(int n, const connection_t connections[n][n])
{
    return bfs(n, connections);
}


//Q2
static int bfs_Q2(int v, int src, int dest, int n, const connection_t a[n][n])
{
    struct queue q;
    q.size = 100;
    q.front = q.rear = 0;
    q.arr = (int *)malloc(q.size * sizeof(int));

    int distance[n];
    int visited[n];
    int pred[n];
    for (int i = 0; i < n; i++)
    {
        distance[i] = -1;
        pred[i] = -1;
        visited[i] = 0;
    }

    visited[src] = 1;
    distance[src] = 0;
    enqueue(&q, src);
    while (!isEmpty(&q))
    {
        int node = dequeue(&q);
        for (int j = 0; j < n; j++)
        {
            if ((a[node][j].distance != INT_MAX && a[node][j].distance != 0) && visited[j] == 0)
            {
                visited[j] = 1;
                distance[j] = distance[node] + 1;
                pred[j] = node;
                enqueue(&q, j);

                if (j == dest)
                    j=n;
            }
        }
    }

    int crawl = dest;
    struct queue path;
    path.size = 100;
    path.front = path.rear = 0;
    path.arr = (int *)malloc(path.size * sizeof(int));
    enqueue(&path, crawl);
    while (pred[crawl] != -1)
    {
        enqueue(&path, pred[crawl]);
        crawl = pred[crawl];
    }

    return distance[dest];
}

int q2(const airport_t *src, const airport_t *dest, int n, int k,
       const connection_t connections[n][n])
{
    int srctodest = bfs_Q2(src->num_id, src->num_id, dest->num_id, n, connections);
    if (srctodest <= k)
        return 1;
    return 0;
}

//Q3
int q3(const airport_t *src, int n, const connection_t connections[n][n])
{
    int start = 0;
    for (int i = 0; i < n; i++)
    {
        if (src->num_id != i)
            if (connections[src->num_id][i].distance != INT_MAX)
                if (connections[i][src->num_id].distance != INT_MAX)
                    start = start + 1;
    }
    if (start != 0)
        return 1;
    else
        return 0;
}

//Q4
static void swap(airport_t *a, airport_t *b)
{
    airport_t c = *a;
    *a = *b;
    *b = c;
}
static int partition(int n, airport_t airport_list[n], int low, int high, int (*predicate_func)(const airport_t *, const airport_t *))
{
    airport_t pivot = airport_list[high];

    // pointer for greater element
    int i = (low - 1);

    // traverse each element of the array
    // compare them with the pivot
    for (int j = low; j < high; j++)
    {
        if (predicate_func(&airport_list[j], &pivot))
        {
            i++;
            // swap element at i with element at j
            swap(&airport_list[i], &airport_list[j]);
        }
    }

    // swap the pivot element with the greater element at i
    swap(&airport_list[i + 1], &airport_list[high]);

    // return the partition point
    return (i + 1);
}
static void quickSort(int n, airport_t airport_list[n], int low, int high, int (*predicate_func)(const airport_t *, const airport_t *))
{
    if (low < high)
    {
        int pi = partition(n, airport_list, low, high, predicate_func);

        // recursive call on the left of pivot
        quickSort(n, airport_list, low, pi - 1, predicate_func);

        // recursive call on the right of pivot
        quickSort(n, airport_list, pi + 1, high, predicate_func);
    }
}
void q4(int n, int (*predicate_func)(const airport_t *, const airport_t *),
        airport_t airport_list[n])
{
    quickSort(n, airport_list, 0, n - 1, predicate_func);
}

//Q5
static int same(airport_t airport1, airport_t airport2)
{
    int pref=0;
    while(airport1.airport_name[pref]!='\0' && airport2.airport_name[pref]!='\0' && airport1.airport_name[pref]==airport2.airport_name[pref])
    {
        pref++;
    }
    return pref;
}
pair_t q5(int n, airport_t airports[n])
{
    pair_t ans = {-1, -1};
    int max=0;
    int sim;
    for(int i=0;i<n;i++)
    {
        for(int j=i+1;j<n;j++)
        {
            sim=same(airports[i],airports[j]);
            if(max<sim)
            {
                max=sim;
                ans.first=airports[i].num_id;
                ans.second=airports[j].num_id;
            }
        }
    }    
    return ans;
}

//Q6
static int binend(int fee[],int low,int high,int amount,int n)
{
    if(high>=low)
    {
        int mid=low + (high-low)/2;
        if(fee[mid]==amount)
            return mid+1;
        else if((fee[mid-1]<amount) && (amount<fee[mid]))
            return mid;
        else if(mid==n-1)
            return mid+1;
        
        if(fee[mid]>amount)
            return binend(fee,low,mid-1,amount,n);
        return binend(fee,mid+1,high,amount,n);
    }
    return -1;
}
int q6(int n, int amount, const int entry_fee[n])
{
    int fee[n];
    for(int i=0;i<n;i++)
    {    
        fee[i]=entry_fee[i];
    }
    
    int out=binend(fee,0,n-1,amount,n);
    /* int sum=0;
    for(int i=0;i<n;i++)
    {
        if(entry_fee[i]<=amount)
        {
            ++out;
        }
    } */
    return out;
}

//Q7
static void shifttable(const char *pat, int search[])
{
    int i, j, m;
    m = len(pat);
    for (i = 0; i < 100; i++)
        search[i] = m;
    for (j = 0; j < m - 1; j++)
        search[pat[j]] = m - 1 - j;
}

static int horsepool(const char src[], const char *p, int t[])
{
    int i, j, k, m, n;
    n = len(src);
    m = len(p);
    i = m - 1;
    while (i < n)
    {
        k = 0;
        while ((k < m) && (p[m - 1 - k] == src[i - k]))
            k++;
        if (k == m)
            return (i - m + 1);
        else
            i += t[src[i]];
    }
    return -1;
}

void q7(int n, const char *pat, int contains[n], const airport_t airports[n])
{
    int *search = (int *)malloc(100 * sizeof(int));

    for (int i = 0; i < 100; i++)
    {
        search[i] = 0;
    }
    for (int i = 0; i < n; i++)
    {
        shifttable(pat, search);
        if (horsepool(airports[i].airport_name, pat, search) != -1)
        {
            contains[i] = 1;
        }
    }
}

//Q8
typedef struct stack
{
    int arr[100];
    int top;
}stack_t;

static void init(stack_t* s)
{
    s->top=-1;
}

static int full(stack_t* s)
{
    return s->top==100-1;
}

static void push(stack_t* s,int ele)
{
    if(!full(s))
    {
        s->top=s->top+1;
        s->arr[s->top]=ele;
    }
}

static int pop(stack_t* s)
{
    
    return s->arr[s->top--];
}

static int top(stack_t* s)
{
    
    return s->arr[s->top];
}

static void insert(int cycles[25][25],int v,int* cycle_no)
{
    int i=*cycle_no;
    int index=-1;
    for(int j=0;j<25 && index == -1;j++)
    {
        if(cycles[i][j]==-1)
        {
            index=j;
        }
    }
    cycles[i][index]=v;
}
static void cycle(stack_t* s,int v,int cycles[25][25],int* cycle_no)
{
    stack_t s2;
    init(&s2);
    push(&s2,top(s));
    pop(s);
    while(top(&s2)!=v)
    {
        push(&s2,top(s));
        pop(s);
    }
    while(s2.top!=-1)
    {
        insert(cycles,top(&s2),cycle_no);
        push(s,top(&s2));
        pop(&s2);
    }
}
static void DFS_tree(int n,const connection_t connections[n][n],stack_t* s,int visited[n],int cycles[25][25],int* cycle_no)
{
    int u=top(s);
    for(int i=0;i<n;i++)
    {
        if(connections[u][i].distance!=0 && connections[u][i].distance!=INT_MAX &&visited[i]==0)
        {
            *cycle_no=*cycle_no+1;
            cycle(s,i,cycles,cycle_no);
        }
        else if(connections[u][i].distance!=0 && connections[u][i].distance!=INT_MAX &&visited[i]==-1)
        {
            push(s,i);
            visited[i]=0;
            DFS_tree(n,connections,s,visited,cycles,cycle_no);
        }
    }
    visited[top(s)]=1;
    pop(s);
}
static void find_cycles(int n,const connection_t connections[n][n],int visited[n],int cycles[25][25],int* cycle_no)
{
    for(int i=0;i<n;i++)
    {
        if(visited[i]==-1)
        {
            stack_t s;
            init(&s);
            push(&s,i);
            visited[i]=0;
            DFS_tree(n,connections,&s,visited,cycles,cycle_no);
        }
    }
}
int q8(int n, int trip_order[n - 1], const connection_t connections[n][n])
{
    int visited[n];
    int cycles[25][25];
    int cycle_no = 0;
    int min_index;
    int min = INT_MAX;
    int cost=0;
    int p,q;
    for(int i=0;i<n;i++)
    {
        visited[i]=-1;
    }
    for(int a=0;a<25;a++)
    {
        for(int b=0;b<25;b++)
        {
            cycles[a][b]=-1;
        }
    }
    find_cycles(n,connections,visited,cycles,&cycle_no);
    int count[cycle_no+1];
    for(int i=0;i<cycle_no+1;i++)
    {
        count[i]=0;
    }
    int res[cycle_no+1][n];
    int x=0;
    int y=0;
    for(int a=0;a<cycle_no+1;a++)
    {
        for(int b=0;b<n;b++)
        {
            res[a][b]=-1;
        }
    }
    for(int a=0;a<25;a++)
    {
        y=0;
        int flag=0;
        for(int b=0;b<25;b++)
        {
            if(cycles[a][b]!=-1)
            {
                if(!flag)
                {
                    x++;
                    flag=1;
                }
                res[x][y]=cycles[a][b];
                count[x]=count[x]+1;
                y++;
            }
        }
    }
    for(int a=1;a<cycle_no+1;a++)
    {
        if(count[a]==n-1)
        {
            cost=0;
            // last_index=n-1;
            for(int b=0;b<n-1;b++)
            {
                if(res[a][b]!=-1 && res[a][b+1]!=-1)
                {
                    p=res[a][b];
                    q= res[a][b+1];
                    cost+= connections[p][q].distance;
                }
            }
            cost+=connections[q][res[a][0]].distance;
            if(cost<min)
            {
                min=cost;
                min_index=a;
            }
        }
    }
    if(min==INT_MAX)
    {
        return -1;
    }
    else
    {
        for(int i=0;i<n-1;i++)
        {
            trip_order[i]=cycles[min_index][i];
        }
        return min;
    }
}

//Q9
typedef struct edge
{
    int u, v, w;
} edge_t;

typedef struct edge_list
{
    edge_t data[400];
    int n;
} edgeList_t;

static int find(int belongs[], int vertexNo)
{
    return (belongs[vertexNo]);
}

static void applyUnion(int n, int belongs[], int c1, int c2)
{
    int i;

    for (i = 0; i < n; i++)
        if (belongs[i] == c2)
            belongs[i] = c1;
}

static void sort(edgeList_t *elist)
{
    int i, j;
    edge_t temp;

    for (i = 1; i < elist->n; i++)
        for (j = 0; j < elist->n - 1; j++)
            if (elist->data[j].w > elist->data[j + 1].w)
            {
                temp = elist->data[j];
                elist->data[j] = elist->data[j + 1];
                elist->data[j + 1] = temp;
            }
}

static int print(pair_t edges[], edgeList_t *spanlist)
{
    int i, cost = 0;

    for (i = 0; i < spanlist->n; i++)
    {
        edges[i].first = spanlist->data[i].v;
        edges[i].second = spanlist->data[i].u;
        cost = cost + spanlist->data[i].w;
    }

    return cost;
}

// Applying Krushkal Algo
static void kruskalAlgo(int n, const connection_t connections[n][n], edgeList_t *elist, edgeList_t *spanlist)
{
    int belongs[400], i, j, cno1, cno2;

    elist->n = 0;

    for (i = 1; i < n; i++)
        for (j = 0; j < i; j++)
        {
            if (connections[i][j].time != 0)
            {
                elist->data[elist->n].u = i;
                elist->data[elist->n].v = j;
                elist->data[elist->n].w = connections[i][j].time;
                elist->n++;
            }
        }

    sort(elist);

    for (i = 0; i < n; i++)
        belongs[i] = i;

    spanlist->n = 0;

    for (i = 0; i < elist->n; i++)
    {
        cno1 = find(belongs, elist->data[i].u);
        cno2 = find(belongs, elist->data[i].v);

        if (cno1 != cno2)
        {
            spanlist->data[spanlist->n] = elist->data[i];
            spanlist->n = spanlist->n + 1;
            applyUnion(n, belongs, cno1, cno2);
        }
    }
}

int q9(int n, pair_t edges[n - 1], const connection_t connections[n][n])
{
    edgeList_t elist;
    edgeList_t spanlist;
    kruskalAlgo(n, connections, &elist, &spanlist);
    int res = 0;
    res = print(edges, &spanlist);
    return res;
}


//Q10
static void Dijkstra(int n, const connection_t connections[n][n], int start, const int dest[], int costs[], int k)
{
    int cost[n][n], distance[n], pred[n];
    int visited[n], count, mindistance, nextnode, i, j;

    // Creating cost matrix
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            if (connections[i][j].time == 0)
                cost[i][j] = INT_MAX;
            else
                cost[i][j] = connections[i][j].time;

    for (i = 0; i < n; i++)
    {
        distance[i] = cost[start][i];
        pred[i] = start;
        visited[i] = 0;
    }

    distance[start] = 0;
    visited[start] = 1;
    count = 1;

    while (count < n - 1)
    {
        mindistance = INT_MAX;

        for (i = 0; i < n; i++)
            if (distance[i] < mindistance && !visited[i])
            {
                mindistance = distance[i];
                nextnode = i;
            }

        visited[nextnode] = 1;
        for (i = 0; i < n; i++)
            if (!visited[i])
                if (mindistance + cost[nextnode][i] < distance[i])
                {
                    distance[i] = mindistance + cost[nextnode][i];
                    pred[i] = nextnode;
                }
        count++;
    }

    // Printing the distance

    for (int i = 0; i < k; i++)
    {
        costs[i] = distance[dest[i]];
    }

}

void q10(int n, int k, const airport_t *src,
         const connection_t connections[n][n], const int destinations[k],
         int costs[k])
{
    Dijkstra(n, connections, src->num_id, destinations, costs, k);
}

