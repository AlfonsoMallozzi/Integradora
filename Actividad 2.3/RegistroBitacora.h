#ifndef REGISTRO_BITACORA_H
#define REGISTRO_BITACORA_H

#include <string>
#include <tuple>

class RegistroBitacora {
private:
    int mes;
    int dia;
    int hora;
    int minuto;
    int segundo;

    std::string ipPuerto;
    std::string mensaje;

public:
    RegistroBitacora();
    RegistroBitacora(int mes, int dia, int hora, int minuto, int segundo,
                     const std::string& ipPuerto,
                     const std::string& mensaje);

    int getMes() const;
    int getDia() const;
    int getHora() const;
    int getMinuto() const;
    int getSegundo() const;
    std::string getIpPuerto() const;
    std::string getMensaje() const;

    // Complejidad: O(1) tiempo, O(1) espacio
    std::tuple<int,int,int,int,int> getFechaClave() const;

    // Complejidad: O(n) tiempo, O(n) espacio
    std::string toString() const;

    // Complejidad: O(1) tiempo, O(1) espacio
    bool operator<(const RegistroBitacora& other) const;
    bool operator<=(const RegistroBitacora& other) const;

    static int mesATextoANumero(const std::string& mesTexto);
    static std::string mesNumeroATexto(int mes);
};

#endif
