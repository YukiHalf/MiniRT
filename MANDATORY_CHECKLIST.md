# miniRT mandatory checklist

**Status at audit: not ready for mandatory evaluation.**

Reference: [miniRT subject, version 10.0](/Users/yuki/Desktop/minirt.pdf): common instructions on page 4, mandatory requirements on pages 8–12, README requirements on page 13, and bonus separation on pages 14–15.

This checklist covers the mandatory renderer, input safety, build rules, Norm, documentation, and verification. It records required work; it does not claim the fixes have been implemented. It is not a substitute for the required root `README.md`.

- `[ ]` means unfinished or not fully verified.
- `[x]` in the audit baseline means that specific case was exercised successfully. It does not certify every case or remain valid automatically after changes.
- Work through the priorities below before adding more pattern or specular features.

## 1. P0 — Fix memory safety and crash paths

### File reader

Files: `inc/libft/get_next_line/get_next_line_bonus.c`, `inc/libft/get_next_line/get_next_line_bonus.h`.

Confirmed failure: AddressSanitizer reported a global-buffer-overflow at `get_next_line_bonus.c:104` while loading a valid sphere scene. `buffer` is declared as `buffer[BUFFER_SIZE]`, `BUFFER_SIZE` is `1`, and the array is indexed by the file descriptor.

- [ ] Separate descriptor storage capacity from the number of bytes read per operation. Do not fix this merely by increasing `BUFFER_SIZE`.
- [ ] Use correctly bounded per-descriptor storage, or a reader design appropriate for loading one scene file at a time.
- [ ] Validate a descriptor before using it as an array index.
- [ ] Handle allocation failures in the line reader without dereferencing null pointers or losing owned buffers.
- [ ] Distinguish read errors and allocation failures from normal end-of-file, and propagate failures to `scene_load()`.
- [ ] Free retained reader buffers and close the scene descriptor on success and every error path.
- [ ] Remove the `"> "` debug output from `get_next_line()` so loading a scene does not print terminal prompts.
- [ ] Re-run a valid scene through AddressSanitizer and confirm the reported out-of-bounds access is gone.

### Application safety

Files: `src/main.c`, `src/scene_parser/scene_parser.c`, `src/shade.c`, `src/app.c`.

Confirmed failure: the parser accepted a sphere scene without a light, and the actual executable terminated with signal 11. `shade_hit()` accesses `world->lights[0]` even when no light exists.

- [ ] Validate the completed scene before preparing camera transforms or entering the render loop.
- [ ] Require a usable camera; reject empty files and missing-camera scenes rather than rendering with zero-initialized camera data.
- [ ] Prevent the missing-light crash. With the current renderer, reject scenes without a required light before rendering. If ambient-only scenes are accepted under the evaluation rules, implement that path explicitly without reading `lights[0]`.
- [ ] Check required ambient/light records consistently with the evaluation rules. The subject specifies uppercase-element uniqueness; do not confuse that with validation of a usable complete scene.
- [ ] Propagate intersection/allocation failures instead of silently converting them into a black pixel or ignoring them during shadow checks.
- [ ] Verify cleanup after partial initialization: objects, lights, intersection arrays, image/window resources, and file-reader buffers.
- [ ] Verify no segmentation faults, double frees, invalid accesses, or leaks on normal exit and malformed-input paths.

## 2. P0 — Complete scene and argument validation

Files: `src/main.c`, `src/error.c`, `src/scene_parser/`, `inc/parser.h`.

Confirmed gaps: no-argument execution entered the application instead of reporting usage; empty files, missing-camera files, and a directory ending in `.rt` were accepted by `scene_load()`.

- [ ] Require the expected command line: `./miniRT scene.rt`; reject missing and excess arguments.
- [ ] Require the `.rt` extension and report unreadable/nonexistent inputs clearly.
- [ ] Reject a directory named `something.rt`; do not interpret a failed read as a valid empty file.
- [ ] Return a nonzero exit status and print `Error\n` followed by an explicit message for invalid configuration. Preserve useful line numbers for line-level errors.
- [ ] Accept elements in any order, with blank lines and one or more spaces between fields. Preserve existing tab and CRLF support.
- [ ] Recognize exactly the required identifiers: `A`, `C`, `L`, `sp`, `pl`, and `cy`; reject unknown identifiers and incorrect field counts.
- [ ] Reject duplicate `A`, `C`, and `L` declarations in the mandatory format.
- [ ] Validate RGB components as integers in `[0, 255]`.
- [ ] Validate ambient and point-light brightness ratios in `[0, 1]`.
- [ ] Validate positions as finite numeric triples and directions/axes as nonzero normalized triples, using a reasonable floating-point tolerance.
- [ ] Validate strictly positive sphere/cylinder diameters and cylinder heights.
- [ ] Reject malformed and non-finite numeric values without allowing them to reach matrix or intersection calculations.
- [ ] Resolve and test FOV endpoints against evaluation expectations: the PDF specifies `[0, 180]`, while the current parser accepts only `0 < FOV < 180`. Handle any accepted endpoints safely rather than producing invalid projection math.
- [ ] Retest both parser acceptance/rejection and the complete executable. Parser-only success must not hide a later renderer crash.

## 3. P1 — Integrate all mandatory geometry into loaded scenes

Files: `src/main.c` (`prepare_parsed_scene()`), `src/scene/intersection_features*.c`, `src/scene/objects_features*.c`, `src/world.c`.

### Shared object pipeline

- [ ] Give every supported object a valid transform before it reaches `intersect()` or `normal_at()`.
- [ ] Convert parsed object position, axis/normal, and dimensions into transforms consistently with the local-space shape definitions.
- [ ] Do not apply position or dimensions both in the object transform and again in local geometry.
- [ ] Transform a world-space ray into object space exactly once; do not normalize the transformed direction and change the meaning of its intersection `t` values.
- [ ] Keep local shape solvers independent of world-space transforms.
- [ ] Transform normals using the inverse transpose, set vector `w = 0`, and normalize the final world-space normal.
- [ ] Make normal calculation return a valid result or report an explicit error for every reachable shape type; remove the current missing-return path in `local_normal_at()`.
- [ ] Preserve the distinction between a successful miss and an actual intersection-processing failure.
- [ ] Select the nearest nonnegative intersection correctly across mixed-object scenes.

### Spheres

- [ ] Preserve working sphere translation and diameter-to-radius scaling from `.rt` files.
- [ ] Verify misses, two crossings, tangents, rays starting inside, and rays pointing away.
- [ ] Verify surface normals and shadows after changing a sphere's center and diameter.

### Planes

Confirmed failure: all loaded planes retained zero transforms. The checked ray toward the plane at `x = 10` returned no intersection.

- [ ] Build each parsed plane's translation and orientation from its point and normal in `prepare_parsed_scene()`.
- [ ] Keep the canonical local plane consistent with the existing solver: `y = 0`, normal `(0, 1, 0)`.
- [ ] Render horizontal, vertical, translated, and tilted planes correctly from scene files.
- [ ] Verify intersections from both sides and correct misses for parallel/coplanar rays.
- [ ] Verify transformed plane normals, diffuse lighting, and hard shadows in a mixed sphere/plane scene.

### Cylinders

Confirmed failure: `local_intersect()` has no cylinder branch, cylinder normals are missing, and parsed cylinders also retain zero transforms.

- [ ] Implement finite cylinder side intersections.
- [ ] Clip side hits to the cylinder's height.
- [ ] Implement end-cap intersections and normals for the closed finite cylinder expected by the evaluation.
- [ ] Implement side normals and handle rays starting inside the cylinder.
- [ ] Respect the parsed center, normalized axis, diameter, and height when preparing the object transform.
- [ ] Support translation, arbitrary axis orientation, and changes to both diameter and height.
- [ ] Handle tangency, axis-parallel rays, cap-parallel rays, and the side/cap boundary without invalid arithmetic or inconsistent hits.
- [ ] Integrate cylinders into the existing dispatch and nearest-hit pipeline; do not leave their presence causing `intersect_world()` to fail and the renderer to return black.
- [ ] Verify cylinder-only and mixed sphere/plane/cylinder scenes through the actual executable, not just isolated geometry helpers.

## 4. P1 — Correct camera and transformation behavior

Files: `src/camera.c`, `src/main.c` (`world_setup()`), `src/matrix/`, `src/hooks.c`.

- [ ] Correct `view_transform()` so the center ray follows the requested camera direction. The audit requested `+X` and observed a center ray pointing approximately `-X`.
- [ ] Build a valid camera basis for arbitrary normalized directions, including directions parallel or nearly parallel to the usual up vector.
- [ ] Verify camera translation, rotation, and left/right/up/down image placement with an asymmetric scene.
- [ ] Keep the requested FOV horizontal for every aspect ratio. The audit requested `90` degrees at `200x400` and measured approximately `53.13` degrees horizontally.
- [ ] Preserve the camera pose and horizontal FOV when the window is resized.
- [ ] Verify object translation/rotation and light translation from scene data. Sphere and point-light rotation are not required by the subject.
- [ ] Fix the matrix guard that checks the function address: `if (!is_invertible_m4)` must call the function with the matrix.
- [ ] Handle singular transforms explicitly instead of dividing by a zero determinant or pretending an invalid inverse is usable.
- [ ] Verify the transformation behavior through loaded scenes; having translation/rotation helper functions alone is not sufficient.

## 5. P1 — Separate ambient, diffuse, and shadow calculations

Files: `src/main.c`, `src/scene/objects_features_2.c`, `src/shade.c`, `src/world.c`.

### Ambient and diffuse

- [ ] Keep the object's base color independent of the ambient-light color. Do not permanently multiply the whole material color by ambient color in `prepare_parsed_scene()`.
- [ ] Compute ambient illumination from object color, ambient color, and ambient ratio independently of point-light brightness.
- [ ] Compute diffuse illumination from object color, point-light brightness, and the surface/light angle independently of ambient color.
- [ ] Verify that point-light brightness zero does not erase nonzero ambient lighting. With a white object and white ambient strength `0.2`, the audit observed black instead of RGB `(0.2, 0.2, 0.2)`.
- [ ] Verify that black ambient color at zero ambient strength does not erase direct diffuse lighting. In the audit's white-object/white-light check with specular disabled, the result was black instead of RGB `(0.9, 0.9, 0.9)` for the current material's diffuse coefficient.
- [ ] Verify ambient tinting, brightness endpoints, surfaces facing away from the light, and color conversion at the image boundary.
- [ ] Test mandatory ambient/diffuse behavior with optional specular and pattern effects disabled so bonus behavior cannot mask a failure.

### Hard shadows and inside hits

- [ ] Cast shadow rays toward the light and count only blockers between the surface and the light, not objects beyond the light or behind the ray origin.
- [ ] Preserve ambient illumination in shadow while removing direct illumination.
- [ ] Calculate `over_point` after the inside/outside normal has been finalized.
- [ ] Verify the displacement points along the final normal. The audit's inside-sphere hit produced `-EPSILON` along that normal instead of `+EPSILON`.
- [ ] Verify self-shadow avoidance from both outside and inside objects, including scenes with a light inside a sphere/cylinder.
- [ ] Retest cast shadows between different objects and on differently oriented planes.
- [ ] Check and propagate a failed `intersect_world()` call from shadow calculation.

## 6. P2 — Preserve responsive window behavior and cleanup

Files: `src/app.c`, `src/hooks.c`, `src/render.c`.

- [ ] Preserve successful window creation and image presentation on the evaluation platform.
- [ ] Preserve Escape closing the window and exiting successfully.
- [ ] Preserve the native window close button closing the program successfully.
- [ ] Preserve switching windows, minimization/restoration, and resizing without losing the rendered image or corrupting state.
- [ ] Verify responsiveness while rendering a demanding scene, not only after rendering finishes. `render_step()` currently renders all remaining rows in one hook invocation; limit work per invocation if this blocks event handling.
- [ ] Verify that repeated resize/render cycles and both close paths release application-owned resources.
- [ ] Verify graphics initialization/allocation failures exit with an explicit error and correct cleanup.

## 7. P2 — Meet build, library, and Norm requirements

Files: `Makefile`, `inc/libft/Makefile`, `src/`, `inc/`.

### Build and dependencies

- [ ] Build the required executable name `miniRT` using `cc` and `-Wall -Wextra -Werror` for project sources. The main Makefile currently omits `-Werror`.
- [ ] Fix all required-flag compilation errors, including the missing normal return, matrix function-address check, and const mismatch between `shade_hit()` and `is_shadowed()`.
- [ ] Provide working `$(NAME)`, `all`, `clean`, `fclean`, and `re` targets. The PDF's Makefile table also lists `bonus`; the root Makefile currently has no such target.
- [ ] Preserve the verified no-unnecessary-relink behavior.
- [ ] Verify rebuilds after source/header changes, including changes inside libft, rather than relying on an already existing `libft.a`.
- [ ] Compile libft through its own Makefile and ensure the required library sources are part of the submitted repository.
- [ ] Confirm with the school that MLX42 is accepted for this subject. The supplied PDF explicitly names MiniLibX; this approval was not established by the audit.
- [ ] Ensure the approved graphics library and required build dependencies are available on the evaluation machine. The current build clones MLX42 from the network when absent.
- [ ] Review `fclean`: it currently deletes the entire `MLX42` directory. Do not delete required vendored source files or make rebuilding depend on an unavailable download.
- [ ] Verify project code uses only the authorized external functions: the subject's listed I/O/allocation/error functions, math functions, the approved graphics library, and `gettimeofday()`, plus your authorized libft implementations.
- [ ] Keep optional bonus behavior/build rules separate as required by the subject. Do not treat patterns, specular reflection, or colored/multiple lights as completion of missing mandatory features.

### Norm

- [ ] Make production source files pass Norminette. The audit still reported functions over 25 lines in `src/main.c` and `src/scene_parser/scene_parser.c`.
- [ ] Make all project headers pass Norminette: missing headers, indentation/alignment, long lines, macros, and declaration formatting still failed in multiple `inc/*.h` files.
- [ ] Apply the applicable Norm requirements to libft and any submitted bonus code as well.
- [ ] Decide which development-only test utilities to submit; the subject says tests need not be submitted or graded. Do not assume ungraded test code proves the submitted renderer is compliant.
- [ ] Re-run `norminette src inc` after the fixes, plus any additional submitted project-code paths.

## 8. P2 — Add the required root README

The audit found no root `README.md`. This checklist does not fulfill that requirement.

- [ ] Create `README.md` at the repository root and write it in English.
- [ ] Use the subject's required italicized first line, with the actual 42 login(s): `This project has been created as part of the 42 curriculum by ...`.
- [ ] Add a **Description** section explaining the project and its purpose.
- [ ] Add an **Instructions** section covering prerequisites, compilation, execution with an `.rt` file, and exit controls.
- [ ] Add a **Resources** section containing the references actually used.
- [ ] Explain how AI was used, including the tasks and project parts it assisted with.
- [ ] Document the supported scene format and working example commands without claiming unsupported features are implemented.

## 9. P2 — Prepare a focused defense scene set

The subject recommends scenes that make each feature easy to inspect.

- [ ] Spheres: different centers/diameters, overlapping objects, tangent/miss cases, and a camera inside a sphere.
- [ ] Planes: horizontal, vertical, tilted, translated, and viewed from either side.
- [ ] Cylinders: side views, both caps, different diameters/heights, arbitrary axes, and inside views.
- [ ] Mixed scene: spheres, planes, and cylinders together with nearest-hit visibility and cast shadows.
- [ ] Cameras: translated viewpoints, `+X`/`-X`/`+Z`/`-Z` and tilted directions, a near-up direction, different FOVs, and landscape/portrait resizing.
- [ ] Lighting: zero/nonzero point brightness, zero/nonzero ambient strength, colored ambient light, and surfaces facing toward/away from the light.
- [ ] Shadows: occluders between the surface and light, occluders beyond the light, and self-shadow checks inside/outside objects.
- [ ] Invalid inputs: missing arguments/files, wrong extension, directory input, empty files, missing required records, duplicate uppercase elements, unknown identifiers, wrong field counts, malformed/out-of-range numbers, invalid colors, invalid axes, and FOV boundary cases.
- [ ] Check memory safety and leaks on both successful and rejected inputs and after both window-close paths.

## 10. Audit baseline — cases already exercised successfully

These are limited observations from the audited version, not sign-off for the mandatory part. Re-run affected checks after changing the code.

- [x] The normal `make` build completed with its current flags and available dependencies.
- [x] A subsequent `make -n all` scheduled no unnecessary rebuild or relink.
- [x] A sphere-only scene rendered a shaded sphere in the application window.
- [x] Window resize and minimize/restore worked in the checked scene.
- [x] Escape closed the actual application with exit code `0`.
- [x] The native close button closed the actual application with exit code `0`.
- [x] A sphere scaled by two produced the expected intersections at `t = 3` and `t = 7` for the checked ray.
- [x] Reordered elements, blank lines, spaces, and tabs were accepted in the checked valid scene.
- [x] Invalid RGB, duplicate ambient declarations, and unknown identifiers were rejected in the checked parser cases.
- [x] Missing files and incorrect extensions produced explicit `Error\n` messages through the actual executable.
- [x] The existing parser suite reported **58 passed, 0 failed**. It did not catch the confirmed descriptor-buffer overflow or missing-light renderer crash.

## 11. Final mandatory release gate

- [ ] All confirmed crash and invalid-memory-access paths above are fixed and rechecked with instrumentation.
- [ ] All three required geometry types render correctly from `.rt` files, including transforms, dimensions, intersections, and inside cases.
- [ ] Camera pose and horizontal FOV behave correctly across the checked orientations and window shapes.
- [ ] Ambient, diffuse, and hard-shadow behavior pass independently of bonus effects.
- [ ] Invalid configuration is rejected cleanly; successful and failed runs have verified resource cleanup.
- [ ] The executable builds with the required flags and the submitted code passes Norm.
- [ ] Required Makefile targets, library availability, and school approval for the graphics library are resolved.
- [ ] The root README satisfies every required section and disclosure.
- [ ] Required files, including library sources, are actually included in the submission. Review `.gitignore`, which currently ignores `libft` and `MLX42`; do not assume files present locally are submitted.
- [ ] A fresh checkout builds and runs on the evaluation platform without depending on stale local objects or unsubmitted files.
- [ ] Review the implementation with a peer and be able to explain and modify the code during evaluation.

**Do not mark mandatory complete based only on a working sphere screenshot, passing pattern checks, or the existing parser suite.**
