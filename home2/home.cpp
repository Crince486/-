#include "home.h"

home::home(QWidget *parent)
    : QWidget(parent)

{
    this->resize(QSize(800,600));
    this->setStyleSheet("background-color: #FFFAFA;");
    //this->setWindowTitle(QString("欢迎！%1").arg());//需传参调整——————
    this->setWindowIcon(QIcon(":/new/prefix1/image/tomato.png"));

    QStackedWidget *la_StackedWidget = new QStackedWidget();

    //第一页：番茄钟主页面///////////
    page1 = new ClkPage;
    //需要的参数：uid,num 和clk_list

    //第二页：历史数据统计表格
    page2 = new MainWindow;
    //QWidget *page2 = new QWidget(this);
    //第三页：成就系统
    page3 = new Widget;
    //QWidget *page3 = new QWidget(this);


    // 添加页面到堆栈中
    la_StackedWidget->addWidget(page1);
    la_StackedWidget->addWidget(page2);
    la_StackedWidget->addWidget(page3);


    QListWidget *  listWidget_Function = new QListWidget();     //列表框及样式
    listWidget_Function->setViewMode(QListView::IconMode);
    listWidget_Function->setIconSize(QSize(100,100));
    listWidget_Function->setSpacing(40);
    listWidget_Function->setResizeMode(QListWidget::Adjust);
    listWidget_Function->setMovement(QListWidget::Static);
    listWidget_Function->setFixedWidth(200);
    listWidget_Function->setStyleSheet("background-color: #F8F8FF;");

            //setViewMode(QListView::IconMode)  设置列表框的显示模式为图标模式。
            //setIconSize(QSize(64,64))         设置图标的大小为64*64像素。
            //setSpacing(5)                     设置图标之间的间距为5像素。
            //setResizeMode(QListWidget::Adjust)设置列表框大小自适应子项。
            //setMovement(QListWidget::Static)  设置列表框中的子项不可移动。
            //setFixedWidth(120)                设置列表框的宽度为120像素。
            //setStyleSheet("background-color: #87CEFA;");设置列表框的背景颜色。


        QListWidgetItem *item1 = new QListWidgetItem(listWidget_Function);
        item1->setText("番茄钟");
        item1->setTextAlignment(Qt::AlignCenter);
        item1->setIcon(QIcon(":/new/prefix1/image/tomato.png")); //选项图片
        QListWidgetItem *item2 = new QListWidgetItem(listWidget_Function);
        item2->setText("历史");
        item2->setTextAlignment(Qt::AlignCenter);
        item2->setIcon(QIcon(":/new/prefix1/image/history.png")); //选项图片
        QListWidgetItem *item3 = new QListWidgetItem(listWidget_Function);
        item3->setText("成就");
        item3->setTextAlignment(Qt::AlignCenter);
        item3->setIcon(QIcon(":/new/prefix1/image/trophy.png")); //选项图片


    QObject::connect(listWidget_Function, &QListWidget::currentRowChanged,
    la_StackedWidget, &QStackedWidget::setCurrentIndex);

    QHBoxLayout *hboxLayout_Form = new QHBoxLayout();  //总布局
    hboxLayout_Form->addWidget(listWidget_Function,1);            //切换部分
    hboxLayout_Form->addWidget(la_StackedWidget,5);            //显示部分

    this->setLayout(hboxLayout_Form);
    this->resize(QSize(800,600));
}

home::~home()
{

}

void home::initClkPage(int uid,int num,QList<ClkModule*>clk_list){
    page1->set_uid(uid);
    qDebug()<<"page1 uid"<<uid<<page1->get_uid();
    if(num==0)
        return;
    QList<int>hour;
    QList<int> minute;
    QList<QString> name;
    QList<QString> category;
    for(int i = 0;i < num;i++){
        hour<<clk_list[i]->get_hour();
        minute<<clk_list[i]->get_minute();
        name<<clk_list[i]->get_name();
        category<<clk_list[i]->get_category();

    }
    page1->init(num,hour,minute,name,category);

}

void home::initHistoryPage(int uid){
    page2->initview(uid);
}

void home::initAcmPage(int n){
    qDebug()<<"readytoinitacm";
    page3->set_num(n);
    qDebug()<<"numset";
    page3->openAchievementSys();
}

