#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QTimer>
#include <QCoreApplication>
#include <QMainWindow>
#include <QLabel>
#include <QTextStream>
#include <QFile>
#include <QPushButton>
#include <QMessageBox>
#include <iostream>
#include <fstream>

#include "map_info.h"
#include "man.h"
#include "man2.h"
#include "dot.h"
#include "object_original.h"
#include "ghost_red.h"
#include "ghost_blue.h"
#include "ghost_yellow.h"
#include "ghost_pink.h"
#include "mainpage.h"
using namespace map_info;
using namespace std;

#define MAPHEIGHT 21
#define MAPWIDTH 25
#define NUM_OF_GHOST 4
#define OTHER_OBJECT 1
#define BUTTON_WIDTH 120
#define BUTTON_HEIGHT 40
#define DASHBOARD_WIDTH 140
#define DASHBOARD_HEIGHT 200
#define TEXT_COLOR 200,200,200
#define BUTTON_COLOR 30,220,220
#define BUTTON_TEXT_COLOR 30,60,60


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void keyPressEvent(QKeyEvent *);
    void mousePressEvent(QMouseEvent *event);
    void show_message(int);


private slots:
    void menu_close();
    void menu_open();
    void get_man_pos(int,int);
    void get_man2_pos(int,int);
    void get_ghost1_pos(map_info::object_key,int,int);
    void get_ghost2_pos(map_info::object_key,int,int);
    void get_ghost3_pos(map_info::object_key,int,int);
    void get_ghost4_pos(map_info::object_key,int,int);
    void get_object_pos(int,int,map_info::other_object);
    void get_all_eaten();
    void get_power_eaten();
    void get_power_done();
    void get_dot_eaten(int);
    void show_game_over();
    void start_ctrl();
    void edit_ctrl();
    void play();
    void p2mode();

signals:
    void send_edit_pos(int,int);
    void send_new_bitmap(bool [map_info::map_height][map_info::map_width]);
    void send_key(int,map_info::key);
    void send_man_pos(int,int);
    void send_man2_pos(int,int);
    void send_game_over();
    void send_game_over(int);
    void send_power_done();
    void send_ghost1_die();//edit
    void send_ghost2_die();
    void send_ghost3_die();
    void send_ghost4_die();

private:

    QTimer * play_timer;

    //game paremeter
    pos_info ghost_pos[NUM_OF_GHOST];
    pos_info object_pos[OTHER_OBJECT];
    object_original * ghost_1;
    object_original * ghost_2;
    object_original * ghost_3;
    object_original * ghost_4;
    object_key temp_ghost;
    bool object_valid[OTHER_OBJECT];
    int ghost_num;


    object_original * pac_man;
    object_original * pac_man2;
    int man_row[2];
    int man_col[2];
    bool player_id;


    dot * gamedot;
    bool power;
    bool start;
    bool over;


    //initial window data
    Ui::MainWindow *ui;
    mainpage * menu;
    QPushButton * start_control;
    QPushButton * edit_control;
    QPushButton * to_menu;
    QLabel * map[MAPHEIGHT][MAPWIDTH];
    QLabel * background;
    QLabel * play_region;
    QLabel * over_label;
    QLabel * dashboard;
    QLabel * message;
    QPixmap map_color;
    QPixmap bg;
    QPixmap pr;
    QPixmap oi[6];

    int bit_map[MAPHEIGHT][MAPWIDTH];
    int man_score[2];
    int xpos[MAPWIDTH];
    int ypos[MAPHEIGHT];
    int over_width;
    int over_height;
    int over_xpos;
    int over_ypos;
    bool play_mode;//0 :1player , 1 :2player
    bool menu_on_off;
    bool edit_on_off;

};

#endif // MAINWINDOW_H
