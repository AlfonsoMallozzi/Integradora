#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <queue>
#include <limits>
#include <functional>


/*
 * en esta clase se guarda el grafo usando una lista de adyacencia donde la llave es la ip de origen y el vector son sus conexiones
 */

class Graph {
private:
  // lista de adyacencia: ip origen -> (ip destino, peso)
  std::map<std::string, std::vector<std::pair<std::string, int>>> adjList;

public:
  Graph() {}

  /*
   * lee el archivo bitacoraGrafos.txt y construye la lista de adyacencia
   * complejidad O(n + m)
   */
  void readBitacora(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;

    if (!file.is_open()) {
      std::cout << "no se pudo abrir el archivo" << std::endl;
      return;
    }

    int n, m;
    file >> n;
    file >> m;

    // se lee las ips
    std::vector<std::string> ips(n);
    for (int i = 0; i < n; i++) {
      file >> ips[i];
      adjList[ips[i]] = {};
    }

    std::getline(file, line); 

    // se leen las incidencias
    for (int i = 0; i < m; i++) {
      std::string mes, hora, ipOrigen, ipDestino;
      int dia, peso;

      file >> mes >> dia >> hora >> ipOrigen >> ipDestino >> peso;
      std::getline(file, line); 

      // quitar puertos
      ipOrigen = ipOrigen.substr(0, ipOrigen.find(':'));
      ipDestino = ipDestino.substr(0, ipDestino.find(':'));

      adjList[ipOrigen].push_back({ipDestino, peso});
    }

    file.close();
  }

  /*
   * calcula el grado de salida de cada ip
   * complejidad O(n)
   */
  std::map<std::string, int> getOutDegrees() {
    std::map<std::string, int> grados;

    for (auto& it : adjList) {
      grados[it.first] = it.second.size();
    }

    return grados;
  }

  /*
   * algoritmo de dijkstra para una ip inicial
   * implementado de:
   * https://www.geeksforgeeks.org/dsa/dijkstras-shortest-path-algorithm-using-priority_queue-stl/
   *
   * complejidad O((n + m) log n)
   */
  std::map<std::string, int> dijkstra(const std::string& start) {
    const int INF = std::numeric_limits<int>::max();
    std::map<std::string, int> dist;

    for (auto& it : adjList) {
      dist[it.first] = INF;
    }

    dist[start] = 0;

    std::priority_queue<
      std::pair<int, std::string>,
      std::vector<std::pair<int, std::string>>,
      std::greater<std::pair<int, std::string>>
    > pq;

    pq.push({0, start});

    while (!pq.empty()) {
      auto current = pq.top();
      pq.pop();

      int currentDist = current.first;
      std::string currentNode = current.second;

      if (currentDist > dist[currentNode]) continue;

      for (auto& edge : adjList[currentNode]) {
        std::string neighbor = edge.first;
        int weight = edge.second;

        if (dist[currentNode] + weight < dist[neighbor]) {
          dist[neighbor] = dist[currentNode] + weight;
          pq.push({dist[neighbor], neighbor});
        }
      }
    }

    return dist;
  }

  // solo para acceder a la lista si se necesita en el main
  std::map<std::string, std::vector<std::pair<std::string,int>>> getAdjList() {
    return adjList;
  }
};

#endif
