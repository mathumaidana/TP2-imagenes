#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>
#include <thread>
#include <unistd.h>
#include <fstream>
#include "aplicar.h"
#include "ppm.h"
#include <filesystem>

#define ONE_OVER_BILLION 1E-9
namespace fs = std::filesystem;
using namespace std;

int main(int argc, char *argv[])
{
	string filter = string(argv[1]);
	unsigned int n = atoi(argv[2]);
	float p1 = atof(argv[3]);
    string directorio = string(argv[4]);
    string out = string(argv[5]);
	

	for (const auto& imagen : fs::directory_iterator(directorio)) {
        if (fs::is_regular_file(imagen) && imagen.path().extension() == ".ppm"){
			ppm img(imagen.path().string());

			std::size_t found = imagen.path().string().find("/");
			string segundaParte;		

 			if (!std::filesystem::exists(out)) std::filesystem::create_directory(out);

			if (found != std::string::npos) {
				segundaParte = imagen.path().string().substr(found + 1);
			} else {
				std::cout << "El output esta mal!" << std::endl;
				return 0;
			}		
			cout << "Archivo: " << imagen.path() << std::endl;
			aplicar(filter, p1, imagen.path().string(), n, out + "/" + segundaParte, img);
		} 
	}

	return 0;
}