# Drones 2D
A 2D drone simulation powered by neural networks and genetic algorithms.

---

## Screenshots
![Example image 1](/screenshots/screenshot_0001.png)
![Example image 2](/screenshots/screenshot_0002.png)

---

## __Requirements__
- OpenGL 4.3
- glfw3
- glew
- FreeType

---

## __Build__
```bash
git clone https://github.com/kz04px/drones-2d
mkdir drones-2d/build
cd drones-2d/build
cmake ..
make
```

---

## __Network Architecture__
Drones are controlled by feedforward neural networks of size 7,9,4 with tanh activation functions.

Inputs:
- x distance to target
- y distance to target
- x speed
- y speed
- sin(drone orientation)
- cos(drone orientation)
- angular velocity

Outputs:
- Left engine throttle (Clamped between 0.0f and 1.0f)
- Left engine orientation
- Right engine throttle (Clamped between 0.0f and 1.0f)
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

---

## __Command Line Parameters__
```
-benchmark
Enables benchmarking
```

---

## __Thanks__
- [FreeType library](https://www.freetype.org/) - FreeType is a freely available software library to render fonts.
- [RobotoMono-Regular.ttf](https://fonts.google.com/specimen/Roboto+Mono) - A monospace font I think looks nice.
