#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QTextStream>
#include <QFileDialog>
#include <QDebug>
#include <QContextMenuEvent>
#include "add.h"
#include "create.h"
#include "aboutprogram.h"
#include "help.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Laptop List");
    setWindowIcon(QIcon(":/rees/images/Laptop-icon.png"));
    this->addToolBar(Qt::LeftToolBarArea, ui->toolBar);
    ui->toolBar->setStyleSheet("background-color:indigo;");
    ui->menubar->setStyleSheet("background-color:rgb(155, 160, 255); color:indigo;"
                               "selection-background-color: indigo;"
                               "selection-color: white;");
    ui->centralwidget->setStyleSheet("background-color:rgb(200, 210, 250);");

    ui->doubleSpinBox_from->setMaximum(999999.9);
    ui->doubleSpinBox_to->setMaximum(999999.9);
    ui->spinBox_rom->setMaximum(102400);

    ui->tableWidget->setColumnCount(9);
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "Name of laptop"
                              << "Producer" << "Display size" << "Processor"
                              << "RAM" << "ROM" << "USBs amount" << "CD-ROM" << "Price");
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->tableWidget_required->setColumnCount(9);
    ui->tableWidget_required->setRowCount(0);
    ui->tableWidget_required->setHorizontalHeaderLabels(QStringList() << "Name of laptop"
                              << "Producer" << "Display size" << "Processor"
                              << "RAM" << "ROM" << "USBs amount" << "CD-ROM" << "Price");
    ui->tableWidget_required->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_required->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

MainWindow::~MainWindow()
{
    for(auto & tmp : arrLaptop){
        delete tmp;
        qDebug() << &tmp;
    }
    delete ui;
}

QVector<Laptop*>& MainWindow::getArray() {
    return arrLaptop;
}

void MainWindow::on_actionOpen_from_file_triggered()
{
    Laptop *element;
    try {
        QString fileName = QFileDialog:: getOpenFileName(this, "Opening file");
        //QTextStream file;
        QFile file(fileName);
        QTextStream in(&file);

        if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
            throw Exception(QString("Cannot open input file:\n" + fileName +
                                    "\nIt exists or has another address.").toStdString().c_str());
        }else{

            while(!in.atEnd()){
                element = new Laptop();
                in >> *element;
                arrLaptop.push_back(element);
            }

            file.close();
            if(arrLaptop.empty()){
                throw Exception(QString("Cannot scan data from file:\n\""
                                 + fileName + "\"\nBecause it's empty.").toStdString().c_str());
            } else {
                ui->label->setText("File was successfully scanned.");
                output(arrLaptop, ui->tableWidget);
                saved = false;
            }
        }
    }  catch (Exception &e) {
        delete element;
        QMessageBox::critical(this, "Invalid input file", e.what(), QMessageBox::Close);
    }
}

void MainWindow::view()
{
    for(int i = 0; i < arrLaptop.size(); i++) {

        // finding first lexem in name
        int p = 0;
        while ((p = (arrLaptop[i]->getName()).indexOf('_', p)) != -1) {
            arrLaptop[i]->getName()[p] = ' ';
            p++;
        }

        // finding first lexem in producer
        p = 0;
        while ((p = (arrLaptop[i]->getProducer()).indexOf('_', p)) != -1) {
            arrLaptop[i]->getProducer()[p] = ' ';
            p++;
        }

        // finding first lexem in processor
        p = 0;
        while ((p = (arrLaptop[i]->getProcessor()).indexOf('_', p)) != -1) {
            arrLaptop[i]->getProcessor()[p] = ' ';
            p++;
        }
    }
}

void MainWindow::output(QVector<Laptop*> array, QTableWidget* out)
{
    if(!array.empty()){

        out->setRowCount(array.size());
        this->view();

        for(int i = 0; i < out->rowCount(); i++){
            QTableWidgetItem *item = new QTableWidgetItem(array[i]->getName());

            out->setItem(i, 0, item);
            item = new QTableWidgetItem(array[i]->getProducer());
            out->setItem(i, 1, item);
            item = new QTableWidgetItem(QString::number(array[i]->getDisplaySize()));
            out->setItem(i, 2, item);
            item = new QTableWidgetItem(array[i]->getProcessor());
            out->setItem(i, 3, item);
            item = new QTableWidgetItem(QString::number(array[i]->getRam()));
            out->setItem(i, 4, item);
            item = new QTableWidgetItem(QString::number(array[i]->getRom()));
            out->setItem(i, 5, item);
            item = new QTableWidgetItem(QString::number(array[i]->getUsbCount()));
            out->setItem(i, 6, item);
            item = new QTableWidgetItem(array[i]->getCdRom() ? "+" : "-");
            out->setItem(i, 7, item);
            item = new QTableWidgetItem(QString::number(array[i]->getPrice()));
            out->setItem(i, 8, item);
        }
    }else
        QMessageBox::information(this, "Laptop list",
                                 "Nothing to display into table, list is empty", QMessageBox::Close);
}

void MainWindow::on_actionSort_by_manufacturer_triggered()
{
    try {
        if(arrLaptop.empty()){
            throw Exception("Nothing to sort, list is empty");
        } else{
            quickSort(0, arrLaptop.size() - 1);
            output(arrLaptop, ui->tableWidget);
            ui->label->setText("Laptop list, sorted by producer.");
            saved = false;
        }
    }  catch (Exception &e) {
        QMessageBox::information(this, "Laptop list", e.what(), QMessageBox::Close);
    }
}

void MainWindow::quickSort(int from, int to)
{
    if (from < to) {
        int divideIndex = partition(from, to);
        //output(from, to, divideIndex);
        quickSort(from, divideIndex - 1);
        quickSort(divideIndex, to);
    }
}

int MainWindow::partition( int from, int to) {
    int rightIndex = to;
    int leftIndex = from;

    QString pivot = arrLaptop[from + (to - from) / 2]->getProducer();
    while (leftIndex <= rightIndex) {
        while (arrLaptop[leftIndex]->getProducer() < pivot) {
            leftIndex++;
        }

        while (arrLaptop[rightIndex]->getProducer() > pivot) {
            rightIndex--;
        }

        if (leftIndex <= rightIndex) {
            Laptop *tmp  = new Laptop(*arrLaptop[rightIndex]);
            *arrLaptop[rightIndex] = *arrLaptop[leftIndex];
            *arrLaptop[leftIndex] = *tmp;

            leftIndex++;
            rightIndex--;
        }
    }
    return leftIndex;
}



void MainWindow::on_actionMost_RAM_and_CD_triggered()
{
    try {
        if(arrLaptop.empty()) {
            throw Exception("Nothing to display into table, initial list is empty");
        }
        QString currentProducer = ui->lineEdit_producer->text();
        QVector<Laptop*> selected;
        int maxRAM = arrLaptop[0]->getRam();

        for (int i = 1; i < arrLaptop.size(); i++) {
            if(arrLaptop[i]->getRam() > maxRAM) {
                maxRAM = arrLaptop[i]->getRam();
            }
        }

        for (int i = 0; i < arrLaptop.size(); i++) {
            if(arrLaptop[i]->getProducer() == currentProducer
                            && arrLaptop[i]->getRam() == maxRAM
                            && arrLaptop[i]->getCdRom()) {
                selected.push_back(arrLaptop[i]);
            }
        }
        if(selected.empty()) {
            throw Exception("Nothing to display into table, "
                            "there is no requred elements in initial list");
        }
        output(selected, ui->tableWidget_required);
        ui->label->setText(currentProducer + " laptops with maximum RAM and with CD-ROM.");
    }  catch (Exception &e) {
        QMessageBox::information(this, "Laptop list", e.what(), QMessageBox::Close);
    }
}

void MainWindow::on_actionIntel_and_13_14_display_triggered()
{
    try {
        if(arrLaptop.empty()) {
            throw Exception("Nothing to display into table, initial list is empty");
        }
        int currentROM = ui->spinBox_rom->value();
        QVector<Laptop*> selected;

        for (int i = 0; i < arrLaptop.size(); i++) {
            if(arrLaptop[i]->getDisplaySize() >= 13
                            && arrLaptop[i]->getDisplaySize() <= 14
                            && arrLaptop[i]->getRom() == currentROM
                            && arrLaptop[i]->getProcessor() == "Intel") {
                selected.push_back(arrLaptop[i]);
            }
        }
        if(selected.empty()) {
            throw Exception("Nothing to display into table, "
                            "there is no requred elements in initial list");
        }
        output(selected, ui->tableWidget_required);
        ui->label->setText(QString::number(currentROM) + " GB laptops with 13” – 14”"
                                                         " display and Intel processor.");
    }  catch (Exception &e) {
        QMessageBox::information(this, "Laptop list", e.what(), QMessageBox::Close);
    }
}

void MainWindow::on_actionMost_USBs_and_AMD_triggered()
{
    try {
        if(arrLaptop.empty()) {
            throw Exception("Nothing to display into table, initial list is empty");
        }
        QVector<Laptop*> selected;
        int maxUSB = arrLaptop[0]->getUsbCount();

        for (int i = 1; i < arrLaptop.size(); i++) {
            if(arrLaptop[i]->getUsbCount() > maxUSB) {
                maxUSB = arrLaptop[i]->getUsbCount();
            }
        }

        for (int i = 0; i < arrLaptop.size(); i++) {
            if(arrLaptop[i]->getUsbCount() == maxUSB
                            && arrLaptop[i]->getProcessor() == "AMD") {
                selected.push_back(arrLaptop[i]);
            }
        }
        if(selected.empty()) {
            throw Exception("Nothing to display into table, "
                            "there is no requred elements in initial list");
        }
        output(selected, ui->tableWidget_required);
        ui->label->setText("Laptops with maximum USBs and AMD processor.");
    }  catch (Exception &e) {
        QMessageBox::information(this, "Laptop list", e.what(), QMessageBox::Close);
    }
}

void MainWindow::on_actionAverage_RAM_by_producer_triggered()
{
    try {
        if(arrLaptop.empty()) {
            throw Exception("Nothing to display into table, initial list is empty");
        }
        QString currentProducer = ui->lineEdit_producer->text();
        QVector<Laptop*> selected;
        int sumRAM = 0;
        double averageRAM = 0;

        for (int i = 0; i < arrLaptop.size(); i++) {
            sumRAM += arrLaptop[i]->getRam();
        }

        averageRAM = 1.0 * sumRAM / arrLaptop.size();
        //qDebug() << averageRAM;

        for (int i = 0; i < arrLaptop.size(); i++) {
            if(arrLaptop[i]->getRam() >= averageRAM - 0.3 * averageRAM
                    && arrLaptop[i]->getRam() <= averageRAM + 0.3 * averageRAM
                    && arrLaptop[i]->getProducer() == currentProducer) {
                selected.push_back(arrLaptop[i]);
            }
        }
        if(selected.empty()) {
            throw Exception("Nothing to display into table, "
                            "there is no requred elements in initial list");
        }
        output(selected, ui->tableWidget_required);
        ui->label->setText(currentProducer + " laptops in ±30% range from average RAM.");
    }  catch (Exception &e) {
        QMessageBox::information(this, "Laptop list", e.what(), QMessageBox::Close);
    }
}

void MainWindow::on_action_Price_limits_triggered()
{
    try {
        if(arrLaptop.empty()) {
            throw Exception("Nothing to display into table, initial list is empty");
        }
        double fromPrice = ui->doubleSpinBox_from->value();
        double toPrice = ui->doubleSpinBox_to->value();
        QVector<Laptop*> selected;

        for (int i = 0; i < arrLaptop.size(); i++) {
            if(arrLaptop[i]->getPrice() >= fromPrice
                    && arrLaptop[i]->getPrice() <= toPrice) {
                selected.push_back(arrLaptop[i]);
            }
        }
        if(selected.empty()) {
            throw Exception("Nothing to display into table, "
                            "there is no requred elements in initial list");
        }
        output(selected, ui->tableWidget_required);
        ui->label->setText("Laptops from " + QString::number(fromPrice) +
                           " to " + QString::number(toPrice) + " UAH range.");
    }  catch (Exception &e) {
        QMessageBox::information(this, "Laptop list", e.what(), QMessageBox::Close);
    }
}

void MainWindow::on_actionRenew_list_triggered()
{
    if(!arrLaptop.empty()){
        int sizeArr = arrLaptop.size();
        int sizeSecond = ui->tableWidget_required->rowCount();
        for (int i = 0; i < sizeArr; i++) {
            arrLaptop.erase(arrLaptop.begin());
            ui->tableWidget->removeRow(0);
        }
        for (int i = 0; i < sizeSecond; i++) {
            ui->tableWidget_required->removeRow(0);
        }
        ui->label->setText("List of laptops was cleared.");
    }
}

void MainWindow::on_actionAdd_laptop_triggered()
{
    Add addForm;
    addForm.setModal(true);
    int size = arrLaptop.size();
    addForm.exec();
    if(arrLaptop.size() > size){
        output(arrLaptop, ui->tableWidget);
        ui->label->setText("List of laptops with keyboard-added elements.");
        saved = false;
    }
}

void MainWindow::on_actionCreate_new_triggered()
{
    Create howMany;
    howMany.setModal(true);
    howMany.exec();
}

void MainWindow::on_actionSave_to_file_triggered()
{
    try {
        if(!saved){
            if(arrLaptop.empty())
                QMessageBox::information(this, "ListOfBooks", "Nothing to save into file,"
                                                          " list is empty", QMessageBox::Close);
            else{
                if(currentSaveFile == ""){
                    QString fileName = QFileDialog::getSaveFileName(this, "Saving list");
                    currentSaveFile = fileName;
                    QFile file(currentSaveFile);
                    if(file.open(QIODevice::WriteOnly | QIODevice::Text)){
                        QTextStream out(&file);
                        QVector<Laptop*>::iterator iter;
    //                    out << "Author \t " << "Name of book \t\t " << "Year  "
    //                        << "Count of pages  " << "Price" << endl;
                        for(iter = arrLaptop.begin(); iter != arrLaptop.end(); iter++){
                            out << **iter;
                        }
                        out.flush();
                        file.close();
                        saved = true;
                    } else
                        throw Exception(QString("Cannot open output file:\n" + currentSaveFile +
                                            "\nIt exists or has another address.").toStdString().c_str());
                } else {
                    QFile file(currentSaveFile);
                    if(file.open(QIODevice::WriteOnly | QIODevice::Text)){
                        QTextStream out(&file);
                        QVector<Laptop*>::iterator iter;
    //                    out << "Author  " << "Name of book  " << "Year  "
    //                        << "Count of pages  " << "Price" << endl;
                        for(iter = arrLaptop.begin(); iter != arrLaptop.end(); iter++){
                            out << **iter;
                        }
                        out.flush();
                        file.close();
                        saved = true;
                    } else
                        throw Exception(QString("Cannot open output file:\n" + currentSaveFile +
                                            "\nIt exists or has another address.").toStdString().c_str());
                }
            }
        }
    }  catch (Exception &exc) {
        QMessageBox::critical(this, "Invalid input file", exc.what(), QMessageBox::Close);
    }
}

void MainWindow::contextMenuEvent(QContextMenuEvent *event){
    QMenu menu(this);
    menu.setStyleSheet("background-color:rgb(155, 160, 255); color:indigo;"
                               "selection-background-color: indigo;"
                               "selection-color: white;");
    menu.addAction(ui->actionAdd_laptop);
    menu.addAction(ui->actionSort_by_manufacturer);
    menu.addAction(ui->actionMost_RAM_and_CD);
    menu.addAction(ui->actionIntel_and_13_14_display);
    menu.addAction(ui->actionMost_USBs_and_AMD);
    menu.addAction(ui->actionAverage_RAM_by_producer);
    menu.addAction(ui->action_Price_limits);
    menu.addAction(ui->actionRenew_list);
    menu.addAction(ui->actionSave_close);

    menu.exec(event->globalPos());
}

void MainWindow::on_actionSave_close_triggered()
{
    if(!arrLaptop.empty()){
        if (!saved) {

            QMessageBox msgBox;
            msgBox.setWindowIcon(QIcon(":/rees/images/Laptop-icon.png"));
            msgBox.setText("The list of laptops has been modified.");
            msgBox.setIcon(QMessageBox::Question);
            msgBox.setInformativeText("Do you want to save your changes before closing?");
            msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
            msgBox.setDefaultButton(QMessageBox::Save);
            int answer = msgBox.exec();
            if( answer == QMessageBox::Discard) {
                QApplication::quit();
            } else if (answer == QMessageBox::Save){
                on_actionSave_to_file_triggered();
                if(saved)
                    QApplication::quit();
            }
         } else {
            QApplication::quit();
        }
    }else
        QApplication::quit();
}

void MainWindow::closeEvent(QCloseEvent *event) {
    on_actionSave_close_triggered();
}

void MainWindow::on_actionAbout_program_triggered()
{
    AboutProgram info;
    info.setModal(true);
    info.exec();
}

void MainWindow::on_actionLaptopList_help_triggered()
{
    Help help;
    help.setModal(true);
    help.exec();
}
