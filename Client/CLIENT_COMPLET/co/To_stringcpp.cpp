#include "toString.h"

using namespace std;
string to_string(int a)
{
	stringstream ss;
	ss << a;
	return ss.str();
}