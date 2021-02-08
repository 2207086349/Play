#ifndef MAINWIN_H
#define MAINWIN_H

#include <QWidget>
#include <QKeyEvent>
#include <QPixmap>
#include <QPainter>
#include <QDebug>
#include <QPropertyAnimation>
#include <QTimer>
#include <windows.h>

namespace Ui {
class MainWin;
}

class MainWin : public QWidget
{
    Q_OBJECT

public:
    explicit MainWin(QWidget *parent = nullptr);
    ~MainWin();

protected:
    void mouseMoveEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *);

private:
    Ui::MainWin *ui;
    //标题
    bool theTitle = true;
    //小爱心
    struct redHeartS{
        QPixmap redHeart = QPixmap(30, 30);
        int heartX = 0;
        int heartY = 0;
        int HP = 98;
    }redHeartS;
    //是否开始游戏
    bool theGameIsStart = false;
    void theGameStart();
};

#endif // MAINWIN_H
