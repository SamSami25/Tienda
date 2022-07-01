#include "acerca.h"
#include "ui_acerca.h"

Acerca::Acerca(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Acerca)
{
    ui->setupUi(this);
    m_version = "v 0.0";
}

Acerca::~Acerca()
{
    delete ui;
}
void Acerca::setVersion(const QString &newVersion)
{
    m_version = newVersion;
    ui->outVersion->setText("v " + m_version);
}
