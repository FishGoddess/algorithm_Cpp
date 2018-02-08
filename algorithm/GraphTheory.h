#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <fstream> // ifstream 的头文件
#include <sstream> // stringstream 的头文件

// 复杂图，用邻接矩阵代表图
class DenseGraph
{
public:
	DenseGraph(int vertexCount, bool isDirected)
	{
		this->vertexCount = vertexCount;
		this->edgeCount = 0;
		this->isDirected = isDirected;

		for (int i = 0; i < vertexCount; i++)
		{
			matrix.push_back(std::vector<bool>(vertexCount, false));
		}
	}

	// 获取顶点个数
	int getVertexCount() const
	{
		return vertexCount;
	}

	// 获取边的条数
	int getEdgeCount() const
	{
		return edgeCount;
	}

	// 判断两个顶点是否有边
	bool ifHasEdge(int vertex1, int vertex2)
	{
		if (vertex1 < 0 || vertex1 >= vertexCount || vertex2 < 0 || vertex2 >= vertexCount)
		{
			exit(1);
		}

		return matrix[vertex1][vertex2];
	}

	// 在两个顶点中增加一条边
	void addEdge(int vertex1, int vertex2)
	{
		if (vertex1 < 0 || vertex1 >= vertexCount || vertex2 < 0 || vertex2 >= vertexCount)
		{
			exit(1);
		}

		if (ifHasEdge(vertex1, vertex2) == true)
		{
			return;
		}
		else // ifHasEdge(vertex1, vertex2) == false
		{
			matrix[vertex1][vertex2] = true;
			if (vertex1 != vertex2 && isDirected == false)
			{
				// 无向图两向都要加上边
				matrix[vertex2][vertex1] = true;
			}
			edgeCount++;
		}
	}

	// 以矩阵的形式打印这个图
	void print(int vertex = -1)
	{
		// 下面是表的形式
		//if (vertex == -1)
		//{
		//	for (int v = 0; v < vertexCount; v++)
		//	{
		//		std::cout << v << " : ";
		//		Iterator I(*this, v);
		//		for (int w = I.begin(); !I.end(); w = I.next())
		//		{
		//			std::cout << w << " ";
		//		}
		//		std::cout << std::endl;
		//	}
		//}
		//else // 只打印用户给的那个顶点
		//{
		//	std::cout << vertex << " : ";
		//	Iterator I(*this, vertex);
		//	for (int w = I.begin(); !I.end(); w = I.next())
		//	{
		//		std::cout << w << " ";
		//	}
		//	std::cout << std::endl;
		//}

		if (vertex == -1)
		{
			for (int i = 0; i < vertexCount; i++)
			{
				for (int j = 0; j < vertexCount; j++)
				{
					std::cout << matrix[i][j] << "  ";
				}
				std::cout << std::endl;
			}
		}
		else // 只打印一个顶点的
		{
			for (int i = 0; i < vertexCount; i++)
			{
				std::cout << matrix[vertex][i] << "  ";
			}
		}
	}

private:
	int vertexCount;
	int edgeCount;
	bool isDirected;
	std::vector<std::vector<bool>> matrix;

	// 遍历边需要用到这个迭代器
	class Iterator
	{
	public:
		Iterator(DenseGraph& g, int vertex) : G(g)
		{
			this->vertex = vertex;
			index = -1;
		}

		int begin()
		{
			index = -1;

			return next();
		}

		int next()
		{
			for (index += 1; index < G.getVertexCount(); index++)
			{
				if (G.matrix[vertex][index] == true)
				{
					return index;
				}
			}

			return -1;
		}

		bool end()
		{
			return (index >= G.matrix[vertex].size());
		}

	private:
		DenseGraph& G;
		int vertex;
		int index;

	};
};

// 疏密图，用邻接表代表图
class SparseGraph
{
public:
	SparseGraph(int vertexCount, bool isDirected)
	{
		this->vertexCount = vertexCount;
		this->edgeCount = 0;
		this->isDirected = isDirected;

		for (int i = 0; i < vertexCount; i++)
		{
			table.push_back(std::vector<int>());
		}
	}

	// 获取顶点个数
	int getVertexCount() const
	{
		return vertexCount;
	}

	// 获取边的条数
	int getEdgeCount() const
	{
		return edgeCount;
	}

	// 判断两个顶点是否有边
	bool ifHasEdge(int vertex1, int vertex2)
	{
		if (vertex1 < 0 || vertex1 >= vertexCount || vertex2 < 0 || vertex2 >= vertexCount)
		{
			exit(1);
		}

		for (int i = 0; i < table.size(); i++)
		{
			if (table[vertex1][i] == vertex2)
			{
				return true;
			}
		}
		return false;
	}

	// 在两个顶点中增加一条边
	void addEdge(int vertex1, int vertex2)
	{
		if (vertex1 < 0 || vertex1 >= vertexCount || vertex2 < 0 || vertex2 >= vertexCount)
		{
			exit(1);
		}

		/*if (ifHasEdge(vertex1, vertex2) == true)
		{
			return;
		}*/

		table[vertex1].push_back(vertex2);
		if (vertex1 != vertex2 && isDirected == false)
		{
			// 无向图两向都要加上边
			table[vertex2].push_back(vertex1);
		}
		edgeCount++;
	}

	// 以表的形式打印这个图
	void print(int vertex = -1)
	{
		if (vertex == -1)
		{
			for (int v = 0; v < vertexCount; v++)
			{
				std::cout << v << " : ";
				Iterator I(*this, v);
				for (int w = I.begin(); !I.end(); w = I.next())
				{
					std::cout << w << " ";
				}
				std::cout << std::endl;
			}
		}
		else // 只打印用户给的那个顶点
		{
			std::cout << vertex << " : ";
			Iterator I(*this, vertex);
			for (int w = I.begin(); !I.end(); w = I.next())
			{
				std::cout << w << " ";
			}
			std::cout << std::endl;
		}
	}


private:
	int vertexCount;
	int edgeCount;
	bool isDirected;
	std::vector<std::vector<int>> table;

	// 遍历边需要用到这个迭代器
	class Iterator
	{
	public:
		Iterator(SparseGraph& g, int vertex) : G(g)
		{
			this->vertex = vertex;
			index = 0;
		}

		int begin()
		{
			index = 0;
			if (G.table[vertex].size() != NULL)
			{
				return G.table[vertex][index];
			}

			return -1;
		}

		int next()
		{
			index++;
			if (index < G.table[vertex].size())
			{
				return G.table[vertex][index];
			}

			return -1;
		}

		bool end()
		{
			return (index >= G.table[vertex].size());
		}

	private:
		SparseGraph& G;
		int vertex;
		int index;

	};
};

// 从文件读取数据保存在图中
template<typename Graph>
void readGraphFromFile(Graph& graph, const std::string& filename)
{
	std::ifstream file(filename);
	if (file.is_open() == NULL)
	{
		std::cout << "文件打开失败！" << std::endl;
		exit(1);
	}

	std::string line;
	int vertexNum, edgeNum;

	// 从文件读取一行，将这一行作为输入流，保存在数据里面
	std::getline(file, line);
	std::stringstream input(line);
	input >> vertexNum >> edgeNum;

	if (vertexNum != graph.getVertexCount())
	{
		std::cout << "您的图和数据量不符！" << std::endl;
		exit(1);	
	}

	for (int i = 0; i < edgeNum; i++)
	{
		std::getline(file, line);
		std::stringstream input(line);
		int v1, v2;
		input >> v1 >> v2;

		graph.addEdge(v1, v2);

	}
}