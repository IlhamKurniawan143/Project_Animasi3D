#include <GL/freeglut.h>
#include <cstdio>
#include <cmath>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

float xrot = 0;
float yrot = 0;
float xdiff = 0;
float ydiff = 0;
bool mouseDown = false;
bool animating = false; // Variable to store animation state
GLuint texture1, texture2,texture3, texture4;

float scale = 1.0f; // Variable to store object scale
float cameraX = 0.0f; // Camera position on the X-axis
float cameraY = 0.0f; // Camera position on the Y-axis
float cameraZ = -150.0f; // Camera position on the Z-axis

void ukur(int lebar, int tinggi) {
    if (tinggi == 0) tinggi = 1;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, (float)lebar / tinggi, 5, 450);
    glTranslatef(0, 0, -3);
    glMatrixMode(GL_MODELVIEW);
}

void myinit(void) {
    glClearColor(0.1, 0.1, 0.1, 1.0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);

    int width, height, nrChannels;
    unsigned char *data;

    // Load the first texture
    data = stbi_load("kayu.jpeg", &width, &height, &nrChannels, 0);
    if (data) {
        glGenTextures(1, &texture1);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glTexImage2D(GL_TEXTURE_2D, 0, nrChannels == 4 ? GL_RGBA : GL_RGB, width, height, 0, nrChannels == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, data);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        stbi_image_free(data);
    } else {
        printf("Failed to load texture1\n");
    }

    // Load the second texture
    data = stbi_load("din.png", &width, &height, &nrChannels, 0);
    if (data) {
        glGenTextures(1, &texture2);
        glBindTexture(GL_TEXTURE_2D, texture2);
        glTexImage2D(GL_TEXTURE_2D, 0, nrChannels == 4 ? GL_RGBA : GL_RGB, width, height, 0, nrChannels == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, data);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        stbi_image_free(data);
    } else {
        printf("Failed to load texture2\n");
    }
    
	// Load the third texture
	data = stbi_load("besi.jpeg", &width, &height, &nrChannels, 0);
	if (data) {
    	glGenTextures(1, &texture3);
  		glBindTexture(GL_TEXTURE_2D, texture3);
  		glTexImage2D(GL_TEXTURE_2D, 0, nrChannels == 4 ? GL_RGBA : GL_RGB, width, height, 0, nrChannels == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, data);
    	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    	stbi_image_free(data);
	} else {
  	  printf("Failed to load texture3\n");
	}
	
	// Load the fourth texture
    data = stbi_load("meja.jpeg", &width, &height, &nrChannels, 0);
    if (data) {
        glGenTextures(1, &texture4);
        glBindTexture(GL_TEXTURE_2D, texture4);
        glTexImage2D(GL_TEXTURE_2D, 0, nrChannels == 4 ? GL_RGBA : GL_RGB, width, height, 0, nrChannels == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, data);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        stbi_image_free(data);
    } else {
        printf("Failed to load texture1\n");
    }
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        printf("OpenGL error: %d\n", err);
    }
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        mouseDown = true;
        xdiff = x - yrot;
        ydiff = -y + xrot;
    } else {
        mouseDown = false;
    }
}

void mouseMotion(int x, int y) {
    if (mouseDown) {
        yrot = x - xdiff;
        xrot = y + ydiff;
        glutPostRedisplay();
    }
}

void keyboard(unsigned char key, int x, int y) {
    float fraction = 1.0f;
    switch (key) {
        case 'a':
        case 'A':
            yrot -= 5.0f; // Rotate left
            break;
        case 'd':
        case 'D':
            yrot += 5.0f; // Rotate right
            break;
        case 'w':
        case 'W':
            cameraX += fraction * sin(yrot * M_PI / 180.0f);
            cameraZ -= fraction * cos(yrot * M_PI / 180.0f);
            break;
        case 's':
        case 'S':
            cameraX -= fraction * sin(yrot * M_PI / 180.0f);
            cameraZ += fraction * cos(yrot * M_PI / 180.0f);
            break;
        case ' ':
            animating = !animating; // Toggle animation on space key press winda 
            break;
        default:
            break;
    }
    glutPostRedisplay();
}

void animate() {
    if (animating) {
        // Animation logic here
        xrot += 0.3;
        yrot += 0.4;
        glutPostRedisplay();
    }
}

void renderLegChairFront(float xOffset, float zOffset) {
    glBegin(GL_QUADS);
    // Front Face
    glTexCoord2f(0.0f, 0.0f); glVertex3f(xOffset, -2, zOffset -8);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(xOffset + 2, -2, zOffset -8);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(xOffset + 2, -8, zOffset -8);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(xOffset, -8, zOffset -8);

    // Back Face
    glTexCoord2f(0.0f, 0.0f); glVertex3f(xOffset, -2, zOffset - 10);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(xOffset + 2, -2, zOffset - 10);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(xOffset + 2, -8, zOffset - 10);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(xOffset, -8, zOffset - 10);

    // Left Face
    glTexCoord2f(0.0f, 0.0f); glVertex3f(xOffset, -2, zOffset -8);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(xOffset, -2, zOffset - 10);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(xOffset, -8, zOffset - 10);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(xOffset, -8, zOffset -8);

    // Right Face
    glTexCoord2f(0.0f, 0.0f); glVertex3f(xOffset + 2, -2, zOffset -8);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(xOffset + 2, -2, zOffset - 10);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(xOffset + 2, -8, zOffset - 10);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(xOffset + 2, -8, zOffset -8);

    // Bottom Face
    glTexCoord2f(0.0f, 0.0f); glVertex3f(xOffset, -8, zOffset -8);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(xOffset + 2, -8, zOffset -8);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(xOffset + 2, -8, zOffset - 10);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(xOffset, -8, zOffset - 10);
    glEnd();
}
void renderLegChairBack(float xOffset, float zOffset) {
    glBegin(GL_QUADS);
    // Front Face
    glTexCoord2f(0.0f, 0.0f); glVertex3f(xOffset, 5, zOffset -8);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(xOffset + 2, 5, zOffset -8);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(xOffset + 2, -8, zOffset -8);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(xOffset, -8, zOffset -8);

    // Back Face
    glTexCoord2f(0.0f, 0.0f); glVertex3f(xOffset, 5, zOffset - 10);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(xOffset + 2, 5, zOffset - 10);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(xOffset + 2, -8, zOffset - 10);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(xOffset, -8, zOffset - 10);

    // Left Face
    glTexCoord2f(0.0f, 0.0f); glVertex3f(xOffset, 5, zOffset -8);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(xOffset, 5, zOffset - 10);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(xOffset, -8, zOffset - 10);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(xOffset, -8, zOffset -8);

    // Right Face
    glTexCoord2f(0.0f, 0.0f); glVertex3f(xOffset + 2, 5, zOffset -8);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(xOffset + 2, 5, zOffset - 10);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(xOffset + 2, -8, zOffset - 10);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(xOffset + 2, -8, zOffset -8);

    // Bottom Face
    glTexCoord2f(0.0f, 0.0f); glVertex3f(xOffset, -8, zOffset -8);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(xOffset + 2, -8, zOffset -8);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(xOffset + 2, -8, zOffset - 10);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(xOffset, -8, zOffset - 10);
    glEnd();
}
void renderChairBack(float xOffset, float zOffset) {
    glBegin(GL_QUADS);
    // Front Face
    glTexCoord2f(0.0f, 0.0f); glVertex3f(xOffset -10, 5, zOffset -7);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(xOffset , 5, zOffset -7);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(xOffset , 2, zOffset -7);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(xOffset -10, 2, zOffset -7);

    // Back Face
    glTexCoord2f(0.0f, 0.0f); glVertex3f(xOffset -10, 5, zOffset - 9);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(xOffset , 5, zOffset - 9);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(xOffset , 2, zOffset - 9);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(xOffset -10, 2, zOffset - 9);

    // Left Face
    glTexCoord2f(0.0f, 0.0f); glVertex3f(xOffset -10, 5, zOffset -7);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(xOffset -10, 5, zOffset - 9);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(xOffset -10, 2, zOffset - 9);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(xOffset -10, 2, zOffset -7);

    // Right Face
    glTexCoord2f(0.0f, 0.0f); glVertex3f(xOffset , 5, zOffset -7);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(xOffset , 5, zOffset - 9);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(xOffset , 2, zOffset - 9);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(xOffset , 2, zOffset -7);

    // Bottom Face
    glTexCoord2f(0.0f, 0.0f); glVertex3f(xOffset -10, 2, zOffset -7);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(xOffset , 2, zOffset -7);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(xOffset , 2, zOffset - 9);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(xOffset -10, 2, zOffset - 9);
    glEnd();
}

void renderChair(float xOffset) {
    glBegin(GL_QUADS);
    // Chair Top
    // Top
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-37 + xOffset, -2, 0);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-25 + xOffset, -2, 0);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-25 + xOffset, -2, -12);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-37 + xOffset, -2, -12);

    // Bottom
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-37 + xOffset, -1, 0);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-25 + xOffset, -1, 0);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-25 + xOffset, -1, -12);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-37 + xOffset, -1, -12);

    // Right Side
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-25 + xOffset, -1, 0);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-25 + xOffset, -2, 0);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-25 + xOffset, -2, -12);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-25 + xOffset, -2, -12);

    // Left Side
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-37 + xOffset, -1, 0);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-37 + xOffset, -2, 0);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-37 + xOffset, -2, -12);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-37 + xOffset, -1, -12);

    // Front Side
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-37 + xOffset, -1, 0);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-25 + xOffset, -1, 0);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-25 + xOffset, -2, 0);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-37 + xOffset, -2, 0);

    // Back Side
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-37 + xOffset, -1, -12);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-25 + xOffset, -1, -12);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-25 + xOffset, -2, -12);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-37 + xOffset, -2, -12);
    glEnd();

	renderChairBack(-27 + xOffset, -2);
    // Render the 2 legs
    renderLegChairBack(-37 + xOffset, -2);
    renderLegChairBack(-27 + xOffset, -2);
    
    // Render the 2 legs
    renderLegChairFront(-37 + xOffset, 8);
    renderLegChairFront(-27 + xOffset, 8);

}

void renderLegChairFront2(float xOffset, float zOffset) {
    glBegin(GL_QUADS);
    // Front Face
    glTexCoord2f(0.0f, 0.0f); glVertex3f(xOffset, -2, zOffset -28);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(xOffset + 2, -2, zOffset -28);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(xOffset + 2, -8, zOffset -28);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(xOffset, -8, zOffset -28);

    // Back Face
    glTexCoord2f(0.0f, 0.0f); glVertex3f(xOffset, -2, zOffset - 30);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(xOffset + 2, -2, zOffset -30);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(xOffset + 2, -8, zOffset - 30);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(xOffset, -8, zOffset - 30);

    // Left Face
    glTexCoord2f(0.0f, 0.0f); glVertex3f(xOffset, -2, zOffset -28);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(xOffset, -2, zOffset - 30);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(xOffset, -8, zOffset - 30);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(xOffset, -8, zOffset -28);

    // Right Face
    glTexCoord2f(0.0f, 0.0f); glVertex3f(xOffset + 2, -2, zOffset -28);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(xOffset + 2, -2, zOffset - 30);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(xOffset + 2, -8, zOffset - 30);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(xOffset + 2, -8, zOffset -28);

    // Bottom Face
    glTexCoord2f(0.0f, 0.0f); glVertex3f(xOffset, -8, zOffset -28);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(xOffset + 2, -8, zOffset -28);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(xOffset + 2, -8, zOffset - 30);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(xOffset, -8, zOffset - 30);
    glEnd();
}
void renderLegChairBack2(float xOffset, float zOffset) {
    glBegin(GL_QUADS);
    // Front Face
    glTexCoord2f(0.0f, 0.0f); glVertex3f(xOffset, 5, zOffset -28);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(xOffset + 2, 5, zOffset -28);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(xOffset + 2, -8, zOffset -28);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(xOffset, -8, zOffset -28);

    // Back Face
    glTexCoord2f(0.0f, 0.0f); glVertex3f(xOffset, 5, zOffset - 30);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(xOffset + 2, 5, zOffset - 30);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(xOffset + 2, -8, zOffset - 30);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(xOffset, -8, zOffset - 30);

    // Left Face
    glTexCoord2f(0.0f, 0.0f); glVertex3f(xOffset, 5, zOffset -28);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(xOffset, 5, zOffset - 30);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(xOffset, -8, zOffset - 30);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(xOffset, -8, zOffset -28);

    // Right Face
    glTexCoord2f(0.0f, 0.0f); glVertex3f(xOffset + 2, 5, zOffset -28);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(xOffset + 2, 5, zOffset - 30);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(xOffset + 2, -8, zOffset - 30);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(xOffset + 2, -8, zOffset -28);

    // Bottom Face
    glTexCoord2f(0.0f, 0.0f); glVertex3f(xOffset, -8, zOffset -28);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(xOffset + 2, -8, zOffset -28);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(xOffset + 2, -8, zOffset - 30);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(xOffset, -8, zOffset -30);
    glEnd();
}
void renderChairBack2(float xOffset, float zOffset) {
    glBegin(GL_QUADS);
    // Front Face
    glTexCoord2f(0.0f, 0.0f); glVertex3f(xOffset -10, 5, zOffset -27);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(xOffset , 5, zOffset -27);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(xOffset , 2, zOffset -27);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(xOffset -10, 2, zOffset -27);

    // Back Face
    glTexCoord2f(0.0f, 0.0f); glVertex3f(xOffset -10, 5, zOffset - 29);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(xOffset , 5, zOffset - 29);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(xOffset , 2, zOffset - 29);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(xOffset -10, 2, zOffset - 29);

    // Left Face
    glTexCoord2f(0.0f, 0.0f); glVertex3f(xOffset -10, 5, zOffset -27);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(xOffset -10, 5, zOffset - 29);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(xOffset -10, 2, zOffset - 29);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(xOffset -10, 2, zOffset -27);

    // Right Face
    glTexCoord2f(0.0f, 0.0f); glVertex3f(xOffset , 5, zOffset -27);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(xOffset , 5, zOffset - 29);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(xOffset , 2, zOffset - 29);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(xOffset , 2, zOffset -27);

    // Bottom Face
    glTexCoord2f(0.0f, 0.0f); glVertex3f(xOffset -10, 2, zOffset -27);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(xOffset , 2, zOffset -27);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(xOffset , 2, zOffset - 29);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(xOffset -10, 2, zOffset - 29);
    glEnd();
}

void renderChair2(float xOffset) {
    glBegin(GL_QUADS);
    // Chair Top
    // Top
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-37 + xOffset, -2, -20);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-25 + xOffset, -2, -20);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-25 + xOffset, -2, -32);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-37 + xOffset, -2, -32);

    // Bottom
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-37 + xOffset, -1, -20);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-25 + xOffset, -1, -20);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-25 + xOffset, -1, -32);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-37 + xOffset, -1, -32);

    // Right Side
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-25 + xOffset, -1, -20);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-25 + xOffset, -2, -20);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-25 + xOffset, -2, -32);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-25 + xOffset, -2, -32);

    // Left Side
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-37 + xOffset, -1, -20);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-37 + xOffset, -2, -20);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-37 + xOffset, -2, -32);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-37 + xOffset, -1, -32);

    // Front Side
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-37 + xOffset, -1, -20);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-25 + xOffset, -1, -20);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-25 + xOffset, -2, -20);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-37 + xOffset, -2, -20);

    // Back Side
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-37 + xOffset, -1, -32);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-25 + xOffset, -1, -32);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-25 + xOffset, -2, -32);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-37 + xOffset, -2, -32);
    glEnd();

	renderChairBack2(-27 + xOffset, -2);
    // Render the 2 legs
    renderLegChairBack2(-37 + xOffset, -2);
    renderLegChairBack2(-27 + xOffset, -2);
    
    // Render the 2 legs
    renderLegChairFront2(-37 + xOffset, 8);
    renderLegChairFront2(-27 + xOffset, 8);

}


void renderLegTable(float xOffset, float zOffset) {
    glBegin(GL_QUADS);
    // Front Face
    glTexCoord2f(0.0f, 0.0f); glVertex3f(xOffset, 2, zOffset);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(xOffset + 2, 2, zOffset);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(xOffset + 2, -8, zOffset);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(xOffset, -8, zOffset);

    // Back Face
    glTexCoord2f(0.0f, 0.0f); glVertex3f(xOffset, 2, zOffset - 2);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(xOffset + 2, 2, zOffset - 2);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(xOffset + 2, -8, zOffset - 2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(xOffset, -8, zOffset - 2);

    // Left Face
    glTexCoord2f(0.0f, 0.0f); glVertex3f(xOffset, 2, zOffset);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(xOffset, 2, zOffset - 2);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(xOffset, -8, zOffset - 2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(xOffset, -8, zOffset);

    // Right Face
    glTexCoord2f(0.0f, 0.0f); glVertex3f(xOffset + 2, 2, zOffset);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(xOffset + 2, 2, zOffset - 2);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(xOffset + 2, -8, zOffset - 2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(xOffset + 2, -8, zOffset);

    // Bottom Face
    glTexCoord2f(0.0f, 0.0f); glVertex3f(xOffset, -8, zOffset);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(xOffset + 2, -8, zOffset);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(xOffset + 2, -8, zOffset - 2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(xOffset, -8, zOffset - 2);
    glEnd();
}

void renderTable(float xOffset) {
    glBegin(GL_QUADS);
    // Table Top
    // Top
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-40 + xOffset, 3, 8);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-20 + xOffset, 3, 8);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-20 + xOffset, 3, -4);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-40 + xOffset, 3, -4);

    // Bottom
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-40 + xOffset, 2, 8);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-20 + xOffset, 2, 8);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-20 + xOffset, 2, -4);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-40 + xOffset, 2, -4);

    // Right Side
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-20 + xOffset, 2, 8);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-20 + xOffset, 3, 8);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-20 + xOffset, 3, -4);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-20 + xOffset, 2, -4);

    // Left Side
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-40 + xOffset, 2, 8);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-40 + xOffset, 3, 8);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-40 + xOffset, 3, -4);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-40 + xOffset, 2, -4);

    // Front Side
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-40 + xOffset, 2, 8);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-20 + xOffset, 2, 8);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-20 + xOffset, 3, 8);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-40 + xOffset, 3, 8);

    // Back Side
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-40 + xOffset, 2, -4);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-20 + xOffset, 2, -4);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-20 + xOffset, 3, -4);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-40 + xOffset, 3, -4);
    glEnd();

    // Render the 4 legs
    renderLegTable(-40 + xOffset, 8);
    renderLegTable(-40 + xOffset, -2);
    renderLegTable(-22 + xOffset, 8);
    renderLegTable(-22 + xOffset, -2);
}

void renderLegTableBack(float xOffset, float zOffset) {
    glBegin(GL_QUADS);
    // Front Face
    glTexCoord2f(0.0f, 0.0f); glVertex3f(xOffset, 2, zOffset -20);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(xOffset + 2, 2, zOffset -20);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(xOffset + 2, -8, zOffset -20);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(xOffset, -8, zOffset -20);

    // Back Face
    glTexCoord2f(0.0f, 0.0f); glVertex3f(xOffset, 2, zOffset -22);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(xOffset + 2, 2, zOffset -22);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(xOffset + 2, -8, zOffset -22);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(xOffset, -8, zOffset -22);

    // Left Face
    glTexCoord2f(0.0f, 0.0f); glVertex3f(xOffset, 2, zOffset -20);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(xOffset, 2, zOffset -22);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(xOffset, -8, zOffset -22);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(xOffset, -8, zOffset-20);

    // Right Face
    glTexCoord2f(0.0f, 0.0f); glVertex3f(xOffset + 2, 2, zOffset -20);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(xOffset + 2, 2, zOffset -22);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(xOffset + 2, -8, zOffset -22);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(xOffset + 2, -8, zOffset -20);

    // Bottom Face
    glTexCoord2f(0.0f, 0.0f); glVertex3f(xOffset, -8, zOffset -20);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(xOffset + 2, -8, zOffset -20);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(xOffset + 2, -8, zOffset - 22);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(xOffset, -8, zOffset - 22);
    glEnd();
}

void renderTableBack(float xOffset) {
    glBegin(GL_QUADS);
    // TableBack
    // Top
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-40 + xOffset, 3, -12);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-20 + xOffset, 3, -12);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-20 + xOffset, 3, -24);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-40 + xOffset, 3, -24);

    // Bottom
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-40 + xOffset, 2, -12);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-20 + xOffset, 2, -12);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-20 + xOffset, 2, -24);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-40 + xOffset, 2, -24);

    // Right Side
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-20 + xOffset, 2, -12);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-20 + xOffset, 3, -12);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-20 + xOffset, 3, -24);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-20 + xOffset, 2, -24);

    // Left Side
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-40 + xOffset, 2, -12);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-40 + xOffset, 3, -12);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-40 + xOffset, 3, -24);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-40 + xOffset, 2, -24);

    // Front Side
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-40 + xOffset, 2, -12);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-20 + xOffset, 2, -12);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-20 + xOffset, 3, -12);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-40 + xOffset, 3, -12);

    // Back Side
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-40 + xOffset, 2, -24);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-20 + xOffset, 2, -24);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-20 + xOffset, 3, -24);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-40 + xOffset, 3, -24);
    glEnd();

    // Render the 4 legs
    renderLegTableBack(-40 + xOffset, 8);
    renderLegTableBack(-40 + xOffset, -2);
    renderLegTableBack(-22 + xOffset, 8);
    renderLegTableBack(-22 + xOffset, -2);
}


void renderLegTableTeacher(float xOffset, float zOffset) {
    glBegin(GL_QUADS);
    // Front Face
    glTexCoord2f(0.0f, 0.0f); glVertex3f(xOffset, 2, zOffset +20);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(xOffset + 2, 2, zOffset +20);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(xOffset + 2, -8, zOffset +20);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(xOffset, -8, zOffset +20);

    // Back Face
    glTexCoord2f(0.0f, 0.0f); glVertex3f(xOffset, 2, zOffset +18);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(xOffset + 2, 2, zOffset +18);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(xOffset + 2, -8, zOffset +18);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(xOffset, -8, zOffset +18);

    // Left Face
    glTexCoord2f(0.0f, 0.0f); glVertex3f(xOffset, 2, zOffset +20);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(xOffset, 2, zOffset +18);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(xOffset, -8, zOffset +18);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(xOffset, -8, zOffset +20);

    // Right Face
    glTexCoord2f(0.0f, 0.0f); glVertex3f(xOffset + 2, 2, zOffset +20);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(xOffset + 2, 2, zOffset +18);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(xOffset + 2, -8, zOffset +18);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(xOffset + 2, -8, zOffset +20);

    // Bottom Face
    glTexCoord2f(0.0f, 0.0f); glVertex3f(xOffset, -8, zOffset +20);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(xOffset + 2, -8, zOffset+20);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(xOffset + 2, -8, zOffset +18);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(xOffset, -8, zOffset +18);
    glEnd();
}

void renderTableTeacher(float xOffset) {
    glBegin(GL_QUADS);
    // Table Teacher
    // Top
    glTexCoord2f(0.0f, 0.0f); glVertex3f(45 + xOffset, 3, 28);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(15 + xOffset, 3, 28);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(15 + xOffset, 3, 14);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(45 + xOffset, 3, 14);

    // Bottom
    glTexCoord2f(0.0f, 0.0f); glVertex3f(45 + xOffset, 2, 28);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(15 + xOffset, 2, 28);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(45 + xOffset, 2, 14);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(15 + xOffset, 2, 14);

    // Right Side
    glTexCoord2f(0.0f, 0.0f); glVertex3f(15 + xOffset, 2, 28);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(15 + xOffset, 3, 28);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(15 + xOffset, 3, 14);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(15 + xOffset, 2, 14);

    // Left Side
    glTexCoord2f(0.0f, 0.0f); glVertex3f(45 + xOffset, 2, 28);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(45 + xOffset, 3, 28);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(45 + xOffset, 3, 14);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(45 + xOffset, 2, 14);

    // Front Side
    glTexCoord2f(0.0f, 0.0f); glVertex3f(45 + xOffset, 2, 28);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(15 + xOffset, 2, 28);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(15 + xOffset, 3, 28);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(45 + xOffset, 3, 28);

    // Back Side
    glTexCoord2f(0.0f, 0.0f); glVertex3f(45 + xOffset, 2, 14);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(15 + xOffset, 2, 14);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(15 + xOffset, 3, 14);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(45+ xOffset, 3, 14);
    glEnd();

    // Render the 4 legs
    renderLegTableTeacher(40 + xOffset, 8);
    renderLegTableTeacher(40 + xOffset, -2);
    renderLegTableTeacher(20 + xOffset, 8);
    renderLegTableTeacher(20 + xOffset, -2);
}

void renderFloor(float xOffset) {
    glBegin(GL_QUADS);
    // Floor 
    // Top
    glTexCoord2f(0.0f, 0.0f); glVertex3f(70 + xOffset, -8, 50);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-120 + xOffset, -8, 50);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-120 + xOffset, -8, -50);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(70 + xOffset, -8, -50);

    // Bottom
    glTexCoord2f(0.0f, 0.0f); glVertex3f(70 + xOffset, -10, 50);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-120 + xOffset, -10, 50);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-120 + xOffset, -10, -50);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(70 + xOffset, -10, -50);

    // Right Side
    glTexCoord2f(0.0f, 0.0f); glVertex3f(70 + xOffset, -10, 50);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(70 + xOffset, -8, 50);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(70 + xOffset, -8, -50);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(70 + xOffset, -10, -50);

    // Left Side
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-120 + xOffset, -10, 50);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-120 + xOffset, -8, 50);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-120 + xOffset, -8, -50);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-120 + xOffset, -10, -50);

    // Front Side
    glTexCoord2f(0.0f, 0.0f); glVertex3f(70 + xOffset, -10, 50);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-120 + xOffset, -10, 50);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-120 + xOffset, -8, 50);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(70 + xOffset, -8, 50);

    // Back Side
    glTexCoord2f(0.0f, 0.0f); glVertex3f(70 + xOffset, -10, -50);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-120 + xOffset, -10, -50);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-120 + xOffset, -8, -50);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(70 + xOffset, -8, -50);
    glEnd();

}

void renderWall(float xOffset) {
    glBegin(GL_QUADS);
    // Wall 
    // Top
    glTexCoord2f(0.0f, 0.0f); glVertex3f(72 + xOffset, 40, 50);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(70 + xOffset, 40, 50);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(70 + xOffset, 40, -50);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(72 + xOffset, 40, -50);

    // Bottom
    glTexCoord2f(0.0f, 0.0f); glVertex3f(72 + xOffset, -8, 50);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(70 + xOffset, -8, 50);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(70 + xOffset, -8, -50);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(72 + xOffset, -8, -50);

    // Right Side
    glTexCoord2f(0.0f, 0.0f); glVertex3f(70 + xOffset, -8, 50);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(70 + xOffset, 40, 50);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(70 + xOffset, 40, -50);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(70 + xOffset, -8, -50);

    // Left Side
    glTexCoord2f(0.0f, 0.0f); glVertex3f(72 + xOffset, -8, 50);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(72 + xOffset, 40, 50);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(72 + xOffset, 40, -50);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(72 + xOffset, -8, -50);

    // Front Side
    glTexCoord2f(0.0f, 0.0f); glVertex3f(72 + xOffset, -8, 50);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(70 + xOffset, -8, 50);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(70 + xOffset, 40, 50);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(72 + xOffset, 40, 50);

    // Back Side
    glTexCoord2f(0.0f, 0.0f); glVertex3f(72 + xOffset, -8, -50);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(70 + xOffset, -8, -50);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(70 + xOffset, 40, -50);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(72 + xOffset, 40, -50);
    glEnd();

}

void init() {
    // Enable lighting and set up light properties
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);

    GLfloat light_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat light_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat light_position[] = { 85.0f, 30.0f, 10.0f, 1.0f };

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
}

//Wall2
void renderWall2(float xOffset) {
    glBegin(GL_QUADS);    
	
    // Top
    glTexCoord2f(0.0f, 0.0f); glVertex3f(72 + xOffset, 40, 52);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-120 + xOffset, 40, 52);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-120 + xOffset, 40, 50);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(72 + xOffset, 40, 52);

    // Bottom
    glTexCoord2f(0.0f, 0.0f); glVertex3f(72 + xOffset, -8, 52);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-120 + xOffset, -8, 52);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-120 + xOffset, -8, 50);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(72 + xOffset, -8, 50);

    // Right Side
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-120 + xOffset, -8, 52);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-120 + xOffset, 40, 52);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-120 + xOffset, 40, 50);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-120 + xOffset, -8, 50);

    // Left Side
    glTexCoord2f(0.0f, 0.0f); glVertex3f(72 + xOffset, -8, 52);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(72 + xOffset, 40, 52);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(72 + xOffset, 40, 50);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(72 + xOffset, -8, 50);

    // Front Side
    glTexCoord2f(0.0f, 0.0f); glVertex3f(72 + xOffset, -8, 52);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-120 + xOffset, -8, 52);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-120 + xOffset, 40, 52);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(72 + xOffset, 40, 52);

    // Back Side
    glTexCoord2f(0.0f, 0.0f); glVertex3f(72 + xOffset, -8, 50);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-120 + xOffset, -8, 50);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-120+ xOffset, 40, 50);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(72 + xOffset, 40, 50);
    glEnd();

}



//Door
void renderDoor(float xOffset) {
    glBegin(GL_QUADS);   
    // Left
    glTexCoord2f(0.0f, 0.0f); glVertex3f(69 + xOffset, 30, 20);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(69 + xOffset, -8, 20);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(69 + xOffset, -8, 35);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(69 + xOffset, 30, 35);

    // Right
    glTexCoord2f(0.0f, 0.0f); glVertex3f(71 + xOffset, 30, 20);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(71 + xOffset, -8, 20);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(71 + xOffset, -8, 35);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(71 + xOffset, 30, 35);

    // Front Side
    glTexCoord2f(0.0f, 0.0f); glVertex3f(71 + xOffset, -8, 20);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(69 + xOffset, -8, 20);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(69 + xOffset, 30, 20);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(71 + xOffset, 30, 20);

    // Back Side
    glTexCoord2f(0.0f, 0.0f); glVertex3f(71 + xOffset, -8, 35);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(69 + xOffset, -8, 35);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(69+ xOffset, 30, 35);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(71 + xOffset, 30, 35);
    glEnd();

}

void tampil(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(cameraX, cameraY, cameraZ,
              cameraX + sin(yrot * M_PI / 180.0f), cameraY, cameraZ - cos(yrot * M_PI / 180.0f),
              0.0f, 1.0f, 0.0f);

    glScalef(scale, scale, scale);
    glRotatef(xrot, 1, 0, 0);
    glRotatef(yrot, 0, 1, 0);

    glBindTexture(GL_TEXTURE_2D, texture3); // Bind the thrid texture
    renderFloor(0);

	init();
	
    glBindTexture(GL_TEXTURE_2D, texture2);  // Bind the second texture
    renderWall(0);
	glBindTexture(GL_TEXTURE_2D, texture2);  // Bind the second texture
    renderWall2(0);
    
	glBindTexture(GL_TEXTURE_2D, texture4);  // Bind the fourth texture
    renderTable(0);
	renderTable(+30); // second table with four legs
    renderTable(-30); // thrid table with four legs
    renderTable(-60); // fourth table with four legs
    
    glBindTexture(GL_TEXTURE_2D, texture4);  // Bind the fourth texture
    renderTableBack(0);
    renderTableBack(+30); // second table with four legs
    renderTableBack(-30); // thrid table with four legs
    renderTableBack(-60); // fourth table with four legs
    
    glBindTexture(GL_TEXTURE_2D, texture4);  // Bind the fourth texture
    renderTableTeacher(0);
    glBindTexture(GL_TEXTURE_2D, texture1);  // Bind the first texture
    renderDoor(0);
	glBindTexture(GL_TEXTURE_2D, texture1);  // Bind the first texture
    renderChair(0);
	renderChair(+30); // Second chair with four legs
    renderChair(-30); // Third chair with four legss
    renderChair(-60); // fourth chair with four legs
    
    glBindTexture(GL_TEXTURE_2D, texture1);  // Bind the first texture
    renderChair2(0);
	renderChair2(+30); // Second chair with four legs
    renderChair2(-30); // Third chair with four legss
    renderChair2(-60); // fourth chair with four legs
  
    glFlush();
    glutSwapBuffers();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Meja dengan 3D Transformasi dan Animasi");
    glutDisplayFunc(tampil);
    glutIdleFunc(animate);
    glutReshapeFunc(ukur);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutMotionFunc(mouseMotion);
    myinit();
    glutMainLoop();
    return 0;
}
