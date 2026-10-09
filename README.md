*This project has been created as part of the 42 curriculum by sdarius-, rnauke.*

# miniRT

## Description

miniRT is a ray tracer written in C. Its goal is to generate an image of a three-dimensional scene described in a `.rt` text file, using ray–object intersections, surface normals, lighting, and shadows.

The renderer casts rays from a camera through the image, finds the closest visible surface, and computes its color. The project brings together vector and matrix mathematics, scene parsing, memory management, and window/event handling through MLX42.

The implementation includes spheres, planes, finite cylinders, object transformations, ambient and point lighting, shadows, and procedural stripe patterns. Cube and cone implementations are also present as extensions. Their presence does not imply that the mandatory requirements or bonus evaluation are complete.

**Development status:** the project builds, but mandatory compliance is still in progress. See [MANDATORY_CHECKLIST.md](MANDATORY_CHECKLIST.md) for verification results and remaining issues. In particular, scenes without a light can currently crash, and reader memory safety, camera behavior, and cylinder placement have unresolved findings.

## Instructions

### Dependencies

Build tools and libraries:

- A C compiler (`cc`), Make, Git, and CMake.
- GLFW and the platform's OpenGL/window-system development libraries.
- MLX42, which the Makefile downloads and builds when absent.
- The included libft library, built by the root Makefile.

A graphical desktop session is required to display the renderer window. The first build requires internet access if MLX42 has not already been downloaded.

#### macOS

Install the Xcode Command Line Tools if needed:

```sh
xcode-select --install
```

With [Homebrew](https://brew.sh/) installed:

```sh
brew install cmake glfw
```

The macOS Makefile uses `brew --prefix glfw` to locate GLFW and links the Cocoa, OpenGL, and IOKit frameworks.

#### Linux

For Debian/Ubuntu-based systems, install the build and graphics dependencies:

```sh
sudo apt update
sudo apt install build-essential git cmake libglfw3-dev libgl1-mesa-dev libx11-dev xorg-dev
```

The Makefile has a Linux link configuration. Linux execution has not been verified in the current macOS audit; consult the MLX42 documentation below for distribution-specific dependencies.

### Compilation

From the repository root:

```sh
make
```

This builds libft, prepares MLX42 if necessary, and produces `miniRT`.

Other targets:

| Command | Purpose |
| --- | --- |
| `make clean` | Remove object and dependency files, including libft build objects. |
| `make fclean` | Also remove executables, libft's archive, and the entire `MLX42/` directory. |
| `make re` | Run `fclean`, then rebuild. |
| `make ptest` | Build and run the parser regression checks. |
| `make test` | Build and run the pattern checks, including a ray through shading and lighting. |

**Important:** `make fclean` and `make re` delete `MLX42/`, including any local edits there. A subsequent build may need internet access to download it again. The current Makefile uses `-march=native`; build on the machine where you intend to run the program.

### Execution

Pass a scene file with the `.rt` extension:

```sh
./miniRT scenes/spheres.rt
```

Other supplied scenes include:

```sh
./miniRT scenes/planes.rt
./miniRT scenes/cylinders.rt
```

Press **Escape** or use the window's close button to exit. Resizing the window triggers image resizing and rendering again. Scene contents and camera settings are edited in the scene file; no interactive camera controls are documented here.

Always provide a complete scene with ambient lighting, a camera, and a point light. Do not rely on the current parser to reject every incomplete or unsafe input.

### Scene format

Each nonblank line defines an element. Separate fields with whitespace; write vectors and colors as comma-separated triples.

| Identifier | Fields after the identifier |
| --- | --- |
| `A` | Ambient ratio, RGB color |
| `C` | Camera position, normalized direction, field of view in degrees |
| `L` | Light position, brightness ratio, RGB color |
| `sp` | Sphere center, diameter, RGB color |
| `pl` | Point on plane, normalized normal, RGB color |
| `cy` | Cylinder center, normalized axis, diameter, height, RGB color |

Use one `A`, one `C`, and one `L` record. RGB components are integers from `0` to `255`; brightness ratios are between `0` and `1`. Use positive diameters and heights and unit-length directions. The current parser accepts camera FOV values strictly between `0` and `180` degrees. The cylinder field above describes the subject's intended center convention; the current implementation's base-versus-center mismatch is tracked in the checklist.

A small scene:

```text
A 0.2 255,255,255
C 0,0,-5 0,0,1 60
L -10,10,-10 0.8 255,255,255

sp 0,0,0 2 255,80,80
pl 0,-1,0 0,1,0 200,200,200
```

Save it as `example.rt` and run `./miniRT example.rt`.

### Verification

```sh
make ptest
make test
norminette src inc
```

Norminette is a separate tool; installation instructions are linked below. Passing the parser and pattern checks does not establish full renderer correctness, memory safety, or mandatory compliance. The checklist records the scope and limitations of each audit.

## Resources

- **miniRT subject, version 10.0:** the project specification available through the 42 Intra project page. This is the authority for evaluation requirements; book examples may use different shape conventions.
- **[The Ray Tracer Challenge — Jamis Buck](https://pragprog.com/titles/jbtracer/the-ray-tracer-challenge/):** the primary learning reference used while developing the ray tracer, covering intersections, transformations, normals, shading, shadows, and patterns.
- **[Ray Tracing in One Weekend](https://raytracing.github.io/):** an additional introduction to ray tracing concepts and image generation.
- **[Scratchapixel](https://www.scratchapixel.com/):** explanations of computer graphics mathematics, camera models, and ray–geometry intersections.
- **[MLX42](https://github.com/codam-coding-college/MLX42):** the graphics library used for image display, windows, and input handling; its repository includes build instructions and documentation.
- **[GLFW documentation](https://www.glfw.org/documentation.html):** documentation for the window/context library used by MLX42.
- **[Norminette](https://github.com/42School/norminette):** installation and usage information for the 42 coding-standard checker.

### AI usage

AI assistance was used during development and review for:

- Explaining local-space rays, local normals, intersections, and object transformations while following *The Ray Tracer Challenge*.
- Discussing C header dependencies, forward declarations, pattern/material relationships, and the object parameter passed through `lighting()` and `shade_hit()`.
- Assisting with pattern debug/check code and interpreting parser, shading, and compilation issues.
- Auditing the implementation against the miniRT subject, running build/test/Norm checks and targeted runtime probes, and documenting findings in `MANDATORY_CHECKLIST.md`.
- Drafting this README from the repository's build rules, source code, and observed verification results.

AI-generated explanations, code suggestions, and audit findings are assistance, not proof of correctness. The authors remain responsible for understanding the implementation and validating it against the subject and evaluation requirements.
