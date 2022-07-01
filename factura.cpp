#include "factura.h"


Factura::Factura(QString cedula, QString nombre)
{
    this->cedula=cedula;
    this->nombre=nombre;
}

QString Factura::getCedula()
{
     return this->cedula;
}

QString Factura::getNombre()
{
    return this->nombre;
}

void Factura::setCedula(QString cedula)
{
     this->cedula=cedula;
}

void Factura::setNombre(QString nombre)
{
     this->nombre=nombre;
}
