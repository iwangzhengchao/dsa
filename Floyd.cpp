#include<iostream>
using namespace std;

#define MAXVEX 10
#define INFINITY 65535

typedef int Patharc[MAXVEX][MAXVEX];
typedef int ShortPathTable[MAXVEX][MAXVEX];

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

// Floyd algorithm
void ShortPath_Floyd(MGraph G, Patharc P, ShortPathTable D){
	int i, j, k;
	// 二重循环，初始化P, D
	for(i = 0; i < G.numVertexes; ++i){
		for(j = 0; j < G.numVertexes; ++j){
			D[i][j] = G.arc[i][j];
			P[i][j] = j;
		}
	}
	// 三重循环, Floyd algorithm
	for(k = 0; k < G.numVertexes; ++k){
		for(i = 0; i < G.numVertexes; ++i){
			for(j = 0; j < G.numVertexes; ++j){
				if(D[i][j] > D[i][k]+D[k][j]){
					D[i][j] = D[i][k]+D[k][j];
					P[i][j] = P[i][k];
				}
			}
		}
	}
}

// 打印最短路径
void PrintShortPath(MGraph G, Patharc P, ShortPathTable D){
	int i, j, k;
	cout<<"各顶点之间的最短路径如下: "<<endl;
	for(i = 0; i < G.numVertexes; ++i){
		for(j = i+1; j < G.numVertexes; ++j){
			cout<<"v"<<i<<"--"<<"v"<<j<<" "<<"weight: "<<D[i][j]<<"  Path: "<<i<<" -> ";
			k = P[i][j];
			while(k != j){
				cout<<k<<" -> ";
				k = P[k][j];
			}
			cout<<j<<endl;
		}
		cout<<endl;
	}
}

int main(int argc, char const *argv[]) {
	MGraph G;
	Patharc P;
	ShortPathTable D;
	CreateMGraph(&G);
	ShortPath_Floyd(G, P, D);
	PrintShortPath(G, P, D);
	return 0;
}
