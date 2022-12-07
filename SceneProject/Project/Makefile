#/*!===============================================================
#  S.Ghamri - Universite Gustave Eiffel - samy.ghamri@univ-eiffel.fr
#  X.Osaj - Universite Gustave Eiffel - xhavit.osaj@univ-eiffel.fr
#                            Makefile
#                           01/05/2022
#  ================================================================!*/

CC = gcc

CFLAGS = -Wall -Wno-comment -W -std=c17
LFLAGS = $(libG3X) $(DBG_LIB)
INCLUDE = -I../INCLUDE $(incG3X)
OBJ1 = obj/example1.o obj/sphere.o obj/torus.o obj/cylinder.o obj/cone.o obj/cube.o obj/shape.o
OBJ2 = obj/example2.o obj/sphere.o obj/torus.o obj/cylinder.o obj/cone.o obj/cube.o obj/shape.o
OBJ3 = obj/cube_example.o obj/sphere.o obj/torus.o obj/cylinder.o obj/cone.o obj/cube.o obj/shape.o
OBJ4 = obj/cone_example.o obj/sphere.o obj/torus.o obj/cylinder.o obj/cone.o obj/cube.o obj/shape.o
OBJ5 = obj/torus_example.o obj/sphere.o obj/torus.o obj/cylinder.o obj/cone.o obj/cube.o obj/shape.o
OBJ6 = obj/cylinder_example.o obj/sphere.o obj/torus.o obj/cylinder.o obj/cone.o obj/cube.o obj/shape.o
OBJ7 = obj/sphere_example.o obj/sphere.o obj/torus.o obj/cylinder.o obj/cone.o obj/cube.o obj/shape.o

ALL : example1 example2 cube cone torus cylinder sphere

obj/sphere.o : Shapes/sphere.c include/shape.h

obj/cylindre.o : Shapes/cylindre.c include/shape.h

obj/torus.o : Shapes/torus.c include/shape.h

obj/cube.o : Shapes/cube.c include/shape.h

obj/cone.o : Shapes/cone.c include/shape.h

obj/example1.o : Scenes/example1.c include/shape.h

obj/example2.o : Scenes/example2.c include/shape.h

obj/cube_example.o : Scenes/cube_example.c include/shape.h

obj/cone_example.o : Scenes/cone_example.c include/shape.h

obj/torus_example.o : Scenes/torus_example.c include/shape.h

obj/cylinder_example.o : Scenes/cylinder_example.c include/shape.h

obj/sphere_example.o : Scenes/sphere_example.c include/shape.h

example1: $(OBJ1)
	$(CC) $(INCLUDE) -o $@ $^ $(LFLAGS) $(CFLAGS)
	
example2: $(OBJ2)
	$(CC) $(INCLUDE) -o $@ $^ $(LFLAGS) $(CFLAGS)

cube: $(OBJ3)
	$(CC) $(INCLUDE) -o $@ $^ $(LFLAGS) $(CFLAGS)

cone: $(OBJ4)
	$(CC) $(INCLUDE) -o $@ $^ $(LFLAGS) $(CFLAGS)

torus: $(OBJ5)
	$(CC) $(INCLUDE) -o $@ $^ $(LFLAGS) $(CFLAGS)

cylinder: $(OBJ6)
	$(CC) $(INCLUDE) -o $@ $^ $(LFLAGS) $(CFLAGS)

sphere: $(OBJ7)
	$(CC) $(INCLUDE) -o $@ $^ $(LFLAGS) $(CFLAGS)

obj/%.o: Shapes/%.c include/shape.h
	$(CC) $(INCLUDE) -o $@ -c $< $(LFLAGS) $(CFLAGS)

obj/%.o: Scenes/%.c include/shape.h
	$(CC) $(INCLUDE) -o $@ -c $< $(LFLAGS) $(CFLAGS)
	
clean:
	rm -f obj/*.o
	rm example1 example2 cube cone torus cylinder sphere
