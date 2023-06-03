#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>
#include <thread>
#include <unistd.h>
#include <fstream>
#include "aplicar.h"
#include "ppm.h"

#define ONE_OVER_BILLION 1E-9

using namespace std;

// El siguiente es un template basico que pueden usar como base

int main(int argc, char *argv[])
{

	// Asumimos que los filtros sin p1 se escriben primero (por lo tanto, el primer p1 es no nulo)
	// Asumimos que Zoom no se puede encadenar

	if (string(argv[1]) == "-help")
	{
		cout << "Uso: ./main <filtro> <nthreads> <[p1]> <img1> <custom_output> <[p2]> <img2>" << endl;
		return 0;
	}
	string filter = string(argv[1]);
	unsigned int n = atoi(argv[2]);
	float p1 = atof(argv[3]);
	string img(argv[4]);
	string out = string(argv[5]);
	

	

	if (argv[6]) {
		string img2_string(argv[6]);
		ppm img2(img2_string);
		aplicar(filter, p1, img, n, out, img2);
	} else {
		aplicar(filter, p1, img, n, out, img);
	}
	return 0;
}