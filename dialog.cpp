#include "dialog.h"
#include "ui_dialog.h"
#include <QSerialPort>
#include <QSerialPortInfo>
#include <string>
#include <QDebug>
#include <QMessageBox>
#include <QProcess>
Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    QSqlDatabase mydb= QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("/home/pi/Desktop/Temperature_Humidity.db");
    if(!mydb.open())
        QMessageBox::information(this,"Not Connected","Database is not connected");
        else
        QMessageBox::information(this," Connected","Database is connected");
    QSqlQuery qry;

    ui->LCD_Temp->display("-------");
    arduino = new QSerialPort(this);
    serialBuffer = "";
    parsed_data = "";
    temperature_value = 0.0;

    /*
     *  Testing code, prints the description, vendor id, and product id of all ports.
     *  Used it to determine the values for the arduino uno.
     *
     *
    qDebug() << "Number of ports: " << QSerialPortInfo::availablePorts().length() << "\n";
    foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()){
        qDebug() << "Description: " << serialPortInfo.description() << "\n";
        qDebug() << "Has vendor id?: " << serialPortInfo.hasVendorIdentifier() << "\n";
        qDebug() << "Vendor ID: " << serialPortInfo.vendorIdentifier() << "\n";
        qDebug() << "Has product id?: " << serialPortInfo.hasProductIdentifier() << "\n";
        qDebug() << "Product ID: " << serialPortInfo.productIdentifier() << "\n";
    }
    */


    /*
     *   Identify the port the arduino uno is on.
     */
    bool arduino_is_available = false;
    QString arduino_uno_port_name;
    //
    //  For each available serial port
    foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()){
        //  check if the serialport has both a product identifier and a vendor identifier
        if(serialPortInfo.hasProductIdentifier() && serialPortInfo.hasVendorIdentifier()){
            //  check if the product ID and the vendor ID match those of the arduino uno
            if((serialPortInfo.productIdentifier() == arduino_uno_product_id)
                    && (serialPortInfo.vendorIdentifier() == arduino_uno_vendor_id)){
                arduino_is_available = true; //    arduino uno is available on this port
                arduino_uno_port_name = serialPortInfo.portName();
            }
        }
    }

    /*
     *  Open and configure the arduino port if available
     */
    if(arduino_is_available){
        qDebug() << "Found the arduino port...\n";
        arduino->setPortName(arduino_uno_port_name);
        arduino->open(QSerialPort::ReadOnly);
        arduino->setBaudRate(QSerialPort::Baud9600);
        arduino->setDataBits(QSerialPort::Data8);
        arduino->setFlowControl(QSerialPort::NoFlowControl);
        arduino->setParity(QSerialPort::NoParity);
        arduino->setStopBits(QSerialPort::OneStop);
        QObject::connect(arduino, SIGNAL(readyRead()), this, SLOT(readSerial()));
        serialData.clear();

    }else{
        qDebug() << "Couldn't find the correct port for the arduino.\n";
        QMessageBox::information(this, "Serial Port Error", "Couldn't open serial port to arduino.");
    }
}

Dialog::~Dialog()
{
    if(arduino->isOpen()){
        arduino->close(); //    Close the serial port if it's open.
    }
    delete ui;
}

void Dialog::readSerial()
{
    /*
     * readyRead() doesn't guarantee that the entire message will be received all at once.
     * The message can arrive split into parts.  Need to buffer the serial data and then parse for the temperature value.
     *
     */
    QStringList buffer_split = serialBuffer.split(","); //  split the serialBuffer string, parsing with ',' as the separator

    //  Check to see if there less than 3 tokens in buffer_split.
    //  If there are at least 3 then this means there were 2 commas,
    //  means there is a parsed temperature value as the second token (between 2 commas)
    if(buffer_split.length() < 5){
        // no parsed value yet so continue accumulating bytes from serial in the buffer.
        serialData = arduino->readAll();
        serialBuffer = serialBuffer + QString::fromStdString(serialData.toStdString());
        serialData.clear();
    }else{
        // the second element of buffer_split is parsed correctly, update the temperature value on temp_lcdNumber
        serialBuffer = "";
        qDebug() << buffer_split << "\n";
        parsed_data = buffer_split[1];
        temperature_value = parsed_data.toDouble(); // convert to fahrenheit
        qDebug() << "Temperature: " << temperature_value << "\n";
        parsed_data = QString::number(temperature_value, 'g', 4); // format precision of temperature_value to 4 digits or fewer
        Dialog::updateTemperature(parsed_data);
        parsed_data1 = buffer_split[3];
        humidity_value = 1024-parsed_data1.toDouble(); // convert to fahrenheit
        qDebug() << "Humidity: " << humidity_value << "\n";
        parsed_data1 = QString::number(humidity_value, 'g', 4); // format precision of temperature_value to 4 digits or fewer
        Dialog::updateHumidity(parsed_data1);



        double Temperature1=temperature_value;
        double   Humidity1=humidity_value;
        QSqlQuery qry;
        qry.prepare("INSERT INTO Temperature_Humidity (Temperature,  Humidity) VALUES (?,?);");
        qry.addBindValue(Temperature1);
        qry.addBindValue(Humidity1);
        qry.exec();
        QFile file("/home/pi/Desktop/temperature.txt");
        QFile file1("/home/pi/Desktop/humidity.txt");

        if(!file.open(QFile::WriteOnly | QFile::Text) ){
         QMessageBox::warning(this,"title","file not open");

     }
        if(!file1.open(QFile::WriteOnly | QFile::Text)){
         QMessageBox::warning(this,"title","file not open");

     }
        QTextStream out(&file);
        QTextStream out1(&file1);

        QString temperature = parsed_data;
        out <<temperature;
        QString humidity = parsed_data1;
        out1<<humidity;
        file.flush();
        file.close();

        file1.flush();
        file1.close();
    }

}

void Dialog::updateTemperature(QString sensor_reading)
{
    //  update the value displayed on the lcdNumber
    ui->LCD_Temp->display(sensor_reading);
}
void Dialog::updateHumidity(QString sensor_reading)
{
    //  update the value displayed on the lcdNumber
    ui->LCD_Humidity->display(sensor_reading);
}

void Dialog::on_pushButton_clicked()
{
    double Temperature=temperature_value;
    double   Humidity=humidity_value;
    QSqlQuery qry;
    qry.prepare("INSERT INTO Temperature_Humidity_Button (Temperature,  Humidity) VALUES (?,?);");
    qry.addBindValue(Temperature);
    qry.addBindValue(Humidity);
    qry.exec();
}



