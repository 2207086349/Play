#include "mainwin.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWin w;
    //禁用最大化按钮
    w.setWindowFlag(Qt::WindowMaximizeButtonHint, false);
    //窗口标题
    w.setWindowTitle("UNDERTALE_AU(Made by BiliBili:ResurrectedCells)");
    w.show();

    a.exec();
}
