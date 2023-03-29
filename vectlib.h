#ifndef VECTLIB_H

#define VECTLIB_H

#include <iostream>
#include <string>
#include <fstream>
#include <tuple>
#include <vector>

using namespace std;

#define file1 "NomeRG10.txt"
#define file2 "NomeRG1M.txt"
#define file3 "NomeRG100M.txt"

void addVector(tuple<string, int> value, vector<tuple <string, int>> &temp);
tuple <string, int> makeTuple (string line);
vector<tuple <string, int>> readFile(string fileName);
int menu();
void createFile(string name, vector<tuple <string, int>> temp);


#endif
