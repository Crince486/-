#include "user.h"
#include "qdebug.h"

User::User()
{
}

User::User(int uid,int num,QString un):
    uid(uid),num(num),username(un)
{
    //初始化任务列表
    qDebug()<<"module: uid num username constructed..";
    QSqlQuery query;
    query.exec("select * from clk where uid =" + QString::number(uid));
    QList<int>hour;
    QList<int>minute;
    QList<QString>category;
    QList<QString>name;
    while(query.next()){
        hour<< query.value("hour").toInt();
        minute<<query.value("minute").toInt();
        category<<query.value("category").toString();
        name<<query.value("name").toString();
    }
    qDebug()<<"module: clk data received,ready to construct clk_list";
    for(int i = 0;i < num;i++)
        clk_list << new ClkModule(name[i],category[i],hour[i],minute[i]);
    qDebug()<<"module:clk_list constructed..";

}

int User::get_user_id(){
    return uid;
}
int User::get_user_num(){
    return num;
}

QList<ClkModule*> User::get_clk_list(){
    return clk_list;
}

QString User::get_user_name(){
    return username;
}
