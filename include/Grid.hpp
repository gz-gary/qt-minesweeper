#pragma once
#include <math.h>

class Grid {
public:
    int w, h, grid_cnt_w, grid_cnt_h;

    Grid(int _w, int _h, int _grid_cnt_w, int _grid_cnt_h) :
        w(_w),
        h(_h),
        grid_cnt_w(_grid_cnt_w),
        grid_cnt_h(_grid_cnt_h)
    {}
    int fwi(int w0) { return std::floor(1.0 * w0 / grid_cnt_w * w); }
    int fhi(int h0) { return std::floor(1.0 * h0 / grid_cnt_h * h); }
    int fwd(double ratio) { return std::floor(ratio * w); }
    int fhd(double ratio) { return std::floor(ratio * h); }
};
