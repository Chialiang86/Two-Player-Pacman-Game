#include "man.h"

pacman::pacman(QMainWindow * parent,const int x_pos[],const int y_pos[],object_key color)
    : object_original (parent,x_pos,y_pos,color)
{

    id = color;
    player = 0;

    //set man img
    man_img[map_info::right][0].load(":/object/src/object/man1_r-removebg.png");
    man_img[map_info::right][1].load(":/object/src/object/man2_r-removebg.png");
    man_img[map_info::right][2].load(":/object/src/object/man3_r-removebg.png");
    man_img[map_info::right][3].load(":/object/src/object/man4_r-removebg.png");
    man_img[map_info::right][4].load(":/object/src/object/man5_r-removebg.png");
    man_img[map_info::right][5].load(":/object/src/object/man6_r-removebg.png");
    man_img[map_info::right][6].load(":/object/src/object/man7_r-removebg.png");
    man_img[map_info::left][0].load(":/object/src/object/man1_l-removebg.png");
    man_img[map_info::left][1].load(":/object/src/object/man2_l-removebg.png");
    man_img[map_info::left][2].load(":/object/src/object/man3_l-removebg.png");
    man_img[map_info::left][3].load(":/object/src/object/man4_l-removebg.png");
    man_img[map_info::left][4].load(":/object/src/object/man5_l-removebg.png");
    man_img[map_info::left][5].load(":/object/src/object/man6_l-removebg.png");
    man_img[map_info::left][6].load(":/object/src/object/man7_l-removebg.png");
    man_img[map_info::up][0].load(":/object/src/object/man1_u-removebg.png");
    man_img[map_info::up][1].load(":/object/src/object/man2_u-removebg.png");
    man_img[map_info::up][2].load(":/object/src/object/man3_u-removebg.png");
    man_img[map_info::up][3].load(":/object/src/object/man4_u-removebg.png");
    man_img[map_info::up][4].load(":/object/src/object/man5_u-removebg.png");
    man_img[map_info::up][5].load(":/object/src/object/man6_u-removebg.png");
    man_img[map_info::up][6].load(":/object/src/object/man7_u-removebg.png");
    man_img[map_info::down][0].load(":/object/src/object/man1_d-removebg.png");
    man_img[map_info::down][1].load(":/object/src/object/man2_d-removebg.png");
    man_img[map_info::down][2].load(":/object/src/object/man3_d-removebg.png");
    man_img[map_info::down][3].load(":/object/src/object/man4_d-removebg.png");
    man_img[map_info::down][4].load(":/object/src/object/man5_d-removebg.png");
    man_img[map_info::down][5].load(":/object/src/object/man6_d-removebg.png");
    man_img[map_info::down][6].load(":/object/src/object/man7_d-removebg.png");

    /*QImage temp_img;
    QRgb temp_rgb;
    for(int i = 0 ; i < 4 ; ++ i){
        for(int j = 0 ; j < 7 ; ++ j){
            temp_img = man_img[i][j].toImage();
            temp_rgb = temp_img.pixel(temp_img.width()/2,temp_img.height()/2);
            for(int x = 0; x < temp_img.width() ; ++ x){
                for(int y = static_cast<int>(0.7 * temp_img.height()); y < temp_img.height() ; ++ y){
                    if(temp_img.pixel(x,y) == temp_rgb){
                        temp_img.setPixelColor(QPoint(x,y),QColor(100,x%255,y%255));
                        man_img[i][j] = QPixmap::fromImage(temp_img);
                    }
                }
            }
        }
    }*/

    //set dead
    dead_img[0].load(":/object/src/object/die1.png");
    dead_img[1].load(":/object/src/object/die2.png");
    dead_img[2].load(":/object/src/object/die3.png");
    dead_img[3].load(":/object/src/object/die4.png");
    dead_img[4].load(":/object/src/object/die5.png");
    dead_img[5].load(":/object/src/object/die6.png");
    dead_img[6].load(":/object/src/object/die7.png");
    dead_img[7].load(":/object/src/object/die8.png");
    dead_img[8].load(":/object/src/object/die9.png");
    dead_img[9].load(":/object/src/object/die10.png");

    //set man_label
    man_label = new QLabel(parent);
    man_label->setGeometry(man_xpos,man_ypos,block_width,block_width);
    man_label->close();

    //set act timer
    act_timer = new QTimer(parent);
    act_timer->start(30);
    man_act_index = 0;
    man_act_updown = 1;

    //set move timer
    move_timer = new QTimer(parent);
    move_timer->start(45);
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

    QObject::connect(die_timer,SIGNAL(timeout()),this,SLOT(dead_act()));
    QObject::connect(act_timer,SIGNAL(timeout()),this,SLOT(man_act()));
    QObject::connect(move_timer,SIGNAL(timeout()),this,SLOT(move_method()));
}

void pacman::object_close(){
    over = true;
    die = true;
    speed_x = 0;
    speed_y = 0;
    man_col = map_info::man_initial_x;
    man_row = map_info::man_initial_y;
    man_xpos = map_xpos[map_info::man_initial_x];
    man_ypos = map_ypos[map_info::man_initial_y];
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

void pacman::object_show(){
    over = false;
    man_label->show();
}

void pacman::start_ctrl(){
    start = ! start;
    if(start == false){
        die = true;
        over = false;//for man act
        speed_x = 0;
        speed_y = 0;
        man_col = map_info::man_initial_x;
        man_row = map_info::man_initial_y;
        man_xpos = map_xpos[map_info::man_initial_x];
        man_ypos = map_ypos[map_info::man_initial_y];
        man_x = man_xpos + block_width / 2;
        man_y = man_ypos + block_width / 2;
        temp = map_info::right;
        man_act_index = 0;
        man_label->setGeometry(man_xpos,man_ypos,block_width,block_width);
        man_label->setPixmap(man_img[temp][man_act_index].scaled(block_width,block_width,Qt::KeepAspectRatio));
        man_label->show();
        emit done(tran_y(man_y),tran_x(man_x));//row , col
    } else {
        over = false;
        die = false;
    }
}

void pacman::game_over(int player_id){
    if(player_id == 0){
        over = true;
        die_timer->start(170);
    }
    over = true;
}

void pacman::dead_act(){
    if(over && !die){
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
                man_col = map_info::man_initial_x;
                man_row = map_info::man_initial_y;
                man_xpos = map_xpos[map_info::man_initial_x];
                man_ypos = map_ypos[map_info::man_initial_y];
                man_x = man_xpos + block_width / 2;
                man_y = man_ypos + block_width / 2;
                speed_x = 0;
                speed_y = 0;
                dead_act_index = 0;
                dead_delay_index = 0;
            } else{
                ++ dead_delay_index;
            }
        }
    }
}

void pacman::man_act(){
    if(!over ){
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

void pacman::man_move(int player_id,map_info::key command){
    if(player_id == 0 && start && !over){
        switch(command){
        case map_info::left:
            temp = map_info::left;
            speed_x = - SPEED_ABSO;
            speed_y = 0;
            break;
        case map_info::right:
            temp = map_info::right;
            speed_x = SPEED_ABSO;
            speed_y = 0;
            break;
        case map_info::up:
            temp = map_info::up;
            speed_x = 0;
            speed_y = - SPEED_ABSO;
            break;
        case map_info::down:
            temp = map_info::down;
            speed_x = 0;
            speed_y = SPEED_ABSO;
            break;
        default:break;//none
        }
    }
}

void pacman::move_method(){
    if(start && !over){
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
            man_xpos = map_xpos[col - speed_x / SPEED_ABSO];
            man_ypos = map_ypos[row - speed_y / SPEED_ABSO];
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

int pacman::tran_x(int xpos){
    int x = (xpos - map_info::play_region_x ) / block_width;
    x = xpos - map_info::play_region_x < 0 ? - 1 : x ;
    return x;
}

int pacman::tran_y(int ypos){
    int y = (ypos - map_info::play_region_y ) / block_width;
    y = y >= map_info::map_height ? map_info::map_height - 1 : y ;
    return y;
}

void pacman::debug(){
}
