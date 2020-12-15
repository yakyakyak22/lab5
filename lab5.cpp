#include <iostream> 

#include <windows.h> 

#include <GL/glu.h> 

#include <GL/glut.h> 

#include "stb_image.h" 





GLint Width = 1000, Height = 1000;

double angPhi = 0, angOm = 0;



GLfloat vertices[][3] = {

{-1.0,-1.0,-1.0},

{1.0,-1.0,-1.0},

{1.0,1.0,-1.0},

{-1.0,1.0,-1.0},

{-1.0,-1.0,1.0},

{1.0,-1.0,1.0},

{1.0,1.0,1.0},

{-1.0,1.0,1.0}

};

void polygon(int a, int b, int c, int d, unsigned char* data, int width, int height, int nrChannels)

{

    glRasterPos3d(0.0, 0.0, 0.0);

    glPixelZoom(1, 1);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    static GLuint texName;

    gluBuild2DMipmaps(GL_TEXTURE_2D, 3,

        width,

        height,

        GL_RGB, GL_UNSIGNED_BYTE,

        data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glColor3d(1, 1, 1);

    glBegin(GL_POLYGON);

    glTexCoord2d(1, 1); glVertex3fv(vertices[a]);

    glTexCoord2d(1, 0); glVertex3fv(vertices[b]);

    glTexCoord2d(0, 0); glVertex3fv(vertices[c]);

    glTexCoord2d(0, 1); glVertex3fv(vertices[d]);

    glEnd();

}





void colorcube()

{

    int width, height, nrChannels;

    int width2, height2, nrChannels2;

    int width3, height3, nrChannels3;

    int width4, height4, nrChannels4;

    int width5, height5, nrChannels5;

    int width6, height6, nrChannels6;

    unsigned char* data = stbi_load("1.jpg", &width, &height, &nrChannels, 0);

    unsigned char* data2 = stbi_load("2.jpg", &width2, &height2, &nrChannels2, 0);

    unsigned char* data3 = stbi_load("3.jpg", &width3, &height3, &nrChannels3, 0);

    unsigned char* data4 = stbi_load("4.jpg", &width4, &height4, &nrChannels4, 0);

    unsigned char* data5 = stbi_load("5.jpg", &width5, &height5, &nrChannels5, 0);

    unsigned char* data6 = stbi_load("6.jpg", &width6, &height6, &nrChannels6, 0);



    polygon(0, 3, 2, 1, data, width, height, nrChannels);

    polygon(2, 3, 7, 6, data2, width2, height2, nrChannels2);

    polygon(0, 4, 7, 3, data3, width3, height3, nrChannels3);

    polygon(1, 2, 6, 5, data4, width4, height4, nrChannels4);

    polygon(4, 5, 6, 7, data5, width5, height5, nrChannels5);

    polygon(0, 1, 5, 4, data6, width6, height6, nrChannels6);

}





void Display(void)

{

    glClearColor(0.0, 0.0, 0.0, 0.0);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);



    double x = cos(angPhi) * cos(angOm);

    double y = sin(angOm);

    double z = sin(angPhi) * cos(angOm);

    gluLookAt(x, y, z, 0, 0, 0, 0, 1, 0);

    colorcube();



    glFinish();

}





void processNormalKeys(unsigned char key, int x, int y)

{

    switch (key)

    {

    case 'a':angPhi += 0.1; break;

    case 'd':angPhi -= 0.1; break;

    case 'w':angOm += 0.1; break;

    case 's':angOm -= 0.1; break;

    }



    glutPostRedisplay();

}





void Reshape(GLint w, GLint h)

{

    Width = w;

    Height = h;

    glViewport(0, 0, w, h);

    glEnable(GL_COLOR_MATERIAL);

    glEnable(GL_LIGHTING);

    glEnable(GL_LIGHT0);

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_TEXTURE_2D);

    float ambient[] = { 0.7, 0.7, 0.7, 1 };

    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);

}





int main(int argc, char* argv[])

{

    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH);

    glutInitWindowSize(Width, Height);

    glutCreateWindow("UwU");

    glutReshapeFunc(Reshape);

    glutDisplayFunc(Display);

    glutKeyboardFunc(processNormalKeys);

    glutMainLoop();

    return 0;

}