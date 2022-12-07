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
Node *first_table, *second_table, *first_stool, *first_, *second_stool, *ground;
double mat[4] = {0.5, 0.65, 0.5, 0.5};

Node *create_ground()
{
    Node *ground = init_node();
    Node *first_square = init_node(), *second_square = init_node(), *third_square = init_node(), *fourth_square = init_node();
    add_down(ground, first_square), add_down(first_square, second_square), add_next(first_square, third_square), add_down(third_square, fourth_square);
    G3Xcolor col1 = gris2, col2 = gris;
    material_and_instance(first_square, col1, mat, cube), material_and_instance(second_square, col1, mat, cube), material_and_instance(third_square, col2, mat, cube), material_and_instance(fourth_square, col2, mat, cube);
    homothetie3d(ground, 1., 1., 0.01);
    translation3d(first_square, 1., 1., 0.), translation3d(second_square, -2., -2., 0.), translation3d(third_square, 1., -1., 0.), translation3d(fourth_square, -2., 2., 0.);
    return ground;
}

Node *create_table_leg(double x, double y, double z)
{
    Node *legs = init_node(), *first_leg = init_node(), *second_leg = init_node(), *third_leg = init_node(), *fourth_leg = init_node();
    add_down(legs, first_leg), add_next(first_leg, second_leg), add_next(second_leg, third_leg), add_next(third_leg, fourth_leg);
    G3Xcolor col = gris3;
    material_and_instance(first_leg, col, mat, cylinder), material_and_instance(second_leg, col, mat, cylinder), material_and_instance(third_leg, col, mat, cylinder), material_and_instance(fourth_leg, col, mat, cylinder);
    homothetie3d(legs, 0.09, 0.09, 0.7);
    translation3d(first_leg, x, y, z), translation3d(second_leg, x, -y, z), translation3d(third_leg, -x, -y, z), translation3d(fourth_leg, -x, y, z);
    return legs;
}

Node *create_leg_stool(double x, double y, double z)
{
    Node *legs = init_node(), *first_leg = init_node(), *second_leg = init_node(), *third_leg = init_node(), *fourth_leg = init_node();
    add_down(legs, first_leg), add_next(first_leg, second_leg), add_next(second_leg, third_leg), add_next(third_leg, fourth_leg);
    G3Xcolor col = marron3;
    material_and_instance(first_leg, col, mat, cube), material_and_instance(second_leg, col, mat, cube), material_and_instance(third_leg, col, mat, cube), material_and_instance(fourth_leg, col, mat, cube);
    homothetie3d(legs, 0.09, 0.09, 0.7);
    translation3d(first_leg, x, y, z), translation3d(second_leg, x, -y, z), translation3d(third_leg, -x, -y, z), translation3d(fourth_leg, -x, y, z);
    return legs;
}

Node *create_table()
{
    Node *first_table = init_node(), *plat = init_node(), *legs = legs = create_table_leg(9., 5.5, -1.);
    add_down(first_table, plat), add_next(plat, legs);
    material_and_instance(plat, marron2, mat, cube);
    homothetie3d(plat, 1., 0.7, 0.1);
    translation3d(plat, 0., 0., 1.);
    return first_table;
}

Node *create_stool()
{
    Node *first_ = init_node(), *plat = init_node(), *legs = create_leg_stool(2.5, 2.5, -1.);
    add_down(first_, plat), add_next(plat, legs);
    material_and_instance(plat, marron1, mat, cylinder);
    homothetie3d(plat, 0.5, 0.5, 0.05), homothetie3d(legs, 0.75, 0.75, 0.9);
    translation3d(plat, 0., 0., 1.);
    return first_;
}

void init(void)
{
    sphere = create_sphere();
    torus = create_torus();
    cylinder = create_cylinder();
    cone = create_cone();
    cube = create_cube();
    first_table = create_table();
    second_table = create_table();
    first_ = create_stool();
    second_stool = create_stool();
    ground = create_ground();
    homothetie3d(first_table, 0.75, 0.75, 0.75), homothetie3d(second_table, 0.75, 0.75, 0.75), homothetie3d(first_, 0.75, 0.75, 0.6), homothetie3d(second_stool, 0.75, 0.75, 0.6);
    rotation3dZ(second_table, -0.5), rotation3dZ(second_stool, -0.5), rotation3dZ(first_table, 0.7);
    rotation3dX(second_stool, 3.1);
    translation3d(first_table, 0., -2., 1.41), translation3d(second_table, 0.6, 2.1, 1.41), translation3d(first_, -1., -1., 1.29), translation3d(second_stool, 0.5, -2., -2.2);
}

void draw(void)
{
    draw_node(ground), draw_node(first_table), draw_node(second_table), draw_node(first_), draw_node(second_stool);
}

void anim(void)
{
    free_node(first_), free_node(second_stool), free_node(first_table), free_node(second_table), free_node(ground);
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
