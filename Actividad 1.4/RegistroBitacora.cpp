#include "RegistroBitacora.h"
#include <sstream>

// Constructor por defecto
RegistroBitacora::RegistroBitacora()
    : mes(0), dia(0), hora(0), minuto(0), segundo(0),
      ipPuerto(""), mensaje("") {}

// Constructor con parámetros
RegistroBitacora::RegistroBitacora(int mes, int dia, int hora, int minuto, int segundo,
                                   const std::string& ipPuerto,
                                   const std::string& mensaje)
    : mes(mes), dia(dia), hora(hora), minuto(minuto), segundo(segundo),
      ipPuerto(ipPuerto), mensaje(mensaje) {}

// Getters
int RegistroBitacora::getMes() const { return mes; }
int RegistroBitacora::getDia() const { return dia; }
int RegistroBitacora::getHora() const { return hora; }
int RegistroBitacora::getMinuto() const { return minuto; }
int RegistroBitacora::getSegundo() const { return segundo; }
std::string RegistroBitacora::getIpPuerto() const { return ipPuerto; }
std::string RegistroBitacora::getMensaje() const { return mensaje; }

// Devuelve la fecha como tupla para comparar
// Complejidad: O(1) tiempo, O(1) espacio
std::tuple<int,int,int,int,int> RegistroBitacora::getFechaClave() const {
    return std::make_tuple(mes, dia, hora, minuto, segundo);
}

// Devuelve el registro en formato original (MES EN TEXTO)
// Complejidad: O(n) tiempo, O(n) espacio
std::string RegistroBitacora::toString() const {
    std::ostringstream salida;

    salida << mesNumeroATexto(mes) << " " << dia << " ";

    if (hora < 10) salida << "0";
    salida << hora << ":";

    if (minuto < 10) salida << "0";
    salida << minuto << ":";

    if (segundo < 10) salida << "0";
    salida << segundo << " ";

    salida << ipPuerto << " " << mensaje;
    return salida.str();
}

// Operador < para ordenamiento por fecha
// Complejidad: O(1) tiempo, O(1) espacio
bool RegistroBitacora::operator<(const RegistroBitacora& other) const {
    return getFechaClave() < other.getFechaClave();
}

// Operador <= para búsquedas
// Complejidad: O(1) tiempo, O(1) espacio
bool RegistroBitacora::operator<=(const RegistroBitacora& other) const {
    return getFechaClave() <= other.getFechaClave();
}

// Convierte mes de texto a número
// Complejidad: O(1) tiempo, O(1) espacio
int RegistroBitacora::mesATextoANumero(const std::string& mesTexto) {
    if (mesTexto == "Jan") return 1;
    if (mesTexto == "Feb") return 2;
    if (mesTexto == "Mar") return 3;
    if (mesTexto == "Apr") return 4;
    if (mesTexto == "May") return 5;
    if (mesTexto == "Jun") return 6;
    if (mesTexto == "Jul") return 7;
    if (mesTexto == "Aug") return 8;
    if (mesTexto == "Sep") return 9;
    if (mesTexto == "Oct") return 10;
    if (mesTexto == "Nov") return 11;
    if (mesTexto == "Dec") return 12;
    return 0;
}

// Convierte mes de número a texto
// Complejidad: O(1) tiempo, O(1) espacio
std::string RegistroBitacora::mesNumeroATexto(int mes) {
    if (mes == 1) return "Jan";
    if (mes == 2) return "Feb";
    if (mes == 3) return "Mar";
    if (mes == 4) return "Apr";
    if (mes == 5) return "May";
    if (mes == 6) return "Jun";
    if (mes == 7) return "Jul";
    if (mes == 8) return "Aug";
    if (mes == 9) return "Sep";
    if (mes == 10) return "Oct";
    if (mes == 11) return "Nov";
    if (mes == 12) return "Dec";
    return "???";
}
