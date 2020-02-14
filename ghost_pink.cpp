#include "ghost_pink.h"

ghost_pink::ghost_pink(QWidget * parent,const int x_pos[],const int y_pos[],object_key color)
    : object_original(parent,x_pos,y_pos,color)
{
    //set id
    id = color;

    //set move way
    move_way[0].c =   1; move_way[0].r =   0;
    move_way[1].c =   1; move_way[1].r =   0;
    move_way[2].c = - 1; move_way[2].r =   0;
    move_way[3].c = - 1; move_way[3].r =   0;
    move_way[4].c =   0; move_way[4].r =   1;
    move_way[5].c =   0; move_way[5].r =   1;
    move_way[6].c =   0; move_way[6].r = - 1;
    move_way[7].c =   0; move_way[7].r = - 1;

    //initialize speed
    speed_x = 0;
    speed_y = 0;

    move_timer = new QTimer(parent);
    move_timer->start(5);

    send_move_timer = new QTimer(parent);
    send_move_timer->start(300);


    ghost_label = new QLabel(parent);
    ghost_img[0].load(":/object/src/object/ghost_p1.png");
    ghost_img[1].load(":/object/src/object/ghost_p2.png");
    ghost_label->setPixmap(ghost_img[ghost_act_index].scaled(block_width,block_width,Qt::KeepAspectRatio));
    ghost_label->setGeometry(ghost_xpos,ghost_ypos,block_width,block_width);
    ghost_label->close();

    ghost_weak_img.load(":/object/src/object/ghost_weak.png");

    start = false;
    over = false;
    weak = false;
    die = false;
    move_rand_counter = 0;
    move_rand = 0;
    srand(static_cast<unsigned>(time(nullptr)));

    die_timer = new QTimer;

    ghost_timer = new QTimer(parent);
    ghost_timer->start(100);

    connect(die_timer,SIGNAL(timeout()),this,SLOT(ghost_revival()));
    connect(ghost_timer,SIGNAL(timeout()),this,SLOT(ghost_act()));
    connect(move_timer,SIGNAL(timeout()),this,SLOT(move_method()));
    connect(send_move_timer,SIGNAL(timeout()),this,SLOT(update_to_move()));
}

void ghost_pink::object_close(){
    over = true;
    weak = false;//for act
    die = true;
    ghost_col = map_info::ghostp_initial_x;
    ghost_row = map_info::ghostp_initial_y;
    ghost_xpos = map_xpos[map_info::ghostp_initial_x];
    ghost_ypos = map_ypos[map_info::ghostp_initial_y];
    ghost_x = ghost_xpos + block_width / 2;
    ghost_y = ghost_ypos + block_width / 2;
    ghost_act_index = 0;
    ghost_label->setGeometry(ghost_xpos,ghost_ypos,block_width,block_width);
    ghost_label->setPixmap(ghost_img[ghost_act_index].scaled(block_width,block_width,Qt::KeepAspectRatio));
    ghost_label->update();
    ghost_label->close();
}

void ghost_pink::object_show(){
    over = false;
    ghost_label->show();
}

void ghost_pink::start_ctrl(){
    start = ! start;
    if(start == false){
        over = false;//for act
        weak = false;//for act
        die = true;
        ghost_col = map_info::ghostp_initial_x;
        ghost_row = map_info::ghostp_initial_y;
        ghost_xpos = map_xpos[map_info::ghostp_initial_x];
        ghost_ypos = map_ypos[map_info::ghostp_initial_y];
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
        move_rand_counter = 0;
        move_rand = 0;
    }
}

void ghost_pink::ghost_act(){
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

void ghost_pink::ghost_weak(){
    ghost_label->setPixmap(ghost_weak_img.scaled(block_width,block_width,Qt::KeepAspectRatio));
    ghost_label->update();
    weak = true;
}

void ghost_pink::ghost_recover(){
    ghost_label->setPixmap(ghost_img[ghost_act_index].scaled(block_width,block_width,Qt::KeepAspectRatio));
    ghost_label->update();
    weak = false;
}

void ghost_pink::ghost_die(){
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

void ghost_pink::ghost_revival(){
    die_timer->stop();
    die = false;
    ghost_col = map_info::ghostp_initial_x;
    ghost_row = map_info::ghostp_initial_y;
    ghost_xpos = map_xpos[map_info::ghostp_initial_x];
    ghost_ypos = map_ypos[map_info::ghostp_initial_y];
    ghost_x = ghost_xpos + block_width / 2;
    ghost_y = ghost_ypos + block_width / 2;
    ghost_act_index = 0;
    ghost_label->setGeometry(ghost_xpos,ghost_ypos,block_width,block_width);
    ghost_label->show();
}

void ghost_pink::game_over(){
    ghost_col = map_info::ghostp_initial_x;
    ghost_row = map_info::ghostp_initial_y;
    ghost_xpos = map_xpos[map_info::ghostp_initial_x];
    ghost_ypos = map_ypos[map_info::ghostp_initial_y];
    ghost_x = ghost_xpos + block_width / 2;
    ghost_y = ghost_ypos + block_width / 2;
    ghost_act_index = 0;
    over = true;
    emit ghost_done(id,ghost_row,ghost_col);
}

void ghost_pink::man_pos(int man__r,int man__c){
    man_r = man__r;
    man_c = man__c;
}


void ghost_pink::move_method(){
    //horse
    if(start && !over && !die){
        ghost_xpos = ghost_xpos + speed_x;
        ghost_ypos = ghost_ypos + speed_y;
        ghost_x = ghost_xpos + block_width / 2;
        ghost_y = ghost_ypos + block_width / 2;
        if(speed_x > 0 && speed_y == 0){
            ghost_col = tran_x(ghost_xpos + block_width + 1);//decode
            ghost_row = tran_y(ghost_y);
            ghost_ypos = map_ypos[ghost_row];
            ghost_y = ghost_ypos + block_width / 2;
        }
        else if(speed_y > 0 && speed_x == 0){
            ghost_col = tran_x(ghost_x);//decode
            ghost_row = tran_y(ghost_ypos + block_width + 1);
            ghost_xpos = map_xpos[ghost_col];
            ghost_x = ghost_xpos + block_width / 2;
        }
        else if(speed_x < 0 && speed_y == 0){
            ghost_col = tran_x(ghost_xpos - 1);//decode
            ghost_row = tran_y(ghost_y);
            ghost_ypos = map_ypos[ghost_row];
            ghost_y = ghost_ypos + block_width / 2;
        }
        else if(speed_y < 0 && speed_x == 0){
            ghost_col = tran_x(ghost_x);//decode
            ghost_row = tran_y(ghost_ypos - 1);
            ghost_xpos = map_xpos[ghost_col];
            ghost_x = ghost_xpos + block_width / 2;
        } else{
            ghost_col = tran_x(ghost_xpos);//decode
            ghost_row = tran_y(ghost_ypos);//decode
        }

        if(ghost_row < 0){
            ghost_ypos = map_info::play_region_y ;
            ghost_row = 0;
        }else if(ghost_col < 0){
            ghost_xpos = map_info::play_region_x + block_width * ( map_info::map_width - 1 ) ;
            ghost_col = map_width - 1;
        }else if(ghost_col >= map_info::map_width){
            ghost_xpos = map_info::play_region_x;
            ghost_col = 0;
        }

        if(bit_map[ghost_row][ghost_col] == 0){
            ghost_x = ghost_xpos + block_width / 2;
            ghost_y = ghost_ypos + block_width / 2;
            ghost_label->setGeometry(ghost_xpos,ghost_ypos,block_width,block_width);
            ghost_label->show();
        } else {
            ghost_xpos = map_xpos[ghost_col - speed_x / GHOST_SPEED_ABSO];
            ghost_ypos = map_ypos[ghost_row - speed_y / GHOST_SPEED_ABSO];
            ghost_x = ghost_xpos + block_width / 2;
            ghost_y = ghost_ypos + block_width / 2;
            ghost_col = tran_x(ghost_x);
            ghost_row = tran_y(ghost_y);
            speed_x = 0;
            speed_y = 0;
            ghost_label->setGeometry(ghost_xpos,ghost_ypos,block_width,block_width);
            ghost_label->show();
        }
        //center
        emit ghost_done(id,ghost_row,ghost_col);
        QCoreApplication::processEvents();
    }

}

void ghost_pink::update_to_move(){
    if(start && !over && !die){
        //emit ghost_done(id,ghost_row,ghost_col);
        int col = ghost_col;
        int row = ghost_row;
        bool legal[4] ;
        if(row < map_info::map_height && row >= 0 &&
           col < map_info::map_width  && col >= 0 ){
            //right
            if(col + 1 < map_info::map_width && bit_map[row][col + 1] == false){
                legal[map_info::right] = true;
            }else{
                legal[map_info::right] = false;
            }
            //left
            if(col - 1 >= 0 && bit_map[row][col - 1] == false){
                legal[map_info::left] = true;
            }else{
                legal[map_info::left] = false;
            }
            //down
            if(row + 1 < map_info::map_height && bit_map[row + 1][col] == false){//down
                legal[map_info::down] = true;
            }else{
                legal[map_info::down] = false;
            }
            //up
            if(row - 1 >= 0 && bit_map[row - 1][col] == false){//down
                legal[map_info::up] = true;
            }else{
                legal[map_info::up] = false;
            }
            int temp;

            do{
                temp = rand() % 4;
            }while(!legal[temp]);

            switch(temp){
            case map_info::left:
                speed_x = - GHOST_SPEED_ABSO;
                speed_y = 0;
                break;
            case map_info::right:
                speed_x = GHOST_SPEED_ABSO;
                speed_y = 0;
                break;
            case map_info::up:
                speed_x = 0;
                speed_y = - GHOST_SPEED_ABSO;
                break;
            case map_info::down:
                speed_x = 0;
                speed_y = GHOST_SPEED_ABSO;
                break;
            default:break;//none
            }
        }
    }
}


int ghost_pink::distance(int gr,int gc,int mr,int mc){
    return (gr - mr) * (gr - mr) + (gc - mc) * (gc - mc);
}

int ghost_pink::tran_x(int xpos){
    int x = (xpos - map_info::play_region_x ) / block_width;
    x = xpos - map_info::play_region_x < 0 ? - 1 : x ;
    return x;
}

int ghost_pink::tran_y(int ypos){
    int y = (ypos - map_info::play_region_y ) / block_width;
    y = y >= map_info::map_height ? map_info::map_height - 1 : y ;
    return y;
}

