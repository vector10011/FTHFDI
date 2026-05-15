#include "arm_math.h"
#include <stdint.h>

/*
    Discrete state-space model:

        x[k+1] = Ad * x[k] + Bd * u[k]
        y[k]   = Cd * x[k] + Dd * u[k]

    System size:
        Number of states  = 2
        Number of inputs  = 1
        Number of outputs = 1
*/

#define SYS_NX      2U
#define SYS_NU      1U
#define SYS_NY      1U

typedef struct
{
    /*
        Matrix instances
    */
    arm_matrix_instance_f32 Ad;
    arm_matrix_instance_f32 Bd;
    arm_matrix_instance_f32 Cd;
    arm_matrix_instance_f32 Dd;

    arm_matrix_instance_f32 x;
    arm_matrix_instance_f32 x_next;
    arm_matrix_instance_f32 u;
    arm_matrix_instance_f32 y;

    /*
        Temporary matrices
    */
    arm_matrix_instance_f32 tmp_x;
    arm_matrix_instance_f32 tmp_u;
    arm_matrix_instance_f32 tmp_y1;
    arm_matrix_instance_f32 tmp_y2;

    /*
        Matrix data buffers
    */
    float32_t Ad_data[SYS_NX * SYS_NX];
    float32_t Bd_data[SYS_NX * SYS_NU];
    float32_t Cd_data[SYS_NY * SYS_NX];
    float32_t Dd_data[SYS_NY * SYS_NU];

    float32_t x_data[SYS_NX];
    float32_t x_next_data[SYS_NX];
    float32_t u_data[SYS_NU];
    float32_t y_data[SYS_NY];

    float32_t tmp_x_data[SYS_NX];
    float32_t tmp_u_data[SYS_NX];
    float32_t tmp_y1_data[SYS_NY];
    float32_t tmp_y2_data[SYS_NY];

} StateSpaceModel;


/*
    Initialize model matrices and state.
*/
void StateSpaceModel_Init(StateSpaceModel *model)
{
    /*
        Ad matrix, 2x2

        Ad = [ 1.0   0.01
               0.0   1.0  ]

        CMSIS-DSP uses row-major order.
    */
    model->Ad_data[0] = 1.0f;
    model->Ad_data[1] = 0.01f;
    model->Ad_data[2] = 0.0f;
    model->Ad_data[3] = 1.0f;

    /*
        Bd matrix, 2x1

        Bd = [ 0.00005
               0.01    ]
    */
    model->Bd_data[0] = 0.00005f;
    model->Bd_data[1] = 0.01f;

    /*
        Cd matrix, 1x2

        Cd = [ 1.0  0.0 ]
    */
    model->Cd_data[0] = 1.0f;
    model->Cd_data[1] = 0.0f;

    /*
        Dd matrix, 1x1

        Dd = [ 0.0 ]
    */
    model->Dd_data[0] = 0.0f;

    /*
        Initial state:

        x[0] = [ 0
                 0 ]
    */
    model->x_data[0] = 0.0f;
    model->x_data[1] = 0.0f;

    model->x_next_data[0] = 0.0f;
    model->x_next_data[1] = 0.0f;

    model->u_data[0] = 0.0f;
    model->y_data[0] = 0.0f;

    /*
        Initialize CMSIS-DSP matrix descriptors.
    */
    arm_mat_init_f32(&model->Ad, SYS_NX, SYS_NX, model->Ad_data);
    arm_mat_init_f32(&model->Bd, SYS_NX, SYS_NU, model->Bd_data);
    arm_mat_init_f32(&model->Cd, SYS_NY, SYS_NX, model->Cd_data);
    arm_mat_init_f32(&model->Dd, SYS_NY, SYS_NU, model->Dd_data);

    arm_mat_init_f32(&model->x,      SYS_NX, 1U, model->x_data);
    arm_mat_init_f32(&model->x_next, SYS_NX, 1U, model->x_next_data);
    arm_mat_init_f32(&model->u,      SYS_NU, 1U, model->u_data);
    arm_mat_init_f32(&model->y,      SYS_NY, 1U, model->y_data);

    arm_mat_init_f32(&model->tmp_x,  SYS_NX, 1U, model->tmp_x_data);
    arm_mat_init_f32(&model->tmp_u,  SYS_NX, 1U, model->tmp_u_data);
    arm_mat_init_f32(&model->tmp_y1, SYS_NY, 1U, model->tmp_y1_data);
    arm_mat_init_f32(&model->tmp_y2, SYS_NY, 1U, model->tmp_y2_data);
}


/*
    Perform one simulation step.

    Input:
        input_value = u[k]

    Output:
        returns y[k]

    Calculation:
        y[k]   = Cd * x[k] + Dd * u[k]
        x[k+1] = Ad * x[k] + Bd * u[k]
*/
float32_t StateSpaceModel_Step(StateSpaceModel *model, float32_t input_value)
{
    arm_status status;

    /*
        Set input u[k].
    */
    model->u_data[0] = input_value;

    /*
        Calculate output:

            y[k] = Cd * x[k] + Dd * u[k]
    */

    status = arm_mat_mult_f32(&model->Cd, &model->x, &model->tmp_y1);
    if (status != ARM_MATH_SUCCESS)
    {
        return 0.0f;
    }

    status = arm_mat_mult_f32(&model->Dd, &model->u, &model->tmp_y2);
    if (status != ARM_MATH_SUCCESS)
    {
        return 0.0f;
    }

    status = arm_mat_add_f32(&model->tmp_y1, &model->tmp_y2, &model->y);
    if (status != ARM_MATH_SUCCESS)
    {
        return 0.0f;
    }

    /*
        Calculate next state:

            x[k+1] = Ad * x[k] + Bd * u[k]
    */

    status = arm_mat_mult_f32(&model->Ad, &model->x, &model->tmp_x);
    if (status != ARM_MATH_SUCCESS)
    {
        return 0.0f;
    }

    status = arm_mat_mult_f32(&model->Bd, &model->u, &model->tmp_u);
    if (status != ARM_MATH_SUCCESS)
    {
        return 0.0f;
    }

    status = arm_mat_add_f32(&model->tmp_x, &model->tmp_u, &model->x_next);
    if (status != ARM_MATH_SUCCESS)
    {
        return 0.0f;
    }

    /*
        Copy x_next to x.
        This updates the internal model state.
    */
    model->x_data[0] = model->x_next_data[0];
    model->x_data[1] = model->x_next_data[1];

    /*
        Return output y[k].
    */
    return model->y_data[0];
}


/*
    Optional helper function:
    manually set model state.
*/
void StateSpaceModel_SetState(StateSpaceModel *model, float32_t x1, float32_t x2)
{
    model->x_data[0] = x1;
    model->x_data[1] = x2;
}


/*
    Optional helper function:
    get current state.
*/
void StateSpaceModel_GetState(StateSpaceModel *model, float32_t *x1, float32_t *x2)
{
    if (x1 != 0)
    {
        *x1 = model->x_data[0];
    }

    if (x2 != 0)
    {
        *x2 = model->x_data[1];
    }
}