#include "DirectedGraph.h"

// agrega una arista dirigida from -> to
// complejidad O(1) promedio usando unordered_map
void DirectedGraph::addEdge(const std::string &from, const std::string &to) {
  adjList[from].push_back(to);
  outDegree[from]++;
  inDegree[to]++;

  // asegura que ambas ips existan aunque tengan grado 0
  if (!inDegree.count(from))
    inDegree[from] = 0;
  if (!outDegree.count(to))
    outDegree[to] = 0;
}

const std::unordered_map<std::string, int> &
DirectedGraph::getOutDegrees() const {
  return outDegree;
}

const std::unordered_map<std::string, int> &
DirectedGraph::getInDegrees() const {
  return inDegree;
}

const std::unordered_map<std::string, std::vector<std::string>> &
DirectedGraph::getAdjList() const {
  return adjList;
}

// obtiene la lista de ips destino desde una ip origen
// complejidad O(1) promedio para la busqueda en el mapa
std::vector<std::string>
DirectedGraph::getDestinations(const std::string &ip) const {
  auto it = adjList.find(ip);
  if (it != adjList.end()) {
    return it->second;
  }
  return std::vector<std::string>();
}
