#ifndef MAINPAGE_H
#define MAINPAGE_H
#include <QWidget>
#include <QMainWindow>
#include <QPushButton>
#include <QHBoxLayout>
#include <QLabel>
#include "map_info.h"

#define PLAYER_BUTTON_WIDTH  180
#define PLAYER_BUTTON_HEIGHT  100
#define OBJECT_WIDTH 50

#define BUTTON_COLOR 30,220,220
#define BUTTON_TEXT_COLOR 30,60,60

#define IMG_XPOS 350
#define IMG_YPOS 375
#define IMG_WIDTH 100

#define INFO_XPOS 500
#define INFO_YPOS 375
#define INFO_WIDTH 450
#define INFO_HEIGHT 200

#define XPOS_1 350
#define XPOS_2 440
#define XPOS_3 530
#define XPOS_4 620
#define XPOS_5 710
#define XPOS_6 800
#define YPOS_1 375
#define YPOS_2 525
#define YPOS_3 575

typedef struct Information{
    QLabel * img;
    QLabel * text;
    QString brief_intro;
    QString special_skill;
    QString cd;
    QString speed;
}info;

class mainpage : public QWidget
{
    Q_OBJECT
public:
    mainpage(){}
    mainpage(QMainWindow * parent = nullptr);

    QPushButton * p1;
    QPushButton * p2;
    QPushButton * p1_man;
    QPushButton * p2_man;
    QPushButton * g1;
    QPushButton * g2;
    QPushButton * g3;
    QPushButton * g4;

public slots:
    void object_close();
    void object_show();
    void p1_info_ctrl();
    void p2_info_ctrl();
    void g1_info_ctrl();
    void g2_info_ctrl();
    void g3_info_ctrl();
    void g4_info_ctrl();
signals:

private:
    QPalette object_pal;
    QLabel * game_label;
    QPixmap object_img[6];
    QString object_intro[6];
    QString object_special_skill[6];
    int object_speed[6];
    double object_cd[6];

    info object_info;
    bool p1_ctrl;
    bool p2_ctrl;
    bool g1_ctrl;
    bool g2_ctrl;
    bool g3_ctrl;
    bool g4_ctrl;

};

#endif // MAINPAGE_H
