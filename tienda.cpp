#include "tienda.h"
#include "ui_tienda.h"
#include "ui_acerca.h"
#include "ui_factura.h"


Tienda::Tienda(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Tienda)
{
    ui->setupUi(this);
    m_porGuardar = false;
    // Lista de productos
    cargarProductos();
    // Mostrar los productos en el combo
    // Lazo de repetición que me permite navegar por los elementos de la lista
    foreach (Producto *p, m_productos){
        ui->inProducto->addItem(p->nombre());
    }
    // Configurar cabecera de la tabla
    QStringList cabecera = {"Cantidad", "Producto", "P. unitario", "Subtotal"};
    ui->outDetalle->setColumnCount(4);
    ui->outDetalle->setHorizontalHeaderLabels(cabecera);
    // Establecer el subtotal a 0
    m_subtotal = 0;
}

Tienda::~Tienda()
{
    delete ui;
}
/**
 * @brief Tienda::cargarProductos Carga la lista de productos de la tienda
 */
void Tienda::cargarProductos()
{
    // Crear productos "quemados" en el código
     m_productos.append(new Producto(1, "Leche", 0.80));
     m_productos.append(new Producto(2, "Pan", 0.15));
     m_productos.append(new Producto(3, "Queso", 2.50));
     m_productos.append(new Producto(4,"Yougurth",0.80));
    // Podría leerse de una base de datos, de un archivo o incluso de Internet
    //para obtener el archivo

    /*QDir actual = QDir::current(); //directorio actual
    // El path al archivo CSV
    QString archivoProductos = actual.absolutePath() + "/debug/Productos.csv";
    QFile archivo(archivoProductos);

    //qDebug() << archivo.fileName();

    if (archivo.open(QIODevice::ReadOnly | QIODevice::Text)){

        bool primera = true;
        QTextStream in(&archivo);
        while (!in.atEnd()) {
            QString linea = in.readLine();
            if (primera){
                primera = false;
                continue;
            }
            QStringList datos = linea.split(";");
            QString precio = datos.at(2);
            float p = precio.toFloat();
            int id = datos.at(0).toInt();
            m_productos.append(new Producto(id, datos.at(1), p));
        }
        archivo.close();
    }else{
        qDebug()<< "No se pudo abrir el archivo";
    }*/
}


void Tienda::calcular(float stProducto)
{
    // Calcular valores
    m_subtotal += stProducto;
    float iva = m_subtotal * IVA / 100;
    float total = m_subtotal + iva;
    // Mostrar valores en GUI
    ui->outSubtotal->setText("$ " + QString::number(m_subtotal, 'f', 2));
    ui->outIva->setText("$ " + QString::number(iva, 'f', 2));
    ui->outTotal->setText("$ " + QString::number(total, 'f', 2));
}

void Tienda::salir()
{
    if(m_porGuardar){
        int respuesta = QMessageBox::warning(
                    this,"Salir",
                    "¿Desea guardar el Archivo?","Aceptar","Cancelar");
        if(respuesta == QMessageBox::AcceptRole){
            on_actionGuardar_triggered();
        }
    }
    this->close();
}

/**
 * @brief Tienda::on_inProducto_currentIndexChanged Slot que se dispara al cambiar un elemento
 * @param index Numero del elemento seleccionado en el combo
 */

void Tienda::on_inProducto_currentIndexChanged(int index)
{
    // Obtener el precio del producto actual seleccionado
    float precio = m_productos.at(index)->precio();
    // Mostrar el precio del product en la etiqueta
    ui->outPrecio->setText("$ " + QString::number(precio,'f',2));
    // Resetear el spinbox de cantidad
    ui->inCantidad->setValue(0);
}


void Tienda::on_btnAgregar_released()
{
    // Validar que no se agregen productos con cantidad = 0
    int cantidad = ui->inCantidad->value();
    if (cantidad == 0){
        //Mostrar un Error en la barra de Estado
        ui->statusbar->showMessage("La cantidad no puede ser 0");
        return;
    }
    // Obtener los datos de la GUI
    int i = ui->inProducto->currentIndex();
    Producto *p = m_productos.at(i);

    // Calcular el subrotal del producto
    float subtotal = p->precio() * cantidad;

    // Agregar los datos a la tabla
    int fila = ui->outDetalle->rowCount();
    ui->outDetalle->insertRow(fila);
    ui->outDetalle->setItem(fila, 0, new QTableWidgetItem(QString::number(cantidad)));
    ui->outDetalle->setItem(fila, 1, new QTableWidgetItem(p->nombre()));
    ui->outDetalle->setItem(fila, 2, new QTableWidgetItem(QString::number(p->precio(),'f',2)));
    ui->outDetalle->setItem(fila, 3, new QTableWidgetItem(QString::number(subtotal,'f',2)));

    // Podria leerse de una base de datos
    // Limpiar datos
    ui->inCantidad->setValue(0);
    ui->inProducto->setFocus();

    // Actualizar subtotales
    calcular(subtotal);

}

void Tienda::on_actionAcerca_de_triggered()
{
    // Crear un objeto del cuadro de diálogo
    // Acerca *informacion = new Acerca(this);
    // Enviar datos a la otra ventana
    // informacion->setVersion(VERSION);
    // Mostrar la venta en modo MODAL
    // dialog->exec();
    // informacion->exec();
    // qDebug() << dialog->valor();

}


void Tienda::on_actionNuevo_triggered()
{
    //ui->outDetalle->clearContents();
    while(ui->outDetalle->rowCount() > 0){
        ui->outDetalle->removeRow(0);
    }
}

void Tienda::on_actionAbrir_triggered()
{
    QFile arch;
    QTextStream io;
    QString nombreArch;
    nombreArch = QFileDialog::getOpenFileName(this, "Abrir");
    arch.setFileName(nombreArch);
    arch.open(QIODevice::ReadOnly | QIODevice::Text);
    if(!arch.isOpen()){
        QMessageBox::critical(this, "Error !!!", arch.errorString());
        return;
    }
    io.setDevice(&arch);
    // ui->outDetalle(io.readAll());
    arch.flush();
    arch.close();
}

void Tienda::on_actionGuardar_triggered()
{
    // Abrir un cuadro de diálogo para seleccionar la ruta y archivar a guardar
    QString nombreArchivo = QFileDialog::getSaveFileName ( this , " Guardar Factura de Compra " ,
                                                           QDir::home().absolutePath() + " /factura.csv " ,
                                                           " Archivos de calculo (*.csv)" );
    // Crear un objeto File o un Archivo
    QFile archivo (nombreArchivo);
    if (archivo. open (QFile::WriteOnly | QFile::Truncate)){
        // Crear un objeto "stream" de texto
        QTextStream salida (&archivo);
        // Enviar los datos del resultado a la salida
        salida << ui->outDetalle;
        // Mostrar mensaje en la barra de estados
        ui->statusbar->showMessage("Datos guardados en: " + nombreArchivo, 5000);
        // Crear el archivo
        archivo.close();
    } else {
        // Mensaje de error
        QMessageBox::warning(this ,
                             " Guardar archivo " ,
                             " Nose puede acceder al archivo para guardar los datos " );
    }
}

void Tienda::on_actionSalir_triggered()
{
    salir();
}

void Tienda::on_pushButton_clicked()
{
    if(ui->inCedula->displayText().isEmpty()){
        QMessageBox::warning(this, "Advertencia", "El campo de la cedula esta vacia");
        return;
    }else if(ui->inEmail->displayText().isEmpty()){
        QMessageBox::warning(this, "Advertencia", "El campo del E-mail esta vacio");
        return;
    }else if(ui->inNombre->displayText().isEmpty()){
        QMessageBox::warning(this, "Advertencia", "El campo del nombre esta vacio");
        return;
    }
}

