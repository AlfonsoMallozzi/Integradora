#ifndef HASH_TABLE_QP_H
#define HASH_TABLE_QP_H

#include <vector>
#include <string>
#include "IPSummary.h"

// implementacion de una tabla hash usando direccion abierta
// se utiliza una funcion hash para strings
class HashTableQP {
private:
  std::vector<IPSummary> table;
  std::vector<bool> occupied;
  int size;
  int collisions;

  // funcion hash que convierte una ip en un indice
  int hashFunction(const std::string& ip) const;

public:
  HashTableQP(int tableSize);

  // inserta un resumen de ip en la tabla hash
  void insert(const IPSummary& summary);

  // regresa el numero total de colisiones generadas
  int getCollisions() const;

  // busca una ip en la tabla hash y regresa su resumen
  // regresa nullptr si no se encuentra
  IPSummary* search(const std::string& ip);

  // verifica si una ip existe en la tabla hash
  bool contains(const std::string& ip) const;
};

#endif
