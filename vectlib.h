#ifndef VECTLIB_H

#define VECTLIB_H

#include <iostream>
#include <string>
#include <fstream>
#include <tuple>
#include <vector>
#include <chrono>

using namespace std;
using namespace chrono;

#define file1 "NomeRG1M.txt"
#define file2 "NomeRG10K.txt"
#define file3 "NomeRG100M.txt"

class Node
{
  public:
    int rg;
    string nome;
    Node *next;
  Node(int rg, string nome)
  {
    this->rg = rg;
    this->nome = nome;
    this->next = nullptr;
  }
};

class ordenateList 
{
  public:
    ordenateList(vector<tuple<string, int>> temp);
    void insert(string value, int index = 0);
    void remove(int index = 0);
    vector<tuple<string, int>> getVect();
  private:
    vector<tuple<string, int>> result = {};
};

class linkedList
{
  public: 
    Node *head;
    linkedList();
    void addNode(int rg, string nome);
    void removeNode(int rg);
    void print();
};

int menu();
void getName(int rg, string file);
void getValue(string name, string file);
tuple <string, int> makeTuple (string line);
vector<tuple <string, int>> readFile(string fileName);
void createFile(string name, vector<tuple <string, int>> temp);
void addLinkedList (vector<tuple <string, int>> temp, linkedList *list);
void addVector(tuple<string, int> value, vector<tuple <string, int>> &temp);
#endif
