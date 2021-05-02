# Drones 2D
A 2D drone simulation powered by neural networks and genetic algorithms.

---

## __Requirements__
- OpenGL 3.3
- glfw3
- glew

---

## __Build__
```bash
git clone https://github.com/kz04px/drones-2d
mkdir drones/build
cd drones/build
cmake ..
make
```

---

## __Network Architecture__
Drones are controlled by feedforward neural networks of size 7,9,4

Inputs:
- x distance to target
- y distance to target
- x speed
- y speed
- sin(drone orientation)
- cos(drone orientation)
- angular velocity

Outputs:
- Left engine throttle
- Left engine orientation
- Right engine throttle
- Right engine orientation

---

## __Controls__
```
Esc    - Quit
Space  - Toggle pause
F1     - Toggle debug
F2     - Print debug information
F3     - Toggle wireframe
F4     - Reset camera position
1      - 10 fps simulation
2      - 60 fps simulation (default)
3      - 120 fps simulation
4      - 240 fps simulation
5      - max fps simulation
MMB    - Drag to move camera
Scroll - Zoom in/out
```
