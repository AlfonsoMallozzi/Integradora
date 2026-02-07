/**
 * act 4.3 - actividad integral de grafos
 *
 * equipo:
 * - Ana Regina Rodríguez Múzquiz | A01286913
 * - Javier Barrón Vargas | A00842507
 * - Alfonso José Morales Mallozzi | A00841550
 *
 * compilacion para debug:
 *   g++ -std=c++17 -g -o main main.cpp
 *
 * compilacion para ejecucion:
 *   g++ -std=c++17 -O3 -o main main.cpp
 *
 * ejecucion:
 *   ./main
 */

#include "Graph.h"
#include "MaxHeap.h"

#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <limits>
#include <algorithm>


int main() {

  // se crea el grafo donde se va a guardar la informacion de la bitacora
  Graph g;

  // se lee el archivo bitacoraGrafos.txt y se construye la lista de adyacencia
  // esta parte se hace recorriendo todas las ips y sus incidencias
  // complejidad O(n + m)
  g.readBitacora("bitacora/bitacoraGrafos.txt");

  // calculo el grado de salida de cada ip
  // el grado de salida es simplemente cuantas conexiones tiene cada ip
  // complejidad O(n)
  std::map<std::string, int> grados = g.getOutDegrees();

  // aqui se guarda los grados de salida en el archivo grados_ips.txt
  std::ofstream gradosFile("grados_ips.txt");
  for (auto& it : grados) {
    gradosFile << it.first << " " << it.second << std::endl;
  }
  gradosFile.close();

  // aqui uso un heap para encontrar las ips con mayor grado de salida
  // implementado de:
  // https://www.geeksforgeeks.org/heap-data-structure/

  // complejidad O(n log n)
  MaxHeap<std::pair<int, std::string>> heap(grados.size());

  for (auto& it : grados) {
    heap.push({it.second, it.first});
  }

  // se sacan las 7 ips con mayor grado de salida usando el heap
  std::ofstream topFile("mayores_grados_ips.txt");

  int limite = std::min(7, (int)grados.size());
  std::string bootMaster;

  for (int i = 0; i < limite; i++) {
    auto top = heap.pop(); // (grado, ip)
    topFile << top.second << " " << top.first << std::endl;

    // la primera ip que sale del heap es la que tiene mas conexiones
    // por eso la considero como el boot master
    if (i == 0) {
      bootMaster = top.second;
    }
  }

  topFile.close();

  // se imprime el boot master en pantalla
  std::cout << "el boot master presumiblemente es: "
            << bootMaster << std::endl;

  // ahora se ejecuta dijkstra para encontrar los caminos mas cortos desde el boot master hacia todas las demas ips
  
  // implementado de
  // https://www.geeksforgeeks.org/dsa/dijkstras-shortest-path-algorithm-using-priority_queue-stl/
  
  // complejidad O((n + m) log n)
  std::map<std::string, int> distancias = g.dijkstra(bootMaster);

  // guardo las distancias en el archivo distancia_bootmaster.txt
  std::ofstream distFile("distancia_bootmaster.txt");
  for (auto& it : distancias) {
    distFile << it.first << " " << it.second << std::endl;
  }
  distFile.close();

  // busco la ip que requiere mas esfuerzo para que el boot master la ataque
  // basicamente es la que tiene la distancia mas grande
  std::string ipMasLejana;
  int maxDist = -1;

  for (auto& it : distancias) {
    if (it.second != std::numeric_limits<int>::max() &&
        it.second > maxDist) {
      maxDist = it.second;
      ipMasLejana = it.first;
    }
  }

  // se imprime la ip mas dificil de atacar
  std::cout << "la ip que requiere mas esfuerzo para atacar es: "
            << ipMasLejana << std::endl;

  return 0;
}
