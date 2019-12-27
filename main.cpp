#include "mainwindow.h"
#include "familytree.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    FamilyTree save1;
    FamilyTree save2;
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    a.connect(&a, SIGNAL(focusChanged(QWidget *,QWidget *)),&w,SLOT(changedfocus(QWidget *,QWidget *)));
    a.connect(&a, SIGNAL(focusChanged(QWidget *,QWidget *)),&w,SLOT(insertParents(QWidget *,QWidget *)));



    return a.exec();
}
