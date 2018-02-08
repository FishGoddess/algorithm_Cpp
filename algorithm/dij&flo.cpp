#include <stdio.h>
#include <time.h>
#include <cmath>
#define MAX_DISTANCE 99999

// 产生一个随机图，并写入文件
void createRandomGraph(int number, const char* filename)
{
	FILE* output = freopen(filename, "w", stdout);
	printf("%d\n", number);

	srand((int)time(NULL));
	for (int i = 0; i < number; i++)
	{
		int b = 0;
		int e = 0;
		do // 不允许环的出现
		{
			b = rand() % (number - 1 - 1) + 1;
			e = rand() % (number - 1 - 1) + 1;
		} while (b == e);

		int dis = rand() % 10 + 2;

		printf("%d %d %d\n", b, e, dis);
	}

	fclose(output);
}

// 弗洛伊德找最小路径距离
void Floyd(int** data, int n)
{
	for (int k = 0; k < n; k++)
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (data[i][j] >(data[i][k] + data[k][j]))
				{
					data[i][j] = data[i][k] + data[k][j];
				}
			}
		}
	}
}

// 求解最短路径的Dijkstra算法
void path_Dijkstra(int** adjmat, int u, int vex_num)
{
	// 标记顶点是否被访问过
	bool* isVisited = new bool[vex_num];
	int* dist = new int[vex_num];
	int* pre = new int[vex_num];

	// 扫描出发点到每个顶点的距离
	for (int i = 0; i < vex_num; i++)
	{
		dist[i] = adjmat[u][i]; // 初始化距离数组
		pre[i] = u; // 每一个顶点的前一个顶点都是出发点
		isVisited[i] = false; // 顺便初始化标记数组
	}

	isVisited[u] = true; // 出发点被访问过，打上标记
	pre[u] = -1; // 出发点没有前一个顶点

				 // 不断扫描矩阵，修正记录距离的数组，只要 vex_num - 1 趟
	for (int i = 1; i < vex_num; i++)
	{
		// 从距离数组中找到一个最短的路
		int min = 9999;
		int minVex = 0;
		for (int j = 0; j < vex_num; j++)
		{
			if (!isVisited[j] && min > dist[j])
			{
				min = dist[j];
				minVex = j;
			}
		}

		if (min == 9999)
		{
			// 没有找到最小路，说明这个点是独立的，到别的点距离都是无穷
			break;
		}

		isVisited[minVex] = true; // 打上访问标记
		for (int j = 0; j < vex_num; j++)
		{
			// 如果借助这个 minVex 顶点到另一个顶点的距离比出发点直接到另一个顶点短，修正距离数组和前驱数组
			if (!isVisited[j] && (dist[minVex] + adjmat[minVex][j] < dist[j]))
			{
				dist[j] = dist[minVex] + adjmat[minVex][j];
				pre[j] = minVex;
			}
		}
	}

	delete[] isVisited;
	delete[] dist;
	delete[] pre;
}

// 测试两种算法消耗时间
void testFn()
{
	FILE* input = freopen("graph.txt", "r", stdin);

	int number = 0;
	scanf("%d", &number);
	printf("%d 个顶点。。。\n", number);

	// 生成矩阵
	int** graph = new int*[number];
	for (int i = 0; i < number; i++)
	{
		graph[i] = new int[number];
	}

	int i = 0;
	int j = 0;
	int k = 0;
	while (scanf("%d%d%d", &i, &j, &k) == 3)
	{
		graph[i - 1][j - 1] = k;
		graph[j - 1][i - 1] = k;
	}

	double begin = clock();

	for (int i = 0; i < number; i++)
	{
		path_Dijkstra(graph, i, number);
	}

	double end = clock();

	printf("Dijkstra: %.2lf 秒\n", (end - begin) / 1000);

	begin = clock();

	Floyd(graph, number);

	end = clock();

	printf("Floyd: %.2lf 秒\n", (end - begin) / 1000);

	// 清理资源
	for (int i = 0; i < number; i++)
	{
		delete[] graph[i];
	}
	delete[] graph;
}

int main()
{
	/*int number = 0;
	scanf("%d", &number);
	createRandomGraph(number, "graph.txt");*/

	testFn();

	return 0;
}

