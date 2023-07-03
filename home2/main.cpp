
#include <QDir>
#include <QApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

#include <usercontroller.h>
#include <enroll.h>
#include <load.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //QDir::setCurrent(a.applicationDirPath());//添加这句即可正常使用相对路径

    //连接数据库
    QSqlDatabase data_base = QSqlDatabase::addDatabase("QMYSQL");//添加驱动
    data_base.setHostName("47.115.228.227");  //设置主机地址
    data_base.setPort(3306);  //mysql设置端口
    data_base.setDatabaseName("CLKS");  //设置数据库名称
    data_base.setUserName("root");  //设置用户名
    data_base.setPassword("clks");  //设置密码
    if(!data_base.open())//打开数据库
    {
        qDebug()<<"connect failed";
        qDebug() << data_base.lastError();//.databaseText()  输出错误信息
    }
    else
        qDebug()<<"connect success";
    //data_base.close();//关闭数据库
    /*
    home w;
    w.show();
    qDebug()<<QDir::currentPath();
*/
    //test
    /*
    QSqlQuery query;
    query.exec("insert into user (uid,username,password,count) values(2,\"test2\",123456,0)");
    query.exec("select * from user where uid=2");
    query.next();
    QString username = query.value("username").toString();
    int num = query.value("count").toInt();
    qDebug()<<"查询用户成功"<<username;
    qDebug()<<num;

    UserController test = UserController(username);
    qDebug()<<test.module->get_user_num();
    return a.exec();
*/
    //test2
    /*
    home *h = new home;
    h->show();
    */

    //流程：1.初始化登陆界面
    load w1;
    enroll w2;
    QObject::connect(&w1, SIGNAL(showenroll()), &w2, SLOT(reciveload()));    //与注册界面连接
    //w1.show();
    //2.登陆成功后登陆界面用对应的用户名初始化用户控制器
    UserController *ctrl = new UserController();
    QObject::connect(&w1,SIGNAL(showtomato(QString)),ctrl,SLOT(initController(QString)));
    QObject::connect(&w1,SIGNAL(log_in()),ctrl,SLOT(initView()));
    QObject::connect(&w1,SIGNAL(log_in()),ctrl,SLOT(show_view()));
    QObject::connect(&w1,SIGNAL(log_in()),&w1,SLOT(on_closeButton_clicked()));


    //3.控制器初始化主界面
    w1.show();
    //qDebug()<<ctrl.module->get_user_id();
    //ctrl->initView();
    //ctrl->user_view->show();

    return a.exec();
}
