#include<iostream>
#include<stack>
using namespace std;

#define MAXVEX 9
#define INFINITY 65535

typedef int Patharc[MAXVEX];
typedef int ShortPathTable[MAXVEX];

typedef struct {
	int vex[MAXVEX];
	int arc[MAXVEX][MAXVEX];
	int numVertexes;
} MGraph;

// 构建图
void CreateMGraph(MGraph *G){
	int i, j, k;
	// 初始化图
	G->numVertexes = 9;
	for(i = 0; i < G->numVertexes; ++i){
		G->vex[i] = i;
	}
	for(i = 0; i < G->numVertexes; ++i){
		for(j = 0; j < G->numVertexes; ++j){
			if(i == j)
				G->arc[i][j] = 0;
			else
				G->arc[i][j] = G->arc[j][i] = INFINITY;
		}
	}

	G->arc[0][1] = 1;
	G->arc[0][2] = 5;

	G->arc[1][2] = 3;
	G->arc[1][3] = 7;
	G->arc[1][4] = 5;

	G->arc[2][4] = 1;
	G->arc[2][5] = 7;

	G->arc[3][4] = 2;
	G->arc[3][6] = 3;

	G->arc[4][5] = 3;
	G->arc[4][6] = 6;
	G->arc[4][7] = 9;

	G->arc[5][7] = 5;

	G->arc[6][7] = 2;
	G->arc[6][8] = 7;

	G->arc[7][8] = 4;

	// 设置对称位置元素值
	for(i = 0; i < G->numVertexes; ++i){
		for(j = i; j < G->numVertexes; ++j){
			G->arc[j][i] = G->arc[i][j];
		}
	}
}

void ShortPath_Dijkstra(MGraph G, int v0, Patharc P, ShortPathTable D){
	int final[MAXVEX];
	int i;
	for(i = 0; i < G.numVertexes; ++i){
		final[i] = 0;
		D[i] = G.arc[v0][i];
		P[i] = 0;
	}
	D[v0] = 0;
	final[v0] = 1;
	for(i = 0; i < G.numVertexes; ++i){
		int min = INFINITY;
		int j, k, w;

		for(j = 0; j < G.numVertexes; ++j){// 查找距离V0最近的顶点
			if(!final[j] && D[j] < min){
				k = j;
				min = D[j];
			}
		}
		final[k] = 1;
		for(w = 0; w < G.numVertexes; ++w){// 更新各个顶点的距离
			if(!final[w] && (min + G.arc[k][w]) < D[w]){
				D[w] = min + G.arc[k][w];
				P[w] = k;
			}
		}
	}
}

// 打印最短路径
void PrintShortPath(MGraph G, int v0, Patharc P, ShortPathTable D){
	int i, k;
	stack<int> path;
	cout<<"顶点v"<<v0<<"到其他顶点之间的最短路径如下: "<<endl;
	for(i = 0; i < G.numVertexes; ++i){
		if(i == v0) continue;
		cout<<"v"<<v0<<"--"<<"v"<<i<<" weight: "<<D[i]<<"  Shortest path: ";
		path.push(i);
		int k = P[i];
		while(k != 0){
			path.push(k);
			k = P[k];
		}
		path.push(v0);
		while(!path.empty()){
			if(path.size() != 1)
				cout<<path.top()<<"->";
			else
				cout<<path.top()<<endl;
			path.pop();
		}
	}
}

int main(int argc, char const *argv[]) {
	int v0 = 0; // 源点
	MGraph G;
	Patharc P;
	ShortPathTable D;
	CreateMGraph(&G);
	ShortPath_Dijkstra(G, v0, P, D);
	PrintShortPath(G, v0, P, D);
	return 0;
}
