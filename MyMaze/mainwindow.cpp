#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFile>
#include <QDebug>
#include "widget.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QFile maze(":/data/maze/maze");
    if(maze.open(QFile::ReadOnly)){
        while(!maze.atEnd()){
            QString row=maze.readLine().simplified();

            map.append(row);
        }
    }
    foreach (QString row, map) {
        QWidget *qw=new QWidget();
        QHBoxLayout *bl=new QHBoxLayout();
        bl->setContentsMargins(0,0,0,0);
        qw->setLayout(bl);
        for(int i=0;i<row.size();i++){
            Widget *w=new Widget;
            if(row.at(i)=="0"){
                w->setBg(QColor(255,255,255));
            }
            else{
                w->setBg(QColor(0,0,0));
            }
            bl->addWidget(w);
        }
        ui->verticalLayout->addWidget(qw);
    }



    setWidgetBg(0,0,QColor(255,0,0));
    mapWidth=map.at(0).size();
    mapHeight=map.size();
    setWidgetBg(mapHeight-1,mapWidth-1,QColor(222,111,0));

    maze.close();

    Pos pos(0,0,"");
    queen.append(&pos);
    while(queen.size()!=0){
        Pos *move_node=queen[0];
        queen.removeAt(0);
        QPair<int,int> move_str(move_node->getX(),move_node->getY());

        if (!visited.contains(move_str)){
            visited.append(move_str);
            if (move_node->getX() == mapHeight-1 and move_node->getY() == mapWidth -1){
                qDebug()<<move_node->getPath();
                printPath(move_node->getPath());
                break;
            }
//            qDebug()<<move_node->getX()<<move_node->getY();
            if (move_node->getX()<mapHeight-1 && map.at(move_node->getX()+1).at(move_node->getY())=="0"){
                queen.append(down(move_node));
//                setWidgetBg(move_node->getX()+1,move_node->getY(),QColor(111,33,122));
            }
            if (move_node->getY()>0 && map.at(move_node->getX()).at(move_node->getY()-1)=="0"){
                queen.append(left(move_node));
//                     setWidgetBg(move_node->getX(),move_node->getY()-1,QColor(111,33,122));
            }
            if (move_node->getY()<mapWidth-1 && map.at(move_node->getX()).at(move_node->getY()+1)=="0"){
                queen.append(right(move_node));
//                     setWidgetBg(move_node->getX(),move_node->getY()+1,QColor(111,33,122));
            }
            if (move_node->getX()>0 && map.at(move_node->getX()-1).at(move_node->getY())=="0"){
                queen.append(up(move_node));
//                setWidgetBg(move_node->getX()-1,move_node->getY(),QColor(111,33,122));
            }
        }


    }



}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::printPath(QString path)
{
    int x=0,y=0;
    for(int i=0;i<path.size();i++){
        QString t=path.at(i);
        qDebug()<<x<<y<<t;
        setWidgetBg(y,x,QColor(255,228,181));
        if(t=="D"){
            y++;
        }
        else if(t=="U"){
            y--;

        }
        else if(t=="R"){
            x++;

        }
        else if(t=="L"){
            x--;

        }

    }
}

void MainWindow::setWidgetBg(int y, int x,QColor c)
{
    qobject_cast<Widget*>(ui->verticalLayout->layout()->itemAt(y)->widget()->layout()->itemAt(x)->widget())->setBg(c); ;

}

Pos::Pos(int x, int y, QString path):x(x),y(y),path(path)
{

}

QString Pos::getPath() const
{
    return path;
}

int Pos::getY() const
{
    return y;
}

int Pos::getX() const
{
    return x;
}

Pos *up(Pos *p)
{
   return new Pos(p->getX()-1,p->getY(),p->getPath()+"U");
}

Pos *right(Pos *p)
{
   return new Pos(p->getX(),p->getY()+1,p->getPath()+"R");
}


Pos *down(Pos *p)
{
   return new Pos(p->getX()+1,p->getY(),p->getPath()+"D");
}

Pos *left(Pos *p)
{
       return new Pos(p->getX(),p->getY()-1,p->getPath()+"L");
}
