#include "new_dlg.h"
#include "ui_new_dlg.h"
#include <QDebug>

extern int hour;
extern int minute;
extern QString name;
extern QString category;

new_dlg::new_dlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::new_dlg)
{
    ui->setupUi(this);
}

new_dlg::~new_dlg()
{
    delete ui;
}

void new_dlg::on_btn_new_clicked()
{
    int h = ui->spin_hour->value();
    int m = ui->spin_minute->value();
    QString n = ui->le_name->text();
    QString c = ui->le_category->text();
    if(h==0&&m==0)
        return;//为空
    if(n.length()>7||c.length()>7){
        QMessageBox::warning(this, tr("创建失败"), tr("任务名称和类别名应在4个字符以内"), QMessageBox::Ok);
        return;
    }
    //然后传参并更新界面
    hour = h;
    minute = m;
    name = n;
    category = c;
    qDebug()<<"new dlg uid:"<<uid;
    //qDebug()<<"新建番茄钟的数据："<<uid<<h<<m<<n<<c<<"\\";
    QSqlQuery query;
    query.prepare("INSERT INTO clk(uid, name, category,hour,minute,count) VALUE (:uid, :name, :category,:hour,:minute,:count)");
    query.bindValue(":uid", uid);
    query.bindValue(":name", name);
    query.bindValue(":category", category);
    query.bindValue(":hour", hour);
    query.bindValue(":minute", minute);
    query.bindValue(":count",0);
    query.exec();
    qDebug()<<"新建番茄钟数据上传完毕";
    query.exec(QString("select * from user where uid = %1").arg(uid));
    query.next();
    int count = query.value("count").toInt();
    qDebug()<<"进行新建操作中/此时user count 为："<<count<<"/";
    count += 1;
    query.exec(QString("update user set count =%1 where uid = %2").arg(count).arg(uid));//更新user表番茄钟数量
    qDebug()<<QString("update user set count =%1 where uid = %2").arg(count).arg(uid);
    emit btn_new_clicked();
    this->close();
}
