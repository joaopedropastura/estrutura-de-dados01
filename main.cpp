#include <iostream>
#include <string>
#include <fstream>
#include <tuple>
#include <vector>

using namespace std;

const string file1 = "NomeRG10.txt";
const string file2 = "NomeRG1M.txt";
const string file3 = "NomeRG100M.txt";

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
  return make_tuple(name, nrg);
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

int main() {
  vector<tuple <string, int>> result = {};


  Manipulate *lista = new Manipulate(&result);
  result = readFile(file1);
  for (auto elem : result) 
  {
    int num = get<1>(elem);
    string str = get<0>(elem);
    cout << str << "," << num << endl;
  }

  // int num;
  // string nome;
  // tie(nome, num) = result[0];
  // cout << get<1>(result[0]);
}
