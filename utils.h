#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <math.h>

#define FLAG_DIMENSIONS     (4)         // weight matrix dimensions
#define UNIT_LEN            (0.1)       // 0.1 normalized unit
#define GRAVITY             (-9.8)      // gravity
#define ADJACENT_NUM        (8)         // number of adjacent springs for each mass
#define SURFACE             (-3.5)      // ground plane height
#define DEFAULT_REST_LEN    (10)

typedef enum {
    horizental_spring,
    vertical_spring,
    diagonal_spring_slash,
    diagonal_spring_backslash
} spring_t;

enum spring_attitude{
    up_spring,
    up_right_spring,
    right_spring,
    right_down_spring,
    down_spring,
    left_down_spring,
    left_spring,
    up_left_spring
};

typedef enum {
    simulation_I,
    simulation_II
} simulation_t;

#endif // UTILS_H
