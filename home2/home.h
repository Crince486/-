#ifndef HOME_H
#define HOME_H

#include <QDir>
#include <QWidget>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QListWidget>
#include <clkpage.h>
#include <widget.h>
#include <QScrollArea>
#include <QScrollBar>
#include <mainwindow.h>
#include <clkmodule.h>
//#include <QApplication>

class home : public QWidget
{
    Q_OBJECT

public:
    home(QWidget *parent = nullptr);
    ~home();
    void initClkPage(int uid,int num,QList<ClkModule*>clk_list);//任务列表
    void initHistoryPage(int uid);//历史数据表
    void initAcmPage(int n);//成就列表

private:
    ClkPage *page1;
    MainWindow *page2;
    Widget *page3;
};
#endif // HOME_H
