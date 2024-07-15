#include "lib.h"
#include <iostream>

int main()
{
	setlocale(LC_ALL, 0);
	std::cout << version() << std::endl;
	std::cout << "Это историческое событие для всей отечественной IT-индустри \n";

	return 0;
}
