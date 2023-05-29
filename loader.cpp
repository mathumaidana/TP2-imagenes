#include <iostream>
#include <string>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>
#include "filters.h"
#include <thread>
#include <unistd.h>
#include <fstream>

#define ONE_OVER_BILLION 1E-9

using namespace std;

// El siguiente es un template basico que pueden usar como base

int main(int argc, char *argv[])
{
	string filter = string(argv[1]);
	unsigned int n = atoi(argv[2]);
	float p1 = atof(argv[3]);
    string directorio = string(argv[4]);

    cout << directorio;
	// string img1(argv[4]);
	// ppm img(img1);

	return 0;
}