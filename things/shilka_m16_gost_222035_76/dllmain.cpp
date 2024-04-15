// dllmain.cpp : Определяет точку входа для приложения DLL.
#include "pch.h"
#include "shilka_m16_gost_222035_76.h"

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

void draw_shilka_m16_gost_222035_76(double orig_x, double orig_y, double orig_z) {
    tag_t cyl;
    drawCyl(create, orig_x, orig_y, orig_z, "90", "16", 0, 1, 0, &cyl);

    drawRampHorizontal("shilka_ramp1", orig_x, orig_y, orig_z, 8, 6, 2);
    drawRampHorizontal("shilka_ramp2", orig_x, orig_y + 90, orig_z, 8, 6, -2);
}
