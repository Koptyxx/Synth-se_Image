/*!===============================================================
  S.Ghamri - Universite Gustave Eiffel - samy.ghamri@univ-eiffel.fr
  X.Osaj - Universite Gustave Eiffel - xhavit.osaj@univ-eiffel.fr
                             Torus
                           01/05/2022
  ================================================================!*/

#include "../include/shape.h"
#include <math.h>

void torus_points(Shape *shape, G3Xvector scale_factor, double dcam)
{
    int step_m = 1. / (((scale_factor.x * dcam) + (scale_factor.y * dcam)) / 2.);
    step_m = MAX(1, step_m);

    glPointSize(1);
    glBegin(GL_POINTS);
    for (int i = 0; i < (int)shape->n1 * (int)shape->n2 - step_m; i += step_m)
    {
        normVrtx3dv(shape->norm, shape->vrtx, i);
    }
    glEnd();
}

Shape *init_torus()
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
    shape->draw_points = torus_points, shape->draw_faces = torus_faces;
    return shape;
}

Shape *create_torus()
{
    Shape *shape;
    shape = init_torus();
    if (NULL == shape)
        return NULL;
    int i, j, n2 = shape->n1, n1 = shape->n2;
    double r = 1., s = 0.5, teta = (2. * PI) / (double)n1, phi = (2. * PI) / (double)n2;
    for (i = 0; i < n2 - 1; i++)
    {
        double NRp = cos((double)i * phi), NZp = sin((double)i * phi), Rp = r + s * NRp, Zp = s * NZp;
        for (j = 0; j < n1; j++)
        {
            double x = Rp * cos((double)j * teta), y = Rp * sin((double)j * teta), z = Zp, nx = NRp * cos((double)j * teta), ny = NRp * sin((double)j * teta), nz = NZp;
            shape->vrtx[i * n1 + j] = (G3Xpoint){x, y, z};
            shape->norm[i * n1 + j] = (G3Xvector){nx, ny, nz};
        }
    }
    return shape;
}

void torus_faces(Shape *shape, G3Xvector scale_factor, double dcam)
{
    int i, j, n1 = shape->n1, n2 = shape->n2;
    int step_m = 1. / ((scale_factor.x * dcam) + (scale_factor.y * dcam)) / 2.;
    step_m = MAX(1, step_m);
    int step_p = 1. / (scale_factor.z * dcam);
    step_p = MAX(1, step_p);
    glPointSize(1);
    glBegin(GL_QUADS);
    for (i = 0; i < n1 - step_m - 1; i += step_m)
    {
        for (j = 0; j < n2 - step_p - 1; j += step_p)
        {
            normVrtx3dv(shape->norm, shape->vrtx, (i + step_m) * n2 + j + step_p);
            normVrtx3dv(shape->norm, shape->vrtx, (i + step_m) * n2 + j);
            normVrtx3dv(shape->norm, shape->vrtx, i * n2 + j);
            normVrtx3dv(shape->norm, shape->vrtx, i * n2 + j + step_p);
        }
        normVrtx3dv(shape->norm, shape->vrtx, (i + step_m) * n2);
        normVrtx3dv(shape->norm, shape->vrtx, (i + step_m) * n2 + j);
        normVrtx3dv(shape->norm, shape->vrtx, i * n2 + j);
        normVrtx3dv(shape->norm, shape->vrtx, i * n2);
    }
    for (j = 0; j < n2 - step_p - 1; j += step_p)
    {
        normVrtx3dv(shape->norm, shape->vrtx, i * n2 + j);
        normVrtx3dv(shape->norm, shape->vrtx, i * n2 + j + step_p);
        normVrtx3dv(shape->norm, shape->vrtx, j + step_p);
        normVrtx3dv(shape->norm, shape->vrtx, j);
    }
    normVrtx3dv(shape->norm, shape->vrtx, i * n2 + j);
    normVrtx3dv(shape->norm, shape->vrtx, i * n2);
    normVrtx3dv(shape->norm, shape->vrtx, 0);
    normVrtx3dv(shape->norm, shape->vrtx, j);
    glEnd();
}
