#include "mainpage.h"

mainpage::mainpage(QMainWindow * parent ) : QWidget(parent)
{
    QPixmap game_img(":/object/src/object/game_img.png");
    game_label = new QLabel(parent);
    game_label->setGeometry(100,50,800,250);
    game_label->setPixmap(game_img.scaled(800,300,Qt::KeepAspectRatio));
    game_label->setAlignment(Qt::AlignCenter);
    game_label->show();


    object_pal.setColor(QPalette::ButtonText,QColor(BUTTON_TEXT_COLOR));
    object_pal.setColor(QPalette::Button,QColor(BUTTON_COLOR));
    object_pal.setColor(QPalette::Window,QColor(150,150,150));

    p1 = new QPushButton(parent);
    p1->setGeometry(100,YPOS_1,PLAYER_BUTTON_WIDTH,PLAYER_BUTTON_HEIGHT);
    p1->setText("1 PLAYER");
    p1->setFont(QFont("Courier",26));
    p1->setPalette(object_pal);
    p1->setAutoFillBackground(true);
    p1->show();

    p2 = new QPushButton(parent);
    p2->setGeometry(100,YPOS_2,PLAYER_BUTTON_WIDTH,PLAYER_BUTTON_HEIGHT);
    p2->setText("2 PLAYERS");
    p2->setFont(QFont("Courier",26));
    p2->setPalette(object_pal);
    p2->setAutoFillBackground(true);
    p2->show();

    object_pal.setColor(QPalette::Button,QColor(180,180,180));
    object_pal.setColor(QPalette::Text,QColor(30,30,30));

    QPixmap p1_(":/object/src/object/man7_r-removebg.png");
    p1_.scaled(QSize(OBJECT_WIDTH,OBJECT_WIDTH),Qt::KeepAspectRatioByExpanding);
    QIcon p1_img(p1_);
    p1_img.pixmap(OBJECT_WIDTH,OBJECT_WIDTH);
    p1_man = new QPushButton(parent);
    p1_man->setGeometry(XPOS_1,YPOS_3 ,OBJECT_WIDTH,OBJECT_WIDTH);
    p1_man->setPalette(object_pal);
    p1_man->setIcon(p1_img);
    p1_man->setAutoFillBackground(true);
    p1_man->show();

    QPixmap p2_(":/object/src/object/man27_l.png");
    p2_.scaled(QSize(OBJECT_WIDTH,OBJECT_WIDTH),Qt::KeepAspectRatioByExpanding);
    QIcon p2_img(p2_);
    p2_img.pixmap(OBJECT_WIDTH,OBJECT_WIDTH);
    p2_man = new QPushButton(parent);
    p2_man->setGeometry(XPOS_2,YPOS_3,OBJECT_WIDTH,OBJECT_WIDTH);
    p2_man->setPalette(object_pal);
    p2_man->setIcon(p2_img);
    p2_man->setAutoFillBackground(true);
    p2_man->show();

    QPixmap g1_(":/object/src/object/ghost_r1.png");
    g1_.scaled(QSize(OBJECT_WIDTH,OBJECT_WIDTH),Qt::KeepAspectRatioByExpanding);
    QIcon g1_img(g1_);
    g1_img.pixmap(OBJECT_WIDTH,OBJECT_WIDTH);
    g1 = new QPushButton(parent);
    g1->setGeometry(XPOS_3,YPOS_3,OBJECT_WIDTH,OBJECT_WIDTH);
    g1->setPalette(object_pal);
    g1->setIcon(g1_img);
    g1->setAutoFillBackground(true);
    g1->show();

    QPixmap g2_(":/object/src/object/ghost_b1.png");
    g2_.scaled(QSize(OBJECT_WIDTH,OBJECT_WIDTH),Qt::KeepAspectRatioByExpanding);
    QIcon g2_img(g2_);
    g2_img.pixmap(OBJECT_WIDTH,OBJECT_WIDTH);
    g2 = new QPushButton(parent);
    g2->setGeometry(XPOS_4,YPOS_3,OBJECT_WIDTH,OBJECT_WIDTH);
    g2->setPalette(object_pal);
    g2->setIcon(g2_img);
    g2->setAutoFillBackground(true);
    g2->show();

    QPixmap g3_(":/object/src/object/ghost_y1.png");
    g3_.scaled(QSize(OBJECT_WIDTH,OBJECT_WIDTH),Qt::KeepAspectRatioByExpanding);
    QIcon g3_img(g3_);
    g3_img.pixmap(OBJECT_WIDTH,OBJECT_WIDTH);
    g3 = new QPushButton(parent);
    g3->setGeometry(XPOS_5,YPOS_3,OBJECT_WIDTH,OBJECT_WIDTH);
    g3->setPalette(object_pal);
    g3->setIcon(g3_img);
    g3->setAutoFillBackground(true);
    g3->show();

    QPixmap g4_(":/object/src/object/ghost_p1.png");
    g4_.scaled(QSize(OBJECT_WIDTH,OBJECT_WIDTH),Qt::KeepAspectRatioByExpanding);
    QIcon g4_img(g4_);
    g4_img.pixmap(OBJECT_WIDTH,OBJECT_WIDTH);
    g4 = new QPushButton(parent);
    g4->setGeometry(XPOS_6,YPOS_3,OBJECT_WIDTH,OBJECT_WIDTH);
    g4->setPalette(object_pal);
    g4->setIcon(g4_img);
    g4->setAutoFillBackground(true);
    g4->show();

    object_info.img = new QLabel(parent);
    object_info.img->setGeometry(IMG_XPOS,IMG_YPOS,IMG_WIDTH,IMG_WIDTH);

    object_info.text = new QLabel(parent);
    object_info.text->setGeometry(INFO_XPOS,INFO_YPOS,470,200);
    object_info.text->setAlignment(Qt::AlignLeft|Qt::AlignTop);

    object_img[map_info::red].load(":/object/src/object/ghost_r1.png");
    object_img[map_info::blue].load(":/object/src/object/ghost_b1.png");
    object_img[map_info::yellow].load(":/object/src/object/ghost_y1.png");
    object_img[map_info::pink].load(":/object/src/object/ghost_p1.png");
    object_img[map_info::man].load(":/object/src/object/man7_l-removebg.png");
    object_img[map_info::man2].load(":/object/src/object/man27_r.png");

    object_speed[map_info::red] = 30;
    object_speed[map_info::blue] = 30;
    object_speed[map_info::yellow] = 67;
    object_speed[map_info::pink] = 10;
    object_speed[map_info::man] = 5;
    object_speed[map_info::man2] = 6;

    object_cd[map_info::red] = 2.6;
    object_cd[map_info::blue] = 1;
    object_cd[map_info::yellow] = 3;
    object_cd[map_info::pink] = 0.3;
    object_cd[map_info::man] = 0.04;
    object_cd[map_info::man2] = 0.05;

    QString intr  = "Introduction : ";
    QString empty = "               ";

    object_intro[map_info::red]    = intr  + "A powerful shooter that \n\n" +
                                     empty + "all man fear\n\n";
    object_intro[map_info::blue]   = intr  + "A hentai that always \n\n" +
                                     empty + "approach the man by going\n\n" +
                                     empty + "through the nearest route\n\n";
    object_intro[map_info::yellow] = intr  + "A ghost moves like a \n\n" +
                                     empty + "chess-knight\n\n";
    object_intro[map_info::pink]   = intr  + "A crazy ghost that moves \n\n" +
                                     empty + "unpredictably and fast\n\n";
    object_intro[map_info::man]    = intr  + "A happy man who likes eating \n\n" +
                                     empty + "food all the day\n\n";
    object_intro[map_info::man2]   = intr  + "Just like the happy man but \n\n" +
                                     empty + "move a little bitfaster\n\n";

    p1_ctrl = false;
    p2_ctrl = false;
    g1_ctrl = false;
    g2_ctrl = false;
    g3_ctrl = false;
    g4_ctrl = false;

    connect(p1,SIGNAL(clicked()),this,SLOT(object_close()));
    connect(p2,SIGNAL(clicked()),this,SLOT(object_close()));

    connect(p1_man,SIGNAL(clicked()),SLOT(p1_info_ctrl()));
    connect(p2_man,SIGNAL(clicked()),SLOT(p2_info_ctrl()));
    connect(g1,SIGNAL(clicked()),SLOT(g1_info_ctrl()));
    connect(g2,SIGNAL(clicked()),SLOT(g2_info_ctrl()));
    connect(g3,SIGNAL(clicked()),SLOT(g3_info_ctrl()));
    connect(g4,SIGNAL(clicked()),SLOT(g4_info_ctrl()));

}

void mainpage::object_close(){
    game_label->close();
    p1->close();
    p2->close();
    p1_man->close();
    p2_man->close();
    g1->close();
    g2->close();
    g3->close();
    g4->close();
    object_info.img->close();
    object_info.text->close();
}

void mainpage::object_show(){
    game_label->show();
    p1->show();
    p2->show();
    p1_man->show();
    p2_man->show();
    g1->show();
    g2->show();
    g3->show();
    g4->show();
    object_info.img->close();
    object_info.text->close();
}

void mainpage::p1_info_ctrl(){
    p1_ctrl = ! p1_ctrl;
    if(p1_ctrl){
        object_info.img->setPixmap(object_img[map_info::man].scaled(IMG_WIDTH,IMG_WIDTH,Qt::KeepAspectRatio));
        object_info.speed = QString("move speed : %1\n\n").arg(object_speed[map_info::man]);
        object_info.cd = QString("move CD : %1 d\n\n").arg(object_cd[map_info::man]);
        object_info.brief_intro = object_intro[map_info::man];
        object_info.text->setText(object_info.speed + object_info.cd + object_info.brief_intro);
        object_info.text->setFont(QFont("Courier",16));
        object_info.img->show();
        object_info.text->show();
    }
    else {
        object_info.img->close();
        object_info.text->close();
    }
}
void mainpage::p2_info_ctrl(){
    p2_ctrl = ! p2_ctrl;
    if(p2_ctrl){
        object_info.img->setPixmap(object_img[map_info::man2].scaled(IMG_WIDTH,IMG_WIDTH,Qt::KeepAspectRatio));
        object_info.speed = QString("move speed : %1\n\n").arg(object_speed[map_info::man2]);
        object_info.cd = QString("move CD : %1 s\n\n").arg(object_cd[map_info::man2]);
        object_info.brief_intro = object_intro[map_info::man2];
        object_info.text->setText(object_info.speed + object_info.cd + object_info.brief_intro);
        object_info.text->setFont(QFont("Courier",16));
        object_info.img->show();
        object_info.text->show();
    }
    else {
        object_info.img->close();
        object_info.text->close();
    }
}
void mainpage::g1_info_ctrl(){
    g1_ctrl = ! g1_ctrl;
    if(g1_ctrl){
        object_info.img->setPixmap(object_img[map_info::red].scaled(IMG_WIDTH,IMG_WIDTH,Qt::KeepAspectRatio));
        object_info.speed = QString("move speed : %1\n\n").arg(object_speed[map_info::red]);
        object_info.cd = QString("move CD : %1 s\n\n").arg(object_cd[map_info::red]);
        object_info.brief_intro = object_intro[map_info::red];
        object_info.text->setText(object_info.speed + object_info.cd + object_info.brief_intro);
        object_info.text->setFont(QFont("Courier",16));
        object_info.img->show();
        object_info.text->show();
    }
    else{
        object_info.img->close();
        object_info.text->close();
    }
}
void mainpage::g2_info_ctrl(){
    g2_ctrl = ! g2_ctrl;
    if(g2_ctrl){
        object_info.img->setPixmap(object_img[map_info::blue].scaled(IMG_WIDTH,IMG_WIDTH,Qt::KeepAspectRatio));
        object_info.speed = QString("move speed : %1\n\n").arg(object_speed[map_info::blue]);
        object_info.cd = QString("move CD : %1 s\n\n").arg(object_cd[map_info::blue]);
        object_info.brief_intro = object_intro[map_info::blue];
        object_info.text->setText(object_info.speed + object_info.cd + object_info.brief_intro);
        object_info.text->setFont(QFont("Courier",16));
        object_info.img->show();
        object_info.text->show();
    }
    else {
        object_info.img->close();
        object_info.text->close();
    }
}
void mainpage::g3_info_ctrl(){
    g3_ctrl = ! g3_ctrl;
    if(g3_ctrl){
        object_info.img->setPixmap(object_img[map_info::yellow].scaled(IMG_WIDTH,IMG_WIDTH,Qt::KeepAspectRatio));
        object_info.speed = QString("move speed : %1\n\n").arg(object_speed[map_info::yellow]);
        object_info.cd = QString("move CD : %1 s\n\n").arg(object_cd[map_info::yellow]);
        object_info.brief_intro = object_intro[map_info::yellow];
        object_info.text->setText(object_info.speed + object_info.cd + object_info.brief_intro);
        object_info.text->setFont(QFont("Courier",16));
        object_info.img->show();
        object_info.text->show();
    }
    else {
        object_info.img->close();
        object_info.text->close();
    }
}
void mainpage::g4_info_ctrl(){
    g4_ctrl = ! g4_ctrl;
    if(g4_ctrl){
        object_info.img->setPixmap(object_img[map_info::pink].scaled(IMG_WIDTH,IMG_WIDTH,Qt::KeepAspectRatio));
        object_info.speed = QString("move speed : %1\n\n").arg(object_speed[map_info::pink]);
        object_info.cd = QString("move CD : %1 s\n\n").arg(object_cd[map_info::pink]);
        object_info.brief_intro = object_intro[map_info::pink];
        object_info.text->setText(object_info.speed + object_info.cd + object_info.brief_intro);
        object_info.text->setFont(QFont("Courier",16));
        object_info.img->show();
        object_info.text->show();
    }
    else{
        object_info.img->close();
        object_info.text->close();
    }
}
