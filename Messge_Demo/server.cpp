#include "server.h"
#include "ui_server.h"
#include <QString>

server::server(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::server)
{
    ui->setupUi(this);

    tcpserver = NULL;
    tcpserver = new QTcpServer(this);

    if(tcpserver->listen(QHostAddress::Any, 8888)){
        //server start listen
        connect(tcpserver, SIGNAL(newConnection()), this, SLOT(newConnection()));
        QMessageBox::information(this, "Caution", "Server started");
    }else{
        QMessageBox::information(this, "Caution", "Server start failed");
    }

}

server::~server()
{
    delete ui;
    tcpserver->disconnect();
    tcpserver->close();
}

void server::newConnection()
{
    while(tcpserver->hasPendingConnections()){
        Add_New_Client_Connection(tcpserver->nextPendingConnection());
    }
}

void server::Read_Data_From_Socket()
{
    QTcpSocket *socket = reinterpret_cast<QTcpSocket*>(sender());

    QByteArray Message_From_Server = socket->readAll();

    QString Message = "Client " + QString::number(socket->socketDescriptor()) + ": " + QString::fromStdString(Message_From_Server.toStdString());

    ui->Disply->append(Message);
}

void server::Add_New_Client_Connection(QTcpSocket *socket)
{
    Client_Connection_List.append(socket);
    connect(socket, SIGNAL(readyRead()), this, SLOT(Read_Data_From_Socket()));
    ui->portComboBox->addItem(QString::number(socket->socketDescriptor()));
    QString Client = "Client: " + QString::number(socket->socketDescriptor()) + " Connected with the Server";
    QString ip = "Client " + QString::number(socket->socketDescriptor()) + " IP is " + socket->peerAddress().toString();
    QString port = "Client " + QString::number(socket->socketDescriptor()) + " port is " + QString::number(socket->peerPort());
    ui->Disply->append(Client);
    ui->Disply->append(ip);
    ui->Disply->append(port);
}

void server::on_sendBtn_clicked()
{
    QString Message_For_Client =ui->lineEdit->text();
    QString Receiver = ui->portComboBox->currentText();
    ui->Disply->append("Server: " + Message_For_Client);
    if(ui->typeComboBox->currentText() == "All"){
        foreach(QTcpSocket *socket, Client_Connection_List){
            socket->write(Message_For_Client.toStdString().c_str());
            ui->lineEdit->clear();
        }
    }else{
        foreach(QTcpSocket *socket, Client_Connection_List){
            if(socket->socketDescriptor() == Receiver.toLongLong()){
                socket->write(Message_For_Client.toStdString().c_str());
                ui->lineEdit->clear();
            }
        }
    }
    /*
    foreach(QTcpSocket *socket, Client_Connection_List){
        quint16 socketNo = socket->socketDescriptor();
        ui->Disply(socketNo);
    }
    */
}
