#ifndef REGISTRO_BITACORA_H
#define REGISTRO_BITACORA_H

#include <string>
#include <tuple>

/*
 * Clase que representa un registro de la bitácora.
 * Cada objeto corresponde a una línea del archivo bitacoraData.txt
 */
class RegistroBitacora {
private:
    // Fecha y hora
    int mes;
    int dia;
    int hora;
    int minuto;
    int segundo;

    // Información del evento
    std::string ipPuerto;
    std::string mensaje;

public:
    // Constructores
    RegistroBitacora();
    RegistroBitacora(int mes, int dia, int hora, int minuto, int segundo,
                     const std::string& ipPuerto,
                     const std::string& mensaje);

    // Getters
    int getMes() const;
    int getDia() const;
    int getHora() const;
    int getMinuto() const;
    int getSegundo() const;
    std::string getIpPuerto() const;
    std::string getMensaje() const;

    // Clave de fecha para ordenar y buscar
    // Complejidad: O(1) tiempo, O(1) espacio
    std::tuple<int,int,int,int,int> getFechaClave() const;

    // Devuelve el registro en formato original
    // Complejidad: O(n) tiempo, O(n) espacio
    std::string toString() const;

    // Operadores para ordenamiento y búsqueda
    // Complejidad: O(1) tiempo, O(1) espacio
    bool operator<(const RegistroBitacora& other) const;
    bool operator<=(const RegistroBitacora& other) const;

    // Utilidades para conversión de mes
    // Complejidad: O(1) tiempo, O(1) espacio
    static int mesATextoANumero(const std::string& mesTexto);
    static std::string mesNumeroATexto(int mes);
};

#endif
