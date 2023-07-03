#ifndef CLKMODULE_H
#define CLKMODULE_H
#include <QString>

class ClkModule
{
public:
    ClkModule(QString name, QString category, int hour, int minute);

    QString get_name();
    QString get_category();
    int get_hour();
    int get_minute();
private:
    QString name;//任务名
    QString category;//类别
    int hour;//小时
    int minute;//分钟

};

#endif // CLKMODULE_H
