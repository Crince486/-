#include "usercontroller.h"

UserController::UserController()
{
    //module = new User;
    //user_view = new home;
}

//含参构造函数（好像没用。。
UserController::UserController(QString username){
    //查询uid
    QSqlQuery query;
    QString sql = QString("select * from user where username ='%1'").arg(username);
    qDebug()<<sql;

    query.exec(sql);

    //内容赋值给user
    query.next();
    qDebug()<<query.value("username").toString();
    int uid = query.value(0).toInt();
    int num = query.value(3).toInt();
    module = new User(uid,num,username);
    qDebug()<<"module uid:"<<uid<<module->get_user_id();
}

//含参函数，用username初始化控制器
void UserController::initController(QString username){
    //查询uid
    QSqlQuery query;
    QString sql = QString("select * from user where username ='%1'").arg(username);
    qDebug()<<sql;

    query.exec(sql);
    //query.exec("select * from user where uid =2");

    //内容赋值给user
    query.next();
    qDebug()<<query.value("username").toString();
    int uid = query.value("uid").toInt();
    int num = query.value("count").toInt();//count是番茄钟任务数量
    qDebug()<<"uid:"<<uid<<" num:"<<num<<"ready to construct";
    module = new User(uid,num,username);
    qDebug()<<"module uid:"<<uid<<module->get_user_id();
    qDebug()<<"module constructed";
    user_view = new home;
    qDebug()<<"ctrl constructed..";
}

void UserController::initView(){
    qDebug()<<"ready to initView";

    user_view->setWindowTitle(QString("欢迎！用户: %1").arg(module->get_user_name()));//需传参调整——————
    qDebug()<<"title set..";
    user_view->initClkPage(module->get_user_id(),module->get_user_num(),module->get_clk_list());
    qDebug()<<"page1 constructed";
    user_view->initHistoryPage(module->get_user_id());
    qDebug()<<"page2 constructed";
    user_view->initAcmPage(module->get_user_num());
    qDebug()<<"page3 constructed";


}

void UserController::show_view(){
    qDebug()<<"ready to show";

    user_view->show();
}
