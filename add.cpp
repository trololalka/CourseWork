#include "add.h"
#include "ui_add.h"
#include "mainwindow.h"
#include <QDebug>
#include <QMessageBox>

#define EPS 0.001

Add::Add(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Add)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    setWindowTitle("Add laptop");
    setWindowIcon(QIcon(":/rees/images/Laptop-icon.png"));
    setStyleSheet("background-color:rgb(200, 210, 250);");

    ui->lineEdit_name->setPlaceholderText("Mi Notebook Pro");
    ui->lineEdit_processor->setPlaceholderText("Intel");
    ui->lineEdit_producer->setPlaceholderText("Xiaomi");
    ui->label_error->hide();
    ui->spinBox_rom->setMaximum(102400);
    ui->spinBox_ram->setMaximum(1024);
    ui->spinBox_usb->setMaximum(20);
    ui->spinBox_displaySize->setMaximum(99);
    ui->doubleSpinBox_price->setMaximum(200000.0);

    ui->pushButton_cancel->setStyleSheet("background-color:rgb(155, 160, 255); color:indigo;");
    ui->pushButton_ok->setStyleSheet("background-color:rgb(155, 160, 255); color:indigo;");
}

Add::~Add()
{
    delete ui;
}

void Add::on_pushButton_ok_clicked()
{
    try {
        Laptop *laptop = new Laptop();
        if(!ui->lineEdit_name->text().isEmpty())
            laptop->setName(ui->lineEdit_name->text());
        else {
            delete laptop;
            throw Exception("Cannot scan all data from input form: \nEmpty laptop name.\n");
        }
        if(!ui->lineEdit_producer->text().isEmpty())
            laptop->setProducer(ui->lineEdit_producer->text());
        else {
            delete laptop;
            throw Exception("Cannot scan all data from input form: \nEmpty producer name.\n");
        }
        if(!ui->lineEdit_processor->text().isEmpty())
            laptop->setProcessor(ui->lineEdit_processor->text());
        else {
            delete laptop;
            throw Exception("Cannot scan all data from input form: \nEmpty processor name.\n");
        }
        if(ui->spinBox_displaySize->value())
            laptop->setDisplaySize(ui->spinBox_displaySize->value());
        else {
            delete laptop;
            throw Exception("Cannot scan all data from input form: \nDisplay size cannot be equal to zero.\n");
        }
        if(ui->spinBox_ram->value())
            laptop->setRam(ui->spinBox_ram->value());
        else {
            delete laptop;
            throw Exception("Cannot scan all data from input form: \nRAM size cannot be equal to zero.\n");
        }
        if(ui->spinBox_rom->value())
            laptop->setRom(ui->spinBox_rom->value());
        else {
            delete laptop;
            throw Exception("Cannot scan all data from input form: \nROM size cannot be equal to zero.\n");
        }
        if(ui->spinBox_usb->value())
            laptop->setUsbCount(ui->spinBox_usb->value());
        else {
            delete laptop;
            throw Exception("Cannot scan all data from input form: \nUSBs amount cannot be equal to zero.\n");
        }
        laptop->setCdRom(ui->checkBox_cdRom->isChecked());
        if(ui->doubleSpinBox_price->value() > EPS)
            laptop->setPrice(ui->doubleSpinBox_price->value());
        else {
            delete laptop;
            throw Exception("Cannot scan all data from input form: \nPrice cannot be equal to zero.\n");
        }

        int i = 0;
        if(!(w->getArray().empty())) {
            QVector<Laptop*>::iterator iter;
            iter = w->getArray().begin();
            while((iter != w->getArray().end())
                        &&(laptop->getProducer() > (*iter)->getProducer())){
                ++i;
                ++iter;
            }
        }
        w->getArray().insert(i, laptop);
        this->close();

    }  catch (Exception &exc) {;
        QMessageBox::information(this, "Add Form", exc.what(), QMessageBox::Close);
    }
}
void Add::on_pushButton_cancel_clicked()
{
    this->close();
}
