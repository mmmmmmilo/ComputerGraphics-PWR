#include <GLFW/glfw3.h>
#include <GL/glu.h>
#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

const int N = 20;
const float PI = 3.14159265358979323846264338327950f;

struct Vertex {
    float x, y, z;
    float nx, ny, nz;
};

Vertex egg[N][N];

int selected_light = 0;

float light0_theta = 0.0f;
float light0_phi = 0.0f;
float light0_radius = 10.0f;

float light1_theta = 0.0f;
float light1_phi = 0.0f;
float light1_radius = 10.0f;

bool left_mouse_down = false;
double last_x = 0;
double last_y = 0;

int selected_color_component = 0;

float light0_position[] = {0.0f, 0.0f, 10.0f, 1.0f};
float light0_ambient[]   = {0.1f, 0.1f, 0.1f, 1.0f};
float light0_diffuse[]   = {1.0f, 1.0f, 0.0f, 1.0f};
float light0_specular[]  = {1.0f, 1.0f, 1.0f, 1.0f};

float light1_position[]  = {-10.0f, 5.0f, 0.0f, 1.0f};
float light1_ambient[]   = {0.0f, 0.0f, 0.0f, 1.0f};
float light1_diffuse[]   = {0.0f, 0.0f, 1.0f, 1.0f};
float light1_specular[]  = {1.0f, 1.0f, 1.0f, 1.0f};

float mat_ambient[]   = {0.2f, 0.2f, 0.2f, 1.0f};
float mat_diffuse[]   = {1.0f, 1.0f, 1.0f, 1.0f};
float mat_specular[]  = {1.0f, 1.0f, 1.0f, 1.0f};
float mat_shininess   = 50.0f;


void calculate_egg_data() {
    float u, v;
    for (int i = 0; i < N; ++i) {
        u = (float)i / (N - 1);
        for (int j = 0; j < N; ++j) {
            v = (float)j / (N - 1);

            float factor = (-90 * pow(u, 5) + 225 * pow(u, 4) - 270 * pow(u, 3) + 180 * pow(u, 2) - 45 * u);
            egg[i][j].x = factor * cos(PI * v) * 0.5f;
            egg[i][j].y = (160 * pow(u, 4) - 320 * pow(u, 3) + 160 * pow(u, 2) - 5) * 0.5f;
            egg[i][j].z = factor * sin(PI * v) * 0.5f;

            float xu = (-450 * pow(u, 4) + 900 * pow(u, 3) - 810 * pow(u, 2) + 360 * u - 45) * cos(PI * v);
            float xv = PI * (90 * pow(u, 5) - 225 * pow(u, 4) + 270 * pow(u, 3) - 180 * pow(u, 2) + 45 * u) * sin(PI * v);
            float yu = 640 * pow(u, 3) - 960 * pow(u, 2) + 320 * u;
            float yv = 0;
            float zu = (-450 * pow(u, 4) + 900 * pow(u, 3) - 810 * pow(u, 2) + 360 * u - 45) * sin(PI * v);
            float zv = -PI * (90 * pow(u, 5) - 225 * pow(u, 4) + 270 * pow(u, 3) - 180 * pow(u, 2) + 45 * u) * cos(PI * v);

            float nx = yu * zv - zu * yv;
            float ny = zu * xv - xu * zv;
            float nz = xu * yv - yu * xv;

            float length = sqrt(nx * nx + ny * ny + nz * nz);
            if (length > 0) {
                nx /= length; ny /= length; nz /= length;
            } else {
                nx = 0; ny = 1; nz = 0;
            }

            if (i >= N / 2) {
                 nx = -nx; ny = -ny; nz = -nz;
            }

            egg[i][j].nx = nx;
            egg[i][j].ny = ny;
            egg[i][j].nz = nz;
        }
    }
}

void init_lighting() {
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);

    glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);
    glEnable(GL_LIGHT0);

    glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);
    glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
    glEnable(GL_LIGHT1);
}

void draw_axes() {
    glDisable(GL_LIGHTING);
    glBegin(GL_LINES);
    glColor3f(1.0, 0.0, 0.0); glVertex3f(-10.0, 0.0, 0.0); glVertex3f(10.0, 0.0, 0.0);
    glColor3f(0.0, 1.0, 0.0); glVertex3f(0.0, -10.0, 0.0); glVertex3f(0.0, 10.0, 0.0);
    glColor3f(0.0, 0.0, 1.0); glVertex3f(0.0, 0.0, -10.0); glVertex3f(0.0, 0.0, 10.0);
    glEnd();
    glEnable(GL_LIGHTING);
}

void draw_light_visualization(float* pos, float* color) {
    glDisable(GL_LIGHTING);
    glPushMatrix();
    glTranslatef(pos[0], pos[1], pos[2]);
    glColor3fv(color);

    GLUquadric* quad = gluNewQuadric();
    gluQuadricDrawStyle(quad, GLU_LINE);
    gluSphere(quad, 0.5, 6, 6);
    gluDeleteQuadric(quad);

    glPopMatrix();
    glEnable(GL_LIGHTING);
}

void draw_egg() {
    for (int i = 0; i < N - 1; ++i) {
        for (int j = 0; j < N - 1; ++j) {
            glBegin(GL_TRIANGLES);

            glNormal3f(egg[i][j].nx, egg[i][j].ny, egg[i][j].nz);
            glVertex3f(egg[i][j].x, egg[i][j].y, egg[i][j].z);

            glNormal3f(egg[i+1][j].nx, egg[i+1][j].ny, egg[i+1][j].nz);
            glVertex3f(egg[i+1][j].x, egg[i+1][j].y, egg[i+1][j].z);

            glNormal3f(egg[i][j+1].nx, egg[i][j+1].ny, egg[i][j+1].nz);
            glVertex3f(egg[i][j+1].x, egg[i][j+1].y, egg[i][j+1].z);

            glNormal3f(egg[i][j+1].nx, egg[i][j+1].ny, egg[i][j+1].nz);
            glVertex3f(egg[i][j+1].x, egg[i][j+1].y, egg[i][j+1].z);

            glNormal3f(egg[i+1][j].nx, egg[i+1][j].ny, egg[i+1][j].nz);
            glVertex3f(egg[i+1][j].x, egg[i+1][j].y, egg[i+1][j].z);

            glNormal3f(egg[i+1][j+1].nx, egg[i+1][j+1].ny, egg[i+1][j+1].nz);
            glVertex3f(egg[i+1][j+1].x, egg[i+1][j+1].y, egg[i+1][j+1].z);

            glEnd();
        }
    }
}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
    double delta_x = xpos - last_x;
    double delta_y = ypos - last_y;
    last_x = xpos;
    last_y = ypos;

    if (left_mouse_down) {
        if (selected_light == 0) {
            light0_theta -= delta_x * 0.01f;
            light0_phi   -= delta_y * 0.01f;

            light0_position[0] = light0_radius * cos(light0_theta) * cos(light0_phi);
            light0_position[1] = light0_radius * sin(light0_phi);
            light0_position[2] = light0_radius * sin(light0_theta) * cos(light0_phi);
        } else {
            light1_theta -= delta_x * 0.01f;
            light1_phi   -= delta_y * 0.01f;

            light1_position[0] = light1_radius * cos(light1_theta) * cos(light1_phi);
            light1_position[1] = light1_radius * sin(light1_phi);
            light1_position[2] = light1_radius * sin(light1_theta) * cos(light1_phi);
        }
    }
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT) {
        left_mouse_down = (action == GLFW_PRESS);
    }
    glfwGetCursorPos(window, &last_x, &last_y);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        if (key == GLFW_KEY_ESCAPE) glfwSetWindowShouldClose(window, true);

        if (key == GLFW_KEY_SPACE) {
            selected_light = (selected_light == 0) ? 1 : 0;
            cout << "LIGHT: " << selected_light << "\n";
        }

        if (key == GLFW_KEY_R) { selected_color_component = 0; cout << " RED\n"; }
        if (key == GLFW_KEY_G) { selected_color_component = 1; cout << " GREEN\n"; }
        if (key == GLFW_KEY_B) { selected_color_component = 2; cout << " BLUE\n"; }

        float* current_diffuse = (selected_light == 0) ? light0_diffuse : light1_diffuse;
        if (key == GLFW_KEY_EQUAL || key == GLFW_KEY_KP_ADD) {
            current_diffuse[selected_color_component] += 0.1f;
            if (current_diffuse[selected_color_component] > 1.0f) current_diffuse[selected_color_component] = 1.0f;
            cout << "  Value: " << current_diffuse[selected_color_component] << "\n";
        }
        if (key == GLFW_KEY_MINUS || key == GLFW_KEY_KP_SUBTRACT) {
            current_diffuse[selected_color_component] -= 0.1f;
            if (current_diffuse[selected_color_component] < 0.0f) current_diffuse[selected_color_component] = 0.0f;
            cout << "  value: " << current_diffuse[selected_color_component] << "\n";
        }
    }
}

void render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(0.0, 10.0, 20.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, light0_position);

    glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
    glLightfv(GL_LIGHT1, GL_POSITION, light1_position);

    draw_axes();

    draw_light_visualization(light0_position, light0_diffuse);
    draw_light_visualization(light1_position, light1_diffuse);

    draw_egg();
    glFlush();
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    if (height == 0) height = 1;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (float)width / (float)height, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

int main() {
    if (!glfwInit()) return -1;
    GLFWwindow* window = glfwCreateWindow(800, 600, "Lab 5: Lighting", NULL, NULL);
    if (!window) { glfwTerminate(); return -1; }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);

    calculate_egg_data();
    init_lighting();

    framebuffer_size_callback(window, 800, 600);

    while (!glfwWindowShouldClose(window)) {
        render();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}