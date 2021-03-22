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
    void setB(bool value);

    bool getB() const;

protected:
    //    void paintEvent(QPaintEvent *event);
private:
    Ui::Widget *ui;
    QColor bgColor;
    bool b;
};

#endif // WIDGET_H
