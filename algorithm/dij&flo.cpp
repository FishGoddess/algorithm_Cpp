#include <stdio.h>
#include <time.h>
#include <cmath>
#define MAX_DISTANCE 99999

// ����һ�����ͼ����д���ļ�
void createRandomGraph(int number, const char* filename)
{
	FILE* output = freopen(filename, "w", stdout);
	printf("%d\n", number);

	srand((int)time(NULL));
	for (int i = 0; i < number; i++)
	{
		int b = 0;
		int e = 0;
		do // �������ĳ���
		{
			b = rand() % (number - 1 - 1) + 1;
			e = rand() % (number - 1 - 1) + 1;
		} while (b == e);

		int dis = rand() % 10 + 2;

		printf("%d %d %d\n", b, e, dis);
	}

	fclose(output);
}

// ������������С·������
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

// ������·����Dijkstra�㷨
void path_Dijkstra(int** adjmat, int u, int vex_num)
{
	// ��Ƕ����Ƿ񱻷��ʹ�
	bool* isVisited = new bool[vex_num];
	int* dist = new int[vex_num];
	int* pre = new int[vex_num];

	// ɨ������㵽ÿ������ľ���
	for (int i = 0; i < vex_num; i++)
	{
		dist[i] = adjmat[u][i]; // ��ʼ����������
		pre[i] = u; // ÿһ�������ǰһ�����㶼�ǳ�����
		isVisited[i] = false; // ˳���ʼ���������
	}

	isVisited[u] = true; // �����㱻���ʹ������ϱ��
	pre[u] = -1; // ������û��ǰһ������

				 // ����ɨ�����������¼��������飬ֻҪ vex_num - 1 ��
	for (int i = 1; i < vex_num; i++)
	{
		// �Ӿ����������ҵ�һ����̵�·
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
			// û���ҵ���С·��˵��������Ƕ����ģ�����ĵ���붼������
			break;
		}

		isVisited[minVex] = true; // ���Ϸ��ʱ��
		for (int j = 0; j < vex_num; j++)
		{
			// ���������� minVex ���㵽��һ������ľ���ȳ�����ֱ�ӵ���һ������̣��������������ǰ������
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

// ���������㷨����ʱ��
void testFn()
{
	FILE* input = freopen("graph.txt", "r", stdin);

	int number = 0;
	scanf("%d", &number);
	printf("%d �����㡣����\n", number);

	// ���ɾ���
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

	printf("Dijkstra: %.2lf ��\n", (end - begin) / 1000);

	begin = clock();

	Floyd(graph, number);

	end = clock();

	printf("Floyd: %.2lf ��\n", (end - begin) / 1000);

	// ������Դ
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

