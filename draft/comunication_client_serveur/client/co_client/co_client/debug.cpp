#include "debug.h"

using namespace std;


void debug(string mess, bool stop )
{
	if (true)
		cout << mess << endl;
	if (stop)
		system("pause");
}

string coupeChaine(string &ch, char a)
{
	int p = ch.find(a);
	cout << "init= " + ch + " coupeA= " + a + " length= " + to_string(ch.length()) + " pos= " + to_string(p) << endl;
	if (p == string::npos)
		return "";
	else
	{

		string r = ch.substr(0, p);
		cout << "substr= " + r << endl;
		ch.erase(0, p + 1);
		cout << "coupee= " + ch << endl;
		return r;
	}

}

