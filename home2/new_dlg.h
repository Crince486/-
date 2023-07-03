#ifndef NEW_DLG_H
#define NEW_DLG_H

#include <QDialog>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QMessageBox>

namespace Ui {
class new_dlg;
}

class new_dlg : public QDialog
{
    Q_OBJECT

public:
    explicit new_dlg(QWidget *parent = nullptr);
    ~new_dlg();
    int uid;
signals:
    void btn_new_clicked();

private slots:
    void on_btn_new_clicked();

private:
    Ui::new_dlg *ui;
};

#endif // NEW_DLG_H
