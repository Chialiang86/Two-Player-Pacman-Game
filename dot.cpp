#include "dot.h"

dot::dot(QMainWindow * parent,const int x_pos[],const int y_pos[]) : QWidget(parent)
{
    for(int col = 0 ; col < map_info::map_width ; ++ col)
        map_xpos[col] = x_pos[col];
    for(int row = 0 ; row < map_info::map_height ; ++ row)
        map_ypos[row] = y_pos[row];

    //set counter
    dot_counter = 0;
    start = false;

    for(int row = 0 ; row < map_info::map_height ; ++ row)
        for(int col = 0 ; col < map_info::map_width ; ++ col)
            bit_map[row][col] = map_info::map_value[row][col];

    dot_img.load(":/object/src/object/dot.png");
    power_img.load(":/object/src/object/power.png");
    for(int row = 0 ; row < map_info::map_height ; ++ row)
        for(int col = 0 ; col < map_info::map_width ; ++ col){
            game_dot[row][col] = new dot_info;
            game_dot[row][col]->dot_label = new QLabel(parent);
            game_dot[row][col]->dot_label->setGeometry(map_xpos[col],map_ypos[row],block_width,block_width);
            game_dot[row][col]->dot_label->setPixmap(dot_img.scaled(block_width,block_width,Qt::KeepAspectRatio));
            game_dot[row][col]->dot_label->close();
            game_dot[row][col]->dot_xpos = map_xpos[col];
            game_dot[row][col]->dot_ypos = map_ypos[row];
            game_dot[row][col]->dot_x = map_xpos[col] + block_width / 2;
            game_dot[row][col]->dot_y = map_ypos[row] + block_width / 2;
        }

    //set power info
    power_timer = new QTimer;
    connect(power_timer,SIGNAL(timeout()),this,SLOT(recover_timeout()));
}

void dot::object_close(){
    for(int row = 0 ; row < map_info::map_height ; ++ row)
        for(int col = 0 ; col < map_info::map_width ; ++ col)
            game_dot[row][col]->dot_label->close();
}

void dot::object_show(){
    if(start){
        for(int row = 0 ; row < map_info::map_height ; ++ row){
            for(int col = 0 ; col < map_info::map_width ; ++ col){
                if(bit_map[row][col] == false ){
                    if((col != map_info::man_initial_x || row != map_info::man_initial_y ) &&
                            (col != map_info::man2_initial_x || row != map_info::man2_initial_y) &&
                            (col != 5 || row != 16 ) && ( col != 17 || row != 12)){
                        game_dot[row][col]->dot_label->show();
                    }
                }
            }
        }
    }
}

void dot::start_ctrl(){
    start = ! start;
    if(start){
        //set dot info
        vector<pos_info> record;
        pos_info temp;
        for(int row = 0 ; row < map_info::map_height ; ++ row){
            for(int col = 0 ; col < map_info::map_width ; ++ col){
                if(bit_map[row][col] == false ){
                    if((col != map_info::man_initial_x || row != map_info::man_initial_y ) &&
                            (col != map_info::man2_initial_x || row != map_info::man2_initial_y) &&
                            (col != 5 || row != 16 ) && ( col != 17 || row != 12)){
                        temp.r = row;
                        temp.c = col;
                        record.push_back(temp);
                        ++ dot_counter;
                        game_dot[row][col]->power = false;
                        game_dot[row][col]->exist = true;
                        game_dot[row][col]->dot_label->setPixmap(dot_img.scaled(block_width,block_width,Qt::KeepAspectRatio));
                        game_dot[row][col]->dot_label->show();
                    }
                }
            }
        }
        dot_number = dot_counter;

        srand(static_cast<unsigned>(time(nullptr)));
        unsigned long num;
        for(short i = 0 ; i < MAX_POWER ; ++ i ){
            do{
                 num = static_cast<unsigned long>(rand()) % record.size();
            }while(game_dot[record[num].r][record[num].c]->power);
            game_dot[record[num].r][record[num].c]->power = true;
            game_dot[record[num].r][record[num].c]->dot_label->setPixmap(power_img.scaled(block_width,block_width,Qt::KeepAspectRatio));
            game_dot[record[num].r][record[num].c]->dot_label->show();
        }

    } else {
        for(int row = 0 ; row < map_info::map_height ; ++ row){
            for(int col = 0 ; col < map_info::map_width ; ++ col){
                if(bit_map[row][col] == false )
                    if((col != map_info::man_initial_x || row != map_info::man_initial_y ) &&
                            (col != map_info::man2_initial_x || row != map_info::man2_initial_y) &&
                            (col != 5 || row != 16 ) && ( col != 17 || row != 12))
                        game_dot[row][col]->dot_label->close();
            }
        }
    }

}

void dot::edit_pos(int row,int col){
    bit_map[row][col] = ! bit_map[row][col];
}

void dot::man_pos(int r,int c){
    if(r >= 0 && r < map_info::map_height && c >= 0 && c < map_info::map_width && game_dot[r][c]->exist){
        -- dot_counter;

        game_dot[r][c]->exist = false;
        game_dot[r][c]->dot_label->close();
        emit dot_eaten(0);
        if(dot_counter == 0)
            emit all_eaten();
        if(game_dot[r][c]->power){
            emit power_eaten();
            power_timer->start(6000);
        }
    }
}

void dot::man2_pos(int r,int c){
    if(r >= 0 && r < map_info::map_height && c >= 0 && c < map_info::map_width && game_dot[r][c]->exist){
        -- dot_counter;
        game_dot[r][c]->exist = false;
        game_dot[r][c]->dot_label->close();
        emit dot_eaten(1);
        if(dot_counter == 0)
            emit all_eaten();
        if(game_dot[r][c]->power){
            emit power_eaten();
            power_timer->start(6000);
        }
    }
}

void dot::recover_timeout(){
    emit send_recover();
    power_timer->stop();
}

int dot::tran_x(int xpos){
    int x = (xpos - map_info::play_region_x ) / block_width;
    x = xpos - map_info::play_region_x < 0 ? - 1 : x ;
    return x;
}

int dot::tran_y(int ypos){
    int y = (ypos - map_info::play_region_y ) / block_width;
    y = y >= map_info::map_height ? map_info::map_height - 1 : y ;
    return y;
}
