#include "load.h"
#include "ui_load.h"
#include <QMouseEvent>
#include <QMessageBox>

load::load(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::load)
{
    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint | windowFlags());
}

load::~load()
{
    delete ui;
}

void load::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
    {
        //求坐标差值
        //当前点击坐标-窗口左上角坐标
        p = e->globalPos() - this->frameGeometry().topLeft();
    }
}

void load::mouseMoveEvent(QMouseEvent *e)
{
    if(e->buttons() & Qt::LeftButton)
    {
        //移到左上角
        move(e->globalPos() - p);
    }
}


void load::on_enrollButton_clicked()
{
    emit showenroll();
}

void load::on_minButton_clicked()
{
    showMinimized();
}


void load::on_closeButton_clicked()
{
    close();
}


void load::on_loadButton_clicked()
{
    QString username = ui->userName->text();
    QString password = ui->passWord->text();

    QString str = QString("select *from USER where username = '%1'").arg(username);  //这里的name同理，可能要改
    QSqlQuery query;                            //这个name
    query.exec(str);
    QString name;
    QString pass;

    while (query.next())
    {
        name = query.value(1).toString();
        pass = query.value(2).toString();
    }

    if(username == name && password == pass && username != NULL){     //这里连接主界面 所以tomato文件我什么都没写
        this->close();      //转到主界面，主界面暂定        
        emit showtomato(username);  //主界面文件是tomato.cpp和tomato.h
        emit log_in();

    }
    else{
        QMessageBox::warning(this, tr("登录失败"), tr("用户名或密码输入错误！"), QMessageBox::Ok);
        ui->userName->clear();
        ui->passWord->clear();
        ui->userName->setFocus();
    }
}

