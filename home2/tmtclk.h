#ifndef TMTCLK_H
#define TMTCLK_H

#include <QWidget>

#include <QWidget>
#include <QWidget>
#include <windows.h>
#include <windowsx.h>
#include <QMouseEvent>
#include <QTimer>
#include <QTime>
#include <QLabel>
#include <QCloseEvent>
#include <QPushButton>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlDatabase>

namespace Ui {
class TmtClk;
}

class TmtClk : public QWidget
{
    Q_OBJECT

public:
    explicit TmtClk(QWidget *parent = nullptr);
    ~TmtClk();
    void closeEvent(QCloseEvent *);
    void setter(int h ,int m ,QString);
    void init();

//private:
    float Opacity; //透明度控制
    int state; //用于暂停和恢复暂停
    int tomato_num; //番茄钟计数
    int total_count;//完成总数
    int minute;
    int hour;
    QString name;
    QString current_color;
    QPoint clickPos;
    Ui::TmtClk *ui;
    QTimer *timer;
    QTime time;

private slots:
    void initTime(); //初始化时间
    void updateTime(); //更新时间

    void update_data();

protected:
    //     声明一些函数
    void mousePressEvent(QMouseEvent *e); //鼠标单击事件
    void mouseMoveEvent(QMouseEvent *e); // 鼠标单击拖动窗口

};

#endif // TMTCLK_H
