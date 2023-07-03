#include "clkpage.h"
#include "tmtclk.h"
#include "new_dlg.h"
#include <QDebug>

int hour;
int minute;
QString name;
QString category;

//不用容器的构造函数
//默认构造函数：此时窗体内容为空，只有一个新建按钮
ClkPage::ClkPage(QWidget *parent) :
    QWidget(parent){
    clk_num = 0;
    QGroupBox *gbx_new = new QGroupBox;//新建番茄钟框体
    QPushButton *btn_new = new QPushButton("+");//新建番茄钟的按钮
    QLabel *lb_new = new QLabel(this);
    lb_new->setText("点击加号新建番茄钟");
    lb_new->setAlignment(Qt::AlignHCenter);
    QVBoxLayout *vbox_new = new QVBoxLayout;
    vbox_new->addWidget(lb_new);
    vbox_new->addWidget(btn_new);
    gbx_new->setLayout(vbox_new);
    mainLayout = new QVBoxLayout;
    mainLayout->addWidget(gbx_new);
    mainLayout->addStretch(1);
    setLayout(mainLayout);

    //创建番茄钟的界面
    connect(btn_new,&QPushButton::clicked,[&]{
        dlg =new new_dlg;
        dlg->uid = uid;
        dlg->exec();
        //delete dlg;
        new_clk();
        ;});


}

//设置uid
void ClkPage::set_uid(int i){
    uid = i;
    //dlg->uid=uid;
    qDebug()<<"page1/newdlg uid:-->"<<uid;
}

int ClkPage::get_uid(){
    return uid;
}


//向界面中增加番茄钟模块
void ClkPage::addClk(int h,int m,QString n,QString c){
    clk_num++;qDebug()<<"data";
    clk_hour<<h;
    clk_minute<<m;
    clk_name<<n;
    clk_category<<c;
    QGroupBox *gbx = new QGroupBox(n);
    QHBoxLayout *hbox = new QHBoxLayout;
    QVBoxLayout *vbox = new QVBoxLayout;
    QLabel *lb = new QLabel(this);
    QPushButton *btn_start = new QPushButton(QString("%1:start!").arg(clk_num));
    QPushButton *btn_delete = new QPushButton("delete");
    btn_start->setStyleSheet("background-color: rgb(230, 42, 0);");
    btn_delete->setStyleSheet("background-color: rgb(205, 205, 180);");
    btn_delete->setMaximumWidth(75);
    lb->setText("时长：" + QString::number(h)+"分"+QString::number(m)+"秒"+"\n"+"分类："+c);
    hbox->addWidget(lb);
    hbox->addWidget(btn_delete);
    vbox->addLayout(hbox);
    vbox->addWidget(btn_start);
    gbx->setLayout(vbox);
    mainLayout->insertWidget(1,gbx);

    //连接开始按钮


    connect(btn_start,&QPushButton::clicked,[=]{
        /*if(work_status==1){

            return;
        }
        work_status = 1;*/
        TmtClk *clk_1 = new TmtClk;//创建方法要改
        QString index = QString(btn_start->text()).mid(0,1);
        qDebug()<<index;
        int i =index.toInt() - 1;
        clk_1->setter(clk_hour[i],clk_minute[i],clk_name[i]);//
        clk_1->setWindowModality(Qt::ApplicationModal);//设置模态，堵塞主窗口
        //clk_1->init();
        qDebug()<<clk_1->hour<<"/"<<clk_1->minute<<"/"<<clk_1->name;
        clk_1->show();
        //work_status = 0;
    });

    //连接删除按钮////需改进
    connect(btn_delete,&QPushButton::clicked,[=]{

        hbox->removeWidget(lb);
        hbox->removeWidget(btn_delete);
        vbox->removeItem(hbox);
        vbox->removeWidget(btn_start);
        //hbox=NULL;
        //vbox=NULL;
        delete lb;
        delete btn_delete;
        delete btn_start;
        delete gbx;
        QSqlQuery query;
        query.exec(QString("DELETE FROM clk WHERE name = '%1'").arg(n));//在数据库中删去对应的数据
        query.exec(QString("select * from user where uid = %1").arg(uid));
        query.next();
        int count = query.value("count").toInt();
        qDebug()<<"删除操作中/此时user count 为："<<count<<"/";
        if(count == 0)
            return;
        count -= 1;
        query.exec(QString("update user set count =%1 where uid =%2").arg(count).arg(uid));//更新user表番茄钟数量
        qDebug()<<QString("update user set count =%1 where uid =%2").arg(count).arg(uid);

    });

}



//初始化番茄钟页面
void ClkPage::init(int num,QList<int>hour,QList<int> minute,QList<QString> name,QList<QString> category){
    int clk_num = num;//番茄钟数量
    QList<int> clk_hour= hour;//每个番茄钟小时数
    QList<int> clk_minute = minute;//每个番茄钟分钟数
    QList<QString> clk_name = name;//每个番茄钟的名称
    QList<QString> clk_category = category;//番茄钟分类
    qDebug()<<"data read in..ready to construct clkpage";
    qDebug()<<"num:"<<clk_num;
    for(int i = 0;i < clk_num;i++){
        qDebug()<<"次数"<<i+1;
        addClk(clk_hour[i],clk_minute[i],clk_name[i],clk_category[i]);
    }
};

void ClkPage::new_clk(){
    if(hour==minute&&hour==0)
        return;
    addClk(hour,minute,name,category);
}

ClkPage::~ClkPage()
{
}
