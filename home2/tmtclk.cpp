#include "tmtclk.h"
#include "ui_tmtclk.h"

TmtClk::TmtClk(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TmtClk)
{
    ui->setupUi(this);
    Opacity = 0.8; // 透明度设置
    state = 1;   // 暂停，恢复暂停
    tomato_num = 1; //番茄钟计数
    total_count = 0;//总数
    current_color = "background:#FF4040"; //当前背景色设置
    this->setStyleSheet(current_color);                 //设置背景颜色
    this->setWindowFlags(Qt::FramelessWindowHint);      //设置为无边框窗口
    //this->setMinimumSize(100,50);                        //设置最小尺寸
    //this->setMaximumSize(200,100);                      //设置最大尺寸
    this->setWindowOpacity(Opacity);                    //设置不透明度
    // 置顶
    ::SetWindowPos(HWND(this->winId()), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
    //    // 不置顶
    //    ::SetWindowPos(HWND(this->winId()), HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);

    timer = new QTimer;

    ui->label_clk->setText("专注！");
    ui->Timer->setDigitCount(5);                    //设置显示位数为8位
    initTime();                                      //令LCD显示00:00:00
    timer->setInterval(1000);                        //设置定时器间隔为1000=1s
    //连接槽函数，将timer的timeout行为，连接到updateTime函数中
    connect(timer, SIGNAL(timeout()), this, SLOT(updateTime()));
    //当点击(clicked)pbStart时，调用函数pbStart_clicked
    //connect(ui->pbStart, SIGNAL(clicked()), this, SLOT(pbStart_clicked()));
    timer->start();  //启用定时器
    connect(ui->btn_end,&QPushButton::clicked,this,&QWidget::close);

}

void TmtClk::mousePressEvent(QMouseEvent *e)  //鼠标单击事件
{
    if(e->button()==Qt::LeftButton)
        clickPos=e->pos();

    this->setWindowOpacity(Opacity);
    if (state == 1){
        //暂停
        state = 0;
        this->setStyleSheet("background:#B5B5B5");    //设置暂停背景颜色
        Opacity = 0.2;
        timer->stop();
        this->setWindowOpacity(Opacity);                    //设置不透明度
    }else{//恢复
        state = 1;
        timer->start();
        this->setStyleSheet( current_color);          //恢复背景颜色
        Opacity = 0.8;
    }
    this->setWindowOpacity(Opacity);                    //设置不透明度
}

void TmtClk::mouseMoveEvent(QMouseEvent *e)  //鼠标移动事件
{
    if(e->buttons()&Qt::LeftButton)
        move(e->pos()+pos()-clickPos); //父窗口的左上角+当前鼠标指针移动-初始单击时候鼠标指针的方向
}

void TmtClk::closeEvent(QCloseEvent *e){
    //窗口关闭时弹出的提示窗口
    QMessageBox msgBox;//窗口位置有问题？？？？？？
    this->lower();
    msgBox.setText("提示");
    msgBox.setInformativeText("确认退出番茄钟?");
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Ok);
    int ret = msgBox.exec();
    if(ret == QMessageBox::Ok){
        //若用户点击确认，则接收这个事件,当前窗口会关闭
        update_data();//上传数据
        e->accept();
    }else{
        //若用户点击取消，则忽略这个事件，当前窗口不会关闭
        e->ignore();
    }
}

void TmtClk::setter(int h,int m,QString n){
    hour = h;
    minute = m;
    name = n;
}

void TmtClk::init(){
    timer->start();  //启用定时器
}

void TmtClk::initTime()
{
    time.setHMS(0,0,0); //时间复位 0
    ui->Timer->display(time.toString("mm:ss"));
}

void TmtClk::updateTime()
{
    //每次更新时间，time增加1
    time = time.addSecs(1);
    ui->Timer->display(time.toString("mm:ss"));
    /*if (time.second()==hour && time.second() == minute && tomato_num==0){
        //开始休息
        tomato_num = 1;
        total_count++;
        initTime();
        current_color = "background:#FFF0F5";
        this->setStyleSheet(current_color);    //进入休息色
        ui->label_clk->setText("休息时间");
    }else if(time.second() == 10 && tomato_num == 1){
        //休息三分钟，休息完毕，再次工作
        tomato_num = 0;
        initTime();
        current_color = "background:#FF4040";
        this->setStyleSheet(current_color);    //进入番茄色
        ui->label_clk->setText("专注！");
    }*/
    if (time.minute() == hour and time.second() == minute and tomato_num==1){
        //休息完毕，进入番茄钟
        tomato_num = 0;
        initTime();
        current_color = "background:#FFF0F5";
        ui->label_clk->setText("休息时间");
        this->setStyleSheet(current_color);    //进入番茄色
    }else if(time.second() == 10){
        //番茄钟完毕，进入休息时间
        tomato_num = 1;
        total_count++;
        initTime();
        current_color = "background:#FF4040";
        ui->label_clk->setText("专注！");
        this->setStyleSheet(current_color);    //进入休息色
    }
    }

TmtClk::~TmtClk()
{
    delete ui;
}


void TmtClk::update_data(){
    QSqlQuery query;
    query.exec(QString("select * from clk where name = '%1'").arg(name));
    query.next();
    int c = query.value("count").toInt();
    total_count += c;
    query.exec(QString("update clk set count =%1 where name = '%2'").arg(QString::number(total_count),name));
}
