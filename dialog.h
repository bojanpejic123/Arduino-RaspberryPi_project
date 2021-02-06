#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QSerialPort>
#include <QByteArray>
#include<QFile>
#include<QString>
#include<QtSql>
#include<QtDebug>
#include<QFileInfo>
#include<QSqlDatabase>
#include<QMessageBox>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private slots:
    void readSerial();
    void updateTemperature(QString);
    void updateHumidity(QString);

    void on_pushButton_clicked();


private:
    Ui::Dialog *ui;
    QSqlDatabase db;
QSqlQueryModel *querymodel;
    QSerialPort *arduino;
    static const quint16 arduino_uno_vendor_id = 9025;
    static const quint16 arduino_uno_product_id = 67;
    QByteArray serialData;
    QString serialBuffer;
    QString parsed_data;
    QString parsed_data1;

    double temperature_value;
    double humidity_value;

};

#endif // DIALOG_H
