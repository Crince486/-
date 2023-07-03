#include "enroll.h"
#include "ui_enroll.h"
#include <QMouseEvent>
#include <QMessageBox>
#include <QDebug>
#include <QSqlError>

enroll::enroll(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::enroll)
{
    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint | windowFlags());
    //bool ok = db.open();
    /*if (ok){
        QMessageBox::information(this, "infor", "success");
    }
    else {
        QMessageBox::information(this, "infor", "open failed");
        qDebug()<<"error open database because"<<db.lastError().text();

//    QString str = "create table user(name varchar(32), pass varchar(32));";    这里不需要
//    QSqlQuery query;                                         但如果数据库没有表的话就要加
//    query.exec(str);
    }*/
}

enroll::~enroll()
{
    delete ui;
}

int enroll::password(QString pass){     //判断密码合法性
    for (int i=0; i<pass.length(); i++) {
        if ((pass[i]<'a'||pass[i]>'z')&&(pass[i]<'A'||pass[i]>'Z')&&(pass[i]<'0'||pass[i]>'9')){
            return 0;   //0代表不通过
        }
    }
    if(pass.length()<7||pass.length()>12){    //这里暂填的是7到12，可以修改
        return 0;
    }
    return 1;
}

void enroll::reciveload(){
    this->show();//显示这个界面
}

void enroll::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
    {
        //求坐标差值
        //当前点击坐标-窗口左上角坐标
        p = e->globalPos() - this->frameGeometry().topLeft();
    }
}

void enroll::mouseMoveEvent(QMouseEvent *e)
{
    if(e->buttons() & Qt::LeftButton)
    {
        //移到左上角
        move(e->globalPos() - p);
    }
}

void enroll::on_minButton_clicked()
{
    showMinimized();
}


void enroll::on_closeButton_clicked()
{
    close();
    delete this;
}


void enroll::on_enrollButton_clicked()
{
    QString name = ui->userName->text();
    QString pass = ui->passWord->text();

    QString str_2 = QString("select *from USER where username = '%1'").arg(name);    //这个user是我表的名字，得改
    QSqlQuery query;                               //这个                        那个绿的name是我的参数，可能要改
    query.exec(str_2);                                                           //蓝色的name不能改，改了就错了
    QString rename;

    while (query.next())
    {
    rename = query.value(1).toString();
    }

    if(name==rename){      //检测注册用户是否同名
        QMessageBox::warning(this, tr("注册失败"), tr("用户名已被占用！"), QMessageBox::Ok);
        ui->userName->clear();
        ui->passWord->clear();
        ui->userName->setFocus();
    }
    else{
        if(password(pass)==0){    //密码检测
            QMessageBox::warning(this, tr("注册失败"), tr("请输入合适的密码"), QMessageBox::Ok);
            ui->userName->clear();
            ui->passWord->clear();
            ui->userName->setFocus();
        }
        else{             //注册成功
            QSqlQuery query;
            query.prepare("insert into USER (username, password) values(:name, :pass)");  //user，表的名字，得改
            query.bindValue(":name", name);                      //name和pass是我的参数，可能要改
            query.bindValue(":pass", pass);                      //:name和:pass不能改 蓝色的name pass不能改
            query.exec();
            ui->userName->clear();
            ui->passWord->clear();
            this->close();
            QMessageBox::information(this, tr("注册成功"), tr("账号注册成功"), QMessageBox::Ok);

        }
    }
}

