#ifndef ACMPAGE_H
#define ACMPAGE_H

#include <QWidget>

namespace Ui {
class acmpage;
}

class acmpage : public QWidget
{
    Q_OBJECT

public:
    explicit acmpage(QWidget *parent = nullptr);
    ~acmpage();

private:
    Ui::acmpage *ui;
};

#endif // ACMPAGE_H
