#include "dialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dialog w;
    w.setWindowTitle("Temperature And Humidity Sensors Reading");
    //w.setFixedSize(400,112);
    w.show();

    return a.exec();
}
