#include <tuple>
#include <iostream>

using namespace std;

int main()
{
	tuple<int, int> x;

	x = make_tuple(10, 11);
	cout << get<0>(x);
}