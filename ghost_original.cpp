#include "ghost_original.h"

ghost_original::ghost_original(QWidget * parent,const int x_pos[],const int y_pos[],ghost_key color)
    : QWidget(parent),ghost_color(color)
{

    ghost_act_index = 0;

    //set pos info
    for(int col = 0 ; col < map_info::map_width ; ++ col)
        map_xpos[col] = x_pos[col];
    for(int row = 0 ; row < map_info::map_height ; ++ row)
        map_ypos[row] = y_pos[row];

    switch(ghost_color){
    case map_info::red://red
        ghost_img[0].load(":/object/src/object/ghost_r2.png");
        ghost_img[1].load(":/object/src/object/ghost_r2.png");
        //ghost_img[0].load(":/object/src/object/horse.png");
        //ghost_img[1].load(":/object/src/object/horse.png");
        ghost_col = map_info::ghostr_initial_x;
        ghost_row = map_info::ghostr_initial_y;
        ghost_xpos = map_xpos[map_info::ghostr_initial_x];
        ghost_ypos = map_ypos[map_info::ghostr_initial_y];
        ghost_x = ghost_xpos + block_width / 2;
        ghost_y = ghost_ypos + block_width / 2;
        break;
    case map_info::blue://blue
        ghost_img[0].load(":/object/src/object/ghost_b1.png");
        ghost_img[1].load(":/object/src/object/ghost_b2.png");
        ghost_col = map_info::ghostb_initial_x;
        ghost_row = map_info::ghostb_initial_y;
        ghost_xpos = map_xpos[map_info::ghostb_initial_x];
        ghost_ypos = map_ypos[map_info::ghostb_initial_y];
        ghost_x = ghost_xpos + block_width / 2;
        ghost_y = ghost_ypos + block_width / 2;
        break;
    case map_info::yellow://yellow
        ghost_img[0].load(":/object/src/object/ghost_y1.png");
        ghost_img[1].load(":/object/src/object/ghost_y2.png");
        ghost_col = map_info::ghosty_initial_x;
        ghost_row = map_info::ghosty_initial_y;
        ghost_xpos = map_xpos[map_info::ghosty_initial_x];
        ghost_ypos = map_ypos[map_info::ghosty_initial_y];
        ghost_x = ghost_xpos + block_width / 2;
        ghost_y = ghost_ypos + block_width / 2;
        break;
    case map_info::pink://pink
        ghost_img[0].load(":/object/src/object/ghost_p1.png");
        ghost_img[1].load(":/object/src/object/ghost_p2.png");
        ghost_col = map_info::ghostp_initial_x;
        ghost_row = map_info::ghostp_initial_y;
        ghost_xpos = map_xpos[map_info::ghostp_initial_x];
        ghost_ypos = map_ypos[map_info::ghostp_initial_y];
        ghost_x = ghost_xpos + block_width / 2;
        ghost_y = ghost_ypos + block_width / 2;
        break;
    }

    ghost_label = new QLabel(parent);
    ghost_label->setPixmap(ghost_img[ghost_act_index].scaled(block_width,block_width,Qt::KeepAspectRatio));
    ghost_label->setGeometry(ghost_xpos,ghost_ypos,block_width,block_width);
    ghost_label->show();

    act_timer = new QTimer(parent);
    act_timer->start(100);
    connect(act_timer,SIGNAL(timeout()),this,SLOT(ghost_act()));
}

void ghost_original::ghost_act(){
    if(ghost_act_index == 0){
        ghost_label->setPixmap(ghost_img[ghost_act_index].scaled(block_width,block_width,Qt::KeepAspectRatio));
        ghost_act_index = 1;
    }
    else if(ghost_act_index == 1){
        ghost_label->setPixmap(ghost_img[ghost_act_index].scaled(block_width,block_width,Qt::KeepAspectRatio));
        ghost_act_index = 0;
    }
}
