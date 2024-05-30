#include "arduino.h"

Arduino::Arduino()
{
    data="";
    arduino_port_name="";
    arduino_is_available=false;
    serial=new QSerialPort;
}

QString Arduino::getarduino_port_name()
{
    return arduino_port_name;
}

QSerialPort *Arduino::getserial()
{
   return serial;
}
int Arduino::connect_arduino()
{   // recherche du port sur lequel la carte arduino identifée par  arduino_uno_vendor_id
    // est connectée
    foreach (const QSerialPortInfo &serial_port_info, QSerialPortInfo::availablePorts()){
           if(serial_port_info.hasVendorIdentifier() && serial_port_info.hasProductIdentifier()){
               if(serial_port_info.vendorIdentifier() == arduino_uno_vendor_id && serial_port_info.productIdentifier()
                       == arduino_uno_producy_id) {
                   arduino_is_available = true;
                   arduino_port_name=serial_port_info.portName();
               } } }
        qDebug() << "arduino_port_name is :" << arduino_port_name;
        if(arduino_is_available){ // configuration de la communication ( débit...)
            serial->setPortName(arduino_port_name);
            if(serial->open(QSerialPort::ReadWrite)){
                serial->setBaudRate(QSerialPort::Baud115200); // débit : 9600 bits/s
                serial->setDataBits(QSerialPort::Data8); //Longueur des données : 8 bits,
                serial->setParity(QSerialPort::NoParity); //1 bit de parité optionnel
                serial->setStopBits(QSerialPort::OneStop); //Nombre de bits de stop : 1
                serial->setFlowControl(QSerialPort::NoFlowControl);
                return 0;
            }
            return 1;
        }
        return -1;
}

int Arduino::close_arduino()

{

    if(serial->isOpen()){
            serial->close();
            return 0;
        }
    return 1;


}


 QByteArray Arduino::read_from_arduino()
{
    if(serial->isReadable()){
         data=serial->readAll(); //récupérer les données reçues

         return data;
    }
 }


 QByteArray Arduino::read_from_arduino_event()
 {
     if (serial->isReadable()) {
         QByteArray data = serial->readLine(); // Récupérer les données reçues
         qDebug() << "Données brutes reçues:" << data;

         if (!data.isEmpty()) {
             QString uid = QString::fromLatin1(data).trimmed(); // Convertir les données en QString
             qDebug() << "UID de la carte RFID détectée:" << uid;
             serial->blockSignals(true);
             return data;
         } else {
             qDebug() << "Aucune donnée reçue après readLine().";
         }
     } else {
         qDebug() << "Le port série n'est pas lisible.";
     }
     return QByteArray();
}




int Arduino::write_to_arduino( QByteArray d)

{

    if(serial->isWritable()){
        serial->write(d);  // envoyer des donnés vers Arduino
    }else{
        qDebug() << "Couldn't write to serial!";
    }
    qDebug() << d;

}

void Arduino::write_to_arduino1( QByteArray d)
{
   int i;
QString x;
if(serial->isWritable())
{
    for (i=0;i<d.length();i++)
    {
        x=d[i];
        serial->write(x.toUtf8());
    }  // envoyer des donnés vers Arduino
}
else
{
    qDebug() << "Couldn't write to serial!";
}
}
