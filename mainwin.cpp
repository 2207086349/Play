#include "mainwin.h"
#include "ui_mainwin.h"

void MainWin::paintEvent(QPaintEvent *)
{
    if(theTitle)
    {
        QPainter title_P(this);
        title_P.drawPixmap(20, 200, 600, 40, QPixmap(":/img/theTitle.png"));
        setStyleSheet("background-color: qlineargradient(spread:pad, x1:1, y1:1, x2:1, y2:0, stop:0 rgba(0, 0, 0, 255), stop:1 rgba(255, 255, 255, 255));");
    }

    if(theGameIsStart)
    {
        //填充透明背景
        redHeartS.redHeart.fill(Qt::transparent);
        QPainter painRedHeart_P(&redHeartS.redHeart);
        painRedHeart_P.drawPixmap(0, 0, 30, 30, QPixmap(":/img/redHeart.png"));
        QPainter redHeart_P(this);
        redHeart_P.drawPixmap(redHeartS.heartX - 15, redHeartS.heartY - 15, QPixmap(redHeartS.redHeart));
        /*--------------------画出血条297*33------------------------*/
        QPainter HPY_P(this);
        HPY_P.setBrush(QBrush(Qt::yellow));
        HPY_P.drawRect(QRect(this->width()/2 - 297/2, 700, 297 * (redHeartS.HP/99), 28));
        QPainter HPR_P(this);
        HPR_P.setBrush(QBrush(Qt::red));
        int theRed = 297*(redHeartS.HP/99);
        qDebug() << theRed;
        HPR_P.drawRect(QRect(this->width()/2 - 297/2 + 297, 700, -theRed, 28));
    }
}

MainWin::MainWin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWin)
{
    ui->setupUi(this);
    setMouseTracking(true);
    /*----------------------窗口大小---------------------------*/
    resize(640, 480);
    /*----------------------放标题-----------------------------*/
    theTitle = true;
    update();
    /*----------------------进入游戏的动画----------------------*/
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [=]()mutable{
        theTitle = false;
        timer->stop();
        delete timer;
        QPropertyAnimation *theGameBegin = new QPropertyAnimation(this, "geometry");
        theGameBegin->setDuration(1500);
        theGameBegin->setStartValue(QRect(this->x(), this->y(), this->height(), this->width()));
        theGameBegin->setEndValue(QRect(1920/2 - 500/2, 1080/2 - 750/2, 500, 750));
        theGameBegin->setEasingCurve(QEasingCurve::InOutBack);
        theGameBegin->start(QAbstractAnimation::DeleteWhenStopped);
        connect(theGameBegin, &QPropertyAnimation::finished, this, [=](){
            theGameStart();
        });
    });
    timer->start(2500);
    /*-----------------------这是测试用的-----------------------*/
    //theGameStart();
    this->setWindowFlag(Qt::WindowStaysOnTopHint);
}

MainWin::~MainWin()
{
    delete ui;
}

void MainWin::theGameStart()
{
    setCursor(Qt::BlankCursor);
    theGameIsStart = true;
    //设置背景
    setStyleSheet("background-color: rgb(0, 0, 0);");
    //移动鼠标
    SetCursorPos(this->x() + this->width()/2, this->y() + 700);

    update();
}

void MainWin::mouseMoveEvent(QMouseEvent *event)
{
    redHeartS.heartX = event->x();
    redHeartS.heartY = event->y();
    update();
}
