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
#include <cmath>
#include <algorithm>

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

void boxBlur(ppm &img)
{
	std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();

	ppm tempImg = img; // Crear una imagen temporal para almacenar los resultados

	// Iterar sobre cada píxel de la imagen
	for (int i = 1; i < img.height - 1; i++)
	{
		for (int j = 1; j < img.width - 1; j++)
		{
			int sumR = 0, sumG = 0, sumB = 0;

			// Sumar los valores de los canales de los 9 píxeles vecinos
			for (int k = -1; k <= 1; k++)
			{
			for (int l = -1; l <= 1; l++)
			{
				pixel p = img.getPixel(i + k, j + l);
				sumR += p.r;
				sumG += p.r;
				sumB += p.b;
			}
			}

			// Calcular el promedio de los valores sumados
			int avgR = sumR / 9;
			int avgG = sumG / 9;
			int avgB = sumB / 9;

			// Establecer el nuevo valor del píxel en la imagen temporal
			tempImg.setPixel(i, j, pixel(avgR, avgG, avgB));
		}
	}

	img = tempImg; // Reemplazar la imagen original con la imagen filtrada

	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now(); // Fin del timer
	std::chrono::duration<double> duration = end - start;						  // Duración en segundos

	std::cout << "Duración: " << duration.count() << " segundos" << std::endl;
}

void merge(ppm &img1, ppm &img2, float p1)
{
	float p2 = 1 - p1;
	ppm img_final = img1;

	for (int i = 0; i < img1.height; i++)
	{
		for (int j = 0; j < img1.width; j++)
		{ // Ambas img tienen la misma resolución
			pixel pixel1 = img1.getPixel(i, j);
			pixel pixel2 = img2.getPixel(i, j);

			float red = pixel1.r * p1 + p2 * pixel2.r;
			float green = pixel1.g * p1 + p2 * pixel2.g;
			float blue = pixel1.b * p1 + pixel2.b * p2;
			img_final.setPixel(i, j, pixel(round(red), round(green), round(blue)));
		}
	}
	img1 = img_final;
}

void edgeDetection(ppm &img)
{
	for (int i = 0; i < img.height; i++)
	{
		for (int j = 0; j < img.width; j++)
		{
			pixel p = img.getPixel(i, j);
			int promedio = (p.r + p.g + p.b) / 3;
			img.setPixel(i, j, pixel(promedio, promedio, promedio));
		}
	}
	ppm tempImg = img; // Crear una imagen temporal para almacenar los resultados

	// Iterar sobre cada píxel de la imagen
	for (int i = 1; i < img.height - 1; i++)
	{
		for (int j = 1; j < img.width - 1; j++)
		{
			int sumR = 0, sumG = 0, sumB = 0;

			// Sumar los valores de los canales de los 9 píxeles vecinos
			for (int k = -1; k <= 1; k++)
			{
			for (int l = -1; l <= 1; l++)
			{
				pixel p = img.getPixel(i + k, j + l);
				sumR += p.r;
				sumG += p.r;
				sumB += p.b;
			}
			}

			// Calcular el promedio de los valores sumados
			int avgR = sumR / 9;
			int avgG = sumG / 9;
			int avgB = sumB / 9;

			// Establecer el nuevo valor del píxel en la imagen temporal
			tempImg.setPixel(i, j, pixel(avgR, avgG, avgB));
		}
	}
	img = tempImg; // Reemplazar la imagen original con la imagen filtrada

	// Crear una nueva imagen en escala de grises para almacenar los bordes acentuados
	ppm result(img.width, img.height);

	// Kernel Sobel para detectar bordes verticales
	int sobelVertical[3][3] = {
		{1, 0, -1},
		{2, 0, -2},
		{1, 0, -1}};

	// Convolución de la imagen con el kernel Sobel
	for (int i = 1; i < img.height - 1; i++)
	{
		for (int j = 1; j < img.width - 1; j++)
		{
			int gx = 0;
			int gy = 0;

			// Calcular la convolución para el píxel actual
			for (int k = -1; k <= 1; k++)
			{
			for (int l = -1; l <= 1; l++)
			{
				// Obtener el valor del píxel en la posición correspondiente al kernel
				pixel p = img.getPixel(i + k, j + l);

				// Obtener los valores de los componentes de color
				int r = p.r;
				int g = p.g;
				int b = p.b;

				// Calcular la contribución del píxel al valor de convolución
				int value = sobelVertical[k + 1][l + 1];
				gx += value * r;
				gy += value * g;
				gy += value * b;
			}
			}

			// Calcular la magnitud del gradiente
			int magnitude = sqrt(gx * gx + gy * gy);

			// Establecer el valor de intensidad en la imagen de resultado
			result.setPixel(i, j, pixel(magnitude, magnitude, magnitude));
		}
	}

	// Reemplazar la imagen original con la imagen de resultado
	img = result;
}

void sharpen(ppm &img)
{
	std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();

	ppm tempImg = img; // Crear una imagen temporal para almacenar los resultados

	// Iterar sobre cada píxel de la imagen
	for (int i = 1; i < img.height - 1; i++)
	{
		for (int j = 1; j < img.width - 1; j++)
		{
			int sumR = 0, sumG = 0, sumB = 0;

			// Aplicar el efecto del kernel a los píxeles vecinos
			for (int k = -1; k <= 1; k++)
			{
			for (int l = -1; l <= 1; l++)
			{
				pixel p = img.getPixel(i + k, j + l);
				int coefficient = 0;

				// Asignar el valor del coeficiente según la posición en el kernel
				if ((k == 0 && l == 0)(k == 1 && l == 1)(k == 2 && l == 0))
					coefficient = -1;
				else if ((k == 1 && l == 0) || (k == 1 && l == 2))
					coefficient = 5;

				sumR += coefficient * p.r;
				sumG += coefficient * p.g;
				sumB += coefficient * p.b;
			}
			}

			// Asegurarse de que los valores de los canales estén en el rango válido
			int newR = std::min(std::max(sumR, 0), 255);
			int newG = std::min(std::max(sumG, 0), 255);
			int newB = std::min(std::max(sumB, 0), 255);

			// Establecer el nuevo valor del píxel en la imagen temporal
			tempImg.setPixel(i, j, pixel(newR, newG, newB));
		}
	}

	img = tempImg; // Reemplazar la imagen original con la imagen filtrada

	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now(); // Fin del timer
	std::chrono::duration<double> duration = end - start;						  // Duración en segundos

	std::cout << "Duración: " << duration.count() << " segundos" << std::endl;
}

	void contrastThreads(int iteration, int pixeles, ppm &img, float contrast)
	{
		for (int i = iteration * pixeles; i < pixeles * (iteration + 1); i++)
			for (int j = 0; j < img.width; j++)
			{
			pixel p = img.getPixel(i, j);

			float f = (259 * (contrast + 255)) / (255 * (259 - contrast));

			int r_prima = p.r - 128;
			int g_prima = p.g - 128;
			int b_prima = p.b - 128;

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

void multiContrast(ppm &img, float contrast, unsigned int n)
{
	std::vector<std::thread> threads;
	std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
	int pixeles = img.height / n;
	int resto = img.height % n;

	for (int i = 0; i < n; ++i)
	{
		if (i == threads.size() - 1)
		{
			threads.emplace_back(contrastThreads, i, pixeles + resto, std::ref(img), contrast);
		}
		else
			threads.emplace_back(contrastThreads, i, pixeles, std::ref(img), contrast);
	}

	for (std::thread &thread : threads)
	{
		thread.join();
	}

	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now(); // Fin del timer
	std::chrono::duration<double> duration = end - start;						  // Duración en segundos

	std::cout << "Duración: " << duration.count() << " segundos" << std::endl;
}

void blackWhiteThreads(int iteration, int pixeles, ppm &img)
{
	for (int i = iteration * pixeles; i < pixeles * (iteration + 1); i++)
	{
		for (int j = 0; j < img.width; j++)
		{
			pixel p = img.getPixel(i, j);
			int promedio = (p.r + p.g + p.b) / 3;
			img.setPixel(i, j, pixel(promedio, promedio, promedio));
		}
	}
}

void multiBlackWhite(ppm &img, unsigned int n)
{
	std::vector<std::thread> threads;
	std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
	int pixeles = img.height / n;
	int resto = img.height % n;

	for (int i = 0; i < n; ++i)
	{
		if (i == threads.size() - 1)
		{
			threads.emplace_back(blackWhiteThreads, i, pixeles + resto, std::ref(img));
		}
		else
			threads.emplace_back(blackWhiteThreads, i, pixeles, std::ref(img));
	}

	for (std::thread &thread : threads)
	{
		thread.join();
	}

	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now(); // Fin del timer
	std::chrono::duration<double> duration = end - start;						  // Duración en segundos

	std::cout << "Duración: " << duration.count() << " segundos" << std::endl;
}



// COMPLETAR :)


