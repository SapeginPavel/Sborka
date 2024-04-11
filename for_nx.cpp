#include <uf.h>
#include <iostream>
#include <uf_curve.h>
#include <uf_sket.h>
#include <uf_modl.h>
#include <string>
#include <cstring>

//TODO правильно ли в целом? Почему цилиндр не вычитается?

char** getCharArrForLengths(const char* x, const char* y, const char* z) {
    char* x_copy = new char[strlen(x) + 1];
    strcpy_s(x_copy, strlen(x) + 1, x);

    char* y_copy = new char[strlen(y) + 1];
    strcpy_s(y_copy, strlen(y) + 1, y);

    char* z_copy = new char[strlen(z) + 1];
    strcpy_s(z_copy, strlen(z) + 1, z);

    char** size = new char* [3];
    size[0] = x_copy;
    size[1] = y_copy;
    size[2] = z_copy;

    return size;
}

void ufusr(char* param, int* retcode, int paramLen) {
    UF_initialize();
    ///////////////////////////////////////////////

    /*tag_t Line1Tag = NULL_TAG;
    UF_CURVE_line_t Line_coords1;
    Line_coords1.start_point[0] = 0;
    Line_coords1.start_point[1] = 0;
    Line_coords1.start_point[2] = 0;
    Line_coords1.end_point[0] = 100;
    Line_coords1.end_point[1] = 100;
    Line_coords1.end_point[2] = 100;
    UF_CURVE_create_line(&Line_coords1, &Line1Tag);

    double c1point1[3] = { 0.0,0.0,0.0 };
    double c1point2[3] = { 50.0,50.0,70.0 };
    double c1point3[3] = { 100.0,100.0,100.0 };
    tag_t circule1 = NULL;
    UF_CURVE_create_arc_thru_3pts(1, c1point1, c1point2, c1point3, &circule1);


    tag_t sketch1 = NULL_TAG;
    char scn[129] = "scname1";
    UF_SKET_initialize_sketch(scn, &sketch1);*/

    double coordinates_of_center[3] = { 0,0,0 }; //Трехмерные координаты точки, задающей начало (угловую точку) блока

    //КОРПУС
    tag_t korpus_block;
    UF_MODL_create_block1(UF_NULLSIGN, coordinates_of_center, getCharArrForLengths("60", "107", "43"), &korpus_block);

    //Вычитание из корпуса 1
    tag_t korpus_block_negative1;
    UF_MODL_create_block1(UF_NEGATIVE, coordinates_of_center, getCharArrForLengths("60", "55", "19"), &korpus_block_negative1);

    //Вычитание из корпуса 1
    double coordinates_for_korpus_block_negative2[3] = { coordinates_of_center[0], coordinates_of_center[1], coordinates_of_center [2] + 36 };
    tag_t korpus_block_negative2;
    UF_MODL_create_block1(UF_NEGATIVE, coordinates_for_korpus_block_negative2, getCharArrForLengths("60", "40", "7"), &korpus_block_negative2);


    //ОТВЕРСТИЕ в корпусе сверху
    double c_hole_in_korpus_above[3] = {
        coordinates_of_center[0] + 30,
        coordinates_of_center[1] + 20,
        coordinates_of_center[2] + 19
    };
    char height_above[125] = "17";
    char diam_above[125] = "21";
    double direction_above[3] = { 0, 0, 1.0 };
    tag_t hole_in_korpus_above;
    UF_MODL_create_cyl1(UF_NEGATIVE, c_hole_in_korpus_above, height_above, diam_above, direction_above, &hole_in_korpus_above);


    //ОТВЕРСТИЕ в корпусе справа
    double c_hole_in_korpus_right[3] = {
        coordinates_of_center[0] + 30,
        coordinates_of_center[1] + 107,
        coordinates_of_center[2] + 25
    };
    char height_right[125] = "40";
    char diam_right[125] = "13.546";
    double direction_right[3] = { 0, -1.0, 0 };
    tag_t hole_in_korpus_right;
    UF_MODL_create_cyl1(UF_NEGATIVE, c_hole_in_korpus_right, height_right, diam_right, direction_right, &hole_in_korpus_right);


    //ПЛАСТИНА на корпусе
    double coordinates_of_plastina_on_korpus[3] = { 
        coordinates_for_korpus_block_negative2[0],
        coordinates_for_korpus_block_negative2[1] - 3,
        coordinates_for_korpus_block_negative2[2]
    };
    tag_t plastina_on_korpus_first_part;
    UF_MODL_create_block1(UF_NULLSIGN, coordinates_of_plastina_on_korpus, getCharArrForLengths("60", "43", "7"), &plastina_on_korpus_first_part);

    double coordinates_of_plastina_on_korpus2[3] = {
        coordinates_for_korpus_block_negative2[0],
        coordinates_for_korpus_block_negative2[1] - 3,
        coordinates_for_korpus_block_negative2[2] + 7
    };
    tag_t plastina_on_korpus_second_part;
    UF_MODL_create_block1(UF_POSITIVE, coordinates_of_plastina_on_korpus2, getCharArrForLengths("60", "55", "9"), &plastina_on_korpus_second_part);


    //ОТВЕРСТИЕ в пластине на корпусе
    double c_hole_in_plastines_on_korpus[3] = { 
        coordinates_of_center[0] + 30,
        coordinates_of_center[1] + 20,
        coordinates_of_center[2] + 19 + 17 
    };
    char height1[125] = "16";
    char diam1[125] = "21";
    double direction1[3] = { 0, 0, 1.0 };
    tag_t hole_in_plastines_on_korpus;
    UF_MODL_create_cyl1(UF_NEGATIVE, c_hole_in_plastines_on_korpus, height1, diam1, direction1, &hole_in_plastines_on_korpus);


    //БЛОК (справа, высокий)
    double coordinates_of_long_block[3] = {
        coordinates_of_center[0],
        coordinates_of_center[1] + 107,
        coordinates_of_center[2]
    };
    tag_t long_block;
    UF_MODL_create_block1(UF_NULLSIGN, coordinates_of_long_block, getCharArrForLengths("60", "25", "100"), &long_block);


    //ОТВЕРСТИЕ в высоком блоке справа
    double c_hole_in_long_block_right[3] = {
        coordinates_of_center[0] + 30,
        coordinates_of_center[1] + 107 + 25,
        coordinates_of_center[2] + 25
    };
    char height_long_block_right[125] = "25";
    char diam_long_block_right[125] = "13.546";
    double direction_long_block_right[3] = { 0, -1.0, 0 };
    tag_t hole_in_long_block_right;
    UF_MODL_create_cyl1(UF_NEGATIVE, c_hole_in_long_block_right, height_long_block_right, diam_long_block_right, direction_long_block_right, &hole_in_long_block_right);


    //ОТВЕРСТИЕ в высоком блоке сверху
    double c_hole_in_long_block_above[3] = {
        coordinates_of_center[0] + 30,
        coordinates_of_center[1] + 107 + 12.5,
        coordinates_of_center[2] + 100
    };
    char height_long_block_above[125] = "35";
    char diam_long_block_above[125] = "8.16";
    double direction_long_block_above[3] = { 0, 0, -1.0 };
    tag_t hole_in_long_block_above;
    UF_MODL_create_cyl1(UF_NEGATIVE, c_hole_in_long_block_above, height_long_block_above, diam_long_block_above, direction_long_block_above, &hole_in_long_block_above);


    //БЛОК (справа, на высоком)
    double coordinates_of_block_on_long_block[3] = {
        coordinates_of_center[0],
        coordinates_of_center[1] + 107,
        coordinates_of_center[2] + 100
    };
    tag_t block_on_long_block;
    UF_MODL_create_block1(UF_NULLSIGN, coordinates_of_block_on_long_block, getCharArrForLengths("60", "25", "25"), &block_on_long_block);


    //ОТВЕРСТИЕ в блоке на высоком блоке
    double c_hole_in_block_on_long_block[3] = {
        coordinates_of_center[0] + 30,
        coordinates_of_center[1] + 107 + 12.5,
        coordinates_of_center[2] + 100 + 25
    };
    char height_block_on_long_block[125] = "25";
    char diam_block_on_long_block[125] = "8.16";
    double direction_block_on_long_block[3] = { 0, 0, -1.0 };
    tag_t hole_in_block_on_long_block;
    UF_MODL_create_cyl1(UF_NEGATIVE, c_hole_in_block_on_long_block, height_block_on_long_block, diam_block_on_long_block, direction_block_on_long_block, &hole_in_block_on_long_block);

    ///////////////////////////////////////////////
    UF_terminate();
}

int ufusr_ask_unload(void) {
    return (UF_UNLOAD_IMMEDIATELY);
}


