
#include "widget.h"
#include "ui_widget.h"


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    //, ui(new Ui::Widget)
{
    //ui->setupUi(this);
    this->resize(QSize(680,600));
    //openAchievementSys();

}

Widget::~Widget()
{
    //delete ui;
}

void Widget::set_num(int n){
    num = n;
}
void Widget::openAchievementSys()
{   /*
    // 设置样式表
    // 创建一个 QList 存储 QGroupBox
    QList<QGroupBox*> groupBoxes;
    groupBoxes << ui->groupBox << ui->groupBox_2 << ui->groupBox_3 << ui->groupBox_4 << ui->groupBox_5;
    int maxNum[5] = { 5,15,30,60,99};
    QList<QLabel*> labels;
    labels << ui->label_5 << ui->label_8 << ui->label_11 << ui->label_14 << ui->label_17;

    // 循环遍历列表，并为每个 QGroupBox 设置样式
    foreach (QGroupBox *groupBox, groupBoxes) {
        int index = groupBoxes.indexOf(groupBox); // 获取当前元素的索引

        // 在这里使用 index 进行相应的操作
        qDebug() << "Index:" << index;
        // 根据条件设置不同的背景颜色
        if (num<maxNum[index])
        {
            groupBox->setStyleSheet("QGroupBox { "
                                    "border: 1px solid black; "
                                    "border-radius: 6px; "
                                    "margin-top: 6px;"
                                    "background-color: white;"   // 白色背景
                                    "}"
                                    "QGroupBox::title {"
                                    "subcontrol-origin: margin; "
                                    //"position: top center; "
                                    "padding: 0 3px; "
                                    "}");
        }
        else
        {
            labels[index]->setText("已达成");
            groupBox->setStyleSheet("QGroupBox { "
                                    "border: 1px solid black; "
                                    "border-radius: 6px; "
                                    "margin-top: 6px;"
                                    "background-color: rgb(235, 128, 128);"     // 红色背景
                                    "}"
                                    "QGroupBox::title {"
                                    "subcontrol-origin: margin; "
                                    //"position: top center; "
                                    "padding: 0 3px; "
                                    "}");

        }
    }
    QVBoxLayout *mainlayout =new QVBoxLayout;
    for(int i = 0;i < 5;i++)
    mainlayout->insertWidget(1,groupBoxes[i]);
    mainlayout->addStretch(1);
    setLayout(mainlayout);
*/
    QVBoxLayout *mainlayout = new QVBoxLayout;
    QList<QGroupBox*> gbx;
    QList<QLabel*> status;
    QList<QLabel*> name;
    QList<QLabel*> content;
    QList<QProgressBar*> pb;//
    //初始化控件
    for(int i = 0;i < 5;i++){
        gbx<<new QGroupBox;
        status<<new QLabel;
        name<<new QLabel;
        content<<new QLabel;
        pb<<new QProgressBar;//
    }
    for(int i = 0;i < 5;i++){
        status[i]->setText("未达成");//默认未达成
        pb[i]->setOrientation(Qt::Horizontal); //
        //pb[i]->setMinimumWidth(350);//
        QString qss= "QProgressBar{"
                      "color:yellow;"
                      "border: 1px solid rgb(16, 135, 209);"
                      "background: rgba(248,248,255,180);"
                      "border-radius: 6px; }"
                      "QProgressBar::chunk:enabled {"
                      "border-radius: 4px; "
                      "background: qlineargradient(x1:0, y1:0, x2:1, y2:0 ,stop:0 #9ACBF9, stop:1 #3C64D9);}" ;

        pb[i]->setStyleSheet(qss);
        }
    qDebug()<<"初始化控件";



    //成就1：num>1
    name[0]->setText("初来乍到：");
    qDebug()<<"?1";
    content[0]->setText("创建一个番茄钟    ");
    qDebug()<<"?2";
    pb[0]->setMaximum(1);
    if(num>1){
        pb[0]->setValue(1);
        status[0]->setText("已达成");

    }
    pb[0]->setValue(num);

    //成就2：num>5
    name[1]->setText("新手上路：");
    content[1]->setText("番茄钟数量达到5个 ");
    pb[1]->setMaximum(5);
    if(num>5){
        pb[1]->setValue(5);
        status[1]->setText("已达成");
    }
    pb[1]->setValue(num);

    //成就3：num>15
    name[2]->setText("轻车熟路：");
    content[2]->setText("番茄钟数量达到15个");
    pb[2]->setMaximum(15);
    if(num>15){
        pb[2]->setValue(15);
        status[2]->setText("已达成");
    }
    pb[2]->setValue(num);

    //成就4：num>20
    name[3]->setText("渐入佳境：");
    content[3]->setText("番茄钟数量达到20个");
    pb[3]->setMaximum(20);
    if(num>20){
        pb[3]->setValue(20);
        status[3]->setText("已达成");
    }
    pb[3]->setValue(num);

    //成就5：num>30
    name[4]->setText("老番茄：");
    content[4]->setText("番茄钟数量达到30个");
    pb[4]->setMaximum(30);
    if(num>30){
        pb[4]->setValue(30);
        status[4]->setText("已达成");
    }
    pb[4]->setValue(num);

    //组装控件
    for(int i = 0;i < 5;i++){
        QHBoxLayout *hb = new QHBoxLayout;
        QVBoxLayout *vb = new QVBoxLayout;
        vb->addWidget(name[i]);
        vb->addWidget(content[i]);
        hb->addLayout(vb);
        hb->addWidget(pb[i]);
        hb->addWidget(status[i]);
        hb->setStretchFactor(vb,2);
        hb->setStretchFactor(pb[i],5);
        hb->setStretchFactor(status[i],1);
        gbx[i]->setLayout(hb);
        mainlayout->addWidget(gbx[i],1);

    }
    qDebug()<<"组装控件";

    setLayout(mainlayout);
}




