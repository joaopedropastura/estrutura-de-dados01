#include "vectlib.h"

tuple <string, int> makeTuple (string line)
{
  int i = -1, flag = 0;
  string name = "", rg = "";
  while (line[++i] != '\0')
  {
    if (line[i] == ',') 
    {
      flag++;
      i++;
    } 
    flag == 0 ? name += line[i] : rg += line[i];
  }
  flag--;
  int nrg = stoi(rg);
  return tuple<string, int>(name, nrg);
}

void addVector(tuple<string, int> value, vector<tuple <string, int>> &temp)
{
  temp.resize(temp.size() + 1);
  temp[temp.size() - 1] = value;
}

vector<tuple <string, int>> readFile(string fileName)
{
  vector <tuple <string, int>> vet;
  ifstream myFile(fileName);
  string fileContent, line, tempLine = "";
  
  if (myFile.is_open())
  {
    while (!myFile.eof())
    {
      int i = -1;
      getline(myFile, line);
      if (line[0] == '\0' || line[0] == '\n')
        break;
      while (line[++i] != '\0')
        tempLine += line[i];
      addVector(makeTuple(tempLine), vet);
      tempLine = "";
    }
  }
  myFile.close();
  return vet;
}

void getName(int rg, string file)
{
  vector<tuple<string, int>> result = {};
  result = readFile(file);
  int flag = 0;
  for (auto elem : result) 
  {
    int num = get<1>(elem);
    string str = get<0>(elem);
    if (num == rg)
    { 
      cout << str << endl;
      flag++;
    }
  }
  if (!flag)
    cout << "nenhuma ocorrencia encontrada!";
}

void getValue(string nome, string file)
{
  vector<tuple<string, int>> result = {};
  result = readFile(file);
  int flag = 0;
  for (auto elem : result) 
  {
    int num = get<1>(elem);
    string str = get<0>(elem);
    if (str == nome)
    {
      cout << num << endl;
      flag++;
      break;
    }
  }
  if (!flag)
    cout << "nenhuma ocorrencia encontrada!\n";
}

void addLinkedList (vector<tuple <string, int>> temp, linkedList *list)
{
  for (auto elem : temp)
  {
    int num = get<1>(elem);
    string name = get<0>(elem);
    list->addNode(num, name);
  }
}

int menu()
{
  int option = 0;
  cout <<"\nTRABALHO 01" << '\n';
  cout << "----- DIGITE O NUMERO DA OPÇÂO DESEJADA -----" << '\n';
  cout << "{00} - Para encerrar o programa " << '\n';

  cout << "{01} - Buscar um nome a partir de um RG: " << '\n';
  cout << "{02} - Buscar um RG a partir de um NOME: " << '\n';
  cout << "{03} - Inserir uma amostra no incio: " << '\n';
  cout << "{04} - Remover uma amostra no incio: " << '\n';
  cout << "{05} - Inserir uma amostra no fim: " << '\n';
  cout << "{06} - Remover uma amostra no fim: " << '\n';
  cout << "{07} - Inserir uma amostra em uma posição: " << '\n';
  cout << "{08} - Remover uma amostra em uma posição: " << '\n';
  cout << "{09} - Imprimir lista " << '\n';

  cin >> option;
  return option;
}

void createFile(string name, vector<tuple <string, int>> temp)
{
  ofstream myfile (name + ".txt");
  for (auto elem : temp) 
  {
    int num = get<1>(elem);
    string str = get<0>(elem);
    myfile << str << "," << num << endl;
  }
}


ordenateList::ordenateList(vector<tuple<string, int>> temp) { this->result = temp; }
void ordenateList::insert(string value, int index)
{
  if (index == -1)
    index = result.size();
  tuple<string, int> nValue = makeTuple(value);
  result.resize(result.size() + 1);
  for (int i = result.size() - 1; i >= index; i--) 
    result[i] = i != index ? result[i - 1] : nValue;
}
void ordenateList::remove(int index)
{
  if (index == -1)
    index = result.size();
  for (int i = index; i <= index; i++) 
    result[i] = result[i + 1];
  result.resize(result.size() - 1);
}
vector<tuple<string, int>> ordenateList::getVect() { return result; }

linkedList::linkedList() { this->head = nullptr; };

void linkedList::addNode(int rg, string nome)
{
  Node *node = new Node(rg, nome);
  if(head == nullptr)
    head = node;
  else
  {
    Node *current = head;
    while (current->next != nullptr)
      current = current->next;
    current->next = node;
  }
}

void linkedList::removeNode(int rg)
{
  if (head == nullptr) return;
  if (head->rg == rg)
  {
    Node *tmp = head;
    head = head->next;
    delete tmp;
  }
  else
  {
    Node *current = head;
    while (current->next != nullptr && current->next->rg != rg)
      current = current->next;
    if (current->next != nullptr)
    {
      Node *tmp = current->next;
      current->next = current->next->next;
      delete tmp;
    }
  }
}

void linkedList::print() 
{
    Node* current = head;
    while (current != nullptr) 
    {
      cout << current->rg << " " << current->nome << endl;
      current = current->next;
    }
    cout << endl;
}
