#include "help.h"
#include "ui_help.h"

Help::Help(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Help)
{
    ui->setupUi(this);    
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    setWindowTitle("Laptop List help");
    setWindowIcon(QIcon(":/rees/images/Laptop-icon.png"));
    setStyleSheet("background-color:rgb(200, 210, 250);");
    ui->pushButton->setStyleSheet("background-color:rgb(155, 160, 255); color:indigo;");
    ui->textBrowser->setLineWrapColumnOrWidth(QTextEdit::NoWrap);
    ui->textBrowser->insertPlainText("Інструкція користувача\n"
                                     "\n1.	Компоненти ПЗ\n"
                                     "Програмний пакет розроблено мовою програмування С++ у середовищі розробки Qt 5.14.1 та скомпільовано "
                                     "компілятором MinGW 32bit. ПЗ може експлуатуватися на базі операційної системи Windows. Під час проектування "
                                     "підсистем відбувалося поєднання об’єктно-орієнтованого підходу до програмування з процедурно-орієнтованим. "
                                     "Для коректної роботи пакету необхідна користувацька машина з мінімальною тактовою частотою процесора 1.1 ГГц та ОЗП – не менше 1 Гб."
                                     "\n2.	Встановлення ПЗ\n"
                                     "Для подальшого використання програми “LIstOfBooks” необхідно запустити файл ListOfBooks_63_bit.exe та встановити програму. "
                                     "Решта файлів завантажаться автоматично інсталятором"
                                     "\n3.	Налаштування ПЗ\n"
                                     "Для коректної роботи програми необхідно запустити .exe з відповідною назвою файлу."
                                     "\n4.	Базові функції ПЗ\n"
                                     "\n•	Для того, щоб створити новий порожній список і заповнити його з клавіатури, оберіть пункт меню «File» -> опцію «Create New» "
                                     "або комбінацією гарячих клавіш «Ctrl+N». Є також можливість скористатись відповідною "
                                     "піктограмою на панелі інструментів, просто натиснувши на неї (Зелена кнопка New, 1-ша зверху)."
                                     "\n•	Для того, щоб зчитати список з файлу, оберіть у вкладці «File» -> пункт «Open from file..»"
                                     " або скористайтесь піктограмою на панелі інструментів (1-ша зверху), чи  натисніть  «Ctrl+O». "
                                     "Оберіть файл формату «.txt», з якого хочете отримати список книг."
                                     "\n•	Щоб відсортувати список за спаданням ціни книжок, натисніть кнопку з відповідною піктограмою "
                                     "на панелі інструментів (4-та зверху) або комбінацію клавіш «Сtrl + Q». Або «Tools» -> «Sort by price»."
                                     "\n•	Щоб додати в список нову книжку (5-та зверху), натисніть кнопку з відповідною піктограмою на панелі "
                                     "інструментів або комбінацію клавіш «Сtrl + A». Або «Tools» -> «Add book»."
                                     "\n•	Для виведення книг, написаних після 1980 року, натисніть комбінацію клавіш «Сtrl + P». Або «Tools» -> «Print books after 1980»."
                                     "\n•	Щоб видалити зі списку книжки за завданням, натисніть кнопку з відповідною піктограмою на панелі інструментів (5-та зверху) або комбінацію клавіш «Сtrl + D». Або «Tools» -> «Delete books by task»."
                                     "\n•	Щоб зберегти зміни до файлу-виводу, натисніть кнопку з відповідною піктограмою на панелі інструментів (3-тя зверху) або комбінацію клавіш «Сtrl + S». Або «Tools» -> «Save to file..». Файл виводу згенерується автоматично."
                                     "\n•	Щоб отримати допомогу, написніть  натисніть  комбінацію клавіш «Сtrl + H». З'явиться вікно з необхідною інформацією або Help -> ListOfBooks help."
                                     "\n•	Для отримання інформації про програму,  натисніть кнопку з відповідною піктограмою на панелі інструментів (2-га знизу) або комбінацію клавіш «Сtrl + I»."
                                     "Щоб вийти з програми, можна скористатись кнопкою на панелі інструментів (Червоний хрестик) або нтиснути хрестик у правому верхньому куті."

                                     "\n5.	Аналіз  помилок\n"
                                     "При виникненні проблем у роботі програми, спробуйте перезавантажити її."
                                     "А також вертайтесь у службу підтримки sysoftware@gmail.com.");
}

Help::~Help()
{
    delete ui;
}

void Help::on_pushButton_clicked()
{
    this->close();
}
