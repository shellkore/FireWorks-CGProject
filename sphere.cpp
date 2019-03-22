//
//  sphere.cpp
//  CMSC 405 Final
//
//  Created by Glory Kim on 12/16/16.
//  Copyright © 2016 Glory Kim. All rights reserved.
//

#include <stdio.h>

#include "classes.h"

const float defaultRadius = 5;
const float XRange = 100;

Sphere::Sphere() {
    set(&center.location, (myRandom() - 0.5)*XRange, 0.0, 0.0);
    center.speed.x = (myRandom() - 0.5)*5;
    center.speed.y = (myRandom() + 0.5)*7.5;
    center.speed.z = (myRandom() - 0.5)*5;
    set(&center.acceleration, 0, 0-GRAVITY_PLANET, 0);
    radius = (myRandom() + 0.5)*defaultRadius;
    center.life = int((myRandom() + 0.5)*SPHERE_LIFE);
    number_of_particles = int((myRandom() + 0.5)*NUMBER_OF_PARTICLES);
    set(&(center.color), myRandom(), myRandom(), myRandom());
}

void Sphere::move() {
    center.move();
}

list<Particle *> Sphere::explode() {
    list<Particle *> toReturn;
    for(int i=0;i<number_of_particles;i++)
        toReturn.push_back(new Particle(this));
    return toReturn;
}
