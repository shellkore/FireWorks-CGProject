//
//  particle.cpp
//  CMSC 405 Final
//
//  Created by Glory Kim on 12/16/16.
//  Copyright © 2016 Glory Kim. All rights reserved.
//

#include <stdio.h>

#include "classes.h"

Particle::Particle(Sphere *s) {
    location.x = s->center.location.x + 2*(myRandom() - 0.5)*s->radius;
    location.y = s->center.location.y + 2*(myRandom() - 0.5)*s->radius;
    location.z = s->center.location.z + 2*(myRandom() - 0.5)*s->radius;
    speed.x = (myRandom() - 0.5)*5;
    speed.y = (myRandom() - 0.5)*5;
    speed.z = (myRandom() - 0.5)*5;
    set(&color, s->center.color.x, s->center.color.y, s->center.color.z);
    add(&speed, &(s->center.speed));
    set(&acceleration, 0, 0-GRAVITY_PLANET, 0);
    add(&acceleration, &(s->center.acceleration));
    life = int((myRandom() + 0.5)*PARTICLE_LIFE);
}

void Particle::move() {
    previousLocation = location;
    add(&speed, &acceleration);
    add(&location, &speed);
}
