#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFile>
#include <QDebug>
#include <QTimer>
#include <QTime>
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
                w->setB(0);
            }
            else{
                w->setBg(QColor(0,0,0));
                w->setB(1);
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

}

MainWindow::~MainWindow()
{
    flag=0;
    delete ui;
}

void MainWindow::printPath(QString path,QColor color)
{

    int x=0,y=0;
    for(int i=0;i<path.size();i++){
        QString t=path.at(i);
        //        qDebug()<<x<<y<<t;

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
        setWidgetBg(y,x,color);

    }
       delay(delayMs);
}

void MainWindow::setWidgetBg(int y, int x,QColor c)
{
    qobject_cast<Widget*>(ui->verticalLayout->layout()->itemAt(y)->widget()->layout()->itemAt(x)->widget())->setBg(c);
}


void MainWindow::delay(uint ms)
{
    QTime _Timer = QTime::currentTime().addMSecs(ms);

    while( QTime::currentTime() < _Timer )

        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

}

void MainWindow::erasePath(QString path)
{
    int x=0,y=0;
    for(int i=0;i<path.size();i++){
        QString t=path.at(i);


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
        if(getWidgetBool(y,x)){
            setWidgetBg(y,x,QColor(0,0,0));
        }
        else{
            setWidgetBg(y,x,QColor(255,255,255));
        }

    }


    setWidgetBg(0,0,QColor(255,0,0));
    setWidgetBg(mapHeight-1,mapWidth-1,QColor(222,111,0));

}

void MainWindow::iniBg()
{
    for(int i=0;i<ui->verticalLayout->count();i++) {

        for(int j=0;j<ui->verticalLayout->itemAt(i)->widget()->layout()->count();j++){
            Widget *w=qobject_cast<Widget*>(ui->verticalLayout->itemAt(i)->widget()->layout()->itemAt(j)->widget());
            if(map.at(i).at(j)=="0"){
                w->setBg(QColor(255,255,255));
                w->setB(0);
            }
            else{
                w->setBg(QColor(0,0,0));
                w->setB(1);
            }
        }
    }
}

void MainWindow::bfs()
{
    flag=1;
    queen.clear();
    visited.clear();
    Pos pos(0,0,"");
    queen.append(&pos);
    while(queen.size()!=0 && flag){

        //        目前走的是这一条
        Pos *move_node=queen[0];
        printPath(move_node->getPath(),QColor(255,228,181));

        qDebug()<<move_node->getY()<<move_node->getX()<<move_node->getPath();
        //       当前路径
        queen.removeAt(0);
        QPair<int,int> move_str(move_node->getY(),move_node->getX());

        if (!visited.contains(move_str)){
            visited.append(move_str);
            //             qDebug()<<move_node->getY()<<move_node->getX();
            if (move_node->getY() == mapHeight-1 and move_node->getX() == mapWidth -1){
                qDebug()<<move_node->getPath();
                printPath(move_node->getPath(),QColor(0,255,0));
                break;
            }
            if (move_node->getY()<mapHeight-1 && map.at(move_node->getY()+1).at(move_node->getX())=="0"){
                queen.append(down(move_node));
                setWidgetBg(move_node->getY()+1,move_node->getX(),QColor(122,51,244));
            }
            if (move_node->getX()>0 && map.at(move_node->getY()).at(move_node->getX()-1)=="0"){
                queen.append(left(move_node));
                setWidgetBg(move_node->getY(),move_node->getX()-1,QColor(122,51,244));
            }
            if (move_node->getX()< mapWidth-1 && map.at(move_node->getY()).at(move_node->getX()+1)=="0"){
                queen.append(right(move_node));
                setWidgetBg(move_node->getY(),move_node->getX()+1,QColor(122,51,244));
            }
            if (move_node->getY()>0 && map.at(move_node->getY()-1).at(move_node->getX())=="0"){
                queen.append(up(move_node));
                setWidgetBg(move_node->getY()-1,move_node->getX(),QColor(122,51,244));
            }


        }
        else{
            //已经走过的路径用红色标记
            //            printPath(move_node->getPath(),QColor(255,0,0));

        }
        delay(delayMs);

        erasePath(move_node->getPath());
    }
}

void MainWindow::dfs(int y,int x,Pos *move_node)
{

    qDebug()<<y<<x<<move_node->getPath();
    if(y == mapHeight-1 and x == mapWidth -1){
        printPath(move_node->getPath(),QColor(0,255,0));
        qDebug()<< "exit";
        flag=1;
        return ;
    }
    else{

        QPair<int,int> move_str(y,x);
        if (!visited.contains(move_str))
        {
            printPath(move_node->getPath(),QColor(255,228,181));
            visited.append(move_str);

            if (y<mapHeight-1 && map.at(y+1).at(x)=="0"){
                dfs(y+1,x,down(move_node));

                if(flag){
                    return ;
                }
                erasePath(move_node->getPath());
            }
            if (x>0 && map.at(y).at(x-1)=="0"){
                dfs(y,x-1, left(move_node));

                if(flag){
                    return ;
                }
                erasePath(move_node->getPath());

            }
            if (x< mapWidth-1 && map.at(y).at(x+1)=="0"){

                dfs(y,x+1,right(move_node));

                if(flag){
                    return ;
                }
                erasePath(move_node->getPath());
            }
            if (y>0 && map.at(y-1).at(x)=="0"){

                dfs(y-1,x,up(move_node));

                if(flag){
                    return ;
                }
                erasePath(move_node->getPath());
            }


        }

    }
}

bool MainWindow::getWidgetBool(int y, int x)
{
    return qobject_cast<Widget*>(ui->verticalLayout->itemAt(y)->widget()->layout()->itemAt(x)->widget())->getB();
}

void MainWindow::closeEvent(QCloseEvent *ev)
{
    flag=0;
    QMainWindow::closeEvent(ev);
}

Pos::Pos(int y, int x, QString path):x(x),y(y),path(path)
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
    return new Pos(p->getY()-1,p->getX(),p->getPath()+"U");
}

Pos *right(Pos *p)
{
    return new Pos(p->getY(),p->getX()+1,p->getPath()+"R");
}


Pos *down(Pos *p)
{
    return new Pos(p->getY()+1,p->getX(),p->getPath()+"D");
}

Pos *left(Pos *p)
{
    return new Pos(p->getY(),p->getX()-1,p->getPath()+"L");
}

void MainWindow::on_pushButton_clicked()
{
    iniBg();
    bfs();


}

void MainWindow::on_pushButton_2_clicked()
{
        iniBg();
    flag=0;
    visited.clear();
    Pos pos(0,0,"");
    dfs(0,0,&pos);
}
