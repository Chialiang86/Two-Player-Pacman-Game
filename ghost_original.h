#ifndef GHOST_ORIGINAL_H
#define GHOST_ORIGINAL_H
//This is a virtual class
#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include <QTimer>
#include <cstdlib>
#include <iostream>
#include "map_info.h"
using namespace  map_info;
using namespace std;

class ghost_original : public QWidget
{
    Q_OBJECT
public:
    ghost_original(QWidget *,const int [],const int [],ghost_key);

    QLabel * ghost_label;
    QTimer * act_timer;
    QPixmap ghost_img[2];
    const ghost_key ghost_color;
    int map_xpos[map_info::map_width];
    int map_ypos[map_info::map_height];
    int ghost_row;
    int ghost_col;
    int ghost_x;
    int ghost_y;
    int ghost_xpos;
    int ghost_ypos;
    int ghost_act_index;

    virtual void move_method() = 0;

public slots:
    void ghost_act();

signals:



};

#endif // GHOST_H
