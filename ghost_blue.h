#ifndef GHOST_BLUE_H
#define GHOST_BLUE_H
#include <QTimer>
#include "object_original.h"
#include "map_info.h"
using namespace map_info;


class ghost_blue: public object_original
{
    Q_OBJECT
public:
    ghost_blue(QWidget * ,const int [],const int [],object_key);
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
    void update_to_game();



signals:
    void ghost_done(map_info::object_key,int,int);

private:
    object_key id;
    QLabel * ghost_label;
    QPixmap ghost_img[2];
    QPixmap ghost_weak_img;
    QTimer * ghost_timer;
    QTimer * recover_timer;
    QTimer * move_timer;
    QTimer * send_move_timer;
    QTimer * die_timer;
    pos_info move_way[8];

    bool over;
    bool weak;
    bool die;
    bool start;
    int speed_x;
    int speed_y;
    int man_r;
    int man_c;
private:
};

#endif // GHOST_BLUE_H
