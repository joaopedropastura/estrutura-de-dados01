#include "vectlib.h"

class Manipulate
{
  vector<tuple <string, int>> result = {};
  
  public:
    Manipulate(vector<tuple <string, int>> temp)
    {
      this -> result = temp;
    }      
    static vector<tuple <string, int>> insert(tuple <string, int>, int index = 0)
    {
      vector<tuple <string, int>> temp = {}; 
      return temp;
    }
};

void addVector(tuple<string, int> value, vector<tuple <string, int>> &temp)
{
  temp.resize(temp.size() + 1);
  temp[temp.size() - 1] = value;
}

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

vector<tuple <string, int>> readFile(string fileName)
{
  vector<tuple <string, int>> vet;
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

int menu()
{
  int option = 0;
  cout <<"TRABALHO 01" << '\n';
  cout << "----- DGITE O NUMERO DA OPÇÂO DESEJADA -----" << '\n';
  cout << "{01} - Buscar um nome a partir de um RG: " << '\n';
  cout << "{02} - Buscar um RG a partir de um NOME: " << '\n';
  cout << "{03} - Inserir uma amostra no incio: " << '\n';
  cout << "{04} - Remover uma amostra no incio: " << '\n';
  cout << "{05} - Inserir uma amostra no fim: " << '\n';
  cout << "{06} - Remover uma amostra no fim: " << '\n';
  cout << "{07} - Inserir uma amostra em uma posição: " << '\n';
  cout << "{08} - Remover uma amostra em uma posição: " << '\n';
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
vector<tuple <string, int>> insert(vector<tuple <string, int>> temp, int index = 0)
{
  
}


int main() {

  int x = menu();
  cout << x;
  vector<tuple <string, int>> result = {};
  result = readFile(file1);
  createFile("resultado", result);
  // for (auto elem : result) 
  // {
  //   int num = get<1>(elem);
  //   string str = get<0>(elem);
  //   cout << str << "," << num << endl;
  // }
}
