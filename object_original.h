#ifndef GHOST_ORIGINAL_H
#define GHOST_ORIGINAL_H
//This is a virtual class
#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include <QTimer>
#include <cstdlib>
#include <iostream>
#include "map_info.h"
using namespace  map_info;
using namespace std;

class object_original : public QWidget
{
    Q_OBJECT
public:
    object_original(QWidget *,const int [],const int [],object_key);

    virtual void object_show() = 0;
    virtual void object_close() = 0;
    const object_key object_color;

    bool bit_map[map_info::map_height][map_info::map_width];

    int map_xpos[map_info::map_width];
    int map_ypos[map_info::map_height];
    int ghost_row;
    int ghost_col;
    int ghost_x;
    int ghost_y;
    int ghost_xpos;
    int ghost_ypos;
    int ghost_act_index;
    int man_row;
    int man_col;
    int man_x;
    int man_y;
    int man_xpos;
    int man_ypos;

public slots:
    void update_bitmap(int,int);
    void update_bitmap(bool [map_info::map_height][map_info::map_width]);


protected:
    virtual void move_method() = 0;

};

#endif // GHOST_H
