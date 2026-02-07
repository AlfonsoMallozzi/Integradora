#include "HashTableQP.h"

// constructor de la tabla hash
HashTableQP::HashTableQP(int tableSize) {
  size = tableSize;
  table.resize(size);
  occupied.resize(size, false);
  collisions = 0;
}

// funcion hash
//  complejidad O(n) donde n es el tamaño de la cadena ip
//  implementado de:
//  https://www.geeksforgeeks.org/string-hashing-using-polynomial-rolling-hash-function/
int HashTableQP::hashFunction(const std::string &ip) const {
  unsigned long hash = 0;
  for (char c : ip) {
    hash = hash * 31 + c;
  }
  return hash % size;
}

// inserta usando direccion abierta
// complejidad O(1) promedio, O(n) en el peor de los casos
// implementado de:
// https://www.geeksforgeeks.org/open-addressing-collision-handling-technique-in-hashing/
void HashTableQP::insert(const IPSummary &summary) {
  int index = hashFunction(summary.ip);
  int i = 0;

  // cada intento adicional cuenta como una colision
  while (occupied[(index + i * i) % size]) {
    collisions++;
    i++;
    // proteccion contra tabla llena para evitar loop infinito
    if (i >= size) {
      return; // tabla llena, no se puede insertar
    }
  }

  int finalIndex = (index + i * i) % size;
  table[finalIndex] = summary;
  occupied[finalIndex] = true;
}

// regresa el total de colisiones generadas
int HashTableQP::getCollisions() const { return collisions; }

// busca una ip en la tabla hash y regresa su resumen
// complejidad O(1) promedio, O(n) en el peor de los casos
IPSummary *HashTableQP::search(const std::string &ip) {
  int index = hashFunction(ip);
  int i = 0;

  while (occupied[(index + i * i) % size]) {
    int currentIndex = (index + i * i) % size;
    if (table[currentIndex].ip == ip) {
      return &table[currentIndex];
    }
    i++;
    // si recorrimos toda la tabla, no existe
    if (i >= size) {
      return nullptr;
    }
  }
  return nullptr;
}

// verifica si una ip existe en la tabla hash
// complejidad O(1) promedio, O(n) en el peor de los casos
bool HashTableQP::contains(const std::string &ip) const {
  int index = hashFunction(ip);
  int i = 0;

  while (occupied[(index + i * i) % size]) {
    int currentIndex = (index + i * i) % size;
    if (table[currentIndex].ip == ip) {
      return true;
    }
    i++;
    if (i >= size) {
      return false;
    }
  }
  return false;
}
