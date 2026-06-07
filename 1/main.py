#!/usr/bin/env python3
import math
import numpy as np
import glfw
from OpenGL.GL import *
from OpenGL.GLU import *

N = 20
mode = 1

tab = np.zeros((N, N, 3))
colors = np.zeros((N, N, 3))


def calculate_egg_data():
    global tab, colors

    for i in range(N):
        u = i / (N - 1)
        for j in range(N):
            v = j / (N - 1)

            factor = (-90 * u ** 5 + 225 * u ** 4 - 270 * u ** 3 + 180 * u ** 2 - 45 * u)
            x = factor * math.cos(math.pi * v)
            y = 160 * u ** 4 - 320 * u ** 3 + 160 * u ** 2 - 5
            z = factor * math.sin(math.pi * v)

            tab[i][j] = [x, y, z]
            colors[i][j] = [np.random.rand(), np.random.rand(), np.random.rand()]

    for i in range(N):
        colors[i][N - 1] = colors[i][0]


def spin(angle):
    glRotatef(angle, 1.0, 1.0, 1.0)


def draw_axes():
    glBegin(GL_LINES)
    glColor3f(1.0, 0.0, 0.0)
    glVertex3f(-10.0, 0.0, 0.0)
    glVertex3f(10.0, 0.0, 0.0)

    glColor3f(0.0, 1.0, 0.0)
    glVertex3f(0.0, -10.0, 0.0)
    glVertex3f(0.0, 10.0, 0.0)

    glColor3f(0.0, 0.0, 1.0)
    glVertex3f(0.0, 0.0, -10.0)
    glVertex3f(0.0, 0.0, 10.0)
    glEnd()

def window_resize_callback(window, width, height):
    if height == 0:
        height = 1
    glViewport(0, 0, width, height)
    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()
    gluPerspective(45, width / height, 0.1, 50.0)
    glMatrixMode(GL_MODELVIEW)


def key_callback(window, key, scancode, action, mods):
    global mode
    if action == glfw.PRESS:
        if key == glfw.KEY_1 or key == glfw.KEY_P:
            mode = 1
        elif key == glfw.KEY_2 or key == glfw.KEY_L:
            mode = 2
        elif key == glfw.KEY_3 or key == glfw.KEY_T:
            mode = 3
        elif key == glfw.KEY_4 or key == glfw.KEY_S:
            mode = 4
        elif key == glfw.KEY_ESCAPE:
            glfw.set_window_should_close(window, True)


def render():
    global mode

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
    glLoadIdentity()
    gluLookAt(0, 0, 15, 0, -2.5, 0, 0, 1, 0)

    current_time = glfw.get_time()
    angle = current_time * 20
    spin(angle)

    draw_axes()

    if mode == 1:
        glBegin(GL_POINTS)
        glColor3f(1.0, 1.0, 1.0)
        for i in range(N):
            for j in range(N):
                glVertex3fv(tab[i][j])
        glEnd()

    elif mode == 2:
        glBegin(GL_LINES)
        glColor3f(1.0, 1.0, 0.0)
        for i in range(N - 1):
            for j in range(N - 1):
                p1 = tab[i][j]
                p2 = tab[i + 1][j]
                p3 = tab[i][j + 1]

                glVertex3fv(p1)
                glVertex3fv(p2)

                glVertex3fv(p1)
                glVertex3fv(p3)
        glEnd()

    elif mode == 3:
        glBegin(GL_TRIANGLES)
        for i in range(N - 1):
            for j in range(N - 1):
                glColor3fv(colors[i][j])
                glVertex3fv(tab[i][j])
                glColor3fv(colors[i + 1][j])
                glVertex3fv(tab[i + 1][j])
                glColor3fv(colors[i][j + 1])
                glVertex3fv(tab[i][j + 1])

                glColor3fv(colors[i + 1][j])
                glVertex3fv(tab[i + 1][j])
                glColor3fv(colors[i + 1][j + 1])
                glVertex3fv(tab[i + 1][j + 1])
                glColor3fv(colors[i][j + 1])
                glVertex3fv(tab[i][j + 1])
        glEnd()

    elif mode == 4:
        for i in range(N - 1):
            glBegin(GL_TRIANGLE_STRIP)
            for j in range(N):
                glColor3fv(colors[i][j])
                glVertex3fv(tab[i][j])

                glColor3fv(colors[i + 1][j])
                glVertex3fv(tab[i + 1][j])
            glEnd()


def main():
    if not glfw.init():
        return
    window = glfw.create_window(800, 600, "Egg", None, None)
    if not window:
        glfw.terminate()
        return

    glfw.make_context_current(window)
    glfw.set_key_callback(window, key_callback)
    glfw.set_window_size_callback(window, window_resize_callback)

    calculate_egg_data()
    glEnable(GL_DEPTH_TEST)
    glShadeModel(GL_FLAT)

    window_resize_callback(window, 800, 600)

    while not glfw.window_should_close(window):
        render()
        glfw.swap_buffers(window)
        glfw.poll_events()

    glfw.terminate()


if __name__ == "__main__":
    main()