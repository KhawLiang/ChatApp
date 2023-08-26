#include "client.h"
#include "ui_client.h"

client::client(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::client)
{
    ui->setupUi(this);

    tcpsocket = NULL;
    tcpsocket = new QTcpSocket(this);

    //QString IPAddr = ui->lineEdit_IP->text();
    tcpsocket->connectToHost("10.0.2.15", 8888);
    connect(tcpsocket, SIGNAL(readyRead()), this, SLOT(Read_Data_from_Socket()));
    tcpsocket->open(QIODevice::ReadWrite);
    if(tcpsocket->isOpen()){
        QMessageBox::information(this, "Caution", "Connected to server");
    }else{
        QMessageBox::information(this, "Caution", "Failed connect to server");
    }

}

client::~client()
{
    delete ui;
    tcpsocket->disconnect();
    tcpsocket->close();
}

void client::on_sendBtn_clicked()
{
    if(tcpsocket){
        if(tcpsocket->isOpen()){
            QString WriteData = ui->lineEdit->text();
            tcpsocket->write(WriteData.toStdString().c_str());
            ui->Display->append("Me: " + WriteData);
            ui->lineEdit->clear();
        }else{
            QMessageBox::information(this, "Caution", "Error: " + tcpsocket->errorString());
        }
    }else{
        QMessageBox::information(this, "Caution", "Error: " + tcpsocket->errorString());
    }
}

void client::Read_Data_from_Socket()
{
    if(tcpsocket){
        if(tcpsocket->isOpen()){
            QByteArray Data_From_Server = tcpsocket->readAll();
            //QDataStream DataIn(&Data_From_Server, QIODevice::ReadOnly);
            //DataIn.setVersion(QDataStream::Version::Qt_5_12);

            QString MessageString = QString::fromStdString(Data_From_Server.toStdString());
            //while(DataIn.atEnd() == false){
            //    DataIn >> MessageString;
            //}

            ui->Display->append("Server: " + MessageString);
        }
    }
}
