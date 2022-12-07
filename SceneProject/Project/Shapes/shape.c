/*!===============================================================
  S.Ghamri - Universite Gustave Eiffel - samy.ghamri@univ-eiffel.fr
  X.Osaj - Universite Gustave Eiffel - xhavit.osaj@univ-eiffel.fr
                             Shape
                           01/05/2022
  ================================================================!*/

#include "../include/shape.h"

Node *init_node()
{
    Node *node;
    if (NULL == (node = malloc(sizeof(Node))))
        return NULL;
    node->down = NULL, node->next = NULL, node->instance = NULL;
    if (NULL == (node->Md = malloc(sizeof(G3Xhmat))))
        return NULL;
    if (NULL == (node->scale_factor = malloc(sizeof(G3Xvector))))
        return NULL;
    *(node->Md) = g3x_Identity();
    *(node->scale_factor) = g3x_Mat_x_Vector(*(node->Md), (G3Xvector){1., 1., 1.});
    return node;
}

void update_scale_factor(Node *node, G3Xvector father_scale_factor)
{
    *(node->scale_factor) = g3x_Mat_x_Vector(*(node->Md), father_scale_factor);
    if (node->down != NULL)
    {
        update_scale_factor(node->down, *(node->scale_factor));
    }
    if (node->next != NULL)
    {
        update_scale_factor(node->next, father_scale_factor);
    }
}

void translation3d(Node *node, double x, double y, double z)
{
    *(node->Md) = g3x_Mat_x_Mat(*(node->Md), g3x_Translation3d(x, y, z));
}

void normVrtx3dv(G3Xvector *N, G3Xpoint *P, int i)
{
    g3x_Normal3dv(N[i]);
    g3x_Vertex3dv(P[i]);
}

void free_shape(Shape *shape)
{
    free(shape->vrtx);
    free(shape->norm);
    free(shape);
}

void rotation3dX(Node *node, double angle_x)
{
    *(node->Md) = g3x_Mat_x_Mat(*(node->Md), g3x_RotationX(angle_x));
}

void rotation3dY(Node *node, double angle_y)
{
    *(node->Md) = g3x_Mat_x_Mat(*(node->Md), g3x_RotationY(angle_y));
}

void rotation3dZ(Node *node, double angle_z)
{
    *(node->Md) = g3x_Mat_x_Mat(*(node->Md), g3x_RotationZ(angle_z));
}

void homothetie3d(Node *node, double x, double y, double z)
{
    *(node->Md) = g3x_Mat_x_Mat(*(node->Md), g3x_Homothetie3d(x, y, z));
    update_scale_factor(node, *(node->scale_factor));
}

void material_and_instance(Node *node, G3Xcolor col, double mat[], Shape *shape)
{
    node->col = col;
    node->mat[0] = mat[0];
    node->mat[1] = mat[1];
    node->mat[2] = mat[2];
    node->mat[3] = mat[3];
    node->instance = shape;
}

void draw_node(Node *node)
{
    g3x_Material(node->col, node->mat[0], node->mat[1], node->mat[2], node->mat[3], 1.);
    glPushMatrix();
    glMultMatrixd(node->Md->m);
    if (node->instance != NULL)
        node->instance->draw_faces(node->instance, *(node->scale_factor), compute_cam_node_distance(*(node->Md)));
    if (node->down != NULL)
    {
        draw_node(node->down);
    }
    glPopMatrix();
    if (node->next != NULL)
    {
        draw_node(node->next);
    }
}

void free_node(Node *node)
{
    if (node->instance)
        free_shape(node->instance);
    if (node->down)
        free_node(node->down);
    if (node->next)
        free_node(node->next);
    free(node->Md);
    free(node->scale_factor);
    free(node);
}

double compute_cam_node_distance(G3Xhmat Md)
{
    G3Xpoint node_pos = (G3Xpoint){Md.m[12], Md.m[13], Md.m[14]}, cam_pos = *(g3x_GetCamera()->pos);
    return 4. / (sqrt(pow((node_pos.x - cam_pos.x), 2.) + pow((node_pos.y - cam_pos.y), 2.) + pow((node_pos.z - cam_pos.z), 2.)) / 5.);
}

void add_down(Node *node1, Node *node2)
{
    node1->down = node2;
}

void add_next(Node *node1, Node *node2)
{
    node1->next = node2;
}
