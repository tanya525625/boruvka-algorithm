#include "Header.h"

int main()
{
	int initCountV = 100;
	int finCountV = 100000;
	int n = 10;
	int delta = (finCountV-initCountV)/n;
	int deltaE = 1000;
	test(initCountV, delta, finCountV, deltaE);
	//cout << "HI" << endl;
	/*int V = 1000;
	int E = 15000;
	int delta = 10000;
	test2(V, E, delta);*/
	
	system("pause");
	return 0;
}

