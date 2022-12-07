/*!===============================================================
  S.Ghamri - Universite Gustave Eiffel - samy.ghamri@univ-eiffel.fr
  X.Osaj - Universite Gustave Eiffel - xhavit.osaj@univ-eiffel.fr
                              Cube
                           01/05/2022
  ================================================================!*/

#include "../include/shape.h"
#include <math.h>

void cube_points(Shape *shape, G3Xvector scale_factor, double dcam)
{
    int step_m = 1. / (((scale_factor.x * dcam) + (scale_factor.y * dcam)) / 2.);
    step_m = MAX(1, step_m);

    glPointSize(1);
    glBegin(GL_POINTS);
    for (int i = 0; i < (int)(6 * (shape->n1 * shape->n2)) - step_m; i += step_m)
    {
        normVrtx3dv(shape->norm, shape->vrtx, i);
    }
    glEnd();
}

Shape *init_cube()
{
    Shape *shape;
    shape = shape = malloc(sizeof(Shape));
    if (NULL == shape)
    {
        return NULL;
    }
    shape->n1 = MAXRES * PI / 2.;
    shape->n2 = shape->n1;
    shape->n3 = 1;
    if (NULL == (shape->vrtx = calloc(6 * (shape->n1 * shape->n2), sizeof(G3Xpoint))))
        return NULL;
    if (NULL == (shape->norm = calloc(6 * (shape->n1 * shape->n2), sizeof(G3Xvector))))
        return NULL;
    shape->draw_points = cube_points;
    shape->draw_faces = cube_faces;

    return shape;
}

Shape *create_cube()
{
    Shape *shape;
    shape = init_cube();
    if (NULL == shape)
        return NULL;
    int i, j, n1 = shape->n1, n2 = shape->n2;
    double dX = 2. / (n2 - 1), dY = 2. / (n1 - 1);
    for (i = 0; i < n2; i++)
    {
        for (j = 0; j < n1; j++)
        {
            double x = -1. + j * dX, y = -1. + i * dY;
            shape->vrtx[i * n1 + j] = (G3Xpoint){x, y, -1};
            shape->norm[i * n1 + j] = (G3Xvector){0, 0, -1};
            shape->vrtx[(n2 * n1) + (i * n1) + j] = (G3Xpoint){x, y, 1};
            shape->norm[(n2 * n1) + (i * n1) + j] = (G3Xvector){0, 0, 1};
            shape->vrtx[2 * (n2 * n1) + (i * n1) + j] = (G3Xpoint){x, -1, y};
            shape->norm[2 * (n2 * n1) + (i * n1) + j] = (G3Xvector){0, -1, 0};
            shape->vrtx[3 * (n2 * n1) + (i * n1) + j] = (G3Xpoint){x, 1, y};
            shape->norm[3 * (n2 * n1) + (i * n1) + j] = (G3Xvector){0, 1, 0};
            shape->vrtx[4 * (n2 * n1) + (i * n1) + j] = (G3Xpoint){-1, x, y};
            shape->norm[4 * (n2 * n1) + (i * n1) + j] = (G3Xvector){-1, 0, 0};
            shape->vrtx[5 * (n2 * n1) + (i * n1) + j] = (G3Xpoint){1, x, y};
            shape->norm[5 * (n2 * n1) + (i * n1) + j] = (G3Xvector){1, 0, 0};
        }
    }
    return shape;
}

void cube_faces(Shape *shape, G3Xvector scale_factor, double dcam)
{
    int i, j;
    int n1 = shape->n1, n2 = shape->n2;

    int step_m = 1. / ((scale_factor.x * dcam) + (scale_factor.y * dcam)) / 2.;
    step_m = MAX(1, step_m);
    int step_p = 1. / (scale_factor.z * dcam);
    step_p = MAX(1, step_p);

    glPointSize(1);
    glBegin(GL_QUADS);
    for (i = 0; i < n2 - step_p; i += step_p)
    {
        for (int k = 0; k < 6; k++)
        {
            for (j = 0; j < n1 - step_m; j += step_m)
            {
                normVrtx3dv(shape->norm, shape->vrtx, k * (n2 * n1) + i * n1 + j);
                normVrtx3dv(shape->norm, shape->vrtx, k * (n2 * n1) + i * n1 + j + step_m);
                normVrtx3dv(shape->norm, shape->vrtx, k * (n2 * n1) + (i + step_p) * n1 + j + step_m);
                normVrtx3dv(shape->norm, shape->vrtx, k * (n2 * n1) + (i + step_p) * n1 + j);
            }
        }
    }
    for (int k = 0; k < 6; k++)
    {
        for (j = 0; j < n1 - step_m; j += step_m)
        {
            normVrtx3dv(shape->norm, shape->vrtx, k * (n2 * n1) + i * n1 + j);
            normVrtx3dv(shape->norm, shape->vrtx, k * (n2 * n1) + i * n1 + j + step_m);
            normVrtx3dv(shape->norm, shape->vrtx, k * (n2 * n1) + (n2 - 1) * n1 + j + step_m);
            normVrtx3dv(shape->norm, shape->vrtx, k * (n2 * n1) + (n2 - 1) * n1 + j);
        }
        for (i = 0; i < n2 - step_p; i += step_p)
        {
            normVrtx3dv(shape->norm, shape->vrtx, k * (n2 * n1) + i * n1 + j);
            normVrtx3dv(shape->norm, shape->vrtx, k * (n2 * n1) + i * n1 + (n1 - 1));
            normVrtx3dv(shape->norm, shape->vrtx, k * (n2 * n1) + (i + step_p) * n1 + (n1 - 1));
            normVrtx3dv(shape->norm, shape->vrtx, k * (n2 * n1) + (i + step_p) * n1 + j);
        }
        normVrtx3dv(shape->norm, shape->vrtx, k * (n2 * n1) + i * n1 + j);
        normVrtx3dv(shape->norm, shape->vrtx, k * (n2 * n1) + i * n1 + (n1 - 1));
        normVrtx3dv(shape->norm, shape->vrtx, k * (n2 * n1) + (n2 - 1) * n1 + (n1 - 1));
        normVrtx3dv(shape->norm, shape->vrtx, k * (n2 * n1) + (n2 - 1) * n1 + j);
    }
    glEnd();
}
