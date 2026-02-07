/*
 * Act 5.2 - Actividad Integral sobre el uso de códigos hash
 *
 * equipo:
 * - Ana Regina Rodriguez Múzquiz | A01286913
 * - Javier Barron Vargas | A00842507
 * - Alfonso Jose Morales Mallozzi | A00841550
 *
 * compilación:
 * g++ -std=c++17 -Wall -Wextra -O3 main.cpp DirectedGraph.cpp HashTableQP.cpp
 * -o main
 *
 * ejecución:
 * ./main
 */

#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>

#include "DirectedGraph.h"
#include "HashTableQP.h"
#include "IPSummary.h"

// elimina el puerto de una ip (ej. 192.168.1.1:8080 -> 192.168.1.1)
// complejidad O(n) donde n es la longitud de la cadena
std::string removePort(const std::string &ipPort) {
  size_t pos = ipPort.find(':');
  if (pos == std::string::npos) {
    return ipPort;
  }
  return ipPort.substr(0, pos);
}

// funcion getIPSummary que muestra el resumen de una ip y sus conexiones
// complejidad O(m log m) donde m es el numero de conexiones de la ip
void getIPSummary(const std::string &ip, HashTableQP &hashTable,
                  const DirectedGraph &graph) {
  // buscar la ip en la tabla hash
  IPSummary *summary = hashTable.search(ip);

  if (summary == nullptr) {
    std::cout << "Error: La IP " << ip << " no se encuentra en la bitacora.\n";
    return;
  }

  // imprimir resumen de la ip
  std::cout << "\n========== RESUMEN DE IP ==========\n";
  std::cout << "IP: " << summary->ip << "\n";
  std::cout
      << "Total de direcciones accesadas desde esta IP (aristas salientes): "
      << summary->outDegree << "\n";
  std::cout
      << "Total de direcciones que accedieron a esta IP (aristas entrantes): "
      << summary->inDegree << "\n";
  std::cout << "====================================\n";

  // obtener las ips destino desde la ip consultada
  std::vector<std::string> destinations = graph.getDestinations(ip);

  if (destinations.empty()) {
    std::cout << "\nNo hay direcciones accesadas desde esta IP.\n";
    return;
  }

  // ordenar las ips en orden descendente
  // complejidad O(m log m) donde m es el numero de destinos
  std::sort(destinations.begin(), destinations.end(),
            std::greater<std::string>());

  // imprimir las ips destino ordenadas
  std::cout << "\nLista de direcciones accesadas desde " << ip
            << " (orden descendente):\n";
  std::cout << "--------------------------------------\n";
  for (size_t i = 0; i < destinations.size(); i++) {
    std::cout << (i + 1) << ". " << destinations[i] << "\n";
  }
  std::cout << "--------------------------------------\n";
  std::cout << "Total: " << destinations.size() << " conexiones salientes\n";
}

int main() {
  // se crea el grafo dirigido usando lista de adyacencia
  DirectedGraph graph;

  // se abre el archivo de la bitacora
  std::ifstream file("bitacoraGrafos.txt");
  if (!file.is_open()) {
    std::cerr << "error al abrir el archivo bitacoraGrafos.txt\n";
    return 1;
  }

  // el archivo comienza con dos enteros: n (numero de ips) y m (numero de
  // aristas)
  int n, m;
  file >> n >> m;

  // se leen y descartan las n ips del archivo
  // complejidad O(n)
  std::string ip;
  for (int i = 0; i < n; i++) {
    file >> ip;
  }

  // variables para leer las incidencias
  std::string month, time;
  int day, weight;
  std::string srcIPPort, dstIPPort;

  // se leen las incidencias del archivo
  // complejidad O(m) donde m es el numero de incidencias
  while (file >> month >> day >> time >> srcIPPort >> dstIPPort >> weight) {
    std::string srcIP = removePort(srcIPPort);
    std::string dstIP = removePort(dstIPPort);

    // se agrega la arista dirigida al grafo
    graph.addEdge(srcIP, dstIP);

    // se ignora el resto de la linea (razon de la incidencia)
    file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }

  file.close();

  const auto &outDegrees = graph.getOutDegrees();
  const auto &inDegrees = graph.getInDegrees();

  // se calcula el tamaño de la tabla hash basado en el numero de ips unicas
  // se usa aproximadamente 2x el numero de ips para un buen factor de carga
  int numIPs = static_cast<int>(outDegrees.size());
  int tableSize = std::max(101, numIPs * 2);

  // se crea la tabla hash para almacenar el resumen de cada ip
  HashTableQP hashTable(tableSize);

  // se recorre el conjunto de ips para generar su resumen
  // complejidad O(n)
  for (const auto &pair : outDegrees) {
    IPSummary summary;
    summary.ip = pair.first;
    summary.outDegree = pair.second;
    summary.inDegree =
        inDegrees.count(pair.first) ? inDegrees.at(pair.first) : 0;

    // se inserta el resumen en la tabla hash
    hashTable.insert(summary);
  }

  // tambien insertar ips que solo tienen conexiones entrantes (no estan en
  // outDegrees)
  for (const auto &pair : inDegrees) {
    if (!outDegrees.count(pair.first)) {
      IPSummary summary;
      summary.ip = pair.first;
      summary.outDegree = 0;
      summary.inDegree = pair.second;
      hashTable.insert(summary);
    }
  }

  std::cout << "Tabla hash creada correctamente a partir del grafo dirigido\n";
  std::cout << "Total de colisiones generadas: " << hashTable.getCollisions()
            << std::endl;
  std::cout << "\n";

  // solicitar ip al usuario y validar que exista
  std::string userIP;
  bool validIP = false;

  while (!validIP) {
    std::cout << "Ingrese una direccion IP para consultar (ej. 192.168.1.1): ";
    std::cin >> userIP;

    // validar que la ip existe en la tabla hash
    if (hashTable.contains(userIP)) {
      validIP = true;
    } else {
      std::cout << "Error: La IP ingresada no existe en la bitacora. Intente "
                   "nuevamente.\n";
    }
  }

  // llamar a getIPSummary con la ip validada
  getIPSummary(userIP, hashTable, graph);

  return 0;
}
