#include <bits/stdc++.h>

using namespace std;
const int maxn = 1000010;
const int inf = 0x3f3f3f3f;
const int dx[] = {0, 0, 1, 0, -1};
const int dy[] = {0, 1, 0, -1, 0};

struct Node{
  string s;
  int step;
};

string a;
long long sum;
map<long long, int> vis;
Node ans, tmp;
int nowx, nowy;
char A[4][4];

inline string GraphToString() {
  sum = 0;
  string b;
  for(int i = 1; i <= 3; ++i) {
    for(int j = 1; j <= 3; ++j) {
      b += A[i][j];
      sum = sum * 10 + A[i][j] - '0';
    }
  }
  return b;
}

inline void StringtoGraph(Node now) {
  int pos = 0;
  for(int i = 1; i <= 3; ++i) {
    for(int j = 1; j <= 3; ++j) {
      if(now.s[pos] == '0') nowx = i, nowy = j;
      A[i][j] = now.s[pos++];
    }
  }
}

inline void bfs() {
  queue<Node> q;
  q.push(ans);
  while(!q.empty()) {
    Node now = q.front(); q.pop();
    StringtoGraph(now);
    for(int i = 1; i <= 4; ++i) {
      int nx = nowx + dx[i];
      int ny = nowy + dy[i];
      if(nx >= 1 && nx <= 3 && ny >= 1 && ny <= 3) {
      	swap(A[nowx][nowy], A[nx][ny]);
      	tmp.s = GraphToString();
      	if(tmp.s == "123804765") {
        	printf("%d", now.step + 1);
        	return ;
      	}
      	if(!vis[sum]) {
        	vis[sum] = 1;
        	tmp.step = now.step + 1;
        	q.push(tmp);
      	}
      	swap(A[nowx][nowy], A[nx][ny]);
      }
    }
  }
}


int main() {
  ios::sync_with_stdio(false);
  cin >> a;
  ans.s = a, ans.step = 0;
  for(int i = 0; i < 9; ++i)
    sum = sum * 10 + (a[i] - '0');
  if(sum == 123804765) return printf("0"), 0;
  vis[sum] = 1;
  bfs();
  return 0;
}