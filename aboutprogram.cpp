#include "aboutprogram.h"
#include "ui_aboutprogram.h"

AboutProgram::AboutProgram(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutProgram)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    setWindowTitle("About program");
    setWindowIcon(QIcon(":/rees/images/Laptop-icon.png"));
    setStyleSheet("background-color:rgb(200, 210, 250);");

    QPixmap pic(":/rees/images/Male-Face-icon.png");
    ui->label_icon->setScaledContents(true);
    ui->label_icon->setPixmap(pic);

    ui->pushButton_close->setStyleSheet("background-color:rgb(155, 160, 255); color:indigo;");

}

AboutProgram::~AboutProgram()
{
    delete ui;
}

void AboutProgram::on_pushButton_close_clicked()
{
    close();
}
