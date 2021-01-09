#include "laptop.h"
#include <sstream>
#include <QMessageBox>
#include <QTextStream>

Exception::Exception(const char* err){
    problem = err;
}

const char* Exception::what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_USE_NOEXCEPT{
    return problem;
}

bool isDouble(const std::string& s)
{
  std::istringstream i(s);
  double temp;
  return ((i >> temp) ? true : false);
}

bool isNumber(const std::string &s) {
    return !s.empty() && (std::all_of(s.begin(), s.end(), ::isdigit));
}

Computer::Computer(): name(""), producer(""),
           procesor(""), ram(0), rom(0) {}

Computer::Computer(QString _name, QString _producer, QString _proc,
           int _ram, int _rom): name(_name), producer(_producer),
           procesor(_proc), ram(_ram), rom(_rom) {}

Laptop::Laptop(): Computer("", "", "", 0, 0),
    displaySize(0), usbCount(0),
    cdRom(false), price(0) {}

Laptop::Laptop (QString _name, QString _producer, QString _proc,
           int _ram, int _rom, int _displaySize,
           int _usbCount, bool _cdRom, double _price):
           Computer(_name, _producer, _proc,
           _ram, _rom), displaySize(_displaySize),
           usbCount(_usbCount), cdRom(_cdRom), price(_price) {};

Laptop::Laptop(const Laptop& elem)
{
    name = elem.name;
    producer = elem.producer;
    procesor = elem.procesor;
    ram = elem.ram;
    rom = elem.rom;

    displaySize = elem.displaySize;
    usbCount = elem.usbCount;
    cdRom = elem.cdRom;
    price = elem.price;
}

QString& Laptop::getName() {
    return name;
};

QString Laptop::getProducer() {
    return producer;
};

QString Laptop::getProcessor() {
    return procesor;
};

int Laptop::getRam() {
    return ram;
};

int Laptop::getRom() {
    return rom;
};

int Laptop::getDisplaySize() {
    return displaySize;
};

int Laptop::getUsbCount() {
    return usbCount;
};

bool Laptop::getCdRom() {
    return cdRom;
};

double Laptop::getPrice() {
    return price;
};

void Laptop::setName(QString _name) {
    name = _name;
};

void Laptop::setProducer(QString _prod) {
    producer = _prod;
};
void Laptop::setProcessor(QString _proc) {
    procesor = _proc;
};

void Laptop::setRam(int _ram) {
    ram = _ram;
};

void Laptop::setRom(int _rom) {
    rom = _rom;
};

void Laptop::setDisplaySize(int _dSize) {
    displaySize = _dSize;
};

void Laptop::setUsbCount(int _usb) {
    usbCount = _usb;
};

void Laptop::setCdRom(bool _cd) {
    cdRom = _cd;
};

void Laptop::setPrice(double _price) {
    price = _price;
};

Laptop& Laptop::operator=(const Laptop &elem) {
    name = elem.name;
    producer = elem.producer;
    procesor = elem.procesor;
    ram = elem.ram;
    rom = elem.rom;

    displaySize = elem.displaySize;
    usbCount = elem.usbCount;
    cdRom = elem.cdRom;
    price = elem.price;

    return *this;
}

void operator>> (QTextStream &file, Laptop &elem)
{
    /*
    out << elem.getName() << " \t\t " << elem.getProducer() << " \t\t "
        << elem.getDisplaySize() << "  " << elem.getProcessor()  << "  "
        << elem.getRam() << "  " << elem.getRom() << "  "
        << elem.getUsbCount() << "  " << elem.getCdRom() << "  "
        << elem.getPrice()  << Qt::endl;
    */
    QString str = "";
    file >> str;
    if(str != ""){
        elem.setName(str);
    }else{
        throw Exception("Cannot scan all data from file: \nEmpty laptop name.\n");

//                QMessageBox::warning(this, "Warning", "Cannot scan all data from file: \n"
//                                      "Empty laptop name.", QMessageBox::Cancel);
    }

    str = "";
    file >> str;
    if(str != ""){
        elem.setProducer(str);
    }else{
        throw Exception("Cannot scan all data from file: \nEmpty producer name.\n");
    }

    str = "";
    file >> str;
    if(isNumber(str.toStdString())){
        elem.setDisplaySize(stoi(str.toStdString()));
    }else{
        throw Exception("Cannot scan all data from file: \nLiteral in display size number.\n");
    }

    str = "";
    file >> str;
    if(str != ""){
        elem.setProcessor(str);
    }else{
        throw Exception("Cannot scan all data from file: \nEmpty processor name.\n");
    }

    str = "";
    file >> str;
    if(isNumber(str.toStdString())){
        elem.setRam(stoi(str.toStdString()));
    }else{
        throw Exception("Cannot scan all data from file: \nLiteral in RAM number.\n");
    }

    str = "";
    file >> str;
    if(isNumber(str.toStdString())){
        elem.setRom(stoi(str.toStdString()));
    }else{
        throw Exception("Cannot scan all data from file: \nLiteral in ROM number.\n");
    }

    str = "";
    file >> str;
    if(isNumber(str.toStdString())){
        elem.setUsbCount(stoi(str.toStdString()));
    }else{
        throw Exception("Cannot scan all data from file: \nLiteral in USB count number.\n");
    }

    str = "";
    file >> str;
    if(str == "true"){
        elem.setCdRom(true);
    }else{
        elem.setCdRom(false);
    }

    str = "";
    file >> str;
    if(isDouble(str.toStdString())){
        elem.setPrice(stod(str.toStdString()));
    }else{
        throw Exception("Cannot scan all data from file: \nLiteral in price number.\n");
    }
}

void operator<< (QTextStream &out, Laptop &elem)
{
    out.setFieldWidth(20);
    out << elem.getName();
    out.setFieldWidth(15);
    out << elem.getProducer();
    out.setFieldWidth(6);
    out << elem.getDisplaySize() << "  " << elem.getProcessor()  << "  "
        << elem.getRam() << "  " << elem.getRom() << "  "
        << elem.getUsbCount() << "  " << elem.getCdRom() << "  "
        << elem.getPrice()  << Qt::endl;
}
