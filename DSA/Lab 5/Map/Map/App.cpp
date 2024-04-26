#include "ExtendedTest.h"
#include "ShortTest.h"

#include "Map.h"


#include <iostream>
using namespace std;


int main() {
	cout << "Short test" << endl;
	testAll();
	testAllExtended();

	cout << "That's all!" << endl;
	system("pause");
	return 0;
}


