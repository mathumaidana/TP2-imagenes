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

	unsigned int numThreads = std::thread::hardware_concurrency();
	cout << numThreads;
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
	string img1(argv[4]);
	string out = string(argv[5]);
	ppm img(img1);

	cout << "Aplicando filtros" << endl;

	if (filter == "plain")
	{
		if (n == 1)
		{
			plain(img, (unsigned char)p1);
		}
		else
		{
			multiPlain(img, (unsigned char)p1, n);
		}
	}
	else if (filter == "blackWhite")
	{
		if (n == 1)
		{
			blackWhite(img);
		}
		else
			multiBlackWhite(img, n);
	}
	else if (filter == "shades")
	{
		if (n == 1)
		{
			shades(img, (unsigned char)p1);
		}
		else
		{
			multiShades(img, (unsigned char)p1, n);
		}
	}
	else if (filter == "contrast")
		if (n == 1)
		{
			contrast(img, p1);
		}
		else
		{
			multiContrast(img, p1, n);
		}
	else if (filter == "brightness")
		if (n == 1)
		{
			brightness(img, p1, -1, 1);
		}
		else
		{
			multiBrightness(img, p1, -1, 1, n);
		}
	else if (filter == "boxBlur")
		if (n == 1)
		{
			boxBlur(img);
		}
		else
		{
			multiBoxBlur(img, n);
		}
	else if (filter == "sharpen")
		if (n == 1)
		{
			sharpen(img);
		}
		else
		{
			multiSharpen(img, n);
		}
	else if (filter == "edgeDetection")
		if (n == 1)
		{
			edgeDetection(img);
		}
		else
		{
			multiEdgeDetection(img, n);
		}
	else if (filter == "merge")
	{
		string img2_string(argv[7]);
		ppm img2(img2_string);
		float p2 = atof(argv[6]);
		if (n == 1)
		{
			merge(img, img2, p1);
		}
		else
		{
			multiMerge(img, img2, p1, n);
		}
	}

	cout << "Escribiendo imagen" << endl;
	img.write(out);

	cout << "Listo" << endl;
	return 0;
}