#include "Bitacora.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <queue>
#include <utility>

using namespace std;

// constructor
// complejidad O(1)
Bitacora::Bitacora(string archivo) {
  nombreArchivo = archivo;
}

// este método es el que controla todo el flujo del programa
// complejidad O(n log n)
void Bitacora::procesar() {
  leerArchivo();
  ordenarPorIP();
  guardarBitacoraOrdenada();
  contarAccesosYGuardarTop();
}

// aquí leé el archivo de la bitácora y guarda todo en el vector
// complejidad O(n)
void Bitacora::leerArchivo() {
  ifstream file(nombreArchivo);

  if (!file.is_open()) {
    throw runtime_error("no se pudo abrir el archivo de entrada");
  }

  string linea;
  while (getline(file, linea)) {

    
    stringstream ss(linea);
    string mes, dia, hora, ipPuerto;

    ss >> mes >> dia >> hora >> ipPuerto;

    // saco la ip sin el puerto
    string ip = ipPuerto.substr(0, ipPuerto.find(':'));

    // convierto la ip a número para poder compararla fácil
    // ejemplo: 10.15.175.231 -> 010015175231
    string ipNumStr;
    stringstream ipStream(ip);
    string parte;

    while (getline(ipStream, parte, '.')) {
      if (parte.length() == 1) ipNumStr += "00" + parte;
      else if (parte.length() == 2) ipNumStr += "0" + parte;
      else ipNumStr += parte;
    }

    long long ipNumerica = stoll(ipNumStr);

    registros.push_back(Registro(linea, ip, ipNumerica));
  }

  file.close();
}

// este método manda a llamar el heap sort
// complejidad O(n log n)
void Bitacora::ordenarPorIP() {
  heapSort();
}

// heap sort

// implementacion basada de geeksforgeeks
// https://www.geeksforgeeks.org/heap-sort/
// adapté el código para ordenar un vector de registros usando la ip numérica en lugar de números simples 

//// https://www.geeksforgeeks.org/heap-data-structure/
// acomoda el heap
// complejidad O(log n)
void Bitacora::heapify(int n, int i) {
  int mayor = i;
  int izquierda = 2 * i + 1;
  int derecha = 2 * i + 2;

  if (izquierda < n && registros[izquierda].ipNumerica > registros[mayor].ipNumerica)
    mayor = izquierda;

  if (derecha < n && registros[derecha].ipNumerica > registros[mayor].ipNumerica)
    mayor = derecha;

  if (mayor != i) {
    swap(registros[i], registros[mayor]);
    heapify(n, mayor);
  }
}


// heap sort completo
// complejidad O(n log n)
void Bitacora::heapSort() {
  int n = registros.size();

  // se construye el heap
  for (int i = n / 2 - 1; i >= 0; i--) {
    heapify(n, i);
    if (i == 0) break;
  }

  // se saca uno por uno
  for (int i = n - 1; i > 0; i--) {
    swap(registros[0], registros[i]);
    heapify(i, 0);
  }
}

// guarda la bitácora ya ordenada por ip
// complejidad O(n)
void Bitacora::guardarBitacoraOrdenada() {
  ofstream file("bitacora_ordenada.txt");

  if (!file.is_open()) {
    throw runtime_error("no se pudo crear bitacora_ordenada.txt");
  }

  for (Registro r : registros) {
    file << r.lineaCompleta << endl;
  }

  file.close();
}

//https://www.geeksforgeeks.org/priority-queue-in-cpp-stl/
//https://www.geeksforgeeks.org/binary-heap/
// aquí cuenta cuantas veces se repite cada ip y saca las 10 con mas accesos
// complejidad O(n log n)
void Bitacora::contarAccesosYGuardarTop() {

  // usamos priority_queue para obtener rápido la ip con más accesos
  // https://www.cplusplus.com/reference/queue/priority_queue/
  priority_queue<pair<int, string>> heapAccesos;

  if (registros.empty()) return;

  int contador = 1;

  for (size_t i = 1; i < registros.size(); i++) {
    if (registros[i].ip == registros[i - 1].ip) {
      contador++;
    } else {
      heapAccesos.push(make_pair(contador, registros[i - 1].ip));
      contador = 1;
    }
  }

  heapAccesos.push(make_pair(contador, registros.back().ip));

  ofstream file("ips_con_mayor_acceso.txt");

  if (!file.is_open()) {
    throw runtime_error("no se pudo crear ips_con_mayor_acceso.txt");
  }

  // saco las 10 ips con mas accesos
  for (int i = 0; i < 10 && !heapAccesos.empty(); i++) {
    auto top = heapAccesos.top();
    heapAccesos.pop();

    cout << top.second << " - " << top.first << " accesos" << endl;
    file << top.second << " - " << top.first << " accesos" << endl;
  }

  file.close();
}
