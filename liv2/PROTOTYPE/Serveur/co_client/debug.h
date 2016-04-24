#ifndef DEBUG_E
#define DEBUG_E

#include <iostream>
#include <string>

void debug(std::string mess, bool stop = false,bool cont=false);
void debug(bool a, std::string nom);
std::string coupeChaine(std::string &ch, char a);


#endif // !debug