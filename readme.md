# TP2 Filtros de Imagenes

## Ejecutar filtros single-thread o multi-thread:

### main.cpp

Colocar el siguiente comando para compilar el archivo principal:
_g++ aplicar.cpp filters.cpp ppm.cpp main.cpp -pthread -o main_

Luego, ejecutar de la siguiente manera:

_./main <filtro_elegido> <n_threads> <parametro_1> <imagen> <output_dir>_

Si se quiere utilizar el filtro de merge, se debe agregar la segunda imagen:
  
_./main <filtro_elegido> <n_threads> <parametro_1> <imagen> <output_dir> <imagen2>_
Las imagenes deberian tener las mismas dimensiones.

_Ejemplo_:

- _./main shades 8 3 imgs/chihiro.ppm prueba.ppm_
- _./main shades 8 3 imgs/chihiro.ppm prueba.ppm imgs/ashitaka.ppm_

### loader.cpp

Colocar el siguiente comando para compilar el archivo de loader:
_g++ aplicar.cpp filters.cpp ppm.cpp loader.cpp -pthread -o loader_

Luego, ejecutar de la siguiente manera:
_./loader <filtro_elegido> <n_threads> <paramatro_1> <input_dir> <output_dir>_

Con este comando, introducimos un directorio de entrada, del cual se extraeran todos los archivos .ppm y se les aplicara un filtro. El resultado sera reenviado a el directorio especificado en output_dir.
Merge no forma parte de los filtros en loader.
_Ejemplos:_

- _./loader gradiente 8 1 imgs prueba_

### Filtro experimental

  Como se ve arriba, nuestro filtro de prueba es el gradiente. Sigue la estructura normal de los filtros. El parametro 1 debe ser 1 / 0. De colocar 1, se aplica el gradiente verticalmente, y de colocar 0, horizontalmente.
