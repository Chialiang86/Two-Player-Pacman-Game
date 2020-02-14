#ifndef GHOST_RED_H
#define GHOST_RED_H
#include <QTimer>
#include <cmath>
#include "object_original.h"
#include "map_info.h"

#define BULLET_SPEED 18*;
using namespace map_info;

class ghost_red : public object_original
{
    Q_OBJECT
public:
    ghost_red(QWidget * ,const int [],const int [],object_key);
    int distance(int,int,int,int);
    int tran_x(int);
    int tran_y(int);



public slots:
    virtual void move_method();
    virtual void object_close();
    virtual void object_show();
    void start_ctrl();
    void man_pos(int,int);
    void ghost_weak();
    void ghost_die();
    void ghost_recover();
    void ghost_revival();
    void game_over();
    void ghost_act();
    void shoot();
    void bullet_move();
    void update_to_game();


signals:
    void ghost_done(map_info::object_key,int,int);
    void bullet_done(int,int,map_info::other_object);
    //void none();

private:
    QLabel * ghost_label;
    QLabel * bullet_label;
    QPixmap ghost_img[2];
    QPixmap ghost_weak_img;
    QPixmap bullet_img;
    QTimer * ghost_timer;
    QTimer * move_timer;
    QTimer * shoot_timer;
    QTimer * bullet_move_timer;
    QTimer * send_move_timer;
    QTimer * recover_timer;
    QTimer * die_timer;
    object_key id;
    pos_info move_way[8];

    int bullet_speed_x;
    int bullet_speed_y;
    int bullet_xpos;
    int bullet_ypos;
    int bullet_x;
    int bullet_y;
    int speed_x;
    int speed_y;
    int man_r;
    int man_c;
    bool start;
    bool over;
    bool weak;
    bool die;
    bool is_shoot;

};

#endif // GHOST_RED_H
