//
//  main.cpp
//  CMSC 405 Final
//
//  Created by Glory Kim on 12/16/16.
//  Copyright © 2016 Glory Kim. All rights reserved.
//

#include "classes.h"
#define RENDERING_TRAIL 1

list<Particle *> particles;
int frames;

//smaller than one?
list<Sphere *> spheres;
float SPHERES_PER_FRAME;
float GRAVITY_PLANET;
int SPHERE_LIFE;
int NUMBER_OF_PARTICLES;
int PARTICLE_LIFE;
int renderingStyleType = 0;

GLboolean clearScreen = true;

void initData(void) {
    frames = 0;
    SPHERES_PER_FRAME = 0.05;
    GRAVITY_PLANET = 0.05;
    SPHERE_LIFE = 150;
    NUMBER_OF_PARTICLES = 150;
    PARTICLE_LIFE = 100;
}

void animate(void)
{
    frames++;
    if(SPHERES_PER_FRAME > myRandom())
        spheres.push_back(new Sphere());
    auto spheres_iterator = spheres.begin();
    while(spheres_iterator != spheres.end()) {
        ((*spheres_iterator)->center).life--;
        if(((*spheres_iterator)->center).life <= 0) {
            particles.splice(particles.end(), (*spheres_iterator)->explode());
            delete *spheres_iterator;
            spheres_iterator = spheres.erase(spheres_iterator);
        } else {
            (*spheres_iterator)->move();
            spheres_iterator++;
        }
    }
    auto particles_iterator = particles.begin();
    while(particles_iterator != particles.end()) {
        (*particles_iterator)->life--;
        if((*particles_iterator)->life <= 0) {
            delete *particles_iterator;
            particles_iterator = particles.erase(particles_iterator);
        } else {
            (*particles_iterator)->move();
            particles_iterator++;
        }
    }
    glutPostRedisplay();
}



void display()
{
 
    glLoadIdentity();
    gluLookAt(0.0, 100.0, 1000.0, 0.0, 500.0, 0.0, 0.0, 1.0, 0.0);
    
    // Clear the screen
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glPointSize(1.0f);
    glLineWidth(1.0f);
       for(auto it = spheres.begin(); it != spheres.end(); it++) {
        glPushMatrix();
        glTranslatef(((*it)->center).location.x, ((*it)->center).location.y, ((*it)->center).location.z);
        glColor3f(((*it)->center).color.x, ((*it)->center).color.y, ((*it)->center).color.z);
        glutSolidSphere((*it)->radius, 8, 8);
        glPopMatrix();
    }
    switch(renderingStyleType){
        case RENDERING_TRAIL:
            glBegin(GL_LINES);
            for(auto it = particles.begin(); it != particles.end(); it++) {
                glColor3f((*it)->color.x, (*it)->color.y, (*it)->color.z);
                glVertex3f((*it)->location.x, (*it)->location.y, (*it)->location.z);
                glVertex3f((*it)->previousLocation.x, (*it)->previousLocation.y, (*it)->previousLocation.z);
            }
            glEnd();
            break;
        default:
            glBegin(GL_POINTS);
            for(auto it = particles.begin(); it != particles.end(); it++) {
                glColor3f((*it)->color.x, (*it)->color.y, (*it)->color.z);
                glVertex3f((*it)->location.x, (*it)->location.y, (*it)->location.z);
            }
            glEnd();
            
    }
    
    glAccum(GL_ACCUM, 0.9f);
    
    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y)
{
    //Exit the program
    if(key == 27)
        exit(0);
   
    //Restart Animation after Left Button Mouse Click
    if(key == 32)
        glutIdleFunc(animate);
    
    glutPostRedisplay();
}

void mouseFcn(GLint button, GLint action, GLint x, GLint y)
{
    
    switch (button) {
            
        //  Stop the animation
        case GLUT_LEFT_BUTTON:
            if (action == GLUT_DOWN)
                glutIdleFunc(NULL);
            break;
        default:
            break;
    }
}


void reshape(int width, int height)
{
    glClearColor(0.9, 0.9, 0.9, 1.0);
    glViewport(0, 0, (GLsizei)width, (GLsizei)height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (GLfloat)width / (GLfloat)height, 1.0, 10000.0);
    glMatrixMode(GL_MODELVIEW);
}


void change_gravity(int value) {
    GRAVITY_PLANET = value*0.025;
}

void change_number_of_spheres(int value) {
    SPHERES_PER_FRAME = value/50.0;
}

void change_number_of_particles(int value) {
    NUMBER_OF_PARTICLES = value;
}

void change_sphere_life(int value) {
    SPHERE_LIFE = value;
}

void change_particle_life(int value) {
    PARTICLE_LIFE = value;
}

void change_rendering_style_type(int value) {
    renderingStyleType = value;
}

//Graphics and Menu
void initGraphics(int argc, char *argv[])
{
    initData();
    glutInit(&argc, argv);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutInitDisplayMode(GLUT_DOUBLE);
    glutCreateWindow("Glory Kim -Fireworks  ");
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutReshapeFunc(reshape);
    glutIdleFunc(animate);
    
    auto gravity_planet_submenu = glutCreateMenu(change_gravity);
    glutAddMenuEntry("No Gravity", 0);
    glutAddMenuEntry("The moon", 1);
    glutAddMenuEntry("Earth", 2);
    glutAddMenuEntry("Jupiter", 3);
    glutAddMenuEntry("The Sun", 7);
    auto number_of_spheres_submenu = glutCreateMenu(change_number_of_spheres);
    glutAddMenuEntry("Fewest", 1);
    glutAddMenuEntry("Fewer", 2);
    glutAddMenuEntry("Normal", 3);
    glutAddMenuEntry("More", 10);
    glutAddMenuEntry("Grand Finale", 25);
    auto number_of_particles_submenu = glutCreateMenu(change_number_of_particles);
    glutAddMenuEntry("Fewest", 50);
    glutAddMenuEntry("Fewer", 100);
    glutAddMenuEntry("Normal", 150);
    glutAddMenuEntry("More", 200);
    glutAddMenuEntry("WOW", 500);
    auto sphere_life_submenu = glutCreateMenu(change_sphere_life);
    glutAddMenuEntry("Shortest", 50);
    glutAddMenuEntry("Shorter", 100);
    glutAddMenuEntry("Normal", 150);
    glutAddMenuEntry("Longer", 200);
    glutAddMenuEntry("Longest", 250);
    auto particle_life_submenu = glutCreateMenu(change_particle_life);
    glutAddMenuEntry("Shortest", 50);
    glutAddMenuEntry("Shorter", 100);
    glutAddMenuEntry("Normal", 150);
    glutAddMenuEntry("Longer", 200);
    glutAddMenuEntry("Longest", 250);
    auto rendering_style_type_submenu = glutCreateMenu(change_rendering_style_type);
    glutAddMenuEntry("No Trails", 0);
    glutAddMenuEntry("Trails", 1);
    auto main_menu = glutCreateMenu(NULL);
    glutAddSubMenu("Gravity", gravity_planet_submenu);
    glutAddSubMenu("Number of Spheres", number_of_spheres_submenu);
    glutAddSubMenu("Number of Particles", number_of_particles_submenu);
    glutAddSubMenu("Lifetime of Spheres", sphere_life_submenu);
    glutAddSubMenu("Lifetime of Particles", particle_life_submenu);
    glutAddSubMenu("Rendering Style Type", rendering_style_type_submenu);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

// Main
int main(int argc, char *argv[])
{
    printf("Hello, Enjoy the show!\n");
    printf("Left Mouse Click: Stop Animation\n");
    printf("Spacebar: Start Animation\n");
    printf("Right Mouse Click: Menu Options\n");
    printf("Press 'esc' to exit the program\n");
    printf("\nSet up a grand finale by selecting the following:\n     Gravity: Earth\n     Number of Spheres: Grand Finale\n     Number of Particles: Normal\n     Lifetime of Spheres/Particles: Normal\n     Rendering Style Type: Trails\n\nHave fun! ^.^\n");
    
    srand(time(NULL));
    initGraphics(argc, argv);
    glEnable(GL_POINT_SMOOTH);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouseFcn);
    glutMainLoop();
    return 0;
}
