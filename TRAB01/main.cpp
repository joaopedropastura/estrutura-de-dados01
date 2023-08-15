#include "vect_lib.hpp"

class	UserData
{
	public:
		string rg;
		string name;
};

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
		Node* head;

	public:
		Linkedlist() : head(nullptr) {}

	void insertNode(UserData userData)
	{
		Node* newNode = new Node(userData);
		newNode->next = this->head;
		head = newNode;
	}

	void deleteNode(UserData userData)
	{
		Node* current = head;
		Node* previous = nullptr;

		while(current != nullptr)
		{
			
		}
	};

	void printList()
	{
		Node* current = head;
		while(current != nullptr)
		{
			cout << "Nome: " << current->data.name << endl << "RG: " << current->data.rg;
			current = current->next;
		}
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
	// SequentialList *sl = sl[(SequentialList)malloc(n * sizeof(SequentialList))];

	// if(file.is_open())
	// 	while(file.good())
	// 	{
	// 		file >> string_line;
	// 		cout << string_line + '\n';
	// 	}
	UserData data;
	UserData mariaclara;

	UserData data1{"ana laura", "2345678"};

	mariaclara.name = "maria clara";
	mariaclara.rg = "123456";

	data.name = "Joao Pedro";
	data.rg = "123456789";
	Node node(data);

	Linkedlist lk;


	lk.insertNode(mariaclara);
	lk.insertNode(data);
	lk.insertNode(data1);

	lk.printList();



	// SequentialList sl;
	// SequentialList ll;
}