//
//  classes.h
//  CMSC405Final
//
//  Created by Glory Kim on 12/16/16.
//  Copyright © 2016 Glory Kim. All rights reserved.
//

#ifndef classes_h
#define classes_h

//#include <GLUT/glut.h>
#include <GL/glut.h>
#include <iostream>
#include <stdio.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <list>

using namespace std;

class Triple {
public:
    float x, y, z;
};

class Sphere;

class Particle {
public:
    Triple previousLocation;
    Triple location, speed, acceleration;
    Triple color;
    int life;
    void move();
    Particle() {};
    Particle(Sphere *);
};

class Sphere {
public:
    Particle center;
    float radius;
    int number_of_particles;
    Sphere();
    void move();
    list<Particle *> explode();
};

//Math
double myRandom();
void add(Triple*, Triple *);
void set(Triple*, float, float, float);

extern float SPHERES_PER_FRAME;
extern float GRAVITY_PLANET;
extern int SPHERE_LIFE;
extern int NUMBER_OF_PARTICLES;
extern int PARTICLE_LIFE;




#endif /* classes_h */
