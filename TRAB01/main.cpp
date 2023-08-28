#include "vect_lib.hpp"

class	UserData
{
	public:
		string name;
		string rg;
		// UserData(string name, string rg) : name(name), rg(rg) {}
};

class	Node
{
	public:
		Node *next;
		Node *prev;
		UserData data;
		Node(UserData userData) : data(userData), next(nullptr), prev(nullptr) {}
};

class	Linkedlist
{
	private:

	public:
		Node* head;
		Node* tail;
		unsigned int count;
		Linkedlist() : head(nullptr), tail(nullptr), count(0) {}

	void insertNode(UserData userData, int flag = -1)
	{
		Node* newNode = new Node(userData);
		if (count == 0)
		{
				tail = newNode;
				head = newNode;
		}
		if (flag == 0)
		{
			newNode->next = this->head;
			head = newNode;
		}
		else if (flag == -1)
		{
			this->tail->next = newNode;
			newNode->prev = this->tail;
			this->tail = newNode;
		}

		count++;
	}

	void deleteNode(UserData userData)
	{
		Node* current = head;
		Node* previous = nullptr;

		while(current != nullptr)
		{
			// if(current->data.name == userData.name && current->data.rg == userData.rg)


		}
	};

	void printList()
	{
		Node* current = head;
		while(current != nullptr)
		{
			cout << "Nome: " << current->data.name << endl << "RG: " << current->data.rg << endl;
			current = current->next;
		}
	}
};

int	main()
{
	UserData data;
	UserData mariaclara { "maria clara", "123456" };
	UserData data1 { "ana laura", "2345678" };
	UserData data2 { "fernanda", "09909090" };
	data.name = "Joao Pedro";
	data.rg = "123456789";
	Node node(data);
	Linkedlist lk;

	lk.insertNode(mariaclara, 0);
	lk.insertNode(data);
	lk.insertNode(data1);
	lk.insertNode(data1);
	lk.insertNode(data2);

	// cout << lk.count << endl;
	// cout << lk.tail->data.name << endl;
	// cout << lk.head->data.name;
	lk.printList();
}