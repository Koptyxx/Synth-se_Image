/*!===============================================================
  S.Ghamri - Universite Gustave Eiffel - samy.ghamri@univ-eiffel.fr
  X.Osaj - Universite Gustave Eiffel - xhavit.osaj@univ-eiffel.fr
                         Shape Interface
                           01/05/2022
  ================================================================!*/

#ifndef _OBJECT_
#define _OBJECT_

#include <g3x.h>

#define MAXRES 200

typedef struct _shape_
{
  size_t n1, n2, n3; /* valeurs d’échantillonnage max - la plupart du temps 2 suffisent */
  G3Xpoint *vrtx;    /* tableau des vertex - spécifique d’une forme */
  G3Xvector *norm;   /* tableau des normales - spécifique d’une forme */
  /* méthode d’affichage - spécifique d’une forme */
  void (*draw_points)(struct _shape_ *, G3Xvector scale_factor, double dcam); /* mode GL_POINTS */
  void (*draw_faces)(struct _shape_ *, G3Xvector scale_factor, double dcam);  /* mode GL_TRIANGLES ou GL_QUADS */
} Shape;

typedef struct _node_
{
  struct _node_ *down, *next; /* chaînage */
  G3Xhmat *Md;                /* matrice de transformation directe */
  G3Xcolor col;               /* couleur RGBA */
  double mat[4];              /* 4 réels dans [0,1] : (ambi, diff, spec, shine) */
  G3Xvector *scale_factor;    /* facteurs d’échelles locaux en x,y,z, */
  Shape *instance;            /* une éventuelle instance d’objet */
} Node, *SceneTree;

Shape *init_cone();
Shape *create_cone();
Node *init_node();
void cone_points(Shape *shape, G3Xvector scale_factor, double dcam);
void update_scale_factor(Node *node, G3Xvector father_scale_factor);
void cone_faces(Shape *shape, G3Xvector scale_factor, double dcam);
void translation3d(Node *node, double x, double y, double z);
Shape *init_cube();
Shape *create_cube();
void cube_points(Shape *shape, G3Xvector scale_factor, double dcam);
void cube_faces(Shape *shape, G3Xvector scale_factor, double dcam);
Shape *init_cylinder();
Shape *create_cylinder();
void cylinder_points(Shape *shape, G3Xvector scale_factor, double dcam);
void cylinder_faces(Shape *shape, G3Xvector scale_factor, double dcam);
Shape *init_sphere();
Shape *create_sphere();
void sphere_points(Shape *shape, G3Xvector scale_factor, double dcam);
void sphere_faces(Shape *shape, G3Xvector scale_factor, double dcam);
Shape *init_torus();
Shape *create_torus();
void torus_points(Shape *shape, G3Xvector scale_factor, double dcam);
void torus_faces(Shape *shape, G3Xvector scale_factor, double dcam);
void normVrtx3dv(G3Xvector *N, G3Xpoint *P, int i);
void free_shape(Shape *shape);
void rotation3dX(Node *node, double angle_x);
void rotation3dY(Node *node, double angle_y);
void rotation3dZ(Node *node, double angle_z);
void homothetie3d(Node *node, double x, double y, double z);
void material_and_instance(Node *node, G3Xcolor col, double mat[], Shape *shape);
void draw_node(Node *node);
void free_node(Node *node);
double compute_cam_node_distance(G3Xhmat Md);
void add_down(Node *node1, Node *node2);
void add_next(Node *node1, Node *node2);

#endif