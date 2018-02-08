#pragma once
#include <iostream>
#include <queue>

// 用于排好序的数组的 二分查找法，返回元素的索引
template<typename T>
int binarySearch(T arr[], int n, T target)
{
	int L = 0, R = n - 1;

	while (L <= R)
	{
		// 防止数据溢出
		int middle = L + (R - L) / 2;

		if (arr[middle] == target)
		{
			return middle;
		}

		if (arr[middle] > target)
		{
			R = middle - 1;
		}
		else
		{
			L = middle + 1;
		}
	}

	// 没有找到返回 -1
	return -1;
}

// 二分搜索树
template<typename ID, typename Value>
class BinarySearchTree
{
public:
	BinarySearchTree()
	{
		count = 0;
		root = NULL;
	}

	~BinarySearchTree()
	{
		destroy(root);
	}

	int getSize() const
	{
		return count;
	}

	// 插入一个元素到树中
	void insert(ID id, Value value)
	{
		// 先把树根给稳住
		if (root == NULL)
		{
			root = new Node(id, value);
			count++;
			return;
		}

		Node* currentRoot = root;
		while (true) // root != NULL
		{
			if (currentRoot->value < value)
			{
				if (currentRoot->right == NULL)
				{
					currentRoot->right = new Node(id, value);
					count++;
					return;
				}
				else // currentRoot->right != NULL
				{
					currentRoot = currentRoot->right;
				}
			}
			else if (currentRoot->value > value)
			{
				if (currentRoot->left == NULL)
				{
					currentRoot->left = new Node(id, value);
					count++;
					return;
				}
				else // currentRoot->left != NULL
				{
					currentRoot = currentRoot->left;
				}
			}
			else // currentRoot->value == value
			{
				currentRoot->id = id;
				break;
			}
		}
	}

	// 检查元素是否在这棵树中
	bool isExisted(Value value)
	{
		Node* currentRoot = root;
		while (true)
		{
			if (currentRoot == NULL)
			{
				return false;
			}
			else // currentRoot != NULL
			{
				if (currentRoot->value < value)
				{
					currentRoot = currentRoot->right;
				}
				else if (currentRoot->value > value)
				{
					currentRoot = currentRoot->left;
				}
				else // currentRoot->value == value
				{
					return true;
				}
			}
		}
	}

	// 搜索树里的一个元素
	ID* search(Value value)
	{
		Node* currentRoot = root;
		while (true)
		{
			if (currentRoot == NULL)
			{
				return NULL;
			}
			else // currentRoot != NULL
			{
				if (currentRoot->value < value)
				{
					currentRoot = currentRoot->right;
				}
				else if (currentRoot->value > value)
				{
					currentRoot = currentRoot->left;
				}
				else // currentRoot->value == value
				{
					return &(currentRoot->id);
				}
			}
		}
	}

	// 中序遍历树中的元素，并打印出来，这种方式以从小到大的方式打印
	void middlePrint()
	{
		middlePrint(root);
		std::cout << std::endl;
	}

	// 层序遍历，并打印出来，需要用到队列
	void floorPrint()
	{
		std::queue<Node* > que;
		que.push(root);

		while (!que.empty())
		{
			Node* node = que.front();
			std::cout << node->value << "   ";

			if (node->left)
			{
				que.push(node->left);
			}
			if (node->right)
			{
				que.push(node->right);
			}

			que.pop();
		}

		std::cout << std::endl;
	}

	// 搜索二叉树里的最小值
	Value getMinValue() const
	{
		Node* minNode = getMinNode(root);

		return minNode->value;
	}

	
	// 搜索二叉树里的最大值
	Value getMaxValue() const
	{
		Node* maxNode = getMaxNode(root);

		return maxNode->value;
	}

	// 删除最小值的节点
	void deleteMinValue()
	{
		Node* minNode = getMinNode(root);

		if (minNode->right == NULL)
		{
			destroy(minNode);
		}
		else // minNode->right != NULL
		{
			Node* parentNode = getParentNode(minNode);
			if (parentNode == NULL)
			{
				Node* temp = root->right;
				root->right = NULL;
				destroy(root);
				root = temp;
			}
			else // parentNode != NULL
			{
				parentNode->left = minNode->right;
				minNode->right = NULL;

				destroy(minNode);
			}
		}
	}

	// 删除最大值的节点
	void deleteMaxValue()
	{
		Node* maxNode = getMaxNode(root);

		if (maxNode->left == NULL)
		{
			destroy(maxNode);
		}
		else // maxNode->left != NULL
		{
			Node* parentNode = getParentNode(maxNode);
			if (parentNode == NULL)
			{
				Node* temp = root->left;
				root->left = NULL;
				destroy(root);
				root = temp;
			}
			else // parentNode != NULL
			{
				parentNode->right = maxNode->left;
				maxNode->left = NULL;

				destroy(maxNode);
			}
		}
	}

	// 删除某一个节点
	void deleteValue(Value value)
	{
		// 找不到这个元素的节点，元素可能不存在
		Node* node = findNodeOfValue(value);
		if (node == NULL)
		{
			return;
		}

		Node* parentNode = getParentNode(node);
		if (node->left == NULL)
		{
			if (parentNode == NULL)
			{
				root = node->right;
			}
			else // parentNode != NULL
			{
				if (parentNode->left == node)
				{
					parentNode->left = node->right;
				}
				else // parentNode->right == node
				{
					parentNode->right = node->right;
				}
			}

			node->right = NULL;
			destroy(node);
		}
		else if (node->right == NULL)
		{
			if (parentNode == NULL)
			{
				root = node->left;
			}
			else // parentNode != NULL
			{
				if (parentNode->left == node)
				{
					parentNode->left = node->left;
				}
				else // parentNode->right == node
				{
					parentNode->right = node->left;
				}
			}

			node->left = NULL;
			destroy(node);
		}
		else // node->left ！= NULL && node->right ！= NULL
		{
			Node* newChild = getMaxNode(node->right);
			Node* parent = getParentNode(newChild);
			parent->right = newChild->left;
			newChild->left = node->left;
			node->left = NULL;
			newChild->right = node->right;
			node->right = NULL;
			if (parentNode == NULL)
			{
				root = newChild;
			}
			else // parentNode != NULL
			{
				if (parentNode->left == node)
				{
					parentNode->left = newChild;
				}
				else // parentNode->right == node
				{
					parentNode->right = newChild;
				}
			}
			destroy(node);
		}
	}
	
private:
	struct Node
	{
		ID id;
		Value value;

		Node* left;
		Node* right;

		Node(ID id, Value value)
		{
			this->id = id;
			this->value = value;

			left = NULL;
			right = NULL;
		}
	};
	
	Node* root;
	int count;

	void middlePrint(Node* node)
	{
		if (node != NULL)
		{
			middlePrint(node->left);
			std::cout << node->value << "   ";
			middlePrint(node->right);
		}
	}

	// 析构函数需要，使用后序遍历的原理，把左右孩子都销毁了，才销毁节点
	void destroy(Node* node)
	{
		if (node != NULL)
		{
			destroy(node->left);
			destroy(node->right);

			Node* parentNode = getParentNode(node);
			if (parentNode != NULL)
			{
				if (parentNode->left == node)
				{
					parentNode->left = NULL;
				}
				else if (parentNode->right == node)
				{
					parentNode->right = NULL;
				}
			}

			delete node;
			count--;
		}
	}

	// 查找某一个节点的父节点，root 节点返回 NULL
	Node* getParentNode(Node* node) const
	{
		if (node == root)
		{
			return NULL;
		}
		else
		{
			Node* currentNode = root;

			while (currentNode != NULL)
			{
				if (currentNode->left == node || currentNode->right == node)
				{
					return currentNode;
				}
				else // currentNode 不是 node 的父节点
				{
					if (currentNode->value > node->value)
					{
						currentNode = currentNode->left;
					}
					else if (currentNode->value < node->value)
					{
						currentNode = currentNode->right;
					}
				}
			}
			return NULL;
		}
	}

	// 查找最小节点
	Node* getMinNode(Node* Root) const
	{
		if (Root == NULL)
		{
			std::cout << "这树里没东西。。。" << std::endl;
			exit(1);
		}

		Node* minNode = Root;

		while (minNode->left != NULL)
		{
			minNode = minNode->left;
		}

		return minNode;
	}

	// 查找最大节点
	Node* getMaxNode(Node* Root) const
	{
		if (Root == NULL)
		{
			std::cout << "这树里没东西。。。" << std::endl;
			exit(1);
		}

		Node* maxNode = Root;

		while (maxNode->right != NULL)
		{
			maxNode = maxNode->right;
		}

		return maxNode;
	}

	// 根据元素查找出所属的节点
	Node* findNodeOfValue(Value value)
	{
		if (isExisted(value) == false)
		{
			std::cout << "树里没有这个元素！" << std::endl;
			return NULL;
		}

		Node* node = root;
		while (node != NULL)
		{
			if (node->value == value)
			{
				return node;
			}

			if (node->value > value)
			{
				node = node->left;
			}
			else // node->value < value
			{
				node = node->right;
			}
		}

		return NULL;
	}
};