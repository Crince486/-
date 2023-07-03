
#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QDebug>
#include <QProgressBar>
/*
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE
*/
class Widget : public QWidget

{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void set_num(int n);


    void openAchievementSys();

private slots:

private:
    //Ui::Widget *ui;
    int num;//番茄数
};

#endif // WIDGET_H
