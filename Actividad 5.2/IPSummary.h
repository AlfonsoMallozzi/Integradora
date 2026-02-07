#ifndef IP_SUMMARY_H
#define IP_SUMMARY_H

#include <string>

// almacena el resumen de informacion de una ip
// contiene el total de accesos salientes y entrantes
struct IPSummary {
  std::string ip;
  int outDegree = 0;
  int inDegree = 0;
};

#endif
