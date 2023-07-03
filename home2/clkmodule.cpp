#include "clkmodule.h"

ClkModule::ClkModule(QString name,QString category,int hour,int minute):
    name(name),category(category),hour(hour),minute(minute)
{

}
QString ClkModule::get_name(){
    return name;
}
QString ClkModule::get_category(){
    return category;
}
int ClkModule::get_hour(){
    return hour;
}
int ClkModule::get_minute(){
    return minute;
}
