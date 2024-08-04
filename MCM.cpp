#include<bits/stdc++.h>
using namespace std;

#define END '\n'
#define pb push_back
#define vec vector
#define ll long long

class node_i {
	public:
	int distance = 10e5+7;
	int name = 0; 
};
class priority_queue_trial{
	vec<node_i> nd;
	public:
	void assigner(vec<node_i> nd){
		this->nd = nd;
	}
	void rearrang(){
		int size = nd.size();
		for(int i = size/2 -1 ; i>=0; i--)
			node_hepify(i);
	}
	void insert(node_i s){
		
		nd.pb(s);	
		int size = nd.size(); 
		for(int i = size/2 -1 ; i>=0; i--){
			node_hepify(i);
		}
	}
	
	bool node_empty(){
		return nd.empty();
	}
	void node_hepify(int i){
		int smallest = i;
		int left = 2*i+1;
		int right = 2*i+2;
		
		if(nd[smallest].distance < nd[left].distance && left < nd.size())
			smallest = left;
		
		if(nd[smallest].distance < nd[right].distance && right < nd.size())
			smallest = right;
			
		if(smallest != i){
			auto temp = nd[i];
			nd[i] = nd[smallest];
			nd[smallest] = temp;
			node_hepify(smallest);
		}	
	}
	auto peek(){
		
		return nd[0];	
	}
	
	node_i node_pop(){
		int len = nd.size();
		auto temp = this->nd[0];
			this->nd[0] = this->nd[--len];
			this->nd[len] = temp;
		nd.pop_back();	
		for(int i = len/2 -1 ; i>=0; i--){
			node_hepify(i);
		}
		
		return temp;
	}
};
int bigMod(int a, int b, int M){
	
	if (!b) return 1 % M;
	
	int x = bigMod(a,b/2, M);
	
	x = (x*x) % M;
	
	if(b&1) x = ( x * a )  % M;
	
	return x;
}

void showBigMod(){
	ll a,b,m;
	
	cout<<"Enter Number: ";cin>>a;
	cout<<"Enter power: ";cin>>b;
	cout<<"Enter moduluos: ";cin>>m;
	
	cout<<"Result is: "<< bigMod(a,b,m)<<END;
}

vec<int> seive(int n){
	vec<int> primes;
	bool mark[1000] = {0};
	mark[0]  = mark[1] = true;
	int limit = sqrt(n+1);
	
	primes.pb(2);
	for(int i= 4; i<=n; i+=2) mark[i] = true;
	
	for(int i=3; i<=n; i+=2){
		if(!mark[i]){
			primes.pb(i);
			if(mark[i]<= limit){
				for(int j=i*i; j<=n; j+= i*2){
					mark[j] = true;
				}
			}
		}
	}
	return primes;
}
void showSeive(){
	int n;
	cin>>n;
	
	vec<int> v = seive(n);
	int len = v.size();
	
	for(int i=0; i<len; i++)
		cout<<v[i]<<" ";
	
}

int bigSum(int a, int b, int m){ // 5 2 1 0
	if(!b) return 1;
	if(b==2) return 1 +  a + a*a;
	
	int x = bigSum(a,b/2,m);
	x = x + (bigMod(a,b/2+1,m)*x % m) % m;
	
	if(b&1^1 && b!=2) x -= bigMod(a,b+1,m);
	
	return x;
	
}

void showBigSum(){
	int a,b,m;
	cin>>a>>b>>m;
	
	cout<<bigSum(a,b-1,m)<<END;
}

int egcd(int a,int b, int &x, int &y){
	if(!a){
		x = 0;
		y = 1;
		return b;
	}
	int x1,y1;
	int d = egcd(b%a,a,x1,y1);
	
	x = y1 - (b/a)*x1;
	y = x1;
	return d;
}

void showInverseModulus(){
	int p,m;
	cout<<"Enter co-prime p: ";cin>>p;
	cout<<"Enter Modulus M: ";cin>>m;
	int x,y;
	cout<<bigMod(p,m-2,m)<<END;
	cout<<"egcd: "<<egcd(p,m,x,y)<<END;
	cout<<"x: "<<x<<" y: "<<y<<END;
}

void dfs(bool arr[][5],bool mark[],vec<int> &travarse,int p, int n){
	mark[p] = true;
	travarse.pb(p);
	for(int i=0; i<n; i++){
		if(arr[p][i] && !mark[i])
			dfs(arr,mark,travarse,i,n);
	}
	
}

void showDFS(){
	int n = 5;
	bool arr[5][5] = {
	//	0   1  2  3  4 
		{0, 1, 1, 0, 0},
		{1, 0, 0, 1, 1},
		{1, 0, 0, 0, 0},
		{0, 1, 0, 0, 0},
		{0, 1, 0, 0, 0}
	};
	bool mark[n] = {0};
	vec<int> travarse;
	for(int i=0; i<n; i++){
		if(!mark[i])
			dfs(arr,mark,travarse,i,n);
	}
	int len = travarse.size();
	
	for(int i=0; i<len; i++)
		cout<<travarse[i]<<" ";
}

void bfs(vec<vec<int>> graph, bool mark[], int travarse[], int p,int curr, int &count, int n){
	
	int len  = graph[p].size();
	for(int i=0; i<len; i++){
		if(!mark[ graph[p][i] ]){
			travarse[count++] = graph[p][i];
			mark[graph[p][i]] = true;
		}
	}
	if(curr != n){
		int x = travarse[curr];
		bfs(graph, mark, travarse, x, ++curr, count, n);
	}
	
}
void showBFS(){
	int n, e;
	cout<<"Number of nodes: ";cin>>n;
	cout<<"Number of EDGES: ";cin>>e;
	bool mark[n] = {0};
	// cant use queue yet :v
	int travarse[n];
	int count = 0;
	int curr = 0;
	vec<vec<int>> graph(10);
	
	for(int i=0; i<e; i++){
		int x,y;
		cin>>x>>y;
		graph[x].pb(y);
		graph[y].pb(x);
	}
	
	for(int i=0; i<n; i++){
		if(!mark[i]){
			travarse[count++] = i;
			mark[i] = true;
			bfs(graph,mark,travarse,i,++curr, count, n);
		}
	}
	
	for(int i=0; i<n; i++)
		cout<<travarse[i]<<" ";
}

void show_priority_queue(){
	cout<<"add ten numbers"<<END;
	priority_queue_trial q;
	for(int i= 0; i<10; i++){
		node_i x;
		x.name = i;
		cin>>x.distance;
		
		q.insert(x);
	}
	cout<<"firt time highest"<<END;
	cout<<q.node_pop().name<<END;
	cout<<"net time highest"<<END;
	cout<<q.peek().name<<END;
	
}
void d_bfs(vec<vec<int>> &g,  vec<node_i> &ns, vec<vec<int>> &cost,priority_queue_trial &q, int s){
	int len = g[s].size();
	for(int i=0; i<len; i++){
		if(ns[g[s][i]].distance  > ns[s].distance + cost[s][g[s][i]] ){
			ns[g[s][i]].distance = ns[s].distance + cost[s][g[s][i]];
			q.insert(ns[g[s][i]]);
		}
	}
	if(!q.node_empty()){
		int x = q.node_pop().name;
		d_bfs(g,ns,cost,q,x);
	}
}
void diakstra_bfs(vec<vec<int>> &g, vec<node_i> &ns, vec<vec<int>> &cost, int s){
	priority_queue_trial q;
	ns[s].distance = 0;
	q.insert(ns[0]);
	
	d_bfs(g,ns,cost,q,s);
}

void show_diakstra(){
	int v,e;
	cout<<"Number of nodes: ";cin>>v;
	cout<<"Number of edges: ";cin>>e;
	vec<vec<int>> cost(v);
	vec<vec<int>> g(v);
	vec<int> distance(v);
	vec<node_i> ns;
	for(int i=0; i<v; i++){
		for(int j=0;j<v;j++){
			cost[i].pb(1e5+7);
		}
	}
	for(int i=0; i<e; i++){
		int s,d,h;
		cout<<"source: ";cin>>s;
		cout<<"destination: ";cin>>d;
		cout<<"cost: ";cin>>h;
		g[s].pb(d);
		cost[s][d] = h;
	}
	for(int i=0; i<v; i++){
		node_i nd;
		nd.distance = 1e5+7;
		nd.name = i;
		ns.pb(nd);
	}
	diakstra_bfs(g, ns, cost, 0);
	for(int i =0; i<v; i++){
		cout<<ns[i].distance<<" ";
	}
	
}
void floyd_warshal(vec<vec<int>> cost, int n){
	for(int k=0; k<n; k++){
		for(int i=0; i<n; i++){
			for(int j=0; j<n; j++){
					cost[i][j] = min(cost[i][j],cost[i][k]+cost[k][j]);
			}
		}
	}
}
void show_floyd_warshal(){
	int n,e;
	cout<<"number of nodes: ";cin>>n;
	cout<<"number of edges: ";cin>>e;
	vec<vec<int>> cost(n, vec<int> (n,10e5+7));
	
	
	for(int j=0; j<e; j++){
		int s,d,h;
		cout<<"source: ";cin>>s;
		cout<<"destination: ";cin>>d;
		cout<<"cost: ";cin>>h;
		cost[s][d] = h;
	}
	
	for(int j=0; j<n; j++)
		cost[j][j] = 0;
		
	floyd_warshal(cost,n);
	
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			cout<<cost[i][j]<<" ";
		}
		cout<<END;
	}
}
int main(){
	show_floyd_warshal();
}
	
