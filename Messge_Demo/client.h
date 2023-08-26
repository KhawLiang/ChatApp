#ifndef CLIENT_H
#define CLIENT_H

#include <QDialog>
#include <QTcpSocket>
#include <QMessageBox>
#include <QString>
#include <QUdpSocket>

namespace Ui {
class client;
}

class client : public QDialog
{
    Q_OBJECT

public:
    explicit client(QWidget *parent = nullptr);
    ~client();

private slots:
    void on_sendBtn_clicked();
    void Read_Data_from_Socket();

private:
    Ui::client *ui;

    QTcpSocket *tcpsocket;
};

#endif // CLIENT_H
