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


    //ОТВЕРСТИЕ в корпусе
    double c_hole_in_korpus[3] = {
        coordinates_of_center[0] + 30,
        coordinates_of_center[1] + 20,
        coordinates_of_center[2] + 19
    };
    char height[125] = "17";
    char diam[125] = "21";
    double direction[3] = { 0, 0, 1.0 };
    tag_t hole_in_korpus;
    UF_MODL_create_cyl1(UF_NEGATIVE, c_hole_in_korpus, height, diam, direction, &hole_in_korpus);


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



    ///////////////////////////////////////////////
    UF_terminate();
}

int ufusr_ask_unload(void) {
    return (UF_UNLOAD_IMMEDIATELY);
}


