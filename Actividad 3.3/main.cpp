/*
 * Act 3.3 - Actividad Integral de BST
 *
 * compilación:
 *   g++ -std=c++17 -Wall -O3 *.cpp -o act3_3
 *
 * ejecución:
 *   ./act3_3
 *
 * equipo:
 *  - Ana Regina Rodríguez Múzquiz | A01286913
 *  - Javier Barrón Vargas | A00842507
 *  - Alfonso José Morales Mallozzi | A00841550
 */


#include <iostream>
#include <exception>
#include "Bitacora.h"

using namespace std;

int main() {
  try {

    // se crea el objeto bitácora con el nombre del archivo de entrada
    Bitacora bitacora("bitacoraHeap.txt");
    // se ejecuta todo el proceso completo
    bitacora.procesar();
  } catch (exception &e) {
    
    cout << "error: " << e.what() << endl;
  }
  return 0;
}
