#ifndef TIENDA_H
#define TIENDA_H

#include <QMainWindow>
#include <QDebug>
#include <QDialog>
#include <QDir>
#include <QMessageBox>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>

#include "producto.h"
#include "ui_acerca.h"
#include "ui_factura.h"

#define IVA 12

QT_BEGIN_NAMESPACE
namespace Ui { class Tienda; }
QT_END_NAMESPACE

class Tienda : public QMainWindow
{
    Q_OBJECT

public:
    Tienda(QWidget *parent = nullptr);
    ~Tienda();

private slots:
    void on_inProducto_currentIndexChanged(int index);
    void on_btnAgregar_released();
    void on_actionAcerca_de_triggered();
    void on_actionNuevo_triggered();
    void on_actionGuardar_triggered();
    void on_actionSalir_triggered();
    void on_actionAbrir_triggered();
    void on_btnAgregar_clicked();

    void on_inProducto_activated(int index);

    void on_pushButton_clicked();

private:
    Ui::Tienda *ui;
    QList<Producto*> m_productos;
    void cargarProductos();
    float m_subtotal;
    void calcular(float stProducto);
    void salir();
    bool m_porGuardar;

};
#endif // TIENDA_H
