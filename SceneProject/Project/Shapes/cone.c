/*!===============================================================
  S.Ghamri - Universite Gustave Eiffel - samy.ghamri@univ-eiffel.fr
  X.Osaj - Universite Gustave Eiffel - xhavit.osaj@univ-eiffel.fr
                              Cone
                           01/05/2022
  ================================================================!*/

#include "../include/shape.h"
#include <math.h>

void cone_points(Shape *shape, G3Xvector scale_factor, double dcam)
{
    int step_m = 1. / (((scale_factor.x * dcam) + (scale_factor.y * dcam)) / 2.);
    step_m = MAX(1, step_m);
    glPointSize(1);
    glBegin(GL_POINTS);
    int i;
    for (i = 0; i < (int)((shape->n1 * shape->n3) + (shape->n1 * shape->n2)) - step_m; i += step_m)
    {
        normVrtx3dv(shape->norm, shape->vrtx, i);
    }
    glEnd();
}

Shape *create_cone()
{
    Shape *shape;
    shape = init_cone();
    if (NULL == shape)
        return NULL;
    int i, j, n1 = shape->n1, n2 = shape->n2, n3 = shape->n3;
    double teta = (2. * PI) / (double)n1, phi = PI / (double)n2;
    for (i = 0; i < n3; i++)
    {
        double r = (double)i / (double)(n3 - 1);
        for (j = 0; j < n1; j++)
        {
            double x = r * cos((double)j * teta), y = r * sin((double)j * teta);
            shape->vrtx[(i * n1) + j] = (G3Xpoint){x, y, -1};
            shape->norm[(i * n1) + j] = (G3Xvector){0, 0, -1};
        }
    }
    int start = n1 * n3;
    for (i = 0; i < n2; i++)
    {
        double Zp = cos((double)i * phi);
        for (j = 0; j < n1; j++)
        {
            double x = cos((double)j * teta), y = sin((double)j * teta);
            shape->vrtx[i * n1 + j + start] = (G3Xpoint){((1. - Zp) / 2.) * x, ((1. - Zp) / 2.) * y, Zp};
            shape->norm[i * n1 + j + start] = (G3Xvector){x, y, 0};
        }
    }
    return shape;
}

void cone_faces(Shape *shape, G3Xvector scale_factor, double dcam)
{
    int n1 = shape->n1, n2 = shape->n2, n3 = shape->n3;
    int step_m = 1. / (((scale_factor.x * dcam) + (scale_factor.y * dcam)) / 2.), step_p = 1. / (scale_factor.z * dcam);
    step_m = MAX(1, step_m), step_p = MAX(1, step_p);
    int step_n = step_p;
    glPointSize(1);
    glBegin(GL_QUADS);
    int i, j;
    for (i = 0; i < n3 - step_n; i += step_n)
    {
        for (j = 0; j < n1 - step_m; j += step_m)
        {
            normVrtx3dv(shape->norm, shape->vrtx, i * n1 + j);
            normVrtx3dv(shape->norm, shape->vrtx, i * n1 + j + step_m);
            normVrtx3dv(shape->norm, shape->vrtx, (i + step_n) * n1 + j + step_m);
            normVrtx3dv(shape->norm, shape->vrtx, (i + step_n) * n1 + j);
        }
        normVrtx3dv(shape->norm, shape->vrtx, i * n1 + j);
        normVrtx3dv(shape->norm, shape->vrtx, i * n1);
        normVrtx3dv(shape->norm, shape->vrtx, (i + step_n) * n1);
        normVrtx3dv(shape->norm, shape->vrtx, (i + step_n) * n1 + j);
    }
    for (j = 0; j < n1 - step_m; j += step_m)
    {
        normVrtx3dv(shape->norm, shape->vrtx, i * n1 + j);
        normVrtx3dv(shape->norm, shape->vrtx, i * n1 + j + step_m);
        normVrtx3dv(shape->norm, shape->vrtx, (n3 - 1) * n1 + j + step_m);
        normVrtx3dv(shape->norm, shape->vrtx, (n3 - 1) * n1 + j);
    }
    normVrtx3dv(shape->norm, shape->vrtx, i * n1 + j);
    normVrtx3dv(shape->norm, shape->vrtx, (n3 - 1) * n1 + j);
    normVrtx3dv(shape->norm, shape->vrtx, (n3 - 1) * n1);
    normVrtx3dv(shape->norm, shape->vrtx, i * n1);
    int start = n1 * n3;
    for (i = 0; i < n2 - step_p; i += step_p)
    {
        for (j = 0; j < n1 - step_m; j += step_m)
        {
            normVrtx3dv(shape->norm, shape->vrtx, i * n1 + j + start);
            normVrtx3dv(shape->norm, shape->vrtx, i * n1 + j + step_m + start);
            normVrtx3dv(shape->norm, shape->vrtx, (i + step_p) * n1 + j + step_m + start);
            normVrtx3dv(shape->norm, shape->vrtx, (i + step_p) * n1 + j + start);
        }
        normVrtx3dv(shape->norm, shape->vrtx, i * n1 + j + start);
        normVrtx3dv(shape->norm, shape->vrtx, i * n1 + start);
        normVrtx3dv(shape->norm, shape->vrtx, (i + step_p) * n1 + start);
        normVrtx3dv(shape->norm, shape->vrtx, (i + step_p) * n1 + j + start);
    }
    for (j = 0; j < n1 - step_m; j += step_m)
    {
        normVrtx3dv(shape->norm, shape->vrtx, i * n1 + j + start);
        normVrtx3dv(shape->norm, shape->vrtx, i * n1 + j + step_m + start);
        normVrtx3dv(shape->norm, shape->vrtx, (n2 - 1) * n1 + j + step_m + start);
        normVrtx3dv(shape->norm, shape->vrtx, (n2 - 1) * n1 + j + start);
    }
    normVrtx3dv(shape->norm, shape->vrtx, i * n1 + j + start);
    normVrtx3dv(shape->norm, shape->vrtx, (n2 - 1) * n1 + j + start);
    normVrtx3dv(shape->norm, shape->vrtx, (n2 - 1) * n1 + start);
    normVrtx3dv(shape->norm, shape->vrtx, i * n1 + start);
    glEnd();
}

Shape *init_cone()
{
    Shape *shape;
    shape = malloc(sizeof(Shape));
    if (NULL == shape)
    {
        return NULL;
    }
    shape->n1 = MAXRES * PI, shape->n2 = (shape->n1) / 2., shape->n3 = MAXRES;
    if (NULL == (shape->vrtx = calloc((shape->n1 * shape->n3) + (shape->n1 * shape->n2), sizeof(G3Xpoint))))
        return NULL;
    if (NULL == (shape->norm = calloc((shape->n1 * shape->n3) + (shape->n1 * shape->n2), sizeof(G3Xvector))))
        return NULL;
    shape->draw_points = cone_points, shape->draw_faces = cone_faces;
    return shape;
}
