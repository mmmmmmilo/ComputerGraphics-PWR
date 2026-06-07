#include <GLFW/glfw3.h>
#include <GL/glu.h>
#include <iostream>
#include <cmath>
using namespace std;

const int N = 20;
const float PI = 3.14159265358979323846264338327950f;

float tab[N][N][3];

bool model_mode = true;
bool left_mouse_down = false;
bool right_mouse_down = false;
double last_x = 0;
double last_y = 0;

float model_angle_x = 0.0f;
float model_angle_y = 0.0f;
float model_scale = 1.0f;

float cam_radius = 15.0f;
float cam_theta = 0.0f;
float cam_phi = 0.0f;

void calculate_egg_data() {
    float u, v;
    for (int i = 0; i < N; ++i) {
        u = (float)i / (N - 1);
        for (int j = 0; j < N; ++j) {
            v = (float)j / (N - 1);

            float factor = (-90 * pow(u, 5) + 225 * pow(u, 4) - 270 * pow(u, 3) + 180 * pow(u, 2) - 45 * u);
            float x = factor * cos(PI * v);
            float y = 160 * pow(u, 4) - 320 * pow(u, 3) + 160 * pow(u, 2) - 5;
            float z = factor * sin(PI * v);

            tab[i][j][0] = x * 0.1f;
            tab[i][j][1] = y * 0.1f;
            tab[i][j][2] = z * 0.1f;
        }
    }
}

void draw_axes() {
    glBegin(GL_LINES);
    glColor3f(1.0, 0.0, 0.0); glVertex3f(-10.0, 0.0, 0.0); glVertex3f(10.0, 0.0, 0.0); // X
    glColor3f(0.0, 1.0, 0.0); glVertex3f(0.0, -10.0, 0.0); glVertex3f(0.0, 10.0, 0.0); // Y
    glColor3f(0.0, 0.0, 1.0); glVertex3f(0.0, 0.0, -10.0); glVertex3f(0.0, 0.0, 10.0); // Z
    glEnd();
}

void draw_egg() {
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POINTS);
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            glVertex3fv(tab[i][j]);
        }
    }
    glEnd();
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    if (height == 0) height = 1;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (float)width / (float)height, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        if (key == GLFW_KEY_ESCAPE)
            glfwSetWindowShouldClose(window, true);

        if (key == GLFW_KEY_M) {
            model_mode = !model_mode;
            cout << "Mode: " << (model_mode ? "Model" : "Camera") << endl;
        }
    }
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT) {
        left_mouse_down = (action == GLFW_PRESS);
    }
    if (button == GLFW_MOUSE_BUTTON_RIGHT) {
        right_mouse_down = (action == GLFW_PRESS);
    }
    glfwGetCursorPos(window, &last_x, &last_y);
}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
    double delta_x = xpos - last_x;
    double delta_y = ypos - last_y;
    last_x = xpos;
    last_y = ypos;

    float sensitivity = 0.5f;

    if (model_mode) {
        if (left_mouse_down) {
            model_angle_y += delta_x * sensitivity;
            model_angle_x += delta_y * sensitivity;
        }
        if (right_mouse_down) {
            model_scale += delta_y * 0.01f;
            if (model_scale < 0.1f) model_scale = 0.1f;
        }
    }
    else {
        if (left_mouse_down) {
            cam_theta += delta_x * 0.01f;
            cam_phi   += delta_y * 0.01f;

            if (cam_phi > 1.57f) cam_phi = 1.57f;
            if (cam_phi < -1.57f) cam_phi = -1.57f;

            cam_theta = fmod(cam_theta, 2 * PI);
        }
        if (right_mouse_down) {
            cam_radius += delta_y * 0.1f;
            if (cam_radius < 1.0f) cam_radius = 1.0f;
            if (cam_radius > 50.0f) cam_radius = 50.0f;
        }
    }
}

void render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    if (model_mode) {
        gluLookAt(0.0, 0.0, 15.0,
                  0.0, 0.0, 0.0,
                  0.0, 1.0, 0.0);

        glScalef(model_scale, model_scale, model_scale);
        glRotatef(model_angle_x, 1.0, 0.0, 0.0);
        glRotatef(model_angle_y, 0.0, 1.0, 0.0);
    }
    else {
        float x_eye = cam_radius * cos(cam_theta) * cos(cam_phi);
        float y_eye = cam_radius * sin(cam_phi);
        float z_eye = cam_radius * sin(cam_theta) * cos(cam_phi);

        gluLookAt(x_eye, y_eye, z_eye,
                  0.0, 0.0, 0.0,
                  0.0, 1.0, 0.0);
    }

    draw_axes();
    draw_egg();
    glFlush();
}

int main() {
    if (!glfwInit()) return -1;

    GLFWwindow* window = glfwCreateWindow(800, 600, "Lab 4: Egg Interaction", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, key_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);

    calculate_egg_data();
    glEnable(GL_DEPTH_TEST);

    framebuffer_size_callback(window, 800, 600);

    while (!glfwWindowShouldClose(window)) {
        render();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}