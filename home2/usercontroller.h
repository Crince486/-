#ifndef USERCONTROLLER_H
#define USERCONTROLLER_H
#include "user.h"
#include "home.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>
#include <QObject>

class UserController:public QObject
{   Q_OBJECT
public:
    UserController();
    UserController(QString username);//根据用户名初始化控制器
    User *module;
    home *user_view;
public slots:
    void initController(QString username);
    void initView();//初始化界面
    void show_view();//显示界面

//private:

};

#endif // USERCONTROLLER_H
