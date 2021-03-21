#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    void setBg(QColor c);
protected:
//    void paintEvent(QPaintEvent *event);
private:
    Ui::Widget *ui;
    QColor bgColor;
};

#endif // WIDGET_H
