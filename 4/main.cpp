#include <GLFW/glfw3.h>
#include <GL/glu.h>
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

float theta = 0.0f;
float phi = 0.0f;
bool left_mouse_down = false;
double last_x = 0, last_y = 0;
bool show_front_wall = true;

bool use_texture2 = false;

GLuint textureID;
GLuint texture2ID;

bool loadTGA(const char* filename, int txtID) {
    ifstream file(filename, ios::binary);
    if (!file.is_open()) {
        cerr << "Can't open a file: " << filename << "\n";
        return false;
    }

    unsigned char header[18];
    file.read(reinterpret_cast<char*>(header), 18);

    int width = header[12] + (header[13] << 8);
    int height = header[14] + (header[15] << 8);
    int bpp = header[16];

    if (width <= 0 || height <= 0 || (bpp != 24 && bpp != 32)) return false;

    int bytesPerPixel = bpp / 8;
    int imageSize = width * height * bytesPerPixel;
    vector<unsigned char> data(imageSize);
    file.read(reinterpret_cast<char*>(data.data()), imageSize);
    file.close();

    if (txtID == 0) {
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);
    }
    else {
        glGenTextures(1, &texture2ID);
        glBindTexture(GL_TEXTURE_2D, texture2ID);
    }

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    GLenum format = (bpp == 32) ? GL_BGRA : GL_BGR;
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, format, GL_UNSIGNED_BYTE, data.data());

    return true;
}

void init() {
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    loadTGA("tekstura.tga", 0);
    loadTGA("tekstura2.tga", 1);
}

void draw_triangle(float x1, float y1, float z1, float u1, float v1,
                   float x2, float y2, float z2, float u2, float v2,
                   float x3, float y3, float z3, float u3, float v3) {
    glBegin(GL_TRIANGLES);
    glTexCoord2f(u1, v1); glVertex3f(x1, y1, z1);
    glTexCoord2f(u2, v2); glVertex3f(x2, y2, z2);
    glTexCoord2f(u3, v3); glVertex3f(x3, y3, z3);
    glEnd();
}

void render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(0.0, 10.0, 15.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glRotatef(theta, 0.0, 1.0, 0.0);
    glRotatef(phi, 1.0, 0.0, 0.0);

    if (use_texture2) {
        glBindTexture(GL_TEXTURE_2D, texture2ID);
    } else {
        glBindTexture(GL_TEXTURE_2D, textureID);
    }

    float size = 5.0f;
    float height = 8.0f;

    draw_triangle(-size, 0,  size, 0.0, 0.0,
                   size, 0,  size, 1.0, 0.0,
                   size, 0, -size, 1.0, 1.0);

    draw_triangle( size, 0, -size, 1.0, 1.0,
                  -size, 0, -size, 0.0, 1.0,
                  -size, 0,  size, 0.0, 0.0);

    float apexX = 0, apexY = height, apexZ = 0;
    float apexU = 0.5f, apexV = 0.5f;

    if (show_front_wall) {
        draw_triangle(-size, 0, size, 0.0, 0.0,
                       size, 0, size, 1.0, 0.0,
                       apexX, apexY, apexZ, apexU, apexV);
    }

    draw_triangle( size, 0,  size, 1.0, 0.0,
                   size, 0, -size, 1.0, 1.0,
                   apexX, apexY, apexZ, apexU, apexV);

    draw_triangle( size, 0, -size, 1.0, 1.0,
                  -size, 0, -size, 0.0, 1.0,
                   apexX, apexY, apexZ, apexU, apexV);

    draw_triangle(-size, 0, -size, 0.0, 1.0,
                  -size, 0,  size, 0.0, 0.0,
                   apexX, apexY, apexZ, apexU, apexV);

    glFlush();
}

void cursor_callback(GLFWwindow* window, double xpos, double ypos) {
    double delta_x = xpos - last_x;
    double delta_y = ypos - last_y;
    last_x = xpos; last_y = ypos;
    if (left_mouse_down) {
        theta += delta_x * 0.5f;
        phi += delta_y * 0.5f;
    }
}

void mouse_callback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT) left_mouse_down = (action == GLFW_PRESS);
    glfwGetCursorPos(window, &last_x, &last_y);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        if (key == GLFW_KEY_H) show_front_wall = !show_front_wall;
        if (key == GLFW_KEY_ESCAPE) glfwSetWindowShouldClose(window, true);
        if (key == GLFW_KEY_SPACE) use_texture2 = !use_texture2;
    }
}

void resize_callback(GLFWwindow* window, int width, int height) {
    if (height == 0) height = 1;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (float)width/height, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

int main() {
    if (!glfwInit()) return -1;
    GLFWwindow* window = glfwCreateWindow(800, 600, "Lab 6: Texturing", NULL, NULL);
    if (!window) { glfwTerminate(); return -1; }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, resize_callback);
    glfwSetCursorPosCallback(window, cursor_callback);
    glfwSetMouseButtonCallback(window, mouse_callback);
    glfwSetKeyCallback(window, key_callback);

    init();
    resize_callback(window, 800, 600);

    while (!glfwWindowShouldClose(window)) {
        render();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}