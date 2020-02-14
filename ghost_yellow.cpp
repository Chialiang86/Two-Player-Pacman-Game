#include "ghost_yellow.h"

ghost_yellow::ghost_yellow(QWidget * parent,const int x_pos[],const int y_pos[],object_key color)
    : object_original(parent,x_pos,y_pos,color)
{
    //set id
    id = color;

    //set move way
    move_way[0].c =   1; move_way[0].r =   2;
    move_way[1].c =   1; move_way[1].r = - 2;
    move_way[2].c =   2; move_way[2].r =   1;
    move_way[3].c =   2; move_way[3].r = - 1;
    move_way[4].c = - 2; move_way[4].r =   1;
    move_way[5].c = - 2; move_way[5].r = - 1;
    move_way[6].c = - 1; move_way[6].r =   2;
    move_way[7].c = - 1; move_way[7].r = - 2;

    //initialize speed
    speed_x = 0;
    speed_y = 0;

    move_timer = new QTimer(parent);
    move_timer->start(3000);

    send_move_timer = new QTimer(parent);
    send_move_timer->start(70);

    ghost_label = new QLabel(parent);
    ghost_img[0].load(":/object/src/object/ghost_y1.png");
    ghost_img[1].load(":/object/src/object/ghost_y2.png");
    ghost_label->setPixmap(ghost_img[ghost_act_index].scaled(block_width,block_width,Qt::KeepAspectRatio));
    ghost_label->setGeometry(ghost_xpos,ghost_ypos,block_width,block_width);
    ghost_label->close();

    ghost_weak_img.load(":/object/src/object/ghost_weak.png");

    start = false;
    over = false;
    weak = false;
    die = false;

    die_timer = new QTimer;

    ghost_timer = new QTimer(parent);
    ghost_timer->start(100);

    connect(die_timer,SIGNAL(timeout()),this,SLOT(ghost_revival()));
    connect(ghost_timer,SIGNAL(timeout()),this,SLOT(ghost_act()));
    connect(move_timer,SIGNAL(timeout()),this,SLOT(move_method()));
    connect(send_move_timer,SIGNAL(timeout()),this,SLOT(update_to_game()));
}

void ghost_yellow::object_close(){
    over = true;
    weak = false;//for act
    die = true;
    ghost_col = map_info::ghosty_initial_x;
    ghost_row = map_info::ghosty_initial_y;
    ghost_xpos = map_xpos[map_info::ghosty_initial_x];
    ghost_ypos = map_ypos[map_info::ghosty_initial_y];
    ghost_x = ghost_xpos + block_width / 2;
    ghost_y = ghost_ypos + block_width / 2;
    ghost_act_index = 0;
    ghost_label->setGeometry(ghost_xpos,ghost_ypos,block_width,block_width);
    ghost_label->setPixmap(ghost_img[ghost_act_index].scaled(block_width,block_width,Qt::KeepAspectRatio));
    ghost_label->close();
}

void ghost_yellow::object_show(){
    over = false;
    ghost_label->show();
}

void ghost_yellow::start_ctrl(){
    start = ! start;
    if(start == false){
        over = false;//for act
        weak = false;//for act
        die = true;
        ghost_col = map_info::ghosty_initial_x;
        ghost_row = map_info::ghosty_initial_y;
        ghost_xpos = map_xpos[map_info::ghosty_initial_x];
        ghost_ypos = map_ypos[map_info::ghosty_initial_y];
        ghost_x = ghost_xpos + block_width / 2;
        ghost_y = ghost_ypos + block_width / 2;
        ghost_act_index = 0;
        ghost_label->setGeometry(ghost_xpos,ghost_ypos,block_width,block_width);
        ghost_label->setPixmap(ghost_img[ghost_act_index].scaled(block_width,block_width,Qt::KeepAspectRatio));
        ghost_label->update();
    } else {
        over = false;
        weak = false;
        die = false;
    }
}

void ghost_yellow::ghost_act(){
    if(!over && !weak){
        if(ghost_act_index == 0){
            ghost_label->setPixmap(ghost_img[ghost_act_index].scaled(block_width,block_width,Qt::KeepAspectRatio));
            ghost_act_index = 1;
        }
        else if(ghost_act_index == 1){
            ghost_label->setPixmap(ghost_img[ghost_act_index].scaled(block_width,block_width,Qt::KeepAspectRatio));
            ghost_act_index = 0;
        }
    }
}

void ghost_yellow::ghost_weak(){
    ghost_label->setPixmap(ghost_weak_img.scaled(block_width,block_width,Qt::KeepAspectRatio));
    ghost_label->update();
    weak = true;
}

void ghost_yellow::ghost_recover(){
    ghost_label->setPixmap(ghost_img[ghost_act_index].scaled(block_width,block_width,Qt::KeepAspectRatio));
    ghost_label->update();
    weak = false;
}

void ghost_yellow::ghost_die(){
    die = true;
    ghost_xpos = -1;
    ghost_ypos = -1;
    ghost_x = -1;
    ghost_y = -1;
    ghost_row = -1;
    ghost_col = -1;
    ghost_label->close();
    emit ghost_done(id,ghost_row,ghost_col);
    die_timer->start(3000);
}

void ghost_yellow::ghost_revival(){
    die_timer->stop();
    die = false;
    ghost_col = map_info::ghosty_initial_x;
    ghost_row = map_info::ghosty_initial_y;
    ghost_xpos = map_xpos[map_info::ghosty_initial_x];
    ghost_ypos = map_ypos[map_info::ghosty_initial_y];
    ghost_x = ghost_xpos + block_width / 2;
    ghost_y = ghost_ypos + block_width / 2;
    ghost_act_index = 0;
    ghost_label->setGeometry(ghost_xpos,ghost_ypos,block_width,block_width);
    ghost_label->setPixmap(ghost_img[ghost_act_index].scaled(block_width,block_width,Qt::KeepAspectRatio));
    ghost_label->show();
}


void ghost_yellow::man_pos(int man__r,int man__c){
    man_r = man__r;
    man_c = man__c;
}

void ghost_yellow::game_over(){
    ghost_col = map_info::ghosty_initial_x;
    ghost_row = map_info::ghosty_initial_y;
    ghost_xpos = map_xpos[map_info::ghosty_initial_x];
    ghost_ypos = map_ypos[map_info::ghosty_initial_y];
    ghost_x = ghost_xpos + block_width / 2;
    ghost_y = ghost_ypos + block_width / 2;
    ghost_act_index = 0;
    over = true;
    emit ghost_done(id,ghost_row,ghost_col);
}


void ghost_yellow::move_method(){
    //horse
    if(start && !over && !die){
        int square_distance;
        int min_distance = 1000;
        int min_index = - 1;
        for(int i = 0 ; i < 8 ; ++ i){
            if(ghost_row + move_way[i].r >= 0 && ghost_row + move_way[i].r < map_height &&
               ghost_col + move_way[i].c >= 0 && ghost_col + move_way[i].c < map_width &&
                    bit_map[ghost_row + move_way[i].r][ghost_col + move_way[i].c] == false){
                square_distance = distance(ghost_row + move_way[i].r,ghost_col + move_way[i].c,man_r,man_c);
                if(square_distance < min_distance){
                    min_distance = square_distance;
                    min_index = i;
                }
            }
        }
        if(min_index >= 0){
            ghost_row = ghost_row + move_way[min_index].r;
            ghost_col = ghost_col + move_way[min_index].c;
            speed_x = move_way[min_index].c * block_width;
            speed_y = move_way[min_index].r * block_width;
            ghost_xpos = ghost_xpos + speed_x;
            ghost_ypos = ghost_ypos + speed_y;
            ghost_x = ghost_x + block_width / 2;
            ghost_y = ghost_y + block_width / 2;
            ghost_label->setGeometry(ghost_xpos,ghost_ypos,block_width,block_width);
            ghost_label->update();
        } else {
            speed_x = 0;
            speed_y = 0;
        }
        emit ghost_done(id,ghost_row,ghost_col);

    } else {
        speed_x = 0;
        speed_y = 0;
    }

}

void ghost_yellow::update_to_game(){
    if(start && !over && !die)
        emit ghost_done(id,ghost_row,ghost_col);
}

int ghost_yellow::distance(int gr,int gc,int mr,int mc){
    return (gr - mr) * (gr - mr) + (gc - mc) * (gc - mc);
}

int ghost_yellow::tran_x(int xpos){
    int x = (xpos - map_info::play_region_x ) / block_width;
    x = xpos - map_info::play_region_x < 0 ? - 1 : x ;
    return x;
}

int ghost_yellow::tran_y(int ypos){
    int y = (ypos - map_info::play_region_y ) / block_width;
    y = y >= map_info::map_height ? map_info::map_height - 1 : y ;
    return y;
}


