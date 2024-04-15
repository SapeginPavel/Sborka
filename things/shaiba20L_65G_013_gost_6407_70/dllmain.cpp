// dllmain.cpp : Определяет точку входа для приложения DLL.
#include "pch.h"
#include "shaiba_20L_65G_013_gost_6402_70.h"

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

inline tag_t drawLineTag(double start_point[3], double end_point[3]) {
    tag_t LineTag = NULL_TAG;
    UF_CURVE_line_t Line_coords;
    Line_coords.start_point[0] = start_point[0];
    Line_coords.start_point[1] = start_point[1];
    Line_coords.start_point[2] = start_point[2];
    Line_coords.end_point[0] = end_point[0];
    Line_coords.end_point[1] = end_point[1];
    Line_coords.end_point[2] = end_point[2];
    UF_CURVE_create_line(&Line_coords, &LineTag);
    return LineTag;
}

inline void extrudeSketch(tag_t sketch, int length) {
    uf_list_p_t Ext3;
    UF_FEATURE_SIGN extsign3 = UF_NULLSIGN;
    UF_MODL_create_list(&Ext3);
    UF_MODL_put_list_item(Ext3, sketch);
    char tapang3[5] = { "0.0" };
    char ext3s[15] = "0.0";
    std::string temp3 = std::to_string(length);
    char ext3e[15];
    strcpy_s(ext3e, temp3.c_str());
    char* ExtLimit3[2] = { ext3s, ext3e };
    double extpoint3[3] = { 50.0,0.0,0.0 };
    double extdir3[3] = { 0.0,0.0,1.0 };
    uf_list_p_t ExtFeatureList3;
    UF_MODL_create_extruded(Ext3, tapang3, ExtLimit3, extpoint3, extdir3, extsign3,
        &ExtFeatureList3);
    UF_MODL_delete_list(&ExtFeatureList3);
    UF_MODL_delete_list(&Ext3);
}

void draw_9_Shayba_20L_65G_013_GOST_6402(double orig_x, double orig_y, double orig_z) {
    tag_t sketch1 = NULL_TAG;
    char scn[129] = "scname1";
    UF_SKET_initialize_sketch(scn, &sketch1); // <<<<<<<<<<<<

    int option = 2;
    double matrix[9] = { 1,0,0,0,1,0,0,0,0 };
    tag_t object[2];
    int reference[2];
    int plane_dir = 2;
    UF_SKET_create_sketch(scn, option, matrix, object, reference, plane_dir, &sketch1);

    double interR = 20.5;
    double outerR = 31.5;
    double hole = 3;
    double height = 4;

    double inter_point1[3] = { orig_x,orig_y - (hole / 2),orig_z };
    double inter_point2[3] = { orig_x + interR,orig_y,orig_z };
    double inter_point3[3] = { orig_x,orig_y + (hole / 2),orig_z };
    tag_t inter_circule = NULL;
    UF_CURVE_create_arc_thru_3pts(1, inter_point1, inter_point2, inter_point3, &inter_circule);

    double outer_point1[3] = { orig_x - (outerR - interR) / 2,orig_y - (hole / 2),orig_z };
    double outer_point2[3] = { orig_x - (outerR - interR) / 2 + outerR,orig_y,orig_z };
    double outer_point3[3] = { orig_x - (outerR - interR) / 2,orig_y + (hole / 2),orig_z };
    tag_t outer_circule = NULL;

    UF_CURVE_create_arc_thru_3pts(1, outer_point1, outer_point2, outer_point3, &outer_circule);

    double start_point1[3] = { orig_x,orig_y - (hole / 2),orig_z };
    double end_point1[3] = { start_point1[0] - (outerR - interR) / 2, start_point1[1], start_point1[2] };

    double start_point2[3] = { orig_x,orig_y + (hole / 2),orig_z };
    double end_point2[3] = { start_point2[0] - (outerR - interR) / 2, start_point2[1], start_point2[2] };

    tag_t SketchLine[8] = {
        inter_circule,
        outer_circule,
        drawLineTag(start_point1, end_point1),
        drawLineTag(start_point2, end_point2),
    };
    UF_SKET_add_objects(sketch1, 4, SketchLine);
    UF_SKET_terminate_sketch(); // <<<<<<<<<<<<
    extrudeSketch(sketch1, height);
}