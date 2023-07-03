#ifndef USER_H
#define USER_H
#include "clkmodule.h"
#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>

class User
{
public:
    User();
    User(int uid,int num,QString un);

    //id的getter
    int get_user_id();
    int get_user_num();
    QString get_user_name();
    QList<ClkModule*>get_clk_list();

private:
    //id
    int uid;
    int num;
    QString username;
    QList<ClkModule*>clk_list;//任务列表
};

#endif // USER_H
