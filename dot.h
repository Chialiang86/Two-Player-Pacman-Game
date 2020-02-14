#ifndef DOT_H
#define DOT_H
#include <iostream>
#include <QWidget>
#include <QObject>
#include <QMainWindow>
#include <QPixmap>
#include <QLabel>
#include <QTimer>
#include <cstdlib>
#include <unistd.h>
#include "map_info.h"
using namespace map_info;
using namespace std;

#define MAX_POWER 5

typedef struct Dot_info{
    QLabel * dot_label;
    bool exist;
    bool power;
    int dot_x;
    int dot_y;
    int dot_xpos;
    int dot_ypos;
}dot_info;

class dot : public QWidget
{
    Q_OBJECT
public:
    dot(){}
    dot(QMainWindow *,const int [],const int []);
    int tran_x(int);
    int tran_y(int);

    QTimer * power_timer;

public slots:
    void man_pos(int,int);
    void man2_pos(int,int);
    void recover_timeout();
    void start_ctrl();
    void object_close();
    void object_show();
    void edit_pos(int,int);

signals:
    void dot_eaten(int);
    void all_eaten();
    void send_recover();
    void power_eaten();

private:
    QPixmap dot_img;
    QPixmap power_img;
    dot_info * game_dot[map_info::map_height][map_info::map_width];
    dot_info * game_power[MAX_POWER];
    pos_info pacman_pos[2];
    bool bit_map[map_info::map_height][map_info::map_width];

    int map_xpos[map_info::map_width];
    int map_ypos[map_info::map_height];
    int dot_counter;
    int dot_number;
    bool start;
};

#endif // DOT_H
