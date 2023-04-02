#include "vectlib.h"

void resizeVector(vector<tuple<string, int>> &vetor, int flag = 1)
{
  // vetor = (vector)realloc( vetor, sizeof(vector<tuple<string, int>>));
}

class Manipulate {
private:
  vector<tuple<string, int>> result = {};

public:
  Manipulate(vector<tuple<string, int>> temp) { this->result = temp; }

  void insert(string value, int index = 0)
  {
    tuple<string, int> nValue = makeTuple(value);
    result.resize(result.size() + 1);
    for (int i = result.size() - 1; i >= index; i--) 
      result[i] = i != index ? result[i - 1] : nValue;
  }

  void remove(int index = 0)
  {
    for (int i = index; i <= index; i++) 
      result[i] = result[i + 1];
    result.resize(result.size() - 1);
  }
  vector<tuple<string, int>> getVect() { return result; }
};

int main() {
  int x = menu();
  cout << x;
  
  auto start = high_resolution_clock::now(); 
  vector<tuple<string, int>> result = {};
  result = readFile(file1);
  Manipulate m(result);
  m.insert("joao paulo,11009943", 1);
  // m.remove(0);
  createFile("resultado", m.getVect());
  auto end = high_resolution_clock::now();
  duration<double> duration = end - start;
  cout << "Tempo de execução: " << duration.count() << " segundos" << endl;

}
