# Cub3D

## 🕹️ Overview

**Cub3D** is a **raycasting** project inspired by the early 3D game *Wolfenstein 3D*. It is part of the 42 School curriculum and serves as your first step into the world of **graphics programming**, **game engines**, and **real-time rendering**.

The goal is to render a 3D view from a first-person perspective using a 2D map, applying raycasting techniques. It includes player movement, wall collision, and basic texture rendering—all built from scratch using **C** and the **MLX42** library.

## 🎯 Objectives

- Render a 3D projection based on a 2D map using raycasting
- Parse a configuration `.cub` file that defines the map and textures
- Display walls, a sky and floor color, and textured surfaces
- Handle player movement and view rotation with keyboard input
- Implement proper collision detection

## 🗺️ Map Format

The configuration file (`.cub`) must include:

- **Texture paths** for each wall direction (NO, SO, WE, EA)
- **Floor and ceiling colors**
- A **map** composed of:
  - `1` for walls
  - `0` for empty space
  - `N`, `S`, `E`, `W` for player starting position and direction
 
### Example map:

NO ./textures/north.xpm

SO ./textures/south.xpm

WE ./textures/west.xpm

EA ./textures/east.xpm

F 220,100,0

C 225,30,0


111111

100001

1000N1

111111


## 🎮 Controls

- W / A / S / D: Move forward, left, backward, right

- ← / → (arrow keys): Rotate view

- ESC: Exit the game

## ▶️ Usage

./cub3D maps/example.cub
