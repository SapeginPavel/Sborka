#pragma once

#include <uf_defs.h>
#include <uf_curve.h>
#include <uf_sket.h>
#include <uf_modl_utilities.h>
#include <NXDrawUtils.h>

/// <summary>
/// Рисует деталь 5 – болт М20х70 ГОСТ 7805-70
/// </summary>
/// <param name="orig_x">Координата x центра нижней грани болта</param>
/// <param name="orig_y">Координата y центра нижней грани болта</param>
/// <param name="orig_z">Координата z центра нижней грани болта</param>
inline void __declspec(dllexport) draw_bolt_m20_gost_7805_70(double orig_x, double orig_y, double orig_z);