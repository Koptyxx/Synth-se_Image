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
static G3Xcolor gris4 = {0.7, 0.7, 0.7, 0.00};
Shape *sphere, *torus, *cylinder, *cone, *cube;
Node *scene;
double mat[4] = {0.5, 0.65, 0.5, 0.5};

Node *create_spinning()
{
    Node *spinning = init_node(), *s = init_node(), *t = init_node(), *cyl = init_node();
    add_down(spinning, s), add_next(s, t), add_next(t, cyl);
    G3Xcolor col = gris;
    material_and_instance(s, col, mat, sphere), material_and_instance(t, col, mat, torus), material_and_instance(cyl, col, mat, cylinder);
    homothetie3d(cyl, 0.05, 0.05, 1.), homothetie3d(s, 0.3, 0.3, 0.3), homothetie3d(t, 0.3, 0.3, 0.2);
    translation3d(s, 0., 0., -1.3), translation3d(t, 0., 0., -2), translation3d(spinning, 0., 0., 1.);
    return spinning;
}

Node *create_chessboard()
{
    Node *chessboard = init_node(), *first_square = init_node(), *second_square = init_node(), *third_square = init_node(), *fourth_square = init_node();
    add_down(chessboard, first_square), add_down(first_square, second_square), add_next(first_square, third_square), add_down(third_square, fourth_square);
    G3Xcolor col1 = (G3Xcolor){0.1, 0.1, 0.1, 1.}, col2 = gris;
    material_and_instance(first_square, col1, mat, cube), material_and_instance(second_square, col1, mat, cube), material_and_instance(third_square, col2, mat, cube), material_and_instance(fourth_square, col2, mat, cube);
    homothetie3d(chessboard, 0.4, 0.4, 0.01);
    translation3d(first_square, 1., 1., 0.), translation3d(second_square, -2., -2., 0.), translation3d(third_square, 1., -1., 0.), translation3d(fourth_square, -2., 2., 0.);
    return chessboard;
}

Node *create_ground()
{
    Node *ground = init_node();
    Node *chess1 = create_chessboard(), *chess2 = create_chessboard(), *chess3 = create_chessboard(), *chess4 = create_chessboard(), *chess5 = create_chessboard(), *chess6 = create_chessboard(), *chess7 = create_chessboard();
    add_down(ground, chess1), add_next(chess1, chess2), add_next(chess2, chess3), add_next(chess3, chess4), add_next(chess4, chess5), add_next(chess5, chess6), add_next(chess6, chess7);
    translation3d(chess1, 12., 0., 0.), translation3d(chess2, 8., 0., 0.), translation3d(chess3, 4., 0., 0.), translation3d(chess4, 0., 0., 0.), translation3d(chess5, -4., 0., 0.), translation3d(chess6, -8., 0., 0.), translation3d(chess7, -12., 0., 0.), translation3d(ground, 0., 0., -1.44);
    return ground;
}

Node *create_tower()
{
    Node *tower = init_node(), *cub = init_node(), *t = init_node(), *cyl = init_node(), *spinning = create_spinning();
    add_down(tower, cyl), add_next(cyl, t), add_next(t, cub), add_next(cub, spinning);
    G3Xcolor col = gris;
    material_and_instance(t, col, mat, torus), material_and_instance(cyl, col, mat, cylinder), material_and_instance(cub, col, mat, cube);
    homothetie3d(cyl, 0.150, 0.150, 1.), homothetie3d(cub, 0.4, 0.4, 0.1), homothetie3d(t, 0.125, 0.125, 0.175), homothetie3d(spinning, 0.5, 0.5, 0.5);
    rotation3dX(spinning, 15 * (PI / 180)), rotation3dY(spinning, 15 * (PI / 180));
    translation3d(cub, 0., 0., -11.), translation3d(t, 0., 0., -6.), translation3d(spinning, 0., 0., 0.85), translation3d(tower, 0., 0., -0.25);
    return tower;
}

Node *create_towers()
{
    Node *towers = init_node(), *tower1 = create_tower(), *tower2 = create_tower(), *tower3 = create_tower(), *tower4 = create_tower();
    add_down(towers, tower1), add_next(tower1, tower2), add_next(tower2, tower3), add_next(tower3, tower4);
    rotation3dZ(tower2, 90 * (PI / 180)), rotation3dZ(tower3, 180 * (PI / 180)), rotation3dZ(tower4, 270 * (PI / 180));
    translation3d(tower1, 0.4, 1.2, 0.), translation3d(tower2, 1.2, 0.4, 0.), translation3d(tower3, 0.4, 1.2, 0.), translation3d(tower4, 1.2, 0.4, 0.);
    return towers;
}

Node *create_scene()
{
    Node *scene = init_node();
    Node *ground = create_ground();
    Node *towers1 = create_towers(), *towers2 = create_towers(), *towers3 = create_towers(), *towers4 = create_towers(), *towers5 = create_towers(), *towers6 = create_towers(), *towers7 = create_towers();
    add_down(scene, ground), add_next(ground, towers1), add_next(towers1, towers2), add_next(towers2, towers3), add_next(towers3, towers4), add_next(towers4, towers5), add_next(towers5, towers6), add_next(towers6, towers7);
    translation3d(towers1, 4.8, 0., 0.), translation3d(towers2, 3.2, 0., 0.), translation3d(towers3, 1.6, 0., 0.), translation3d(towers4, 0.0, 0., 0.), translation3d(towers5, -1.6, 0., 0.), translation3d(towers6, -3.2, 0., 0.), translation3d(towers7, -4.8, 0., 0.);
    return scene;
}

void init(void)
{
    cylinder = create_cylinder(), cone = create_cone(), cube = create_cube(), sphere = create_sphere(), torus = create_torus();
    scene = create_scene();
}

void draw(void)
{
    draw_node(scene);
}

void quit(void)
{
    free_node(scene);
    free_shape(sphere), free_shape(torus), free_shape(cylinder), free_shape(cone), free_shape(cube);
}

int main(int argc, char **argv)
{
    g3x_InitWindow(argv[0], WIDTH, HEIGHT);
    g3x_SetInitFunction(init);
    g3x_SetDrawFunction(draw);
    g3x_SetExitFunction(quit);
    return g3x_MainStart();
}