#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    resize(1000,700);

    //set bg
    bg.load(":/background/src/background/background.jpg");
    background = new QLabel(this);
    background->setGeometry(0,0,1000,700);
    background->setPixmap(bg.scaled(1000,700,Qt::KeepAspectRatioByExpanding));
    background->show();

    //set play region
    int map_x = map_info::play_region_x;
    int map_y = map_info::play_region_y;
    int map_width = map_info::play_region_width;
    int map_height = map_info::play_region_height;
    pr.load(":/background/src/background/play_region.jpg");
    play_region = new QLabel(this);
    play_region->setGeometry(map_x,map_y,map_width,map_height);
    play_region->setPixmap(pr.scaled(map_width,map_height,Qt::KeepAspectRatioByExpanding));
    play_region->close();

    //set dashboard
    man_score[0] = 0;
    man_score[1] = 0;
    QPalette text_pal;
    text_pal.setColor(QPalette::Text,QColor(220,220,220));
    dashboard = new QLabel(this);
    dashboard->setGeometry(40,35,DASHBOARD_WIDTH,DASHBOARD_HEIGHT);
    dashboard->setFont(QFont("Courier",22));
    dashboard->setAlignment(Qt::AlignCenter);
    dashboard->close();

    //set pushbutton
    QPalette button_pal;
    button_pal.setColor(QPalette::Button,QColor(BUTTON_COLOR));
    button_pal.setColor(QPalette::ButtonText,QColor(BUTTON_TEXT_COLOR));
    start_control = new QPushButton(this);
    start_control->setGeometry(50,250,BUTTON_WIDTH,BUTTON_HEIGHT);
    start_control->setText(" START ");
    start_control->setFont(QFont("Courier",20));
    start_control->setPalette(button_pal);
    start_control->setAutoFillBackground(true);
    start_control->close();

    to_menu = new QPushButton(this);
    to_menu->setGeometry(50,320,BUTTON_WIDTH,BUTTON_HEIGHT);
    to_menu->setText(" MENU ");
    to_menu->setFont(QFont("Courier",20));
    to_menu->setPalette(button_pal);
    to_menu->setAutoFillBackground(true);
    to_menu->close();

    edit_control = new QPushButton(this);
    edit_control->setGeometry(50,390,BUTTON_WIDTH,BUTTON_HEIGHT);
    edit_control->setText(" EDIT ");
    edit_control->setFont(QFont("Courier",20));
    edit_control->setPalette(button_pal);
    edit_control->setAutoFillBackground(true);
    edit_control->close();

    //set message
    message = new QLabel(this);
    message->setGeometry(20,480,180,200);
    message->setFont(QFont("Courier",16));
    message->setAlignment(Qt::AlignCenter|Qt::AlignTop);

    //set pos info
    for(int x = 0 ; x < map_info::map_width ; ++ x)
        xpos[x] = map_x + block_width * x;
    for(int y = 0 ; y < map_info::map_height ; ++ y)
        ypos[y] = map_y + block_width * y;

    //set game parameter
    power = false;//to ctrl man & ghost
    start = false;

    //set map info
    map_color.load(":/color/src/color/map_colorb.png");
    for(int row = 0 ; row < map_info::map_height ; ++ row){
        for(int col = 0 ; col < map_info::map_width ; ++ col){
            map[row][col] = new QLabel(this);
            map[row][col]->setGeometry(xpos[col],ypos[row],block_width,block_width);
            map[row][col]->setPixmap(map_color.scaled(block_width,block_width,Qt::KeepAspectRatio));
            map[row][col]->close();
            bit_map[row][col] = 0;
            if(map_info::map_value[row][col]){
                bit_map[row][col] = 1;
            }
        }
    }

    //set pacman
    gamedot = new dot(this,xpos,ypos);
    ghost_1 = new ghost_red(this,xpos,ypos,map_info::red);
    ghost_2 = new ghost_blue(this,xpos,ypos,map_info::blue);
    ghost_3 = new ghost_yellow(this,xpos,ypos,map_info::yellow);
    ghost_4 = new ghost_pink(this,xpos,ypos,map_info::pink);
    pac_man = new pacman(this,xpos,ypos,map_info::man);
    pac_man2 = new pacman2(this,xpos,ypos,map_info::man2);//temp not use

    for(int i = 0 ; i < OTHER_OBJECT ;++ i){
        object_pos[i].c = -1;
        object_pos[i].r = -1;
        object_valid[i] = false;
    }

    //set menu
    menu = new mainpage(this);

    //set over info
    player_id = 0;//0: pa ,1: p2
    over_width = map_info::over_object_width;
    over_height = map_info::over_object_height;
    over_xpos = map_info::play_region_x + (map_info::play_region_width - over_width) / 2;
    over_ypos = map_info::play_region_y + (map_info::play_region_height - over_height) / 2;
    oi[0].load(":/object/src/object/over_lose_img.png");
    oi[1].load(":/object/src/object/over_win_img.png");
    oi[2].load(":/object/src/object/over_lose_img1.png");
    oi[3].load(":/object/src/object/over_win_img1.png");
    oi[4].load(":/object/src/object/over_lose_img2.png");
    oi[5].load(":/object/src/object/over_win_img2.png");
    over_label = new QLabel(this);
    over_label->setGeometry(over_xpos,over_ypos,over_width,over_height);
    over = false;

    play_timer = new QTimer(this);

    menu->object_show();

    menu_on_off = true;
    edit_on_off = false;

    connect(play_timer,SIGNAL(timeout()),this,SLOT(play()));

    connect(menu->p1,SIGNAL(clicked()),this,SLOT(menu_close()));
    connect(menu->p1,SIGNAL(clicked()),gamedot,SLOT(object_show()));
    connect(menu->p1,SIGNAL(clicked()),pac_man,SLOT(object_show()));
    connect(menu->p1,SIGNAL(clicked()),ghost_1,SLOT(object_show()));
    connect(menu->p1,SIGNAL(clicked()),ghost_2,SLOT(object_show()));
    connect(menu->p1,SIGNAL(clicked()),ghost_3,SLOT(object_show()));
    connect(menu->p1,SIGNAL(clicked()),ghost_4,SLOT(object_show()));

    connect(menu->p2,SIGNAL(clicked()),this,SLOT(menu_close()));
    connect(menu->p2,SIGNAL(clicked()),this,SLOT(p2mode()));
    connect(menu->p2,SIGNAL(clicked()),gamedot,SLOT(object_show()));
    connect(menu->p2,SIGNAL(clicked()),pac_man ,SLOT(object_show()));
    connect(menu->p2,SIGNAL(clicked()),pac_man2,SLOT(object_show()));
    connect(menu->p2,SIGNAL(clicked()),pac_man2,SLOT(valid()));
    connect(menu->p2,SIGNAL(clicked()),ghost_1,SLOT(object_show()));
    connect(menu->p2,SIGNAL(clicked()),ghost_2,SLOT(object_show()));
    connect(menu->p2,SIGNAL(clicked()),ghost_3,SLOT(object_show()));
    connect(menu->p2,SIGNAL(clicked()),ghost_4,SLOT(object_show()));

    connect(start_control,SIGNAL(clicked()),this,SLOT(start_ctrl()));
    connect(start_control,SIGNAL(clicked()),gamedot,SLOT(start_ctrl()));
    connect(start_control,SIGNAL(clicked()),pac_man,SLOT(start_ctrl()));
    connect(start_control,SIGNAL(clicked()),pac_man2,SLOT(start_ctrl()));
    connect(start_control,SIGNAL(clicked()),ghost_1,SLOT(start_ctrl()));
    connect(start_control,SIGNAL(clicked()),ghost_2,SLOT(start_ctrl()));
    connect(start_control,SIGNAL(clicked()),ghost_3,SLOT(start_ctrl()));
    connect(start_control,SIGNAL(clicked()),ghost_4,SLOT(start_ctrl()));

    connect(edit_control,SIGNAL(clicked()),this,SLOT(edit_ctrl()));
    connect(this,SIGNAL(send_edit_pos(int,int)),gamedot,SLOT(edit_pos(int,int)));
    connect(this,SIGNAL(send_edit_pos(int,int)),pac_man,SLOT(update_bitmap(int,int)));
    connect(this,SIGNAL(send_edit_pos(int,int)),pac_man2,SLOT(update_bitmap(int,int)));
    connect(this,SIGNAL(send_edit_pos(int,int)),ghost_1,SLOT(update_bitmap(int,int)));
    connect(this,SIGNAL(send_edit_pos(int,int)),ghost_2,SLOT(update_bitmap(int,int)));
    connect(this,SIGNAL(send_edit_pos(int,int)),ghost_3,SLOT(update_bitmap(int,int)));
    connect(this,SIGNAL(send_edit_pos(int,int)),ghost_4,SLOT(update_bitmap(int,int)));

    connect(to_menu,SIGNAL(clicked()),this,SLOT(menu_open()));
    connect(to_menu,SIGNAL(clicked()),menu,SLOT(object_show()));
    connect(to_menu,SIGNAL(clicked()),gamedot,SLOT(object_close()));
    connect(to_menu,SIGNAL(clicked()),pac_man,SLOT(object_close()));
    connect(to_menu,SIGNAL(clicked()),pac_man2,SLOT(object_close()));
    connect(to_menu,SIGNAL(clicked()),ghost_1,SLOT(object_close()));
    connect(to_menu,SIGNAL(clicked()),ghost_2,SLOT(object_close()));
    connect(to_menu,SIGNAL(clicked()),ghost_3,SLOT(object_close()));
    connect(to_menu,SIGNAL(clicked()),ghost_4,SLOT(object_close()));

    connect(gamedot,SIGNAL(dot_eaten(int)),this,SLOT(get_dot_eaten(int)));

    connect(this,SIGNAL(send_key(int,map_info::key)),pac_man,SLOT(man_move(int,map_info::key)));
    connect(this,SIGNAL(send_key(int,map_info::key)),pac_man2,SLOT(man_move(int,map_info::key)));
    connect(pac_man,SIGNAL(done(int,int)),this,SLOT(get_man_pos(int,int)));
    connect(pac_man2,SIGNAL(done(int,int)),this,SLOT(get_man2_pos(int,int)));

    connect(ghost_1,SIGNAL(ghost_done(map_info::object_key,int,int)),this,SLOT(get_ghost1_pos(map_info::object_key,int,int)));
    connect(ghost_1,SIGNAL(bullet_done(int,int,map_info::other_object)),this,SLOT(get_object_pos(int,int,map_info::other_object)));
    connect(ghost_2,SIGNAL(ghost_done(map_info::object_key,int,int)),this,SLOT(get_ghost2_pos(map_info::object_key,int,int)));
    connect(ghost_3,SIGNAL(ghost_done(map_info::object_key,int,int)),this,SLOT(get_ghost3_pos(map_info::object_key,int,int)));
    connect(ghost_4,SIGNAL(ghost_done(map_info::object_key,int,int)),this,SLOT(get_ghost4_pos(map_info::object_key,int,int)));

    connect(this,SIGNAL(send_man_pos(int,int)),gamedot,SLOT(man_pos(int,int)));
    connect(this,SIGNAL(send_man2_pos(int,int)),gamedot,SLOT(man2_pos(int,int)));
    connect(this,SIGNAL(send_man_pos(int,int)),ghost_1,SLOT(man_pos(int,int)));
    connect(this,SIGNAL(send_man_pos(int,int)),ghost_2,SLOT(man_pos(int,int)));
    connect(this,SIGNAL(send_man_pos(int,int)),ghost_3,SLOT(man_pos(int,int)));
    connect(this,SIGNAL(send_man_pos(int,int)),ghost_4,SLOT(man_pos(int,int)));

    connect(gamedot,SIGNAL(all_eaten()),this,SLOT(get_all_eaten()));//for game over
    connect(gamedot,SIGNAL(power_eaten()),this,SLOT(get_power_eaten()));//for game over
    connect(gamedot,SIGNAL(power_eaten()),ghost_1,SLOT(ghost_weak()));
    connect(gamedot,SIGNAL(power_eaten()),ghost_2,SLOT(ghost_weak()));
    connect(gamedot,SIGNAL(power_eaten()),ghost_3,SLOT(ghost_weak()));
    connect(gamedot,SIGNAL(power_eaten()),ghost_4,SLOT(ghost_weak()));
    connect(gamedot,SIGNAL(send_recover()),this,SLOT(get_power_done()));
    connect(gamedot,SIGNAL(send_recover()),ghost_1,SLOT(ghost_recover()));
    connect(gamedot,SIGNAL(send_recover()),ghost_2,SLOT(ghost_recover()));
    connect(gamedot,SIGNAL(send_recover()),ghost_3,SLOT(ghost_recover()));
    connect(gamedot,SIGNAL(send_recover()),ghost_4,SLOT(ghost_recover()));
    connect(this,SIGNAL(send_ghost1_die()),ghost_1,SLOT(ghost_die()));
    connect(this,SIGNAL(send_ghost2_die()),ghost_2,SLOT(ghost_die()));
    connect(this,SIGNAL(send_ghost3_die()),ghost_3,SLOT(ghost_die()));
    connect(this,SIGNAL(send_ghost4_die()),ghost_4,SLOT(ghost_die()));

    connect(this,SIGNAL(send_game_over(int)),pac_man,SLOT(game_over(int)));
    connect(this,SIGNAL(send_game_over(int)),pac_man2,SLOT(game_over(int)));
    connect(this,SIGNAL(send_game_over()),ghost_1,SLOT(game_over()));
    connect(this,SIGNAL(send_game_over()),ghost_2,SLOT(game_over()));
    connect(this,SIGNAL(send_game_over()),ghost_3,SLOT(game_over()));
    connect(this,SIGNAL(send_game_over()),ghost_4,SLOT(game_over()));

    connect(pac_man,SIGNAL(dead()) ,this,SLOT(show_game_over()));
    connect(pac_man2,SIGNAL(dead()),this,SLOT(show_game_over()));
}

void MainWindow::p2mode(){
    play_mode = 1;
    QString text_string ;
    man_score[0] = 0;
    man_score[1] = 0;
    if(play_mode == 0){
        text_string = QString("DASHBOARD\n\n1 UP   \nscore %1").arg(man_score[0]);
    }else{
        text_string = QString("DASHBOARD\n\n1 UP   \nscore %1\n\n2 UP   \nscore %2").arg(man_score[0]).arg(man_score[1]);
    }
}

void MainWindow::menu_close(){
     for(int row = 0 ; row < map_info::map_height ; ++ row)
         for(int col = 0 ; col < map_info::map_width ; ++ col)
             if(bit_map[row][col])
                 map[row][col]->show();
     play_region->show();
     start_control->show();
     edit_control->show();
     to_menu->show();

     over_label->close();
     dashboard->close();
     message->close();

     play_timer->stop();
     menu_on_off = false;
}

void MainWindow::menu_open(){
    for(int row = 0 ; row < map_info::map_height ; ++ row)
        for(int col = 0 ; col < map_info::map_width ; ++ col)
                map[row][col]->close();
    play_mode = 0;

    over_label->close();
    play_region->close();
    start_control->close();
    edit_control->close();
    to_menu->close();
    dashboard->close();
    message->close();

    play_timer->stop();
    menu_on_off = true;
}

void MainWindow::start_ctrl(){
    start = ! start;
    if(start){
        for(int i = 0 ; i < NUM_OF_GHOST ; ++ i){
            ghost_pos[1].r = 0;
            ghost_pos[1].c = 0;
        }
        QString text_string ;
        man_score[0] = 0;
        man_score[1] = 0;
        if(play_mode == 0){
            text_string = QString("DASHBOARD\n\n1 UP   \nscore %1").arg(man_score[0]);
        }else{
            text_string = QString("DASHBOARD\n\n1 UP   \nscore %1\n\n2 UP   \nscore %2").arg(man_score[0]).arg(man_score[1]);
        }
        dashboard->setText(text_string);
        dashboard->show();
        message->setText("Have fun playing!");
        message->show();
        over = false;
        start_control->setText(" RESTART ");
        start_control->update();
        edit_on_off = false;
        edit_control->setText("EDIT");
        over_label->close();
        play_timer->start(50);
    } else {
        over = true;
        QString text_string ;
        man_score[0] = 0;
        man_score[1] = 0;
        if(play_mode == 0){
            text_string = QString("DASHBOARD\n\n1 UP   \nscore %1").arg(man_score[0]);
        }else{
            text_string = QString("DASHBOARD\n\n1 UP   \nscore %1\n\n2 UP   \nscore %2").arg(man_score[0]).arg(man_score[1]);
        }
        dashboard->setText(text_string);
        dashboard->show();
        message->close();
        start_control->setText(" START ");
        start_control->update();
        edit_on_off = false;
        over_label->close();
        play_timer->stop();
    }
}

void MainWindow::edit_ctrl(){
    if(!start){
        edit_on_off = ! edit_on_off;
        if(edit_on_off){
            edit_control->setText("EDITED");
            message->setText("Editing map...");
            message->show();
        }else{
            edit_control->setText("EDIT");
            message->setText("End edit");
            message->show();
        }
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event){
    switch(event->key()){
    case Qt::Key_Left: emit send_key(0,map_info::left); break;
    case Qt::Key_Right: emit send_key(0,map_info::right); break;
    case Qt::Key_Up: emit send_key(0,map_info::up); break;
    case Qt::Key_Down: emit send_key(0,map_info::down); break;
    case Qt::Key_A: emit send_key(1,map_info::left); break;
    case Qt::Key_D: emit send_key(1,map_info::right); break;
    case Qt::Key_W: emit send_key(1,map_info::up); break;
    case Qt::Key_S: emit send_key(1,map_info::down); break;
    default: break;
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event){
    if(edit_on_off && !menu_on_off && !start){
        int col = ( event->x() - map_info::play_region_x) / map_info::block_width;
        int row = ( event->y() - map_info::play_region_y) / map_info::block_width;
        //outside check
        if(!(row > 8) || !(row < 12) || !(col > 10) || !(col < 14) ){
            //inside check
            if(col > 1 && row > 1 && col < map_info::map_width - 2 && row < map_info::map_height - 2){
                bit_map[row][col] = ! bit_map[row][col];
                if(bit_map[row][col]){
                    message->setText(QString("Edit position on\n"
                                             "row : %1 col : %2\n").arg(row + 1).arg(col + 1));
                    map[row][col]->show();
                }
                else{
                    map[row][col]->close();
                    message->setText(QString("Edit position off\n"
                                             "row : %1 col : %2\n").arg(row + 1).arg(col + 1));
                }
                emit send_edit_pos(row,col);
            }else{
                message->setText(QString("Illegal position \n"
                                         "row : %1 col : %2\n").arg(row + 1).arg(col + 1));
            }
        }else{
            message->setText(QString("Illegal position \n"
                                     "row : %1 col : %2\n").arg(row + 1).arg(col + 1));
        }
    }
}

void MainWindow::get_man_pos(int man_r,int man_c){
    //player_id = 0;
    man_row[0] = man_r;
    man_col[0] = man_c;
    emit send_man_pos(man_row[0],man_col[0]);
    if(man_col[0] >= 0 && man_col[0] < map_info::map_width &&
            man_row[0] >= 0 && man_row[0] < map_info::map_height ){

    }
}

void MainWindow::get_man2_pos(int man_r,int man_c){
    //player_id = 1;
    man_row[1] = man_r;
    man_col[1] = man_c;
    emit send_man2_pos(man_row[1],man_col[1]);//to dot
    emit send_man_pos(man_row[1],man_col[1]);
    if(man_col[1] >= 0 && man_col[1] < map_info::map_width &&
            man_row[1] >= 0 && man_row[1] < map_info::map_height ){

    }
}

void MainWindow::get_ghost1_pos(map_info::object_key key,int ghost_r,int ghost_c){
    ghost_pos[key].r = ghost_r;
    ghost_pos[key].c = ghost_c;
}
void MainWindow::get_ghost2_pos(map_info::object_key key,int ghost_r,int ghost_c){
    ghost_pos[key].r = ghost_r;
    ghost_pos[key].c = ghost_c;
}
void MainWindow::get_ghost3_pos(map_info::object_key key,int ghost_r,int ghost_c){
    ghost_pos[key].r = ghost_r;
    ghost_pos[key].c = ghost_c;
}
void MainWindow::get_ghost4_pos(map_info::object_key key,int ghost_r,int ghost_c){
    ghost_pos[key].r = ghost_r;
    ghost_pos[key].c = ghost_c;
}

void MainWindow::get_object_pos(int ob_r,int ob_c,map_info::other_object ob_key){
    object_pos[map_info::bullet].r = ob_r;
    object_pos[map_info::bullet].c = ob_c;
    switch(ob_key){
    case map_info::bullet:
        if(object_pos[map_info::bullet].r >= 0 &&
           object_pos[map_info::bullet].r < map_info::map_height &&
           object_pos[map_info::bullet].c >= 0 &&
           object_pos[map_info::bullet].c < map_info::map_width){
            object_valid[map_info::bullet] = true;
            break;
        }
    }
}

void MainWindow::get_power_eaten(){
    power = true;
}

void MainWindow::get_power_done(){
    power = false;
}

void MainWindow::play(){//被動觸發
    if(!over){//active play
        //1 players
        if(play_mode == 0){
            if(power){
                for(int i = 0 ; i < NUM_OF_GHOST ; ++ i){
                    if(man_row[player_id] == ghost_pos[i].r && man_col[player_id] == ghost_pos[i].c){
                        switch(i){
                        case map_info::red:
                            man_score[0] += 50;
                            emit send_ghost1_die();
                            break;
                        case map_info::blue:
                            man_score[0] += 50;
                            emit send_ghost2_die();
                            break;
                        case map_info::yellow:
                            man_score[0] += 50;
                            emit send_ghost3_die();
                            break;
                        case map_info::pink:
                            man_score[0] += 50;
                            emit send_ghost4_die();
                            break;
                        default: break;
                        }
                    }
                }
            } else {
                for(int i = 0 ; i < NUM_OF_GHOST ; ++ i){
                    if(man_row[player_id] == ghost_pos[i].r && man_col[player_id] == ghost_pos[i].c){
                        over = true;
                        emit send_game_over();
                        emit send_game_over(0);
                        break;
                    }
                }
            }
            //check other object
            for(int i = 0 ; i < OTHER_OBJECT ; ++ i){
                if(!power && object_valid[i] && man_row[player_id] == object_pos[i].r && man_col[player_id] == object_pos[i].c){
                    over = true;
                    emit send_game_over();
                    emit send_game_over(player_id);
                }
                object_valid[i] = false;
            }

        }else{
            if(power){
                for(int i = 0 ; i < NUM_OF_GHOST ; ++ i){
                    for(int p = 0 ; p < 2 ; ++ p){
                        if(man_row[p] == ghost_pos[i].r && man_col[p] == ghost_pos[i].c){
                            switch(i){
                            case map_info::red:
                                man_score[p] += 50;
                                emit send_ghost1_die();
                                break;
                            case map_info::blue:
                                man_score[p] += 50;
                                emit send_ghost2_die();
                                break;
                            case map_info::yellow:
                                man_score[p] += 50;
                                emit send_ghost3_die();
                                break;
                            case map_info::pink:
                                man_score[p] += 50;
                                emit send_ghost4_die();
                                break;
                            default: break;
                            }
                        }
                    }
                }
            } else {
                for(int i = 0 ; i < NUM_OF_GHOST ; ++ i){
                    for(int p = 0 ; p < 2 ; ++ p){
                        if(man_row[p] == ghost_pos[i].r && man_col[p] == ghost_pos[i].c){
                            emit send_game_over(p);
                            emit send_game_over();
                            over = true;
                            player_id = p;//over set
                            cout<<"---------------------"<<endl;
                            cout<<"p "<<p<<endl;
                            cout<<"man row: "<<man_row[p]<<" col: "<<man_col[p]<<endl;
                            cout<<"ghost "<<i<<" row: "<<ghost_pos[i].r<<" col: "<<ghost_pos[i].c<<endl;
                            break;
                        }
                    }
                }
            }
            //check other object
            for(int i = 0 ; i < OTHER_OBJECT ; ++ i){
                for(int p = 0 ; p < 2 ; ++ p){
                    if(!power && object_valid[i] && man_row[p] == object_pos[i].r
                            && man_col[p] == object_pos[i].c){
                        emit send_game_over(p);
                        emit send_game_over();
                        over = true;
                        player_id = p;//over set
                    }
                }
                object_valid[i] = false;
            }
        }

    }
}

void  MainWindow::get_dot_eaten(int player_id){
    man_score[player_id] += 10;
    QString text_string;
    if(play_mode == 0){
        text_string = QString("DASHBOARD\n\n1 UP   \nscore %1").arg(man_score[0]);
    }else{
        text_string = QString("DASHBOARD\n\n1 UP   \nscore %1\n\n2 UP   \nscore %2").arg(man_score[0]).arg(man_score[1]);
    }
    dashboard->setText(text_string);
    dashboard->setAlignment(Qt::AlignCenter);
    dashboard->show();
}

void MainWindow::show_game_over(){
    if(play_mode == 0){
        over_label->setPixmap(oi[0].scaled(over_width,over_height,Qt::KeepAspectRatio));
        over_label->show();
    }else{
        if(man_score[0] > man_score[1]){
            show_message(1);
            over_label->setPixmap(oi[4].scaled(over_width,over_height,Qt::KeepAspectRatio));
            over_label->show();
        }else if(man_score[0] < man_score[1]){
            show_message(2);
            over_label->setPixmap(oi[2].scaled(over_width,over_height,Qt::KeepAspectRatio));
            over_label->show();
        }else{
            if(player_id == 0){
                show_message(2);
                over_label->setPixmap(oi[2].scaled(over_width,over_height,Qt::KeepAspectRatio));
                over_label->show();
            }else{
                show_message(1);
                over_label->setPixmap(oi[4].scaled(over_width,over_height,Qt::KeepAspectRatio));
                over_label->show();
            }
        }
    }
}

void MainWindow::get_all_eaten(){
    over = true;
    if(play_mode == 0){
        over_label->setPixmap(oi[1].scaled(over_width,over_height,Qt::KeepAspectRatio));
        over_label->show();
    }else{
        if(man_score[0] > man_score[1]){
            show_message(1);
            over_label->setPixmap(oi[3].scaled(over_width,over_height,Qt::KeepAspectRatio));
            over_label->show();
        }else if(man_score[0] < man_score[1]){
            show_message(2);
            over_label->setPixmap(oi[5].scaled(over_width,over_height,Qt::KeepAspectRatio));
            over_label->show();
        }else{
            if(player_id == 0){
                show_message(2);
                over_label->setPixmap(oi[3].scaled(over_width,over_height,Qt::KeepAspectRatio));
                over_label->show();

            }else{
                show_message(1);
                over_label->setPixmap(oi[5].scaled(over_width,over_height,Qt::KeepAspectRatio));
                over_label->show();
            }
        }
    }
}

void MainWindow::show_message(int win_id){
    if(play_mode == 1){
        message->setText(QString("PLAYER %1 WINS").arg(win_id));
        message->show();
    }
}



MainWindow::~MainWindow()
{
    delete ui;
}
