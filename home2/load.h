#ifndef LOAD_H
#define LOAD_H

#include <QWidget>
#include "enroll.h"

QT_BEGIN_NAMESPACE
namespace Ui { class load; }
QT_END_NAMESPACE

class load : public QWidget
{
    Q_OBJECT

public:
    load(QWidget *parent = nullptr);
    ~load();

protected:

    void mouseMoveEvent(QMouseEvent *e);//鼠标移动
    void mousePressEvent(QMouseEvent *e);

private slots:
    void on_enrollButton_clicked();

    void on_minButton_clicked();

    void on_closeButton_clicked();

    void on_loadButton_clicked();

signals:
    void showenroll();
    void showtomato(QString username);
    void log_in();

private:
    Ui::load *ui;

    QPoint p;
};
#endif // LOAD_H
