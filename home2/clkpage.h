#ifndef CLKPAGE_H
#define CLKPAGE_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QGroupBox>
#include <QString>
#include <QVBoxLayout>
#include <QList>
#include <QMessageBox>
#include <QApplication>
#include <QScrollArea>
#include <QScrollBar>
#include <new_dlg.h>

class ClkPage : public QWidget
{
    Q_OBJECT

public:
    explicit ClkPage(QWidget *parent = nullptr);
    ~ClkPage();
    int work_status;//工作状态
    /*void set_num(int);
    void set_hour(int*);
    void set_minute(int*);
    void set_name(char*);
    void set_category(char*);*/
    void set_uid(int);
    int get_uid();
    void addClk(int h,int m,QString n,QString c);//要加参数
    void init(int num,QList<int>hour,QList<int> minute,QList<QString> name,QList<QString> category);
private slots:
    void new_clk();//新建番茄钟
private:
    int uid;
    int clk_num ;//番茄钟数量
    QList<int> clk_hour;//每个番茄钟小时数
    QList<int> clk_minute;//每个番茄钟分钟数
    QList<QString> clk_name;//每个番茄钟的名称
    QList<QString> clk_category;//番茄钟分类
    QVBoxLayout *mainLayout;//界面布局
    new_dlg *dlg;//新建页面弹窗
    /*
    QList<QGroupBox*> clk;//用于组装番茄钟的groupbox容器
    QList<QPushButton*> btn_start;//用于组装番茄钟的PushButton容器
    QList<QPushButton*> btn_delete;//用于组装番茄钟的PushButton容器
    QList<QLabel*> lb;//用于组装番茄钟的PushButton容器

    QGroupBox *gbx_new = new QGroupBox;//新建番茄钟框体
    QPushButton *btn_new = new QPushButton("+");//新建番茄钟的按钮
    QLabel *lb_new = new QLabel(this);*/

};

#endif // CLKPAGE_H
