/**
 * Actividad 2.3 – Estructuras de datos lineales
 *
 * Equipo:
 * - Ana Regina Rodríguez Múzquiz | A01286913
 * - Javier Barrón Vargas | A00842507
 * - Alfonso José Morales Mallozzi | A00841550
 *
 * Compilar:
 *   g++ -std=c++17 -Wall main.cpp RegistroBitacora.cpp -o act2_3
 *
 * Ejecutar:
 *   ./act2_3
 */

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "RegistroBitacora.h"
#include "DoublyLinkedList.h"

// complejidad O(1) 
RegistroBitacora leerFechaUsuario(const std::string& s) {
    std::istringstream iss(s);
    std::string mesTxt, horaCompleta;
    int dia = 0, hora = 0, minuto = 0, segundo = 0;
    char c;

    iss >> mesTxt >> dia >> horaCompleta;

    std::istringstream tiempo(horaCompleta);
    tiempo >> hora >> c >> minuto >> c >> segundo;

    int mes = RegistroBitacora::mesATextoANumero(mesTxt);
    return RegistroBitacora(mes, dia, hora, minuto, segundo, "", "");
}

int main() {
    std::ifstream archivo("bitacoraData.txt");
    if (!archivo.is_open()) {
        std::cout << "No se pudo abrir bitacoraData.txt\n";
        return 1;
    }

    DoublyLinkedList<RegistroBitacora> listaOriginal;
    std::string linea;

    // lectura del archivo 
    // complejidad O(n)
    while (getline(archivo, linea)) {
        std::string mesTxt, horaTxt, ip, mensaje;
        int dia = 0, h = 0, m = 0, s = 0;
        char c;

        std::istringstream iss(linea);
        iss >> mesTxt >> dia >> horaTxt >> ip;
        getline(iss, mensaje);
        if (!mensaje.empty() && mensaje[0] == ' ') mensaje.erase(0, 1);

        std::istringstream tiempo(horaTxt);
        tiempo >> h >> c >> m >> c >> s;

        listaOriginal.addLast(
            RegistroBitacora(
                RegistroBitacora::mesATextoANumero(mesTxt),
                dia, h, m, s, ip, mensaje
            )
        );
    }
    archivo.close();

    std::cout << "Registros leidos: " << listaOriginal.getNumElements() << "\n";

    // comparacion de merge y quick
    DoublyLinkedList<RegistroBitacora> listaMerge = listaOriginal;
    DoublyLinkedList<RegistroBitacora> listaQuick = listaOriginal;

    long long compMerge = 0, movMerge = 0;
    long long compQuick = 0, swapsQuick = 0;

    // merge sort
    // https://www.geeksforgeeks.org/dsa/merge-sort-for-doubly-linked-list/
    // Complejidad O (n log n)
    std::cout << "\nOrdenando con MergeSort...\n";
    listaMerge.sortMerge(compMerge, movMerge);

    //Quick sort
    // Complejidad O(n log n)
    std::cout << "Ordenando con QuickSort...\n";
    listaQuick.sortQuick(compQuick, swapsQuick);

    std::cout << "\n--- Comparacion de Ordenamientos ---\n";
    std::cout << "MergeSort: comparaciones = " << compMerge
              << ", movimientos = " << movMerge << "\n";
    std::cout << "QuickSort: comparaciones = " << compQuick
              << ", swaps = " << swapsQuick << "\n";

    DoublyLinkedList<RegistroBitacora>& listaOrdenada = listaMerge;

    //se guarda
    listaOrdenada.saveToFile("bitacora_ordenada.txt");
    std::cout << "\nSe guardo: bitacora_ordenada.txt\n";

    //se piden las fechas
    std::string f1, f2;
    std::cout << "\nFecha inicio (ej: Jun 01 00:22:36): ";
    getline(std::cin, f1);
    if (f1.empty()) getline(std::cin, f1);

    std::cout << "Fecha fin (ej: Jun 01 08:23:57): ";
    getline(std::cin, f2);

    RegistroBitacora inicio = leerFechaUsuario(f1);
    RegistroBitacora fin = leerFechaUsuario(f2);

    if (fin < inicio) {
        RegistroBitacora tmp = inicio;
        inicio = fin;
        fin = tmp;
    }

    //verificar si existen las fechas
    bool existeInicio = listaOrdenada.existsExact(inicio);
    bool existeFin = listaOrdenada.existsExact(fin);

    if (!existeInicio) std::cout << "Aviso: la fecha inicial NO esta exacta en la bitacora.\n";
    if (!existeFin) std::cout << "Aviso: la fecha final NO esta exacta en la bitacora.\n";

    //búsqueda binaria
    // complejidad O(log n)
    NodeDLL<RegistroBitacora>* iniNode = listaOrdenada.lowerBound(inicio);
    NodeDLL<RegistroBitacora>* finNode = listaOrdenada.upperBoundLastLE(fin);

    std::ofstream out("resultado_busqueda.txt");
    if (!out.is_open()) {
        std::cout << "No se pudo crear resultado_busqueda.txt\n";
        return 1;
    }

    std::cout << "\n--- Registros en el rango ---\n";

    if (!iniNode || !finNode) {
        std::cout << "No hay registros dentro del rango.\n";
        out << "No hay registros dentro del rango.\n";
        out.close();
        return 0;
    }

    NodeDLL<RegistroBitacora>* p = iniNode;

    // Aquí reviso si la fecha inicial quedó después de la final.
    // Si pasa eso, entonces no hay datos que mostrar en el rango.
    if (finNode->getData() < p->getData()) {
        std::cout << "No hay registros dentro del rango.\n";
        out << "No hay registros dentro del rango.\n";
        out.close();
        return 0;
    }
    
    // complejidad O(k), aquí 'k' es el número de registros en el rango 
    while (p) {
        const RegistroBitacora& r = p->getData();

        std::cout << r.toString() << "\n";
        out << r.toString() << "\n";

        if (p == finNode) break;
        p = p->getNext();
    }

    out.close();
    std::cout << "\nSe guardo: resultado_busqueda.txt\n";

    return 0;
}
