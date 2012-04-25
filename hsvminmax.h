#ifndef HSVMINMAX_H
#define HSVMINMAX_H

struct HSVMinMax
{
    HSVMinMax() {
        hue_min = 255;
        hue_max = 0;
        sat_min = 255;
        sat_max = 0;
        val_min = 255;
        val_max = 0;
    }

    unsigned char hue_min, hue_max, sat_min, sat_max, val_min, val_max;
};

#endif // HSVMINMAX_H
