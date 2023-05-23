#include <iostream>
#include <string>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include "filters.h"
#include <thread>  
#include <atomic>  
#include "ppm.h"
#include <chrono>

#define BLACK 0

using namespace std;

// Filtro plano como ejemplo
void plain(ppm& img, unsigned char c){
 	std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();

	for(int i = 0; i < img.height; i++)
		for(int j = 0; j < img.width; j++)			
			img.setPixel(i, j, pixel(c,c,c));
	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now(); // Fin del timer
    std::chrono::duration<double> duration = end - start; // Duración en segundos

    std::cout << "Duración: " << duration.count() << " segundos" << std::endl;
}

void printIteration(int iteration, int pixeles, ppm& img, unsigned char c) {
	for(int i = iteration * pixeles; i < pixeles * (iteration + 1); i++)
		for(int j = 0; j < img.width; j++)			
			img.setPixel(i, j, pixel(c,c,c));
}

void multiPlain(ppm& img, unsigned char c, unsigned int n){
    std::vector<std::thread> threads;
 	std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
	int pixeles = img.height / n;
	int resto = img.height % n;

 	for (int i = 0; i < n; ++i) {
		if (i == threads.size() - 1) {
        threads.emplace_back(printIteration, i, pixeles + resto, std::ref(img), c);
		}
        threads.emplace_back(printIteration, i, pixeles, std::ref(img), c);
    }

	for (std::thread& thread : threads) {
        thread.join();
    }

	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now(); // Fin del timer
    std::chrono::duration<double> duration = end - start; // Duración en segundos

    std::cout << "Duración: " << duration.count() << " segundos" << std::endl;
}

void brightness(ppm &img, float b, int start, int end)
{
	for (int i = 0; i < img.height; i++)
	{
		for (int j = 0; j < img.width; j++)
		{
		pixel p = img.getPixel(i, j);
		int brillo = static_cast<int>(p.r * b);
		int r = min(p.r + brillo, 255);
		int g = min(p.g + brillo, 255);
		int b = min(p.b + brillo, 255);

		img.setPixel(i, j, pixel(r, g, b));
		}
	}
}

void contrast(ppm &img, float contrast)
{
	std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();

	for (int i = 0; i < img.height; i++)
	{
		for (int j = 0; j < img.width; j++)
		{
		pixel p = img.getPixel(i, j);

		int r_prima = p.r - 128;
		int g_prima = p.g - 128;
		int b_prima = p.b - 128;

		float f = (259 * (contrast + 255)) / (255 * (259 - contrast));

		float nuevo_r = f * r_prima + 128;
		float nuevo_g = f * g_prima + 128;
		float nuevo_b = f * b_prima + 128;

		if (nuevo_r < 0)
		{
			nuevo_r = 0;
		}
		else if (nuevo_r > 255)
		{
			nuevo_r = 255;
		}

		if (nuevo_g < 0)
		{
			nuevo_g = 0;
		}
		else if (nuevo_g > 255)
		{
			nuevo_g = 255;
		}

		if (nuevo_b < 0)
		{
			nuevo_b = 0;
		}
		else if (nuevo_b > 255)
		{
			nuevo_b = 255;
		}

		img.setPixel(i, j, pixel(nuevo_r, nuevo_g, nuevo_b));
		}
	}

	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now(); // Fin del timer
	std::chrono::duration<double> duration = end - start;						  // Duración en segundos

	std::cout << "Duración: " << duration.count() << " segundos" << std::endl;
}

void blackWhite(ppm& img){
	for(int i = 0; i < img.height; i++) {
		for(int j = 0; j < img.width; j++) {
			pixel p = img.getPixel(i,j);
			int promedio = (p.r + p.g + p.b) / 3;
			img.setPixel(i, j, pixel(promedio,promedio,promedio));
		}
	}
}

void shades(ppm& img, unsigned char shades){
	for(int i = 0; i < img.height; i++) {
		for(int j = 0; j < img.width; j++) {
			pixel p = img.getPixel(i,j);
			int rango = 255 / (shades - 1);
			int gprima =  (p.r + p.g + p.b) / 3;
			int g =(gprima / rango) * rango;
			img.setPixel(i, j, pixel(g,g,g));
		}
	}
}

// COMPLETAR :)


