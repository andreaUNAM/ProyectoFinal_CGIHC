// Draw rotating Torus with GLFW3
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <glfw3.h>

#include "iostream"
#include "string"


using namespace std;

static void drawTorus(int numMajor, int numMinor, float majorRadius, float minorRadius)
{
    static double PI = 3.1415926535897932384626433832795;

    double majorStep = 2.0 * PI / numMajor;
    double minorStep = 2.0 * PI / numMinor;


    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    for (int i = 0; i < numMajor; ++i) {
        double a0 = i * majorStep;
        double a1 = a0 + majorStep;
        GLdouble x0 = cos(a0);
        GLdouble y0 = sin(a0);
        GLdouble x1 = cos(a1);
        GLdouble y1 = sin(a1);

        glBegin(GL_TRIANGLE_STRIP);

        for (int j = 0; j <= numMinor; ++j) {
            double b = j * minorStep;
            GLdouble c = cos(b);
            GLdouble r = minorRadius * c + majorRadius;
            GLdouble z = minorRadius * sin(b);

            glNormal3d(x0 * c, y0 * c, z / minorRadius);
            glTexCoord2d(i / (GLdouble)numMajor, j / (GLdouble)numMinor);
            glVertex3d(x0 * r, y0 * r, z);

            glNormal3d(x1 * c, y1 * c, z / minorRadius);
            glTexCoord2d((i + 1) / (GLdouble)numMajor, j / (GLdouble)numMinor);
            glVertex3d(x1 * r, y1 * r, z);
        }

        glEnd();
    }
}


static void renderMesh(float majorRadius, float minorRadius)
{
    glLoadIdentity();

    glBegin(GL_LINES);
    glColor4ub(255, 0, 0, 255);
    glVertex3f(0, 0, 0);
    glVertex3f(0.75, 0, 0);

    glColor4ub(0, 0, 255, 255);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 0.75);

    glColor4ub(0, 255, 0, 255);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0.75, 0);

    glEnd();

    drawTorus(20, 20, majorRadius, minorRadius);
}


int main()
{
    float majorRadius = -1.0f;
    float minorRadius = -1.0f;
    int scr_width = 0;
    int scr_height = 0;
    while (scr_width <= 0) {
        cout << "Ingrese el valor deseado del ancho de resolucion\n$";
        cin >> scr_width;
    }
    while (scr_height <= 0) {
        cout << "Ingrese el valor deseado del alto de resolucion\n$";
        cin >> scr_height;
    }
    while (minorRadius < 0.0 || minorRadius >= 1.0) {
        cout << "Ingrese el valor del radio menor entre 0 y 1\n$";
        cin >> minorRadius;
    }

    while (majorRadius < minorRadius || majorRadius > 1.0) {
        cout << "Ingrese el valor del radio major entre 0 y 1\n$";
        cin >> majorRadius;
    }

    GLFWwindow* window;

    if (!glfwInit()) {
        fprintf(stderr, "Failed to start glfw\n");
        return -1;
    }

    //Set OpenGL Revision
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    //Create Window
    window = glfwCreateWindow(scr_width, scr_height, "OpenGL with GLFW", NULL, NULL);
    if (!window) {
        fprintf(stderr, "Failed to make window\n");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    while (!glfwWindowShouldClose(window)) {
        double mx, my, t, dt;
        int winWidth, winHeight;
        int fbWidth, fbHeight;
        float ratio;

        glfwGetCursorPos(window, &mx, &my);
        glfwGetWindowSize(window, &winWidth, &winHeight);
        glfwGetFramebufferSize(window, &fbWidth, &fbHeight);

        ratio = (float)fbWidth / (float)winWidth;
        glViewport(0, 0, fbWidth, fbHeight);

        glClearColor(0.3, 0.3, 0.3, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        renderMesh(majorRadius,minorRadius);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}