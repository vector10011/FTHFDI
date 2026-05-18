#include "arm_math.h"
#include <stdint.h>

#define                 MATRIX_MAX_SIZE                                   0x7UL

typedef struct my_matrix
{
    arm_matrix_instance_f32 d;
    float32_t val[MATRIX_MAX_SIZE * MATRIX_MAX_SIZE];
}my_matrix_t;

typedef struct my_system
{
    my_matrix_t A;
    my_matrix_t B;
    my_matrix_t C;
    my_matrix_t D;

    my_matrix_t x;
    my_matrix_t u;
    my_matrix_t y;

    my_matrix_t x_next;

    my_matrix_t A_MULT_x;
    my_matrix_t B_MULT_u;
    my_matrix_t C_MULT_x;
    my_matrix_t D_MULT_u;
}my_system_t;


/*
    Discrete state-space model:

        x[k+1] = Ad * x[k] + Bd * u[k]
        y[k]   = Cd * x[k] + Dd * u[k]

    System size:
        Number of states  = 2
        Number of inputs  = 1
        Number of outputs = 1
*/

void StateSpaceModel_Init(my_system_t *model, uint16_t states, uint16_t inputs, uint16_t outputs);
void StateSpaceModel_Step(my_system_t *model);
