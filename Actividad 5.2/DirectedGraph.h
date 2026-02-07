#ifndef DIRECTED_GRAPH_H
#define DIRECTED_GRAPH_H

#include <string>
#include <unordered_map>
#include <vector>


// grafo dirigido representado mediante lista de adyacencia
// cada ip es un nodo y cada acceso es una arista dirigida
class DirectedGraph {
private:
  // lista de adyacencia: ip -> lista de ips destino
  std::unordered_map<std::string, std::vector<std::string>> adjList;

  // mapas para almacenar grados de entrada y salida
  std::unordered_map<std::string, int> outDegree;
  std::unordered_map<std::string, int> inDegree;

public:
  // agrega una arista para al grafo
  void addEdge(const std::string &from, const std::string &to);

  // getters para los grados
  const std::unordered_map<std::string, int> &getOutDegrees() const;
  const std::unordered_map<std::string, int> &getInDegrees() const;

  // getter para la lista de adyacencia completa
  const std::unordered_map<std::string, std::vector<std::string>> &
  getAdjList() const;

  // obtiene la lista de ips destino desde una ip origen
  std::vector<std::string> getDestinations(const std::string &ip) const;
};

#endif
