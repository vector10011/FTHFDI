#include "my_math.h"
#include "arm_math_types.h"

// void StateSpaceModel_Init(my_system_t *model, uint16_t states, uint16_t inputs, uint16_t outputs)
// {
//     arm_mat_init_f32(&model->A.c, states, states, model->A.val);
//     arm_mat_init_f32(&model->B.c, states, inputs, model->B.val);
//     arm_mat_init_f32(&model->C.c, outputs, states, model->C.val);
//     arm_mat_init_f32(&model->D.c, outputs, inputs, model->D.val);

//     arm_mat_init_f32(&model->x.c, states, 1, model->x.val);
//     arm_mat_init_f32(&model->u.c, inputs, 1, model->u.val);
//     arm_mat_init_f32(&model->y.c, outputs, 1, model->y.val);
//     arm_mat_init_f32(&model->x_next.c, states, 1, model->x_next.val);

//     arm_mat_init_f32(&model->A_MULT_x.c, states, 1, model->A_MULT_x.val);
//     arm_mat_init_f32(&model->B_MULT_u.c, states, 1, model->B_MULT_u.val);
//     arm_mat_init_f32(&model->C_MULT_x.c, outputs, 1, model->C_MULT_x.val);
//     arm_mat_init_f32(&model->D_MULT_u.c, outputs, 1, model->D_MULT_u.val);
// }

// void StateSpaceModel_DiscreteEuler(my_system_t *model, float32_t T_s)
// {
//     // Ad = I + A * T_s
//     my_matrix_t I;
//     for (uint16_t i = 0; i < MATRIX_MAX_SIZE; i++) {
//         I.val[i * MATRIX_MAX_SIZE + i] = 1.0f;
//     }
//     arm_mat_init_f32(&I, MATRIX_MAX_SIZE, MATRIX_MAX_SIZE, I.val);
//     I.c.numRows = model->A.c.numRows;
//     I.c.numCols = model->A.c.numCols;

//     my_matrix_t A_scaled;
//     arm_mat_init_f32(&A_scaled, model->A.c.numRows, model->A.c.numCols, A_scaled.val);
//     arm_mat_scale_f32(&model->A.c, T_s, &A_scaled);

//     arm_mat_init_f32(&model->A.d, model->A.c.numRows, model->A.c.numCols, model->A.d.val);
//     arm_mat_add_f32(&I, &A_scaled, &model->A.d);

//     // Bd = B * T_s
//     arm_mat_init_f32(&model->B.d, model->B.c.numRows, model->B.c.numCols, model->B.d.val);
//     arm_mat_scale_f32(&model->B.c, T_s, &model->B.d);
// }

void StateSpaceModel_Step(my_system_t *model)
{
    arm_status status = 0;
    // A * x
    status = arm_mat_mult_f32(&model->A.d, &model->x.d, &model->A_MULT_x.d);
    if (status != ARM_MATH_SUCCESS) {
        // TODO: Handle error
    }
    // B * u
    status = arm_mat_mult_f32(&model->B.d, &model->u.d, &model->B_MULT_u.d);
    if (status != ARM_MATH_SUCCESS) {
        // TODO: Handle error
    }
    // x_next = A * x + B * u
    status = arm_mat_add_f32(&model->A_MULT_x.d, &model->B_MULT_u.d, &model->x_next.d);
    if (status != ARM_MATH_SUCCESS) {
        // TODO: Handle error
    }

    // y = C * x + D * u
    if(model->D.val[0] != 0.0f)
    {
        // C * x
        status = arm_mat_mult_f32(&model->C.d, &model->x.d, &model->C_MULT_x.d);
        if (status != ARM_MATH_SUCCESS) {
            // TODO: Handle error
        }
        // D * u
        status = arm_mat_mult_f32(&model->D.d, &model->u.d, &model->D_MULT_u.d);
        if (status != ARM_MATH_SUCCESS) {
            // TODO: Handle error
        }
        // y = C * x + D * u
        status = arm_mat_add_f32(&model->C_MULT_x.d, &model->D_MULT_u.d, &model->y.d);
        if (status != ARM_MATH_SUCCESS) {
            // TODO: Handle error
        }
    }
    else
    {
        // y = C * x
        status = arm_mat_mult_f32(&model->C.d, &model->x.d, &model->y.d);
        if (status != ARM_MATH_SUCCESS) {
            // TODO: Handle error
        }
    }

    // Update state
    arm_copy_f32(model->x_next.d.pData,
                 model->x.d.pData,
                 (uint32_t)model->x_next.d.numRows * model->x_next.d.numCols);
}
