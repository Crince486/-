#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QtCharts>
#include <QWidget>
#include <QScrollArea>
#include <QList>
#include <QSqlQuery>
#include <QSqlDatabase>

QT_CHARTS_USE_NAMESPACE

    //QT_BEGIN_NAMESPACE
    //namespace Ui { class MainWindow; }
    //QT_END_NAMESPACE

    class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void initPie();
    void initBar();
    void initdata(int uid);
    void initview(int uid);

private:
    //Ui::MainWindow *ui;
    QChart *pie;// = new QChart();
    QChart *bar;// = new QChart();
    QList<QString> category;
    QList<QString>name;
    QList<int>cate_count;
    QList<int>name_count;
};
#endif // MAINWINDOW_H
