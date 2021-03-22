#include "widget.h"
#include "ui_widget.h"

#include <QPaintEvent>
#include <QPainter>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::setBg(QColor c)
{

    ui->label->setStyleSheet(tr("background-color:rgb(%1,%2,%3);").arg(c.red()).arg(c.green()).arg(c.blue()));
}

void Widget::setB(bool value)
{
    b = value;
}

bool Widget::getB() const
{
    return b;
}

