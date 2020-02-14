#include "man2.h"

pacman2::pacman2(QMainWindow * parent,const int x_pos[],const int y_pos[],object_key color)
    : object_original (parent,x_pos,y_pos,color)
{
    id = color;
    player = 1;

    //set man img
    man_img[map_info::right][0].load(":/object/src/object/man27_r.png");
    man_img[map_info::right][1].load(":/object/src/object/man22_r.png");
    man_img[map_info::right][2].load(":/object/src/object/man23_r.png");
    man_img[map_info::right][3].load(":/object/src/object/man24_r.png");
    man_img[map_info::right][4].load(":/object/src/object/man25_r.png");
    man_img[map_info::right][5].load(":/object/src/object/man26_r.png");
    man_img[map_info::right][6].load(":/object/src/object/man27_r.png");
    man_img[map_info::left][0].load(":/object/src/object/man21_l.png");
    man_img[map_info::left][1].load(":/object/src/object/man22_l.png");
    man_img[map_info::left][2].load(":/object/src/object/man23_l.png");
    man_img[map_info::left][3].load(":/object/src/object/man24_l.png");
    man_img[map_info::left][4].load(":/object/src/object/man25_l.png");
    man_img[map_info::left][5].load(":/object/src/object/man26_l.png");
    man_img[map_info::left][6].load(":/object/src/object/man27_l.png");
    man_img[map_info::up][0].load(":/object/src/object/man21_u.png");
    man_img[map_info::up][1].load(":/object/src/object/man22_u.png");
    man_img[map_info::up][2].load(":/object/src/object/man23_u.png");
    man_img[map_info::up][3].load(":/object/src/object/man24_u.png");
    man_img[map_info::up][4].load(":/object/src/object/man25_u.png");
    man_img[map_info::up][5].load(":/object/src/object/man26_u.png");
    man_img[map_info::up][6].load(":/object/src/object/man27_u.png");
    man_img[map_info::down][0].load(":/object/src/object/man21_d.png");
    man_img[map_info::down][1].load(":/object/src/object/man22_d.png");
    man_img[map_info::down][2].load(":/object/src/object/man23_d.png");
    man_img[map_info::down][3].load(":/object/src/object/man24_d.png");
    man_img[map_info::down][4].load(":/object/src/object/man25_d.png");
    man_img[map_info::down][5].load(":/object/src/object/man26_d.png");
    man_img[map_info::down][6].load(":/object/src/object/man27_d.png");

    /*QImage temp_img;
    QRgb temp_rgb;
    for(int i = 0 ; i < 4 ; ++ i){
        for(int j = 0 ; j < 7 ; ++ j){
            temp_img = man_img[i][j].toImage();
            temp_rgb = temp_img.pixel(temp_img.width()/2,temp_img.height()/2);
            for(int x = 0; x < temp_img.width() ; ++ x){
                for(int y = 0; y < temp_img.height() ; ++ y){
                    if(temp_img.pixel(x,y) == temp_rgb){
                        temp_img.setPixelColor(QPoint(x,y),QColor(x%255,y%255,100));
                        man_img[i][j] = QPixmap::fromImage(temp_img);
                    }
                }
            }
        }
    }*/

    //set dead
    dead_img[0].load(":/object/src/object/die21.png");
    dead_img[1].load(":/object/src/object/die22.png");
    dead_img[2].load(":/object/src/object/die23.png");
    dead_img[3].load(":/object/src/object/die24.png");
    dead_img[4].load(":/object/src/object/die25.png");
    dead_img[5].load(":/object/src/object/die26.png");
    dead_img[6].load(":/object/src/object/die27.png");
    dead_img[7].load(":/object/src/object/die28.png");
    dead_img[8].load(":/object/src/object/die29.png");
    dead_img[9].load(":/object/src/object/die210.png");

    //set man_label
    man_label = new QLabel(parent);
    man_label->setGeometry(man_xpos,man_ypos,block_width,block_width);
    man_label->close();

    //set act timer
    act_timer = new QTimer(parent);
    man_act_index = 0;
    man_act_updown = 1;

    //set move timer
    move_timer = new QTimer(parent);
    speed_x = 0;
    speed_y = 0;
    temp = map_info::right;

    //set die timer
    die_timer = new QTimer(parent);
    dead_act_index = 0;
    dead_delay_index = 0;

    die = false;
    over = false;
    start = false;
    is_valid = false;

    QObject::connect(die_timer,SIGNAL(timeout()),this,SLOT(dead_act()));
    QObject::connect(act_timer,SIGNAL(timeout()),this,SLOT(man_act()));
    QObject::connect(move_timer,SIGNAL(timeout()),this,SLOT(move_method()));
}

void pacman2::valid(){
    is_valid = true;
    act_timer->start(40);
    move_timer->start(40);
}

void pacman2::object_close(){
    is_valid = false;
    act_timer->stop();
    move_timer->stop();
    over = true;
    die = true;
    speed_x = 0;
    speed_y = 0;
    man_col = map_info::man2_initial_x;
    man_row = map_info::man2_initial_y;
    man_xpos = map_xpos[map_info::man2_initial_x];
    man_ypos = map_ypos[map_info::man2_initial_y];
    man_x = man_xpos + block_width / 2;
    man_y = man_ypos + block_width / 2;
    temp = map_info::right;
    man_act_index = 0;
    man_label->setGeometry(man_xpos,man_ypos,block_width,block_width);
    man_label->setPixmap(man_img[temp][man_act_index].scaled(block_width,block_width,Qt::KeepAspectRatio));
    man_label->show();
    emit done(tran_y(man_y),tran_x(man_x));//row , col
    man_label->close();
}

void pacman2::object_show(){
    over = false;
    man_label->show();
}

void pacman2::start_ctrl(){
    start = ! start;
    if(is_valid && is_valid && start == false){
        die = true;
        over = false;//for man act
        speed_x = 0;
        speed_y = 0;
        man_col = map_info::man2_initial_x;
        man_row = map_info::man2_initial_y;
        man_xpos = map_xpos[map_info::man2_initial_x];
        man_ypos = map_ypos[map_info::man2_initial_y];
        man_x = man_xpos + block_width / 2;
        man_y = man_ypos + block_width / 2;
        temp = map_info::right;
        man_act_index = 0;
        man_label->setGeometry(man_xpos,man_ypos,block_width,block_width);
        man_label->setPixmap(man_img[temp][man_act_index].scaled(block_width,block_width,Qt::KeepAspectRatio));
        man_label->show();
        emit done(tran_y(man_y),tran_x(man_x));//row , col
    } else if(is_valid ){
        over = false;
        die = false;
    }
}

void pacman2::game_over(int player_id){
    if(player_id == 1){
        over = true;
        die_timer->start(170);
    }
    over = true;
}

void pacman2::dead_act(){
    if(is_valid && over && !die){
        if(dead_act_index < 10){
            man_label->setPixmap(dead_img[dead_act_index].scaled(block_width,block_width));
            QCoreApplication::processEvents();
            ++ dead_act_index;
        }
        else {
            if(dead_delay_index == 5){
                man_label->close();
                emit dead();
                die = true;
                die_timer->stop();
                man_col = map_info::man2_initial_x;
                man_row = map_info::man2_initial_y;
                man_xpos = map_xpos[map_info::man2_initial_x];
                man_ypos = map_ypos[map_info::man2_initial_y];
                man_x = man_xpos + block_width / 2;
                man_y = man_ypos + block_width / 2;
                speed_x = 0;
                speed_y = 0;
                dead_act_index = 0;
                dead_delay_index = 0;
                //emit done(tran_y(man_y),tran_x(man_x));//row , col
            } else{
                ++ dead_delay_index;
            }
        }
    }
}

void pacman2::man_act(){
    if(is_valid && !over ){
        if(man_act_updown){
            man_label->setPixmap(man_img[temp][man_act_index].scaled(block_width,block_width,Qt::KeepAspectRatio));
            ++ man_act_index;
            if(man_act_index == 7){
                man_act_updown = false;
                man_act_index = 5;
            }
        } else {
            man_label->setPixmap(man_img[temp][man_act_index].scaled(block_width,block_width,Qt::KeepAspectRatio));
            -- man_act_index;
            if(man_act_index == -1){
                man_act_updown = true;
                man_act_index = 0;
            }
        }
    }
}

void pacman2::man_move(int player_id,map_info::key command){
    if(player_id == 1 && is_valid && start && !over){
        switch(command){
        case map_info::left:
            temp = map_info::left;
            speed_x = - SPEED_ABSO2;
            speed_y = 0;
            break;
        case map_info::right:
            temp = map_info::right;
            speed_x = SPEED_ABSO2;
            speed_y = 0;
            break;
        case map_info::up:
            temp = map_info::up;
            speed_x = 0;
            speed_y = - SPEED_ABSO2;
            break;
        case map_info::down:
            temp = map_info::down;
            speed_x = 0;
            speed_y = SPEED_ABSO2;
            break;
        default:break;//none
        }
    }
}

void pacman2::move_method(){
    if(is_valid && start && !over){
        int col;
        int row;
        man_xpos = man_xpos + speed_x;
        man_ypos = man_ypos + speed_y;
        man_x = man_xpos + block_width / 2;
        man_y = man_ypos + block_width / 2;
        if(speed_x > 0 && speed_y == 0){
            col = tran_x(man_xpos + block_width + 1);//decode
            row = tran_y(man_y);
            man_ypos = map_ypos[row];
            man_y = man_ypos + block_width / 2;
        }
        else if(speed_y > 0 && speed_x == 0){
            col = tran_x(man_x);//decode
            row = tran_y(man_ypos + block_width + 1);
            man_xpos = map_xpos[col];
            man_x = man_xpos + block_width / 2;
        }
        else if(speed_x < 0 && speed_y == 0){
            col = tran_x(man_xpos - 1);//decode
            row = tran_y(man_y);
            man_ypos = map_ypos[row];
            man_y = man_ypos + block_width / 2;
        }
        else if(speed_y < 0 && speed_x == 0){
            col = tran_x(man_x);//decode
            row = tran_y(man_ypos - 1);
            man_xpos = map_xpos[col];
            man_x = man_xpos + block_width / 2;
        } else{
            col = tran_x(man_xpos);//decode
            row = tran_y(man_ypos);//decode
        }

        if(row < 0){
            man_ypos = map_info::play_region_y ;
            row = 0;
        }else if(col < 0){
            man_xpos = map_info::play_region_x + block_width * ( map_info::map_width - 1 ) ;
            col = map_width - 1;
        }else if(col >= map_info::map_width){
            man_xpos = map_info::play_region_x;
            col = 0;
        }

        if(bit_map[row][col] == 0){
            man_x = man_xpos + block_width / 2;
            man_y = man_ypos + block_width / 2;
            man_label->setGeometry(man_xpos,man_ypos,block_width,block_width);
            man_label->show();
        } else {
            man_xpos = map_xpos[col - speed_x / SPEED_ABSO2];
            man_ypos = map_ypos[row - speed_y / SPEED_ABSO2];
            man_x = man_xpos + block_width / 2;
            man_y = man_ypos + block_width / 2;
            speed_x = 0;
            speed_y = 0;
            man_label->setGeometry(man_xpos,man_ypos,block_width,block_width);
            man_label->show();
        }
        //center
        emit done(tran_y(man_y),tran_x(man_x));//row , col
        debug();
    }
}

int pacman2::tran_x(int xpos){
    int x = (xpos - map_info::play_region_x ) / block_width;
    x = xpos - map_info::play_region_x < 0 ? - 1 : x ;
    return x;
}

int pacman2::tran_y(int ypos){
    int y = (ypos - map_info::play_region_y ) / block_width;
    y = y >= map_info::map_height ? map_info::map_height - 1 : y ;
    return y;
}

void pacman2::debug(){
}
