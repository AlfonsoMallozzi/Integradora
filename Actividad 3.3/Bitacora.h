#ifndef BITACORA_H
#define BITACORA_H

#include <vector>
#include <string>
#include "Registro.h"

using namespace std;

class Bitacora {
  private:
    // aquí se guarda todos los registros leídos del archivo
    vector<Registro> registros;

    // nombre del archivo de entrada
    string nombreArchivo;

    // métodos internos
    void leerArchivo();
    void ordenarPorIP();
    void heapify(int n, int i);
    void heapSort();
    void guardarBitacoraOrdenada();
    void contarAccesosYGuardarTop();

  public:
    // constructor
    // complejidad O(1)
    Bitacora(string archivo);

    // método principal
    // complejidad O(n log n)
    void procesar();
};

#endif
