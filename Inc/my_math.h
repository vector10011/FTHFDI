#include "arm_math.h"
#include <stdint.h>

#define                 MATRIX_MAX_SIZE                                   0x4UL

typedef struct my_matrix
{
    arm_matrix_instance_f32 c;
    arm_matrix_instance_f32 d;
    float32_t val[MATRIX_MAX_SIZE * MATRIX_MAX_SIZE];
}my_matrix_t;

typedef struct my_system
{
    arm_matrix_instance_f32 A;
    arm_matrix_instance_f32 B;
    arm_matrix_instance_f32 C;

    arm_matrix_instance_f32 x;
    arm_matrix_instance_f32 u;
    arm_matrix_instance_f32 y;

    arm_matrix_instance_f32 x_next;

    arm_matrix_instance_f32 A_MULT_x;
    arm_matrix_instance_f32 B_MULT_u;
    arm_matrix_instance_f32 C_MULT_x;
    arm_matrix_instance_f32 D_MULT_u;
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

// void StateSpaceModel_Init(my_system_t *model, uint16_t states, uint16_t inputs, uint16_t outputs);
// void StateSpaceModel_DiscreteEuler(my_system_t *model, float32_t T_s);
void StateSpaceModel_Step(my_system_t *model);
