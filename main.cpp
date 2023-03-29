#include "vectlib.h"

class Manipulate
{
  private: 
    vector<tuple <string, int>> result = {};

  public:
    Manipulate(vector<tuple <string, int>> temp)
    {
      this -> result = temp;
    }      
    void insert(string value, int index)
    {
      tuple<string, int>nValue = makeTuple(value);
      bool flag = false;
      for (int i = 0; i < result.size() + 1; i++) 
      {
        
        auto temp = result[i - 1];
        if (i >= index)
        {
          if(i == index)
          {
            result.resize(result.size() + 1);
            result[i] = nValue;
            flag = true;
          }
          else
           result[i] = flag ? temp : result[i];
          // temp[i] = result[flag ? i-1 : i];
        // i == index ? temp[i] = nValue : temp[i] = result[i] ;
        }
      }
    }
    vector<tuple <string, int>> getVect()
    {
      return result;
    }
};

// vector<t         le <string, int>> insert(vector<tuple <string, int>> temp, int index = 0)
// {
  
// }
int main() {

  vector<tuple <string, int>> result = {};
  result = readFile(file1);
  Manipulate m(result);
  m.insert("joao paulo,10009943", 3);
  int x  = menu();
  cout << x;
  createFile("resultado", m.getVect());
  // for (auto elem : result) 
  // {
  //   int num = get<1>(elem);
  //   string str = get<0>(elem);
  //   cout << str << "," << num << endl;
  // }
}
