# Suma de Arreglos con OpenMP en C++ (LLVM)

Este proyecto implementa la suma elemento a elemento de dos arreglos `A`
y `B` utilizando:

-   Una versión secuencial (un solo hilo)
-   Una versión paralela con OpenMP (`#pragma omp parallel for`)

El objetivo es comparar el tiempo de ejecución entre ambas versiones y
analizar el impacto del paralelismo.

------------------------------------------------------------------------

## Requisitos

-   macOS
-   Homebrew
-   LLVM
-   OpenMP (libomp)
-   Visual Studio Code (opcional)

Instalación de dependencias:

``` bash
brew install llvm libomp
```

------------------------------------------------------------------------

## Compilación

Para compilar el programa utilizando LLVM y OpenMP, ejecute el siguiente
comando en la carpeta del proyecto:

``` bash
/opt/homebrew/opt/llvm/bin/clang++ -std=c++17 -O2 -Xpreprocessor -fopenmp   -I/opt/homebrew/opt/libomp/include   -L/opt/homebrew/opt/libomp/lib -lomp parallel.cpp -o suma_omp
```

------------------------------------------------------------------------

## Ejecución

Después de compilar, ejecute el programa con:

``` bash
./suma_omp
```

El programa mostrará:

-   Número de hilos disponibles
-   Tiempo secuencial
-   Tiempo paralelo
-   Speedup aproximado
-   Verificación de resultados

------------------------------------------------------------------------

## Uso con Diferentes Cantidades de Threads

OpenMP permite controlar el número de hilos mediante la variable de
entorno `OMP_NUM_THREADS`.

### Ejecutar con 4 threads

``` bash
OMP_NUM_THREADS=4 ./suma_omp
```

### Ejecutar con 6 threads

``` bash
OMP_NUM_THREADS=6 ./suma_omp
```

### Ejecutar con 8 threads

``` bash
OMP_NUM_THREADS=8 ./suma_omp
```

------------------------------------------------------------------------

## Ejecutar Varias Veces

Para dejar fijo un número de hilos:

``` bash
export OMP_NUM_THREADS=4
./suma_omp
```

Para cambiarlo:

``` bash
export OMP_NUM_THREADS=6
```

------------------------------------------------------------------------

## Control Avanzado (Opcional)

``` bash
OMP_NUM_THREADS=6 OMP_PROC_BIND=true OMP_PLACES=cores ./suma_omp
```

------------------------------------------------------------------------

## Estructura del Proyecto

    .
    ├── parallel.cpp
    ├── README.md
    └── suma_omp

------------------------------------------------------------------------

## Descripción del Funcionamiento

1.  Se generan dos arreglos `A` y `B` con valores aleatorios.
2.  Se calcula su suma de forma secuencial.
3.  Se calcula la misma suma usando OpenMP.
4.  Se mide el tiempo con `std::chrono`.
5.  Se muestran los primeros valores.
6.  Se valida el resultado.

------------------------------------------------------------------------

## Notas sobre Rendimiento

-   Con arreglos pequeños, el paralelo puede ser más lento.
-   Con arreglos grandes, el paralelo puede mejorar.
-   El rendimiento depende del hardware.
-   Al incrementar los hilos, dependiendo del número de elementos el paralelo también puede ser más lento.

------------------------------------------------------------------------
