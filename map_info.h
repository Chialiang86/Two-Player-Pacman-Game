#ifndef MAP_INFO_H
#define MAP_INFO_H
#include <iostream>
using namespace std;

namespace map_info {

    typedef enum Key{left,right,up,down,none} key;

    typedef enum Object_key_key{red,blue,yellow,pink,man,man2} object_key;

    typedef enum Other_object{bullet} other_object;

    typedef struct Pos_info{

        int r;

        int c;

    }pos_info;

    const int ghostr_initial_x = 11;

    const int ghostr_initial_y = 9;

    const int ghostb_initial_x = 13;

    const int ghostb_initial_y = 9;

    const int ghosty_initial_x = 11;

    const int ghosty_initial_y = 11;

    const int ghostp_initial_x = 13;

    const int ghostp_initial_y = 11;

    const int man_initial_x = 23;

    const int man_initial_y = 19;

    const int man2_initial_x = 1;

    const int man2_initial_y = 1;

    const int map_width = 25;

    const int map_height = 21;

    const int block_width = 30;

    const int play_region_x = 215;

    const int play_region_y = 35;

    const int play_region_width = 750;

    const int play_region_height = 630;

    const int over_object_width = 625;

    const int over_object_height = 250;

    const bool map_value[map_info::map_height][map_info::map_width] = {
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,1,1,1,0,1,0,1,1,1,0,1,0,1,0,1,0,1,0,1,1,1,0,1},
    {1,0,0,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1},
    {1,0,1,1,1,0,1,0,0,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1},
    {1,0,1,0,0,0,1,0,1,1,1,0,0,0,1,0,1,0,1,0,0,0,1,0,1},
    {1,0,1,0,1,1,1,0,1,0,0,0,1,0,1,0,1,0,1,0,1,1,1,0,1},
    {1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,0,0,1,0,1},
    {1,0,1,0,1,0,0,0,1,0,1,1,1,1,1,0,1,0,1,0,1,0,1,0,1},
    {1,0,1,0,1,1,1,0,1,1,1,0,0,0,1,1,1,1,1,0,1,1,1,0,1},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {1,0,1,1,1,1,1,0,1,1,1,0,0,0,1,0,1,1,1,0,1,1,1,0,1},
    {1,0,0,0,0,0,1,0,1,0,1,1,1,1,1,0,1,0,1,0,1,0,1,0,1},
    {1,0,1,1,1,1,1,0,1,0,1,0,0,0,0,0,1,1,1,0,1,0,1,0,1},
    {1,0,1,0,0,0,0,0,1,0,0,0,1,0,1,0,1,0,1,0,1,0,1,0,1},
    {1,0,1,0,1,1,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1},
    {1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1},
    {1,0,1,0,1,1,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1},
    {1,0,1,0,1,0,1,0,1,1,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
    };
}


#endif // MAP_INFO_H
