#include "vectlib.h"

void checkTime()
{
  vector<tuple<string, int>> result = {};

  auto start = high_resolution_clock::now();

  auto end = high_resolution_clock::now();
  duration<double> duration = end - start;
  cout << "Tempo de execução: " << duration.count() << " segundos" << endl;
}

void menuFile()
{
  cout << "----- DIGITE O NUMERO DO ARQUIVO DESEJADO -----\n";
  cout << "{00} - Para encerrar o programa " << '\n';
}

string chooseFile()
{
  
}

int main() {  
  
  vector<tuple<string, int>> result = {};
  string file =  file1;
  linkedList list;
  string name;
  int rg;
  
  result = readFile(file);
  auto start = high_resolution_clock::now();
  addLinkedList(result, &list);
  auto end = high_resolution_clock::now();
  duration<double> duration = end - start;
  cout << "Tempo de execução (LISTA ENCADEADA)  : " << duration.count() << " segundos" << endl;
  // start = high_resolution_clock::now();
  ordenateList m(result);
  // end = high_resolution_clock::now();
  // duration = end - start;
  // cout << "Tempo de execução (LISTA SEQUENCIAL) : " << duration.count() << " segundos" << endl;
  switch (menu())
  {
    case 0:
      break;
    case 1:
      cin >> rg;
      start = high_resolution_clock::now();
      getName(rg, file);
      end = high_resolution_clock::now();
      duration = end - start;
      cout << "Tempo de execução: " << duration.count() << " segundos" << endl;
      menu();
    case 2:
      cin >> name;
      start = high_resolution_clock::now();
      getValue(name, file);
      end = high_resolution_clock::now();
      duration = end - start;
      cout << "Tempo de execução: " << duration.count() << " segundos" << endl;
      menu();
    case 3:
      cin >> name;
      start = high_resolution_clock::now();
      m.insert(name, 0);
      end = high_resolution_clock::now();
      duration = end - start;
      cout << "Tempo de execução: " << duration.count() << " segundos" << endl;
      menu();
    case 4:
      cin >> name;
      start = high_resolution_clock::now();
      m.remove(0);
      end = high_resolution_clock::now();
      duration = end - start;
      cout << "Tempo de execução: " << duration.count() << " segundos" << endl;
      menu();
    case 5:
      cin >> name;
      start = high_resolution_clock::now();
      m.insert(name, -1);
      end = high_resolution_clock::now();
      duration = end - start;
      cout << "Tempo de execução: " << duration.count() << " segundos" << endl;
      menu();
    case 6:
      cin >> name;
      start = high_resolution_clock::now();
      m.remove(-1);
      end = high_resolution_clock::now();
      duration = end - start;
      cout << "Tempo de execução: " << duration.count() << " segundos" << endl;
      menu();
     case 7:
      cin >> name;
      cin >> rg;
      start = high_resolution_clock::now();
      m.insert(name, rg);
      end = high_resolution_clock::now();
      duration = end - start;
      cout << "Tempo de execução: " << duration.count() << " segundos" << endl;
      menu();
    case 8:
      cin >> rg;
      start = high_resolution_clock::now();
      m.remove(rg);
      end = high_resolution_clock::now();
      duration = end - start;
      cout << "Tempo de execução: " << duration.count() << " segundos" << endl;
      menu();
    case 9:
      list.print();
      menu();
    
  }
  createFile("resultado", m.getVect());
  end = high_resolution_clock::now();
  duration = end - start;
  cout << "Tempo de execução: " << duration.count() << " segundos" << endl;
}
