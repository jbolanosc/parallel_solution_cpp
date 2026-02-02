#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <omp.h>

// Llena un vector con valores aleatorios reproducibles usando un seed fijo.
static void fill_random(std::vector<int>& v, int seed, int minv = 0, int maxv = 100) {
    std::mt19937 rng(seed);
    std::uniform_int_distribution<int> dist(minv, maxv);
    for (auto& x : v) x = dist(rng);
}

// Verifica que cada elemento del arreglo resultado sea igual a A[i] + B[i].
static bool verify_sum(const std::vector<int>& A,
                       const std::vector<int>& B,
                       const std::vector<int>& R) {
    if (A.size() != B.size() || A.size() != R.size()) return false;
    for (size_t i = 0; i < A.size(); ++i) {
        if (R[i] != A[i] + B[i]) return false;
    }
    return true;
}

int main() {
    const int N = 100;

    std::vector<int> A(N), B(N), R_seq(N), R_par(N);

    fill_random(A, 42);
    fill_random(B, 123);

    std::cout << "Arreglos llenados con valores aleatorios [0..100]\n";


    // Suma secuencial: un solo hilo calcula todos los elementos.
    // Se registra el tiempo inicial para medir el rendimiento. 
    auto t1 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < N; ++i) {
        R_seq[i] = A[i] + B[i];
    }
    auto t2 = std::chrono::high_resolution_clock::now();

    // Suma paralela con OpenMP: cada hilo procesa una parte del arreglo sin dependencias.
    auto t3 = std::chrono::high_resolution_clock::now();

    #pragma omp parallel for default(none) shared(A, B, R_par, N) schedule(static)
    for (int i = 0; i < N; ++i) {
        R_par[i] = A[i] + B[i];
    }

    auto t4 = std::chrono::high_resolution_clock::now();

    auto seq_us = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
    auto par_us = std::chrono::duration_cast<std::chrono::microseconds>(t4 - t3).count();

    std::cout << "\nThreads disponibles (omp_get_max_threads): " << omp_get_max_threads() << "\n";
    std::cout << "Tiempo secuencial: " << seq_us << " us\n";
    std::cout << "Tiempo paralelo:   " << par_us << " us\n";

    // Cálculo del speedup: relación entre tiempo secuencial y paralelo.
    double speedup = (par_us > 0) ? (double)seq_us / (double)par_us : 0.0;
    std::cout << "Speedup aprox (seq/par): " << speedup << "x\n";

    // Imprime los primeros elementos de un arreglo para validar visualmente los resultados.
    auto print_first = [&](const std::string& name, const std::vector<int>& v, int k = 10) {
        std::cout << "\n" << name << " (primeros " << k << "): ";
        for (int i = 0; i < k && i < (int)v.size(); ++i) {
            std::cout << v[i] << (i + 1 < k ? ", " : "");
        }
        std::cout << "\n";
    };

    print_first("A", A);
    print_first("B", B);
    print_first("R_par", R_par);


    // Se valida que ambos métodos produzcan resultados correctos.
    std::cout << "\nVerificacion secuencial: " << (verify_sum(A, B, R_seq) ? "OK" : "FAIL") << "\n";
    std::cout << "Verificacion paralelo:   " << (verify_sum(A, B, R_par) ? "OK" : "FAIL") << "\n";

    return 0;
}