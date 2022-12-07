/*!===============================================================
  S.Ghamri - Universite Gustave Eiffel - samy.ghamri@univ-eiffel.fr
  X.Osaj - Universite Gustave Eiffel - xhavit.osaj@univ-eiffel.fr
                             Scene
                           01/05/2022
  ================================================================!*/

#include "../include/shape.h"

static int WIDTH = 512, HEIGHT = 512;
static G3Xcolor marron1 = {0.30, 0.20, 0.10, 0.00};
static G3Xcolor marron2 = {0.50, 0.40, 0.20, 0.00};
static G3Xcolor marron3 = {0.4, 0.3, 0.2, 0.00};
static G3Xcolor rouge = {1.00, 0.00, 0.00, 0.00};
static G3Xcolor vert = {0.00, 1.00, 0.00, 0.00};
static G3Xcolor bleu = {0.00, 0.00, 1.00, 0.00};
static G3Xcolor jaune = {1.00, 1.00, 0.00, 0.00};
static G3Xcolor cyan = {0.00, 1.00, 1.00, 0.00};
static G3Xcolor orange = {0.75, 0.50, 0.00, 0.00};
static G3Xcolor vert2 = {0.50, 0.75, 0.00, 0.00};
static G3Xcolor metal = {0.60, 0.75, 0.95, 0.00};
static G3Xcolor glass = {0.90, 0.90, 1.00, 0.00};
static G3Xcolor gris = {0.5, 0.5, 0.5, 0.00};
static G3Xcolor gris2 = {0.3, 0.3, 0.3, 0.00};
static G3Xcolor gris3 = {0.45, 0.5, 0.5, 0.00};
Shape *sphere, *torus, *cylinder, *cone, *cube;
Node *c;
double mat[4] = {0.5, 0.65, 0.5, 0.5};

Node *create_cone_example(double x, double y, double z)
{
    Node *cu = init_node();
    G3Xcolor col = rouge;
    material_and_instance(cu, col, mat, cone);
    homothetie3d(cu, 1., 1., 1.);
    return cu;
}

void init(void)
{
    sphere = create_sphere();
    torus = create_torus();
    cylinder = create_cylinder();
    cone = create_cone();
    cube = create_cube();
    c = create_cone_example(1., 1., 1.);
}

void draw(void)
{
    draw_node(c);
}

void anim(void)
{
    free_shape(sphere), free_shape(torus), free_shape(cylinder), free_shape(cone), free_shape(cube);
}

int main(int argc, char **argv)
{
    g3x_InitWindow(argv[0], WIDTH, HEIGHT);
    g3x_SetInitFunction(init);
    g3x_SetDrawFunction(draw);
    g3x_SetAnimFunction(anim);
    return g3x_MainStart();
}