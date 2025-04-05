# Cub3D

## Overview
Cub3D is a graphical project inspired by the classic 90s game Wolfenstein 3D, designed to explore ray-casting techniques. The goal is to create a dynamic, first-person perspective view inside a maze, rendered using the MiniLibX library. This project aims to simulate a 3D environment with basic movement and texture mapping, providing an educational dive into computer graphics fundamentals.

## Features
- **Ray-Casting Engine**: Renders a 3D maze from a 2D map using ray-casting.
- **Player Movement**: WASD keys for movement, arrow keys for rotation.
- **Texture Mapping**: Walls rendered with textures specified in a `.cub` file.
- **Map Parsing**: Reads a `.cub` file to configure the maze layout, textures, and colors.
- **Window Management**: Utilizes MiniLibX for window creation and event handling.

## Prerequisites
- **Operating System**: Linux or macOS (MiniLibX compatibility).
- **Compiler**: GCC or Clang.
- **Dependencies**: MiniLibX library (either system-installed or compiled from source), Libft (for utility functions).
- **Tools**: Make, Git.

## Installation
1. **Clone the Repository**:
   ```bash
   git clone https://github.com/username/cub3d.git
   cd cub3d
   ```
2. **Compile Libft** (if included as a submodule):
   ```bash
   cd libft
   make
   cd ..
   ```
3. **Compile MiniLibX** (if using source):
   ```bash
   cd mlx
   make
   cd ..
   ```
4. **Build the Project**:
   ```bash
   make
   ```

## Usage
Run the program with a valid `.cub` map file:
```bash
./cub3d maps/example.cub
```
- **Controls**:
  - `W`: Move forward
  - `A`: Strafe left
  - `S`: Move backward
  - `D`: Strafe right
  - `Left/Right Arrows`: Rotate view
  - `ESC`: Exit

## Project Structure
```
cub3d/
├── includes/         # Header files
│   ├── cub3d.h       # Main project header
│   └── structs.h     # Structure definitions
├── src/              # Source files
│   ├── main.c        # Entry point and initialization
│   ├── parser/       # Map and config parsing
│   │   ├── parse_map.c
│   │   └── parse_utils.c
│   ├── raycaster/    # Ray-casting logic
│   │   ├── raycast.c
│   │   └── render.c
│   ├── player/       # Player movement and controls
│   │   └── movement.c
│   ├── graphics/     # MiniLibX rendering functions
│   │   ├── draw.c
│   │   └── textures.c
│   └── utils/        # Utility functions
│       └── error.c
├── libft/            # Libft library (submodule or copy)
├── mlx/              # MiniLibX library (if included)
├── maps/             # Example .cub map files
│   └── example.cub
├── Makefile          # Build rules
└── README.md         # This file
```

## Map File Format (.cub)
A `.cub` file defines the maze layout and rendering settings:
- **Resolution**: `R 1920 1080`
- **Textures**: `NO ./textures/north.xpm`, `SO`, `WE`, `EA`
- **Colors**: `F 220,100,0` (floor), `C 100,150,200` (ceiling)
- **Map**: Grid of `0` (empty), `1` (wall), `N/S/E/W` (player spawn), surrounded by walls.

Example:
```
R 800 600
NO ./textures/north.xpm
SO ./textures/south.xpm
WE ./textures/west.xpm
EA ./textures/east.xpm
F 50,50,50
C 100,100,100

111111
100001
10N001
111111
```

## Implementation Details
- **Main Loop**: Initializes MiniLibX, parses the map, and enters the rendering loop.
- **Ray-Casting**: Casts rays for each screen column, calculates wall distances, and scales wall heights.
- **Textures**: Loads `.xpm` files via MiniLibX and maps them to wall segments.
- **Error Handling**: Validates map integrity and resource availability, exits gracefully on failure.

## Contributing
1. Fork the repository.
2. Create a feature branch (`git checkout -b feature/xyz`).
3. Commit changes (`git commit -m "Add feature XYZ"`).
4. Push to the branch (`git push origin feature/xyz`).
5. Open a pull request.

## License
This project is licensed under the MIT License.

## Acknowledgments
- 42 School for the project inspiration.
- MiniLibX documentation and community.
