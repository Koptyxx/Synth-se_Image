/*!===============================================================
  S.Ghamri - Universite Gustave Eiffel - samy.ghamri@univ-eiffel.fr
  X.Osaj - Universite Gustave Eiffel - xhavit.osaj@univ-eiffel.fr
                             Sphere
                           01/05/2022
  ================================================================!*/

#include "../include/shape.h"
#include <math.h>

void sphere_points(Shape *shape, G3Xvector scale_factor, double dcam)
{
    int step_m = 1. / (((scale_factor.x * dcam) + (scale_factor.y * dcam)) / 2.);
    step_m = MAX(1, step_m);

    glPointSize(1);
    glBegin(GL_POINTS);
    int i;
    for (i = 0; i < (int)shape->n1 * (int)shape->n2 - step_m; i += step_m)
    {
        normVrtx3dv(shape->norm, shape->vrtx, i);
    }
    glEnd();
}

Shape *init_sphere()
{
    Shape *shape;
    shape = malloc(sizeof(Shape));
    if (NULL == shape)
        return NULL;
    shape->n1 = MAXRES * PI, shape->n2 = (shape->n1) / 2., shape->n3 = 1;
    if (NULL == (shape->vrtx = calloc(shape->n1 * shape->n2, sizeof(G3Xpoint))))
        return NULL;
    if (NULL == (shape->norm = calloc(shape->n1 * shape->n2, sizeof(G3Xvector))))
        return NULL;
    shape->draw_points = sphere_points, shape->draw_faces = sphere_faces;
    return shape;
}

Shape *create_sphere()
{
    Shape *shape;
    shape = init_sphere();
    if (NULL == shape)
        return NULL;
    int i, j, n1 = shape->n1, n2 = shape->n2;
    double teta = (2. * PI) / (double)n1, phi = PI / (double)n2;
    i = 0;
    for (j = 0; j < n1; j++)
    {
        shape->vrtx[i * n1 + j] = (G3Xpoint){0., 0., +1.};
        shape->norm[i * n1 + j] = (G3Xvector){0., 0., +1.};
    }
    for (i = 1; i < n2 - 1; i++)
    {
        double Zp = cos((double)i * phi), Rp = sin((double)i * phi);
        for (j = 0; j < n1; j++)
        {
            double x = Rp * cos((double)j * teta), y = Rp * sin((double)j * teta), z = Zp;
            shape->vrtx[i * n1 + j] = (G3Xpoint){x, y, z};
            shape->norm[i * n1 + j] = (G3Xvector){x, y, z};
        }
    }
    j = n2 - 1;
    for (j = 0; j < n1; j++)
    {
        shape->vrtx[i * n1 + j] = (G3Xpoint){0., 0., -1.};
        shape->norm[i * n1 + j] = (G3Xvector){0., 0., -1.};
    }
    return shape;
}

void sphere_faces(Shape *shape, G3Xvector scale_factor, double dcam)
{
    int i, j, n1 = shape->n1, n2 = shape->n2;
    int step_m = 1. / ((scale_factor.x * dcam) + (scale_factor.y * dcam)) / 2.;
    step_m = MAX(1, step_m);
    int step_p = 1. / (scale_factor.z * dcam);
    step_p = MAX(1, step_p);
    glPointSize(1);
    glBegin(GL_QUADS);
    for (i = 0; i < (int)n2 - step_p; i += step_p)
    {
        for (j = 0; j < (int)n1 - step_m; j += step_m)
        {
            normVrtx3dv(shape->norm, shape->vrtx, i * n1 + j);
            normVrtx3dv(shape->norm, shape->vrtx, i * n1 + j + step_m);
            normVrtx3dv(shape->norm, shape->vrtx, (i + step_p) * n1 + j + step_m);
            normVrtx3dv(shape->norm, shape->vrtx, (i + step_p) * n1 + j);
        }

        normVrtx3dv(shape->norm, shape->vrtx, i * n1 + j);
        normVrtx3dv(shape->norm, shape->vrtx, i * n1);
        normVrtx3dv(shape->norm, shape->vrtx, (i + step_p) * n1);
        normVrtx3dv(shape->norm, shape->vrtx, (i + step_p) * n1 + j);
    }

    for (j = 0; j < (int)n1 - step_m; j += step_m)
    {

        normVrtx3dv(shape->norm, shape->vrtx, i * n1 + j);
        normVrtx3dv(shape->norm, shape->vrtx, i * n1 + j + step_m);
        normVrtx3dv(shape->norm, shape->vrtx, n2 * n1 - step_m);
        normVrtx3dv(shape->norm, shape->vrtx, n2 * n1 - step_m);
    }

    normVrtx3dv(shape->norm, shape->vrtx, i * n1 + j);
    normVrtx3dv(shape->norm, shape->vrtx, i * n1);
    normVrtx3dv(shape->norm, shape->vrtx, n2 * n1 - step_m);
    normVrtx3dv(shape->norm, shape->vrtx, n2 * n1 - step_m);
    glEnd();
}
