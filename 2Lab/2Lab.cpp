#include <iostream>
#include <string>
#include <cmath>
#include <stack>
#include <map>
using namespace std;

template<class T>
struct Node {
	T data;
	Node* left, * right;
	float sum;
};

template<class T>
class BinaryTree
{
protected:
	Node<T>* root;

public:
	BinaryTree()
	{
		root = NULL;
	}

	void DelTree(Node<T>* root)
	{
		if (root != NULL)
		{
			DelTree(root->left);
			DelTree(root->right);
			delete root;
		}
	}

	void PrintTree(Node<T>* root, int r)
	{
		if (root != NULL)
		{
			PrintTree(root->right, r + 5);
			for (int i = 0; i < r; i++)
				printf(" ");
			printf("%s\n", root->data.c_str());
			PrintTree(root->left, r + 5);
		}
	}

	~BinaryTree()
	{
		DelTree(root);
	}

	Node<T>* CreateNode(string data)
	{
		Node<T>* ptr;
		ptr = new Node<T>;
		ptr->data = data;
		ptr->left = NULL;
		ptr->right = NULL;
		return ptr;
	}

	Node<T>* GetRoot()
	{
		return root;
	}

	void ReplaceRoot(Node<T>* NodeForReplace)
	{
		root = NodeForReplace;
	}


	virtual void CreateTree(string IPZstr) = 0;
	virtual void CountTree(Node<string>* r, float i1) = 0;
};

class MyBinaryTree : public BinaryTree<string>
{
	virtual void CreateTree(string IPZstr) override
	{
		std::string::size_type ind;
		//while ((ind = IPZstr.find(' ')) != std::string::npos) // удаление пробелов из входной строки
		//{
		//	IPZstr.erase(ind, 1);
		//}

		//Stack* StackObject = new Stack;

		stack<Node<string>*> StackObject;
		for (auto i = IPZstr.begin(); i != IPZstr.end(); i++)
		{
			if (*i == '+' || *i == '-' || *i == '*' || *i == '/')
			{
				string tmp_for_digit = "";
				tmp_for_digit += *i;
				auto tmp = CreateNode(tmp_for_digit);
				
				tmp->right = StackObject.top();
				StackObject.pop();

				tmp->left = StackObject.top();
				StackObject.pop();

				StackObject.push(tmp);

				//delete tmp;
			}
			else if(isalnum(*i))
			{
				string tmp_for_digit = "";
				tmp_for_digit += *i;
				while (isalnum(*i++))
				{
					if (*i == ' ' || *i == '+' || *i == '-' || *i == '*' || *i == '/')
					{
						*i--;
						break;
					}
					tmp_for_digit += *i;
				}
				StackObject.push(CreateNode(tmp_for_digit));
			}
		}
		root = StackObject.top();
		StackObject.pop();

	}

	virtual void CountTree(Node<string>* r, float i1) override
	{
		int q, l32;
		char l3[10], l4[10], l31[10], lz[1];

		bool flag = 0;

		if (r != NULL) {
			CountTree(r->left, i1);
			CountTree(r->right, i1);
		}
		else
			return;

		switch (r->data[0]) {
		case '0': {
			r->sum = stof(r->data); break;
		}
		case '1': {
			r->sum = stof(r->data); break;
		}
		case '2': {
			r->sum = stof(r->data); break;
		}
		case '3': {
			r->sum = stof(r->data); break;
		}
		case '4': {
			r->sum = stof(r->data); break;
		}
		case '5': {
			r->sum = stof(r->data); break;
		}
		case '6': {
			r->sum = stof(r->data); break;
		}
		case '7': {
			r->sum = stof(r->data); break;
		}
		case '8': {
			r->sum = stof(r->data); break;
		}
		case '9': {
			r->sum = stof(r->data); break;
		}
		case 't': {
			r->sum = tan(r->right->sum);
			break;
		}
		case 'c': {
			r->sum = cos(r->right->sum);
			break;
		}
		case 's': {
			if (r->data[1] == 'i')
				r->sum = sin(r->right->sum);
			if (r->data[1] == 'q')
				r->sum = sqrt(r->right->sum);
			break;
		}
		case 'l': {
			r->sum = log(r->right->sum);
			break;
		}
		case 'x': {
			r->sum = i1; break;
		}
		case '+': {
			r->sum = r->left->sum + r->right->sum;
			break;
		}
		case '-': {
			r->sum = r->left->sum - r->right->sum;
			break;
		}
		case '*': {
			r->sum = r->left->sum * r->right->sum;
			break;
		}
		case '/': {
			r->sum = r->left->sum / r->right->sum;
			break;
		}
				flag = 1;
		}
	}
};

// создаёт ОПЗ из строки
std::string RPN(std::string str)
{
	std::string srpn;

	std::string::size_type ind;
	while ((ind = str.find(' ')) != std::string::npos) // удаление пробелов из входной строки
	{
		str.erase(ind, 1);
	}

	for (int i = 0; i < str.size(); ++i) // учёт отрицательных чисел
	{
		if ((str[i] == '+' || str[i] == '-') && (0 == i || (!isalnum(str[i - 1]) && str[i - 1] != '.' && str[i - 1] != ')')))
		{
			auto it = std::find_if(str.begin() + i + 1, str.end(), [](char const c) {return !isalnum(c); });
			str.insert(it, ')');
			str.insert(i, "(0");
			int nnn = 0;
		}
	}

	std::cout << str << std::endl;

	std::map<char, size_t> map; // карта весов символов
	map.insert(std::make_pair('*', 3));
	map.insert(std::make_pair('/', 3));
	map.insert(std::make_pair('+', 2));
	map.insert(std::make_pair('-', 2));
	map.insert(std::make_pair('(', 1));
	std::stack<char> stack;
	for (auto c : str) // формировка результирующей строки в ОПЗ
	{
		if (!isalnum(c) && ('.' != c))
		{
			srpn += ' ';
			if (')' == c)
			{
				while (stack.top() != '(')
				{
					srpn += stack.top();
					stack.pop();
					srpn += ' ';
				}
				stack.pop();
			}
			else if ('(' == c)
			{
				stack.push(c);
			}
			else if (stack.empty() || (map[stack.top()] < map[c]))
			{
				stack.push(c);
			}
			else
			{
				do
				{
					srpn += stack.top();
					srpn += ' ';
					stack.pop();
				} while (!(stack.empty() || (map[stack.top()] < map[c])));
				stack.push(c);
			}
		}
		else
		{
			srpn += c;
		}
	}
	while (!stack.empty())// остаток из стека добавляется в результ. строку
	{
		srpn += stack.top();
		srpn += ' ';
		stack.pop();
	}
	//std::cout << srpn << std::endl; // результирующая строка в ОПЗ

	return srpn;
}

int main()
{
	std::string str;
	std::cin >> str;
	std::string srpn = RPN(str);
	std::cout << "RPN: " << srpn << std::endl; // результат обратной польской записи

	BinaryTree<string>* MyTree = new MyBinaryTree();
	MyTree->CreateTree(srpn);
	MyTree->PrintTree(MyTree->GetRoot(), 0);
	MyTree->CountTree(MyTree->GetRoot(), 0);
	std::cout << std::endl << MyTree->GetRoot()->sum;
	return 0;
}