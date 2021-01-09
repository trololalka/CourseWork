#include "create.h"
#include "ui_create.h"
#include "mainwindow.h"

Create::Create(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Create)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    setWindowTitle("Create new list");
    setWindowIcon(QIcon(":/rees/images/Laptop-icon.png"));
    setStyleSheet("background-color:rgb(200, 210, 250);");

    ui->pushButton_cancel->setStyleSheet("background-color:rgb(155, 160, 255); color:indigo;");
    ui->pushButton_ok->setStyleSheet("background-color:rgb(155, 160, 255); color:indigo;");
}

Create::~Create()
{
    delete ui;
}

void Create::on_pushButton_ok_clicked()
{
    int count = ui->spinBox->value();
    for (int i = 0; i<count; ++i) {
        w->on_actionAdd_laptop_triggered();
    }
    this->close();
}

void Create::on_pushButton_cancel_clicked()
{
    this->close();
}
