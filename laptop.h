#ifndef LAPTOP_H
#define LAPTOP_H
#include <QString>
#include <QTableWidget>
#include <exception>
#include <fstream>

class Exception: public std::exception
{
    const char* problem;
public:
    Exception(const char*);
    virtual const char* what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_USE_NOEXCEPT;
};

class Computer
{
protected:
    QString name;
    QString producer;
    QString procesor;
    int ram;
    int rom;

public:
    Computer();
    Computer(QString _name, QString _producer, QString _proc,
              int _ram, int _rom);
    //~Computer();
};

class Laptop: public Computer
{
    int displaySize;
    int usbCount;
    bool cdRom;
    double price;

public:
    Laptop();
    Laptop(QString _name, QString _producer, QString _proc,
              int _ram, int _rom, int _displaySize,
              int _usbCount, bool _cdRom, double _price);
    Laptop(const Laptop&);
    //~Laptop();

    QString& getName();
    QString getProducer();
    QString getProcessor();
    int getRam();
    int getRom();
    int getDisplaySize();
    int getUsbCount();
    bool getCdRom();
    double getPrice();

    void setName(QString);
    void setProducer(QString);
    void setProcessor(QString);
    void setRam(int);
    void setRom(int);
    void setDisplaySize(int);
    void setUsbCount(int);
    void setCdRom(bool);
    void setPrice(double);

    Laptop& operator=(const Laptop& elem);
    friend void operator>> (QTextStream &file, Laptop &elem);
    friend void operator<< (QTextStream &out, Laptop &elem);

};

#endif // LAPTOP_H
