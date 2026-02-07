#include "Sorts.h"

void Sorts::bubbleSort(std::vector<RegistroBitacora> &datos,
                       long long &comparaciones, long long &swaps) {
  int n = datos.size();

  comparaciones = 0;
  swaps = 0;

  for (int i = 0; i < n - 1; i++) {
    for (int j = 0; j < n - i - 1; j++) {
      comparaciones++;

      if (datos[j + 1] < datos[j]) {
        RegistroBitacora temp = datos[j];
        datos[j] = datos[j + 1];
        datos[j + 1] = temp;
        swaps++;
      }
    }
  }
}

void Sorts::quickSort(std::vector<RegistroBitacora> &datos, int low, int high,
                      long long &comparaciones, long long &swaps) {
  if (low < high) {
    int pi = partition(datos, low, high, comparaciones, swaps);

    quickSort(datos, low, pi - 1, comparaciones, swaps);
    quickSort(datos, pi + 1, high, comparaciones, swaps);
  }
}

int Sorts::partition(std::vector<RegistroBitacora> &datos, int low, int high,
                     long long &comparaciones, long long &swaps) {
  // Pivote al final
  RegistroBitacora pivot = datos[high];
  int i = (low - 1);

  for (int j = low; j <= high - 1; j++) {
    comparaciones++;
    // pivot >= datos[j] ?
    // Como sobrecargamos <, usamos datos[j] < pivot
    if (datos[j] < pivot) {
      i++;
      RegistroBitacora temp = datos[i];
      datos[i] = datos[j];
      datos[j] = temp;
      swaps++;
    }
  }
  RegistroBitacora temp = datos[i + 1];
  datos[i + 1] = datos[high];
  datos[high] = temp;
  swaps++;
  return (i + 1);
}
