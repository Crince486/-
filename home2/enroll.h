#ifndef ENROLL_H
#define ENROLL_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>

namespace Ui {
class enroll;
}

class enroll : public QWidget
{
    Q_OBJECT

public:
    explicit enroll(QWidget *parent = nullptr);
    ~enroll();

    int password(QString pass);

protected:
    void mouseMoveEvent(QMouseEvent *e);//鼠标移动
    void mousePressEvent(QMouseEvent *e);

private slots:
    void reciveload();

    void on_minButton_clicked();

    void on_closeButton_clicked();

    void on_enrollButton_clicked();

private:
    Ui::enroll *ui;

    QPoint p;

    QSqlDatabase db;
};

#endif // ENROLL_H
