#include "vect_lib.hpp"

class	UserData
{
	public:
		string rg;
		string name;
};

// class	Node
// {
// 	Node *next;
// 	public:
// 		Node(string name, string rg)
// 		{
// 			this->user_data.name = name;
// 			this->user_data.rg = rg;
// 			this->next = NULL;
// 		}
// 	private:
// 		UserData user_data;
// };

class	Node
{
	public:
		Node *next;
		UserData data;
		Node(UserData userData) : data(userData), next(nullptr) {}
};
class	Linkedlist
{
	private:
		Node *head;

	public:
		Linkedlist() { this->head = NULL; }

	void insertNode(UserData userData)
	{
		Node 
	}
};

// void LinkedList :: DeleteNode(UserData userData)
// {

// }


int	main()
{
	string fileName = "NomeRG10.txt";
	ifstream file (fileName);
	string string_line;
	int n = 1;
	// SequentialList *sl[] = sl[(SequentialList)malloc(n * sizeof(SequentialList))];

	if(file.is_open())
		while(file.good())
		{
			file >> string_line;
			cout << string_line + '\n';
		}
	UserData data;

	data.name = "Joao Pedro";
	data.rg = "123456789";
	Node node(data);

	cout << node.data.name;

	// SequentialList sl;
	// SequentialList ll;
}