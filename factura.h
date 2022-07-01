#ifndef FACTURA_H
#define FACTURA_H

#include <QString>

class Factura
{

private:

    QString cedula;
    QString nombre;

public:

    Factura(QString cedula,QString nombre);
    QString getCedula();
    QString getNombre();
    void setCedula(QString cedula);
    void setNombre(QString nombre);


};

#endif // FACTURA_H
