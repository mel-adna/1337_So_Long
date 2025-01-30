# so_long Guide

## Introduction

`so_long` is a graphical project from 42/1337 that requires you to create a small 2D game using the **MiniLibX** library. The player moves on a map, collects items, avoids enemies (optional), and reaches an exit. The goal of this project is to get familiar with **event handling, rendering, and game logic**.

## Learning Resources

- **MiniLibX Documentation**: [https://harm-smits.github.io/42docs/libs/minilibx](https://harm-smits.github.io/42docs/libs/minilibx)
- **42Docs (LibX, Graphics, and Events)**: [https://harm-smits.github.io/42docs/](https://harm-smits.github.io/42docs/)
- **Game Loop and Rendering Basics**: [https://gamedev.stackexchange.com/questions/86291/what-is-a-game-loop](https://gamedev.stackexchange.com/questions/86291/what-is-a-game-loop)
- **Understanding Flood Fill Algorithm** (for path validation): [https://en.wikipedia.org/wiki/Flood_fill](https://en.wikipedia.org/wiki/Flood_fill)
- **Handling Key Events in MiniLibX**: Check MiniLibX event functions

---

## Features to Implement

- **Rendering the Map** using MiniLibX
- **Player Movement**
- **Collecting Items**
- **Checking for a Valid Path** to the exit
- **Counting Moves** (to display at each move)
- **Handling Window Close Events**
- **Bonus Features**: Animations, enemy AI, sprite changes, etc.

## How to Install & Run

### Prerequisites

- You must be on **macOS or Linux** (MiniLibX is not natively supported on Windows)
- Have **Makefile**, **gcc**, and **MiniLibX** installed

### Installing MiniLibX

```bash
# On macOS
brew install minilibx

# On Linux (Debian-based systems)
sudo apt-get install libxext-dev libxrandr-dev libx11-dev libbsd-dev
```

### Cloning and Compiling

```bash
git clone https://github.com/yourgithubusername/so_long.git
cd so_long
make
./so_long maps/sample.ber
```

## File Structure

```
so_long/
├── src/           # Source files
│   ├── main.c     # Entry point
│   ├── render.c   # Handles rendering
│   ├── events.c   # Handles key presses and window closing
│   ├── movement.c # Moves the player and updates the map
│   ├── map.c      # Loads and validates the map
├── includes/      # Header files
│   ├── so_long.h  # Main header file
├── maps/          # Folder containing .ber map files
├── assets/        # Sprites for the game
├── Makefile       # Compilation rules
└── README.md      # This guide
```

---

## How to Create Maps

- Maps should be **rectangular**
- Must contain:
  - `1` → Walls
  - `0` → Walkable space
  - `C` → Collectibles
  - `E` → Exit
  - `P` → Player Start Position
- Example (`sample.ber`):

```
11111
1P0C1
10001
1C0E1
11111
```

## Common Errors and Fixes

| Error | Possible Cause | Fix |
|--------|--------------|------|
| `Segmentation fault` | Accessing NULL pointers | Check for invalid malloc returns and uninitialized variables |
| `Map not displaying` | Incorrect map path | Ensure the map file exists and follows the `.ber` format |
| `Game closes immediately` | No event loop | Ensure `mlx_loop()` is running |
| `Leaks detected` | Missing free() calls | Use `valgrind --leak-check=full ./so_long` to debug |

## Bonus Ideas

- **Enemy AI** (chasing the player)
- **Animations** (moving sprites)
- **Score System** (displaying score and time taken)
- **Sound Effects** (using `system()` calls)

---

## Conclusion

The `so_long` project is an excellent way to understand game loops, event handling, and rendering. Take your time with the **map parsing** and **event handling**, as these are common areas where errors happen.

For further questions, refer to the **MiniLibX documentation** or ask in the **42/1337 community forums**!

Happy coding! 🚀

