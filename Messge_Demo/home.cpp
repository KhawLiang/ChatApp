#include "home.h"
#include "ui_home.h"
#include "server.h"
#include "client.h"

home::home(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::home)
{
    ui->setupUi(this);
}

home::~home()
{
    delete ui;
}

void home::on_startServerBtn_clicked()
{
    server *svr = new server();
    svr->show();
}

void home::on_addClntBtn_clicked()
{
    client *clnt = new client();
    clnt->show();
}
