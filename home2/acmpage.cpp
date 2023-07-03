#include "acmpage.h"
#include "ui_acmpage.h"

acmpage::acmpage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::acmpage)
{
    ui->setupUi(this);
}

acmpage::~acmpage()
{
    delete ui;
}
