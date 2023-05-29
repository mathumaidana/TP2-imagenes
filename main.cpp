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

	if (filter == "plain") {
		if (p1 < 0 || p1 > 255) {
			cout << "El parametro debe ser menor o igual a 255 y mayor o igual a 0" << endl;
			return 0;
		}
		if (n >= 2) multiPlain(img, (unsigned char)p1, n);
		else plain(img, (unsigned char)p1);
	}
	else if (filter == "blackWhite") {
		if (n >= 2) multiBlackWhite(img, n);
		else blackWhite(img);
	}
	else if (filter == "shades") {
		if (p1 < 1) {
			cout << "El parametro debe ser un numero entero mayor o igual a 1" << endl;
			return 0;
		}
		if (n >= 2) multiShades(img, (unsigned char)p1, n);
		else shades(img, (unsigned char)p1);
	}
	else if (filter == "contrast") {
		if (p1 < 0 || p1 > 1) {
			cout << "El parametro debe ser un numero decimal 0 / 1" << endl;
			return 0;
		}
		if (n >= 2) multiContrast(img, p1, n);
		else contrast(img, p1);
	}
	else if (filter == "brightness") {
		if (p1 -1 || p1 > 1) {
			cout << "El parametro debe ser un decimal entre -1 / 1" << endl;
			return 0;
		}
		if (n >= 2) multiBrightness(img, p1, -1, 1, n);
		else brightness(img, p1, -1, 1);
	}
	else if (filter == "boxBlur") {
		if (n >= 2) multiBoxBlur(img, n);
		else boxBlur(img);
	}
	else if (filter == "sharpen") {
		if (n >= 2) multiSharpen(img, n);
		else sharpen(img);
	}
	else if (filter == "edgeDetection") {
		if (n >= 2) multiEdgeDetection(img, n);
		else edgeDetection(img);
	}
	else if (filter == "merge") {
		string img2_string(argv[7]);
		ppm img2(img2_string);
		float p2 = atof(argv[6]);
		if (p1 < 0 || p1 > 1) {
			cout << "El parametro debe estar entre 0 / 1";
			return 0;
		}
		if (img.height != img2.height || img.width != img2.width) {
			cout << "Las imagenes deben tener las mismas dimensiones";
			return 0;
		}
		if (n >= 2) multiMerge(img, img2, p1, n);
		else merge(img, img2, p1);
	}
	else if (filter == "gradiente") {
		if(p1 != 0 || p1 != 1) {
			cout << "El parametro debe ser 0 / 1";
			return 0;
		}
		gradiente(img, p1);
	}
	else {
		cout << "Filtro no existe..." << endl;
		return 0; 
	}

	cout << "Escribiendo imagen" << endl;
	img.write(out);

	cout << "Listo" << endl;
	return 0;
}