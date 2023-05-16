#include <iostream>
#include <string>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include "filters.h"
#include <thread>  
#include <atomic>  

#define BLACK 0

using namespace std;

// Filtro plano como ejemplo
void plain(ppm& img, unsigned char c){
	for(int i = 0; i < img.height; i++)
		for(int j = 0; j < img.width; j++)			
			img.setPixel(i, j, pixel(c,c,c));
}

void blackWhite(ppm& img, unsigned char c){
	for(int i = 0; i < img.height; i++)
		for(int j = 0; j < img.width; j++)	
		
			unsigned char red = img.pixels[i][j].red;
            unsigned char green = img.pixels[i][j].green;
            unsigned char blue = img.pixels[i][j].blue;

			img.setPixel(i, j, pixel(c,c,c));
}

// COMPLETAR :)


