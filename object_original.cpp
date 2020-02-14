#include "object_original.h"

object_original::object_original(QWidget * parent,const int x_pos[],const int y_pos[],object_key color)
    : QWidget(parent),object_color(color)
{
    ghost_act_index = 0;

    for(int row = 0 ; row < map_info::map_height ; ++ row)
        for(int col = 0 ; col < map_info::map_width ; ++ col)
            bit_map[row][col] = map_info::map_value[row][col];

    //set pos info
    for(int col = 0 ; col < map_info::map_width ; ++ col)
        map_xpos[col] = x_pos[col];
    for(int row = 0 ; row < map_info::map_height ; ++ row)
        map_ypos[row] = y_pos[row];

    switch(object_color){
    case map_info::red://red
        ghost_col = map_info::ghostr_initial_x;
        ghost_row = map_info::ghostr_initial_y;
        ghost_xpos = map_xpos[map_info::ghostr_initial_x];
        ghost_ypos = map_ypos[map_info::ghostr_initial_y];
        ghost_x = ghost_xpos + block_width / 2;
        ghost_y = ghost_ypos + block_width / 2;
        break;
    case map_info::blue://blue
        ghost_col = map_info::ghostb_initial_x;
        ghost_row = map_info::ghostb_initial_y;
        ghost_xpos = map_xpos[map_info::ghostb_initial_x];
        ghost_ypos = map_ypos[map_info::ghostb_initial_y];
        ghost_x = ghost_xpos + block_width / 2;
        ghost_y = ghost_ypos + block_width / 2;
        break;
    case map_info::yellow://yellow
        ghost_col = map_info::ghosty_initial_x;
        ghost_row = map_info::ghosty_initial_y;
        ghost_xpos = map_xpos[map_info::ghosty_initial_x];
        ghost_ypos = map_ypos[map_info::ghosty_initial_y];
        ghost_x = ghost_xpos + block_width / 2;
        ghost_y = ghost_ypos + block_width / 2;
        break;
    case map_info::pink://pink
        ghost_col = map_info::ghostp_initial_x;
        ghost_row = map_info::ghostp_initial_y;
        ghost_xpos = map_xpos[map_info::ghostp_initial_x];
        ghost_ypos = map_ypos[map_info::ghostp_initial_y];
        break;
    case map_info::man:
        //man act img
        man_col = map_info::man_initial_x;
        man_row = map_info::man_initial_y;
        man_xpos = map_xpos[map_info::man_initial_x];
        man_ypos = map_ypos[map_info::man_initial_y];
        man_x = man_xpos + block_width / 2;
        man_y = man_ypos + block_width / 2;
        break;
    case map_info::man2:
        //man act img
        man_col = map_info::man2_initial_x;
        man_row = map_info::man2_initial_y;
        man_xpos = map_xpos[map_info::man2_initial_x];
        man_ypos = map_ypos[map_info::man2_initial_y];
        man_x = man_xpos + block_width / 2;
        man_y = man_ypos + block_width / 2;
        break;
    }

}

void object_original::update_bitmap(int row,int col){
    bit_map[row][col] = ! bit_map[row][col];
}

void object_original::update_bitmap(bool new_bitmap[map_info::map_height][map_info::map_width]){
    for(int row = 0 ; row < map_info::map_height ; ++ row)
        for(int col = 0 ; col < map_info::map_width ; ++ col)
            bit_map[row][col] = new_bitmap[row][col];
}

