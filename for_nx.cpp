#include <uf.h>
#include <iostream>
#include <uf_curve.h>
#include <uf_sket.h>

void ufusr(char* param, int* retcode, int paramLen) {
    UF_initialize();
    ///////////////////////////////////////////////

    tag_t Line1Tag = NULL_TAG;
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
    UF_SKET_initialize_sketch(scn, &sketch1);


    ///////////////////////////////////////////////
    UF_terminate();
}

int ufusr_ask_unload(void) {
    return (UF_UNLOAD_IMMEDIATELY);
}
