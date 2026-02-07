/**
 * - Ana Regina Rodríguez Múzquiz | A01286913
 * - Javier Barrón Vargas | A00842507
 * - Alfonso José Morales Mallozzi | A00841550
 *
 * Compilar:
 *   g++ -std=c++17 -Wall -o act1_4 main.cpp RegistroBitacora.cpp Sorts.cpp
 */

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "RegistroBitacora.h"
#include "Sorts.h"

// Lee una fecha ingresada por el usuario y la convierte a un objeto
// RegistroBitacora Complejidad: O(1) tiempo, O(1) espacio
RegistroBitacora leerFechaUsuario(const std::string &s) {
  std::istringstream iss(s);

  std::string mesTxt;
  std::string horaCompleta;
  int dia;

  iss >> mesTxt >> dia >> horaCompleta;

  int hora = 0;
  int minuto = 0;
  int segundo = 0;
  char c;

  std::istringstream tiempo(horaCompleta);
  tiempo >> hora >> c >> minuto >> c >> segundo;

  int mes = RegistroBitacora::mesATextoANumero(mesTxt);

  return RegistroBitacora(mes, dia, hora, minuto, segundo, "", "");
}

// Devuelve el primer índice i tal que registros[i] >= clave
// Complejidad: O(log n) tiempo, O(1) espacio
int lowerBoundFecha(const std::vector<RegistroBitacora> &registros,
                    const RegistroBitacora &clave) {
  int l = 0;
  int r = (int)registros.size() - 1;
  int ans = (int)registros.size();

  while (l <= r) {
    int mid = l + (r - l) / 2;

    if (!(registros[mid] < clave)) {
      ans = mid;
      r = mid - 1;
    } else {
      l = mid + 1;
    }
  }

  return ans;
}

// Devuelve el último índice i tal que registros[i] <= clave
// Complejidad: O(log n) tiempo, O(1) espacio
int upperBoundUltimoMenorIgual(const std::vector<RegistroBitacora> &registros,
                               const RegistroBitacora &clave) {
  int l = 0;
  int r = (int)registros.size() - 1;
  int ans = -1;

  while (l <= r) {
    int mid = l + (r - l) / 2;

    if (registros[mid] <= clave) {
      ans = mid;
      l = mid + 1;
    } else {
      r = mid - 1;
    }
  }

  return ans;
}

// Verifica si una fecha exacta existe dentro de la bitácora
// Complejidad: O(log n) tiempo, O(1) espacio
bool fechaExisteExacta(const std::vector<RegistroBitacora> &registros,
                       const RegistroBitacora &clave) {
  int i = lowerBoundFecha(registros, clave);

  if (i >= (int)registros.size()) {
    return false;
  }

  return registros[i].getFechaClave() == clave.getFechaClave();
}

int main() {
  std::ifstream archivo("bitacoraData.txt");

  if (!archivo.is_open()) {
    std::cout << "No se pudo abrir el archivo bitacoraData.txt" << std::endl;
    return 1;
  }

  std::vector<RegistroBitacora> registros;
  std::string linea;

  while (getline(archivo, linea)) {

    std::string mesTexto;
    int dia;
    std::string horaCompleta;
    std::string ipPuerto;
    std::string mensaje;

    std::istringstream iss(linea);

    iss >> mesTexto >> dia >> horaCompleta >> ipPuerto;

    getline(iss, mensaje);

    if (!mensaje.empty() && mensaje[0] == ' ') {
      mensaje.erase(0, 1);
    }

    int hora, minuto, segundo;
    char c;

    std::istringstream tiempo(horaCompleta);
    tiempo >> hora >> c >> minuto >> c >> segundo;

    int mes = RegistroBitacora::mesATextoANumero(mesTexto);

    RegistroBitacora registro(mes, dia, hora, minuto, segundo, ipPuerto,
                              mensaje);

    registros.push_back(registro);
  }

  archivo.close();

  std::cout << "Registros leidos: " << registros.size() << std::endl;

  std::vector<RegistroBitacora> registrosBubble = registros;
  std::vector<RegistroBitacora> registrosQuick = registros;

  long long comparacionesBubble = 0;
  long long swapsBubble = 0;

  std::cout << "\nIniciando Bubble Sort..." << std::endl;
  Sorts::bubbleSort(registrosBubble, comparacionesBubble, swapsBubble);

  long long comparacionesQuick = 0;
  long long swapsQuick = 0;

  std::cout << "Iniciando Quick Sort..." << std::endl;
  Sorts::quickSort(registrosQuick, 0, (int)registrosQuick.size() - 1,
                   comparacionesQuick, swapsQuick);

  // Desplegar resultados
  std::cout << "\n--- Resultados de Ordenamiento ---" << std::endl;
  std::cout << "Bubble Sort: Comparaciones = " << comparacionesBubble
            << ", Swaps = " << swapsBubble << std::endl;
  std::cout << "Quick Sort:  Comparaciones = " << comparacionesQuick
            << ", Swaps = " << swapsQuick << std::endl;

  // Guardar la bitácora ordenada (usando el resultado de Quick Sort)
  std::ofstream archivoSalida("bitacora_ordenada.txt");
  if (archivoSalida.is_open()) {
    for (const auto &r : registrosQuick) {
      archivoSalida << r.toString() << std::endl;
    }
    archivoSalida.close();
    std::cout << "\nSe ha guardado la bitacora ordenada en "
                 "'bitacora_ordenada.txt'."
              << std::endl;
  } else {
    std::cout << "\nError al crear 'bitacora_ordenada.txt'." << std::endl;
  }

  registros = registrosQuick;

  std::cout << "\nIngresa la fecha inicial (formato: Mes Dia HH:MM:SS, ej: Jun "
               "01 00:22:36):\n";
  std::string f1;
  std::getline(std::cin, f1);

  if (f1.size() == 0) {
    std::getline(std::cin, f1);
  }

  // Solicitar al usuario la fecha final
  std::cout << "Ingresa la fecha final (formato: Mes Dia HH:MM:SS, ej: Jun 01 "
               "08:23:57):\n";
  std::string f2;
  std::getline(std::cin, f2);

  // Convertir las fechas ingresadas a objetos RegistroBitacora
  RegistroBitacora inicio = leerFechaUsuario(f1);
  RegistroBitacora fin = leerFechaUsuario(f2);

  if (fin < inicio) {
    RegistroBitacora temp = inicio;
    inicio = fin;
    fin = temp;
  }

  // Verificar si las fechas existen de forma exacta en la bitácora
  if (!fechaExisteExacta(registros, inicio)) {
    std::cout << "Aviso: la fecha inicial NO esta exacta en la bitacora.\n";
  }

  if (!fechaExisteExacta(registros, fin)) {
    std::cout << "Aviso: la fecha final NO esta exacta en la bitacora.\n";
  }

  // Buscar los índices que delimitan el rango cerrado [inicio, fin]
  int idxI = lowerBoundFecha(registros, inicio);
  int idxF = upperBoundUltimoMenorIgual(registros, fin);

  // Mostrar los registros dentro del rango de fechas
  std::cout << "\n--- Registros en el rango ---\n";

  if (idxI >= (int)registros.size() || idxF < 0 || idxI > idxF) {
    std::cout << "No hay registros dentro del rango.\n";
  } else {
    for (int i = idxI; i <= idxF; i++) {
      std::cout << registros[i].toString() << std::endl;
    }
  }

  return 0;
}
