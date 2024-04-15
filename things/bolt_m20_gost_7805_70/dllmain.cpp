// dllmain.cpp : Определяет точку входа для приложения DLL.
#include "pch.h"
#include "bolt_m20_gost_7805_70.h"

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

//void draw_bolt_m20_gost_7805_70(double orig_x, double orig_y, double orig_z)
//{
//	double r = 17.3205;
//	// 17.3205 * cos(30)
//	double six_x = 14.99999301;
//	// 17.3205 * sin(30)
//	double six_y = 8.66025;
//	double six_z = 74.2;
//	double points[7][3] = {
//		{orig_x,         orig_y + r,      orig_z + six_z},
//		{orig_x + six_x, orig_y + six_y,  orig_z + six_z},
//		{orig_x + six_x, orig_y + -six_y, orig_z + six_z},
//		{orig_x,         orig_y + -r,     orig_z + six_z},
//		{orig_x - six_x, orig_y + -six_y, orig_z + six_z},
//		{orig_x - six_x, orig_y + six_y,  orig_z + six_z},
//		{orig_x,         orig_y + r,      orig_z + six_z}
//	};
//
//	tag_t base_lines[6];
//	UF_CURVE_line_t base_lines_coords[6];
//	for (int i = 0; i < 6; i++)
//	{
//		base_lines_coords[i].start_point[0] = points[i][0];
//		base_lines_coords[i].start_point[1] = points[i][1];
//		base_lines_coords[i].start_point[2] = points[i][2];
//
//		base_lines_coords[i].end_point[0] = points[i + 1][0];
//		base_lines_coords[i].end_point[1] = points[i + 1][1];
//		base_lines_coords[i].end_point[2] = points[i + 1][2];
//		UF_CURVE_create_line(&base_lines_coords[i], &base_lines[i]);
//	}
//
//	tag_t sketch = NULL_TAG;
//	char sketchName[129] = "base";
//	UF_SKET_initialize_sketch(sketchName, &sketch);
//
//	double matrix[9] = { 1, 0, 0, 0, 1, 0, 0, 0, 0 };
//	tag_t object[2];
//	int reference[2];
//	UF_SKET_create_sketch(sketchName, 2, matrix, object, reference, 2, &sketch);
//	UF_SKET_add_objects(sketch, 6, base_lines);
//	UF_SKET_terminate_sketch();
//
//	uf_list_p_t to_extrude;
//	UF_MODL_create_list(&to_extrude);
//	UF_MODL_put_list_item(to_extrude, sketch);
//	char taper_angel[5] = { "0.0" };
//
//	char extrude_start[15] = "0";
//	char extrude_end[15] = "13.3";
//
//	char* extrude_limit[2] = { extrude_start, extrude_end };
//	double extrude_point[3] = { orig_x, orig_y, orig_z + six_z };
//	double extrude_direction[3] = { 0, 0, 1 };
//	uf_list_p_t extrude_feature_list;
//	UF_MODL_create_extruded(to_extrude, taper_angel, extrude_limit, extrude_point, extrude_direction, create, &extrude_feature_list);
//	UF_MODL_delete_list(&to_extrude);
//	UF_MODL_delete_list(&extrude_feature_list);
//
//	// (13.3 - 10.7272) / tg(30)
//	double ramp_base = 4.456220;
//	drawRamp("ramp1", orig_x, orig_y, orig_z + 87.5, r, r - ramp_base, -2.57277);
//
//	tag_t bolt_cyl = NULL_TAG;
//	drawCyl(add, orig_x, orig_y, orig_z, "87.5", "20", 0, 0, 1, &bolt_cyl);
//
//	drawRamp("ramp2", orig_x, orig_y, orig_z, 10, 7.5, 2.5);
//}

void draw_bolt_m20_gost_7805_70(double orig_x, double orig_y, double orig_z)
{
	double r = 17.3205;
	// 17.3205 * cos(30)
	double six_x = 14.99999301;
	// 17.3205 * sin(30)
	double six_y = 8.66025;
	double six_z = 74.2;
	double points[7][3] = {
		{orig_x,         orig_y + r,      orig_z},
		{orig_x + six_x, orig_y + six_y,  orig_z},
		{orig_x + six_x, orig_y + -six_y, orig_z},
		{orig_x,         orig_y + -r,     orig_z},
		{orig_x - six_x, orig_y + -six_y, orig_z},
		{orig_x - six_x, orig_y + six_y,  orig_z},
		{orig_x,         orig_y + r,      orig_z}
	};

	tag_t base_lines[6];
	UF_CURVE_line_t base_lines_coords[6];
	for (int i = 0; i < 6; i++)
	{
		base_lines_coords[i].start_point[0] = points[i][0];
		base_lines_coords[i].start_point[1] = points[i][1];
		base_lines_coords[i].start_point[2] = points[i][2];

		base_lines_coords[i].end_point[0] = points[i + 1][0];
		base_lines_coords[i].end_point[1] = points[i + 1][1];
		base_lines_coords[i].end_point[2] = points[i + 1][2];
		UF_CURVE_create_line(&base_lines_coords[i], &base_lines[i]);
	}

	tag_t sketch = NULL_TAG;
	char sketchName[129] = "base";
	UF_SKET_initialize_sketch(sketchName, &sketch);

	double matrix[9] = { 1, 0, 0, 0, 1, 0, 0, 0, 0 };
	tag_t object[2];
	int reference[2];
	UF_SKET_create_sketch(sketchName, 2, matrix, object, reference, 2, &sketch);
	UF_SKET_add_objects(sketch, 6, base_lines);
	UF_SKET_terminate_sketch();

	uf_list_p_t to_extrude;
	UF_MODL_create_list(&to_extrude);
	UF_MODL_put_list_item(to_extrude, sketch);
	char taper_angel[5] = { "0.0" };

	char extrude_start[15] = "0";
	char extrude_end[15] = "13.3";

	char* extrude_limit[2] = { extrude_start, extrude_end };
	double extrude_point[3] = { orig_x, orig_y, orig_z + six_z };
	double extrude_direction[3] = { 0, 0, -1 };
	uf_list_p_t extrude_feature_list;
	UF_MODL_create_extruded(to_extrude, taper_angel, extrude_limit, extrude_point, extrude_direction, create, &extrude_feature_list);
	UF_MODL_delete_list(&to_extrude);
	UF_MODL_delete_list(&extrude_feature_list);

	// (13.3 - 10.7272) / tg(30)
	double ramp_base = 4.456220;
	drawRamp("ramp1", orig_x, orig_y, orig_z - 13.3, r, r - ramp_base, 2.57277);

	tag_t bolt_cyl = NULL_TAG;
	drawCyl(add, orig_x, orig_y, orig_z, "87.5", "20", 0, 0, 1, &bolt_cyl);

	drawRamp("ramp2", orig_x, orig_y, orig_z + 87.5, 10, 7.5, -2.5);
}