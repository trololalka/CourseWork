#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "laptop.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void view();
    void output(QVector<Laptop*>, QTableWidget*);
    void quickSort(int, int);
    int partition(int, int);
    QVector<Laptop*>& getArray();

public slots:
    void on_actionAdd_laptop_triggered();

private slots:
    void on_actionOpen_from_file_triggered();
    void on_actionSort_by_manufacturer_triggered();
    void on_actionMost_RAM_and_CD_triggered();
    void on_actionIntel_and_13_14_display_triggered();
    void on_actionMost_USBs_and_AMD_triggered();
    void on_actionAverage_RAM_by_producer_triggered();
    void on_action_Price_limits_triggered();
    void on_actionRenew_list_triggered();
    void on_actionCreate_new_triggered();
    void on_actionSave_to_file_triggered();
    void on_actionSave_close_triggered();
    void contextMenuEvent(QContextMenuEvent *event);
    void closeEvent(QCloseEvent *event);

    void on_actionAbout_program_triggered();

    void on_actionLaptopList_help_triggered();

private:
    Ui::MainWindow *ui;
    QVector<Laptop*> arrLaptop;
    bool saved = false;
    QString currentSaveFile = "";
};
extern MainWindow *w;
#endif // MAINWINDOW_H
