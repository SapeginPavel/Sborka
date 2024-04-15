// dllmain.cpp : Определяет точку входа для приложения DLL.
#include "pch.h"
#include "shayba_16_gost_10450_78.h"

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

void draw_shayba_16_gost_10450_78(double orig_x, double orig_y, double orig_z) {
    tag_t outer_cyl = NULL_TAG;
    drawCyl(create, orig_x, orig_y, orig_z, "2.5", "28", 0, 1, 0, &outer_cyl);

    tag_t inner_cyl = NULL_TAG;
    drawCyl(subtract, orig_x, orig_y, orig_z, "2.5", "16.6526", 0, 1, 0, &inner_cyl);
}