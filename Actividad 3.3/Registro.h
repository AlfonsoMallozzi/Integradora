#ifndef REGISTRO_H
#define REGISTRO_H

#include <string>

using namespace std;

struct Registro {

  // aquí guardo la línea completa de la bitácora
  string lineaCompleta;

  // aquí se guarda solo la ip sin el puerto
  string ip;

  // ip convertida a número para poder ordenarla
  long long ipNumerica;

  // constructor vacío
  Registro() {}

  // constructor con datos
  // complejidad O(1)
  Registro(string linea, string ipStr, long long ipNum) {
    lineaCompleta = linea;
    ip = ipStr;
    ipNumerica = ipNum;
  }
};

#endif
