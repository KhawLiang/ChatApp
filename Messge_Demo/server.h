#ifndef SERVER_H
#define SERVER_H

#include <QDialog>
#include <QTcpServer>
#include <QTcpSocket>
#include <QMessageBox>
#include <QByteArray>

namespace Ui {
class server;
}

class server : public QDialog
{
    Q_OBJECT

public:
    explicit server(QWidget *parent = nullptr);
    ~server();

private slots:
    void newConnection();
    void Read_Data_From_Socket();

    void on_sendBtn_clicked();

private:
    void Add_New_Client_Connection(QTcpSocket *socket);

private:
    Ui::server *ui;

    QTcpServer *tcpserver;
    QList<QTcpSocket* > Client_Connection_List;
};

#endif // SERVER_H
