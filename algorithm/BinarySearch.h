#pragma once
#include <iostream>
#include <queue>

// �����ź��������� ���ֲ��ҷ�������Ԫ�ص�����
template<typename T>
int binarySearch(T arr[], int n, T target)
{
	int L = 0, R = n - 1;

	while (L <= R)
	{
		// ��ֹ�������
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

	// û���ҵ����� -1
	return -1;
}

// ����������
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

	// ����һ��Ԫ�ص�����
	void insert(ID id, Value value)
	{
		// �Ȱ���������ס
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

	// ���Ԫ���Ƿ����������
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

	// ���������һ��Ԫ��
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

	// ����������е�Ԫ�أ�����ӡ���������ַ�ʽ�Դ�С����ķ�ʽ��ӡ
	void middlePrint()
	{
		middlePrint(root);
		std::cout << std::endl;
	}

	// �������������ӡ��������Ҫ�õ�����
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

	// ���������������Сֵ
	Value getMinValue() const
	{
		Node* minNode = getMinNode(root);

		return minNode->value;
	}

	
	// ����������������ֵ
	Value getMaxValue() const
	{
		Node* maxNode = getMaxNode(root);

		return maxNode->value;
	}

	// ɾ����Сֵ�Ľڵ�
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

	// ɾ�����ֵ�Ľڵ�
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

	// ɾ��ĳһ���ڵ�
	void deleteValue(Value value)
	{
		// �Ҳ������Ԫ�صĽڵ㣬Ԫ�ؿ��ܲ�����
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
		else // node->left ��= NULL && node->right ��= NULL
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

	// ����������Ҫ��ʹ�ú��������ԭ�������Һ��Ӷ������ˣ������ٽڵ�
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

	// ����ĳһ���ڵ�ĸ��ڵ㣬root �ڵ㷵�� NULL
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
				else // currentNode ���� node �ĸ��ڵ�
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

	// ������С�ڵ�
	Node* getMinNode(Node* Root) const
	{
		if (Root == NULL)
		{
			std::cout << "������û����������" << std::endl;
			exit(1);
		}

		Node* minNode = Root;

		while (minNode->left != NULL)
		{
			minNode = minNode->left;
		}

		return minNode;
	}

	// �������ڵ�
	Node* getMaxNode(Node* Root) const
	{
		if (Root == NULL)
		{
			std::cout << "������û����������" << std::endl;
			exit(1);
		}

		Node* maxNode = Root;

		while (maxNode->right != NULL)
		{
			maxNode = maxNode->right;
		}

		return maxNode;
	}

	// ����Ԫ�ز��ҳ������Ľڵ�
	Node* findNodeOfValue(Value value)
	{
		if (isExisted(value) == false)
		{
			std::cout << "����û�����Ԫ�أ�" << std::endl;
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