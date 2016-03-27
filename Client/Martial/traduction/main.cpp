#include <iostream>
#include "envoiAction.h"
#include <sstream>
#include <string>
using namespace std;

string to_String(int a)
{
    stringstream ss;
    ss<<a;
    return ss.str();
}

void decodeTypeMessage(std::string mess)
//envoie vers iTx avec x entre 0 et 6 inclus
{
    string mess_int = mess;
    int premiere_val = stoi(mess_int.substr(0,1));
    mess_int.erase(0,1);

    if ( premiere_val == 0)
    {
        //iT0(mess_int);
        cout << "Message : " << mess_int << ", envoye vers iT0" << endl;
    }

    else if ( premiere_val == 1 )
    {
        //iT1(mess_int);
        cout << "Message : " << mess_int << ", envoye vers iT1" << endl;
    }

     else if ( premiere_val == 2)
    {
        //iT2(mess_int);
        cout << "Message : " << mess_int << ", envoye vers iT2" << endl;
    }

     else if ( premiere_val == 3)
    {
        //iT3(mess_int);
        cout << "Message : " << mess_int << ", envoye vers iT3" << endl;
    }

     else if ( premiere_val == 4)
    {
        //iT4(mess_int);
        cout << "Message : " << mess_int << ", envoye vers iT4" << endl;
    }

     else if ( premiere_val == 5)
    {
        //iT5(mess_int);
        cout << "Message : " << mess_int << ", envoye vers iT5" << endl;
    }

     else if ( premiere_val == 6)
    {
        //iT6(mess_int);
        cout << "Message : " << mess_int << ", envoye vers iT6" << endl;
    }
}
void envAct( int num_coup, int act)
{
    string mess = "3" + to_String(ID_1)+ ";" + to_String(num_coup) + ";" + to_String(act);
    cout << "Message : " << mess << ", envoye par moi le client d'id = " << ID_1 << endl;
}

int main()
{
    /*
    cout << "---- Test unitaire pour envAct(int num_coup, int act), message de type T3 ---" << endl;
    envAct( 235, 25 );
    */


    cout << "---- Test unitaire pour decodeTypeMessage(std::string mess), envoye vers iTx avec x entre 0 et 6 inclus ---" << endl;
    decodeTypeMessage("0354138541");
    decodeTypeMessage("1354138541");
    decodeTypeMessage("2354138541");
    decodeTypeMessage("3354138541");
    decodeTypeMessage("4354138541");
    decodeTypeMessage("5354138541");
    decodeTypeMessage("6354138541");

    return 0;
}
