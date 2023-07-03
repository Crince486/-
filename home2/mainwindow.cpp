#include "mainwindow.h"
//#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->resize(QSize(680,600));

}

MainWindow::~MainWindow()
{
    //delete ui;
}
void MainWindow::initdata(int uid){
    QSqlQuery query;
    //初始化类别容器
    query.exec(QString("select category from clk where uid = %1").arg(QString::number(uid)));
    while(query.next()){
        category<<query.value("category").toString();
    }

    //初始化每个类别相应的完成次数
    for(int i= 0;i<category.size();i++){
        if(category[i].isNull())
            continue;
        query.exec(QString("select * from clk where uid = %1 and category = '%2'").arg(QString::number(uid),category[i]));

        int c = 0;
        while(query.next()){
            int t =query.value("count").toInt();
            c=c+t;

        }
        cate_count<<c;
        //后面相同的类别置null 不重复计数
        //if(i == category.size() - 1)
        //    break;
        for(int t = 0;t < category.size();t++){
            if(t==i)
                continue;
            if(category[t]==category[i])
                category[t]=QString();
        }

    }

    //初始化名称容器
    query.exec(QString("select name from clk where uid = %1").arg(uid));
    while(query.next()){
        name<<query.value("name").toString();
    }

    //初始化每个任务的完成次数
    for(int i= 0;i<name.size();i++){
        query.exec(QString("select count from clk where uid = %1 and name = '%2'").arg(QString::number(uid),name[i]));
        int c = 0;
        while(query.next()){
            c +=query.value("count").toInt();
        }
        name_count<<c;
    }
}

//类别饼图
void MainWindow::initPie(){
    QPieSeries *pie_series = new QPieSeries();
    QList<QString>cate_new;

    int total_count = 0;
    for(int i= 0;i<cate_count.size();i++){
        total_count+=cate_count[i];
    }
    for(int i = 0;i < category.size();i++){
        if(category[i].isNull())
            continue;
        cate_new<<category[i];
}
    qDebug()<<total_count;
    //设置图标名称,占比
    for(int i= 0;i<cate_count.size();i++){
        double a = cate_count[i];
        double b = total_count;
        double t = (a/b)*100;//占比
        qDebug()<<"t:"<<t;
        QString ratio = QString::number(t,'f',1);//设置小数精度：小数点后一位
        qDebug()<<"ratio:"<<ratio;
        pie_series->append(QString("%1  %2 \%").arg(cate_new[i],ratio),cate_count[i]);//设置名称和占比
    }

    pie_series->setLabelsVisible();

    for(int i= 0;i<cate_new.size();i++){

        QPieSlice *slice = pie_series->slices().at(i);
        QColor qc=QColor::fromHsl(rand()%360,rand()%256,rand()%200);//根据数据量随机生成颜色，有可能生成的颜色不适合，待优化。
        slice->setColor(QColor(qc.red(),qc.green(),qc.blue()));
    }
    pie = new QChart();
    pie->addSeries(pie_series);
    pie->setTitle("按类别统计");
}

void MainWindow::initBar(){
    //QBarSet设置为一个任务名一个set
    //每个set中只含一个数据 即任务完成次数
    //往bar_series中append（）每个set
    QBarSeries *bar_series = new QBarSeries();
    QBarSet *set = new QBarSet("番茄钟任务完成次数");
    QSqlQuery query;
    for(int i = 0;i<name.size();i++){
        *set<<name_count[i];
    }
    bar_series->append(set);
    bar = new QChart();
    bar->addSeries(bar_series);
    bar->setTitle("按任务统计");
    bar->setAnimationOptions(QChart::SeriesAnimations);

    QStringList name_bar;
    for(int i = 0;i<name.size();i++){
        name_bar<<name[i];
    }
    //实例化坐标轴文字标识轴
    QBarCategoryAxis *axis = new QBarCategoryAxis();
    //将文字放入标识轴中
    axis->append(name_bar);
    //创建默认的坐标轴
    bar->createDefaultAxes();
    //设置坐标轴
    bar->setAxisX(axis, bar_series);

    //设置图例为显示状态
    bar->legend()->setVisible(true);
    //设置图例位置为底部
    bar->legend()->setAlignment(Qt::AlignBottom);

}

void MainWindow::initview(int uid){

    initdata(uid);//初始化数据
    initPie();//初始化饼图
    initBar();//初始化柱状图

    //将两个chart添加到chartView中
    QChartView *pie_chartview = new QChartView(pie);
    QChartView *bar_chartview = new QChartView(bar);
    pie_chartview->setRenderHint(QPainter::Antialiasing);

    //显示到界面上
    //this->setCentralWidget(chartview);
    //滚动条待解决
    QScrollArea *cenWidget = new QScrollArea;
    QVBoxLayout *mainlayout = new QVBoxLayout(cenWidget);
    mainlayout->addWidget(pie_chartview);
    mainlayout->addWidget(bar_chartview);
    cenWidget->setLayout(mainlayout);
    this->setCentralWidget(cenWidget);
    //this->setCentralWidget(pie_chartview);

}
