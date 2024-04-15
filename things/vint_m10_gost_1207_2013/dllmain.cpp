// dllmain.cpp : Определяет точку входа для приложения DLL.
#include "pch.h"
#include "vint_m10_gost_1207_2013.h"

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

void draw_vint_m10_gost_1207_2013(double orig_x, double orig_y, double orig_z) {
    tag_t cyl = NULL_TAG;
    drawCyl(create, orig_x, orig_y, orig_z, "29.6", "10", 0, 0, 1, &cyl);

    tag_t lines_and_arc[5];
    UF_CURVE_line_t line_coords[4];

    double points[5][3] = {
        {orig_x, orig_y + 8, orig_z + 32.6},
        {orig_x, orig_y + 8, orig_z + 29.6},
        {orig_x, orig_y + 0, orig_z + 29.6},
        {orig_x, orig_y + 0, orig_z + 35.6},
        {orig_x, orig_y + 5, orig_z + 35.6}
    };

    for (int i = 0; i < 4; i++)
    {
        line_coords[i].start_point[0] = points[i][0];
        line_coords[i].start_point[1] = points[i][1];
        line_coords[i].start_point[2] = points[i][2];

        line_coords[i].end_point[0] = points[i + 1][0];
        line_coords[i].end_point[1] = points[i + 1][1];
        line_coords[i].end_point[2] = points[i + 1][2];
        UF_CURVE_create_line(&line_coords[i], &lines_and_arc[i]);
    }

    double second_point[3] = { orig_x, orig_y + 5 + 2.1213, orig_z + 32.6 + 2.1213 };
    UF_CURVE_create_arc_thru_3pts(1, points[0], second_point, points[4], &lines_and_arc[4]);
    
    tag_t sketch = NULL_TAG;
    char name[129] = "vint_cap";
    UF_SKET_initialize_sketch(name, &sketch);

    double matrix[9] = { 0, 0, 1, 0, 1, 0, 0, 0, 0 };
    tag_t object[2];
    int reference[2];
    UF_SKET_create_sketch(name, 2, matrix, object, reference, 2, &sketch);
    UF_SKET_add_objects(sketch, 5, lines_and_arc);
    UF_SKET_terminate_sketch();

    uf_list_p_t revolved;
    UF_MODL_create_list(&revolved);
    UF_MODL_put_list_item(revolved, sketch);
    double revolve_point[3] = { orig_x, orig_y, orig_z };
    char revolve_start[15] = "0";
    char revolve_end[15] = "360";
    char* revolve_limit[2] = { revolve_start, revolve_end };
    double revolve_direction[3] = { 0, 0, 1 };
    uf_list_p_t revolve_feature_list;
    UF_MODL_create_revolved(revolved, revolve_limit, revolve_point, revolve_direction, add, &revolve_feature_list);
    UF_MODL_delete_list(&revolved);
    UF_MODL_delete_list(&revolve_feature_list);

    tag_t sub = NULL_TAG;
    drawBlock(subtract, orig_x - 2.5 / 2, orig_y - 8, orig_z + 33.6, "2.5", "16", "3", &sub);
}
