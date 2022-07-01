#ifndef PERSONA_H
#define PERSONA_H

#include <QString>

class
{
public:
    cliente(QString cedula,QString nombre);
    //get
    QString getCedula();
    QString getNombre();
    //set
    void setCedula(QString cedula);
    void setNombre(QString nombre);
private:
    QString cedula;
    QString nombre;
};

#endif // PERSONA_H
