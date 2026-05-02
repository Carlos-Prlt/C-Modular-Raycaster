# C-Modular-Raycaster (SDL2)

A modular 2.5D raycasting engine written in C using the SDL2 library, heavily inspired by [Lode's famous raycasting tutorial](https://lodev.org/cgtutor/raycasting.html). This project is my own version and builds upon that classic mathematical foundation, managing rendering directly at the pixel buffer level. It features a decoupled architecture, vertical pitch, and a real-time minimap overlay.

## Features

* **Raycasting Rendering:** Uses the DDA (Digital Differential Analyzer) algorithm for precise wall-collision detection.
* **Vertical Pitch:** Simulated up/down looking through horizon shifting.
* **Real-time Minimap:** Overlay minimap that draws active rays and player position.
* **Modular Architecture:** Organized into logical components (`input`, `player`, `render`, `globals`) for easy scaling and maintenance.
* **FPS Independent Physics:** Movement and rotation are calculated using *delta time* (dt) for consistency across different hardware.

## Prerequisites

To compile and run this project, you need a C compiler (e.g., `gcc`), `make`, and **SDL2** development libraries.

### Installing dependencies (Linux - Ubuntu/Debian)

```bash
sudo apt update
sudo apt install gcc make libsdl2-dev
```

### Installing dependencies (macOS - Homebrew)

```bash
brew install sdl2
```

## Building and Running

The project includes a pre-configured Makefile. Open your terminal in the project root and run:

**Compile the project:**
```bash
make
```

**Run the engine:**
```bash
./raycaster
```

**Clean build files (optional):**
```bash
make clean
```

## Controls

| Key | Action |
| :--- | :--- |
| **W** | Move Forward |
| **S** | Move Backward |
| **A** | Strafe Left |
| **D** | Strafe Right |
| **Left Arrow** | Rotate Camera Left |
| **Right Arrow** | Rotate Camera Right |
| **Up Arrow** | Look Up (Pitch) |
| **Down Arrow** | Look Down (Pitch) |
| **ESC** | Exit Program |

## Project Structure

```plaintext
.
├── Makefile          # Build script
├── README.md         # Documentation
├── include/          # Header files (.h)
│   ├── globals.h
│   ├── input.h
│   ├── player.h
│   └── render.h
└── src/              # Source files (.c)
    ├── main.c        # Entry point and main game loop
    ├── globals.c     # Global state and map definitions
    ├── input.c       # SDL2 event handling
    ├── player.c      # Physics, collisions, and rotation
    └── render.c      # Raycasting logic and pixel manipulation
```

## References & Credits

* **Author:** Carlos Peralta Solís

* **Inspiration and tutorials:**
  * Lode's Computer Graphics Tutorial - Raycasting
  * Wolfenstein 3D Raycasting in C by Tim Allan Wheeler.
