#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}
class Pos{
public:
    int getX() const;

    int getY() const;

    QString getPath() const;
    Pos(int x,int y,QString path);
private:

    int x;
    int y;
    QString path;

};
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
//    const int MazeWidth=5;
//    const int MazeHeight=5;
    QVector<Pos*> queen;
    QVector<QString> map;
    QVector<QPair<int,int>>visited;
    QVector<QWidget*    > wv;
    int mapWidth;
    int mapHeight;
    void printPath(QString path);
    void setWidgetBg(int y, int x, QColor c);
};



Pos *up(Pos *p) ;
Pos *down(Pos *p) ;
Pos *left(Pos *p) ;
Pos *right(Pos *p) ;
#endif // MAINWINDOW_H
