//
//  math.cpp
//  CMSC 405 Final
//
//  Created by Glory Kim on 12/16/16.
//  Copyright © 2016 Glory Kim. All rights reserved.
//

#include <stdio.h>

#include "classes.h"

void add(Triple *a, Triple *b) {
    a->x+=b->x;
    a->y+=b->y;
    a->z+=b->z;
}

void set(Triple* t, float x, float y, float z) {
    t->x = x;
    t->y = y;
    t->z = z;
}


double myRandom()
//Return random double within range [0,1]
{
    return (rand()/(double)RAND_MAX);
}


