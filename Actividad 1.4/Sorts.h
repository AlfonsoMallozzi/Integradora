#ifndef SORTS_H
#define SORTS_H

#include <vector>
#include "RegistroBitacora.h"

class Sorts {
public:
    // Ordenamiento burbuja
    // Complejidad: O(n^2) tiempo, O(1) espacio
    static void bubbleSort(std::vector<RegistroBitacora>& datos,
                           long long& comparaciones,
                           long long& swaps);

    // Ordenamiento QuickSort
    // Complejidad: O(n log n) tiempo promedio, O(log n) espacio
    static void quickSort(std::vector<RegistroBitacora>& datos,
                          int low, int high,
                          long long& comparaciones,
                          long long& swaps);

private:
    static int partition(std::vector<RegistroBitacora>& datos,
                         int low, int high,
                         long long& comparaciones,
                         long long& swaps);
};

#endif

