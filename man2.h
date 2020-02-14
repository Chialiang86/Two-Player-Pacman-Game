#ifndef MAN2_H
#define MAN2_H
#include <QApplication>
#include <QObject>
#include <QMainWindow>
#include <QLabel>
#include <QTimer>
#include <QKeyEvent>
#include "object_original.h"
#include "map_info.h"
using namespace map_info;

#define SPEED_ABSO2 5
#define DEAD_DELAY 10

class pacman2 : public  object_original
{
    Q_OBJECT
public:
    pacman2(QMainWindow * ,const int [],const int [],object_key);
    int tran_x(int);
    int tran_y(int);
    void debug();

public slots:
    virtual void move_method();
    virtual void object_close();
    virtual void object_show();
    void start_ctrl();
    void man_act();
    void dead_act();
    void man_move(int,map_info::key);
    void game_over(int);
    void valid();

signals:
    void done(int,int);
    void dead();

private:
    QPixmap man_img[4][7];
    QPixmap dead_img[10];
    QLabel * man_label;
    QTimer * act_timer;
    QTimer * move_timer;
    QTimer * die_timer;
    key temp;
    object_key id;

    int speed_x;
    int speed_y;
    int man_act_index;
    int dead_act_index;
    int dead_delay_index;
    int player;
    bool is_valid;
    bool start;
    bool man_act_updown;
    bool over;
    bool die;
};

#endif // MAN2_H
