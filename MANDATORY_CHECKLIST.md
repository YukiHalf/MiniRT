# miniRT mandatory checklist


Shadows don't work properly thats 4 sure


**Current status: not ready. Fresh builds and ordinary window operation pass, but memory safety, input completeness, camera math, cylinder edge cases, ambient/shadow calculations, required flags, and header Norm still fail. README requirements now pass.**

Reference: [miniRT subject, version 10.0](/Users/yuki/Desktop/minirt.pdf): common instructions on page 4, mandatory requirements on pages 8–12, README requirements on page 13, and bonus separation on pages 14–15.

This checklist covers the mandatory renderer, input safety, build rules, Norm, documentation, and verification. Checkmarks below distinguish source inspection from executed checks. This is not a substitute for the required root `README.md`.

- `[ ]` means unfinished, failing, or not fully verified.
- `[x]` means the stated narrow requirement has supporting evidence. Source-only checks do not certify end-to-end rendering. Section 10 is explicitly historical.
- Work through the priorities below before adding more pattern or specular features.

### Latest recheck evidence and limits

This recheck exercised every section below with fresh builds, isolated probes, source inspection, and actual desktop interaction. An unchecked item can be a demonstrated failure or an explicitly stated verification limit; it is not silently assumed to fail.

| Check | Current evidence |
| --- | --- |
| Build and existing suites | `make -B miniRT` succeeded; `make ptest`: 58 passed, 0 failed; `make test`: 16 passed, 0 failed. |
| Required flags | Fresh `cc -Wall -Wextra -Werror -fsyntax-only` over production build sources failed with seven diagnostics in five files. |
| Norm | `norminette src inc`: production C and libft pass; project headers fail. |
| Parser matrix | 116 cases each in normal and ASan builds: 95 matched expectations, 21 did not, in each variant. |
| Reader safety | Ordinary-descriptor ASan load reproduced the global-buffer-overflow at `get_next_line_bonus.c:104`. |
| Allocation/read failures | 150 single-allocation-failure cases: 10 crashes; 29 successful returns lost required records. Injected read failures leaked retained storage; one returned a partially loaded scene as success. |
| Render mathematics | 192 component assertions passed, 33 failed across 225 assertions; these are not 225 independent checklist items. |
| Actual application | Sphere, plane, cylinder, and mixed scenes displayed. Escape and native close each exited 0. Resize, minimize/restore, and switching windows preserved presentation in the ordinary scene. |
| Stress responsiveness | A 128-sphere scene stalled the desktop automation request for 20 seconds; the probe was terminated. Escape delivery was not established. |
| CLI | Wrong extension, extra arguments, nonexistent file, invalid RGB, duplicate ambient, and unknown identifier exit 1 with an explicit error. Missing light crashes; no argument, missing camera, empty file, and directory input enter the application. |
| Build targets/dependencies | `miniRT`, `all`, `clean`, `fclean`, `re` exercised; `bonus` fails. No unnecessary relink. Root source/header dependencies work, but libft source changes do not rebuild its archive. |
| Source-only snapshot | A temporary copy of tracked working-tree files built and ran on this Mac without reused objects, downloading MLX42. This is not a clean Git-commit or school-platform sign-off. |
| Documentation | Root English README, exact italicized attribution, Description, Instructions, Resources, AI disclosure, and scene examples are present; README is tracked. |

**Probe scope:** parser matrices used descriptor 0 to isolate validation from the separately demonstrated ordinary-descriptor overflow. Baseline normal/ASan parser cleanup kept descriptor counts unchanged and freed tracked project allocations; injected failures did not. Geometry probes compiled current source at `-O0`, used the real `parse_line()`/preparation/shading pipeline, bypassed the unsafe file reader, and disabled specular/pattern effects. Additional numeric probes used `-O3 -ffast-math`, which changed some non-finite rejection behavior; do not treat debug probes as proof of every production floating-point case.

**Cleanup evidence:** `leaks --atExit` reported zero leaks for nonexistent/unknown-identifier rejection. The graphical cylinder run reported 287 leaks / 18,720 bytes, with reported roots in Foundation/AppIntents XPC cycles and restricted memory inspection. This does not establish project-owned leaks, nor does it certify leak-free GUI cleanup.

**Limits:** school approval for MLX42, the actual evaluation platform, peer understanding, all graphics-allocation failure points, concurrent file mutation, and exhaustive leak/geometry coverage remain unverified. No implementation or permanent tests were changed. Temporary probes and copied builds were removed after recording results.

## 1. P0 — Fix memory safety and crash paths

### File reader

Files: `inc/libft/get_next_line/get_next_line_bonus.c`, `inc/libft/get_next_line/get_next_line_bonus.h`.

Still failing in the current recheck: AddressSanitizer reproduced the global-buffer-overflow at `get_next_line_bonus.c:104` on a valid sphere scene. `buffer` remains `buffer[BUFFER_SIZE]`, with `BUFFER_SIZE` equal to `1`, while indexing uses the file descriptor.

Fault injection additionally reproduced null writes at `get_next_line_bonus.c:62` and `:87`. Four of 66 error returns and four of 74 success returns retained one tracked allocation. Of the successful returns, 29 lost ambient or camera records; not every successful return under an injected allocation failure was defective. An injected read error in the second pass returned success with missing ambient/camera and retained storage. Ordinary baseline cleanup passing does not clear these failure paths.

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

Fresh executable failure: a sphere scene with ambient and camera but without a light terminated with signal 11 in this recheck. `shade_hit()` and `is_shadowed()` still access `world->lights[0]`/`scene->lights[0]` unconditionally.

- [ ] Validate the completed scene before preparing camera transforms or entering the render loop.
- [ ] Require a usable camera; reject empty files and missing-camera scenes rather than rendering with zero-initialized camera data.
- [ ] Prevent the missing-light crash. With the current renderer, reject scenes without a required light before rendering. If ambient-only scenes are accepted under the evaluation rules, implement that path explicitly without reading `lights[0]`.
- [ ] Check required ambient/light records consistently with the evaluation rules. The subject specifies uppercase-element uniqueness; do not confuse that with validation of a usable complete scene.
- [ ] Propagate intersection/allocation failures instead of silently converting them into a black pixel or ignoring them during shadow checks.
- [ ] Verify cleanup after partial initialization: objects, lights, intersection arrays, image/window resources, and file-reader buffers.
- [ ] Verify no segmentation faults, double frees, invalid accesses, or leaks on normal exit and malformed-input paths.

## 2. P0 — Complete scene and argument validation

Files: `src/main.c`, `src/error.c`, `src/scene_parser/`, `inc/parser.h`.

Fresh executable checks: no arguments, empty input, missing camera, and a directory ending in `.rt` entered the application and exited 0 only after Escape. Missing light terminated with signal 11. Invalid RGB, duplicate ambient, and unknown identifiers produced `Error`, explicit messages, and correct source line numbers. The isolated parser also accepted missing ambient and objects-only inputs.

- [ ] Require the expected command line: `./miniRT scene.rt`; reject missing and excess arguments.
- [x] Require the `.rt` extension and report unreadable/nonexistent inputs clearly. Evidence: actual executable rejects wrong extension/nonexistent file; normal and ASan parser variants reject a permission-denied file.
- [ ] Reject a directory named `something.rt`; do not interpret a failed read as a valid empty file.
- [ ] Return a nonzero exit status and print `Error\n` followed by an explicit message for invalid configuration. Preserve useful line numbers for line-level errors.
- [x] Accept elements in any order, with blank lines and one or more spaces between fields. Preserve existing tab and CRLF support. Evidence: fresh mixed `cy,L,pl,C,sp,A` input, whitespace/CRLF/no-final-newline probes, and the parser suite. Reader memory safety remains separate.
- [ ] Recognize exactly the required identifiers: `A`, `C`, `L`, `sp`, `pl`, and `cy`; reject unknown identifiers and incorrect field counts. Required dispatch is present, but `cb` and `cn` extensions are also accepted by the mandatory path; resolve bonus separation.
- [x] Reject duplicate `A`, `C`, and `L` declarations in the mandatory format. Evidence: current duplicate guards and parser regression suite.
- [x] Validate RGB components as integers in `[0, 255]`. Evidence: current integer parser and passing parser regression checks.
- [x] Validate ambient and point-light brightness ratios in `[0, 1]`. Evidence: current range checks and parser regression checks. The separate non-finite position/dimension problem remains open below.
- [ ] Validate positions as finite numeric triples and directions/axes as nonzero normalized triples, using a reasonable floating-point tolerance. Ordinary malformed/zero/nonunit cases reject, but `0.` followed by 400 nines is accepted as non-finite coordinates and axes in normal/ASan probes.
- [ ] Validate strictly positive sphere/cylinder diameters and cylinder heights. Zero and negative values reject; generated `NaN` dimensions pass normal/ASan validation.
- [ ] Reject malformed and non-finite numeric values without allowing them to reach matrix or intersection calculations. `parse_double()` accepts the overflowing decimal fraction as `NaN`; its final check rejects infinity but not NaN. Optimized probes still accepted the non-finite sphere position.
- [ ] Resolve and test FOV endpoints against evaluation expectations: the PDF specifies `[0, 180]`; 0/180 reject, while 0.0001/179.9999 pass. The generated-NaN FOV also passes normal/ASan validation.
- [x] Retest both parser acceptance/rejection and the complete executable. Evidence: fresh parser matrices and actual CLI cases above. This action is complete; the observed validation failures are not fixed.

## 3. P1 — Integrate all mandatory geometry into loaded scenes

Files: `src/main.c` (`prepare_parsed_scene()`), `src/scene/intersection_features*.c`, `src/scene/objects_features*.c`, `src/world.c`.

### Shared object pipeline

Current numeric scope: mandatory shapes passed through actual parsing and preparation. Representative transforms and inverse-transpose normals passed, but accepting non-finite inputs prevents a blanket valid-transform guarantee. A synthetic unsupported shape value 99 also returned a successful miss rather than the documented failure; it is not a mandatory parser-produced shape.

- [ ] Give every supported object a valid transform before it reaches `intersect()` or `normal_at()`.
- [ ] Convert parsed object position, axis/normal, and dimensions into transforms consistently with the local-space shape definitions.
- [ ] Do not apply position or dimensions both in the object transform and again in local geometry.
- [x] Transform a world-space ray into object space exactly once; do not normalize the transformed direction and change the meaning of its intersection `t` values. Evidence: solver source inspection and the passing scaled-sphere pattern ray check; exhaustive transformed-shape cases remain open.
- [x] Keep local shape solvers independent of world-space transforms. Evidence: current sphere, plane, cylinder, cube, and cone solver source inspection.
- [x] Transform normals using the inverse transpose, set vector `w = 0`, and normalize the final world-space normal. Evidence: current `normal_at()` source inspection; local shape-normal edge cases remain separate.
- [ ] Make normal calculation return a valid result or report an explicit error for every reachable shape type. The former missing-return path now has a fallback; cylinder cap/side edge cases and explicit unsupported-type behavior still need verification.
- [ ] Preserve the distinction between a successful miss and an actual intersection-processing failure.
- [x] Select the nearest nonnegative intersection correctly across mixed-object scenes. Evidence: a sphere/plane/cylinder probe selected the cylinder at `t=1`; a `t=0` hit was accepted.

### Spheres

- [x] Preserve working sphere translation and diameter-to-radius scaling from `.rt` files. Evidence: parsed center `(3,2,1)`, diameter 4 produced roots 3 and 7, with correct surface normal; the supplied sphere scene also displayed in the actual application.
- [x] Verify misses, two crossings, tangents, rays starting inside, and rays pointing away. Evidence: translated diameter-4 sphere gave roots `3,7`, tangent `5,5`, miss, inside `-2,2`, and away `-7,-3`.
- [ ] Verify surface normals and shadows after changing a sphere's center and diameter.

### Planes

Current evidence: translated horizontal, vertical, and tilted parsed planes produced expected front/back intersections and normals. The supplied axis-aligned plane scene displayed in the actual application. Tilted-plane visual sign-off remains open; ordinary numerical diffuse/shadow checks pass only under the lighting conditions stated below.

- [x] Build each parsed plane's translation and orientation from its point and normal in `prepare_parsed_scene()`. Evidence: source inspection of `prepare_object()`, `prepare_plane()`, and their application call path.
- [x] Keep the canonical local plane consistent with the existing solver: `y = 0`, normal `(0, 1, 0)`. Evidence: current local intersection and normal code.
- [ ] Render horizontal, vertical, translated, and tilted planes correctly from scene files.
- [x] Verify intersections from both sides and correct misses for parallel/coplanar rays. Evidence: horizontal/vertical/tilted planes hit at `t=3` from both sides; parallel/coplanar horizontal rays missed.
- [x] Verify transformed plane normals, diffuse lighting, and hard shadows in a mixed sphere/plane scene. Evidence: normals `(0,1,0)`, `(1,0,0)`, `(0,.6,.8)` passed sphere-occluder numerical checks with white ambient 0.2 and direct brightness 1, specular/patterns disabled. Ambient independence at other brightness/color settings still fails.

### Cylinders

Current numerical failures: center `(0,0,0)`, height 2 should place caps at `y=-1,+1`, but they are at `0,2`; downward cap roots are `1,3` instead of `2,4`. Diameter 2000 loses valid side roots `2000,4000` because the squared local radial direction is below `EPSILON`. A cap-coplanar rim ray misses both boundary crossings. Near the bottom rim, side normal `(0,0,-1)` becomes `(0,-1,0)`. These affect both visible geometry and occlusion.

Ordinary side crossings `2,4`, inside `-1,1`, tangency `3,3`, height clipping, cap crossings, and a translated tilted cylinder's side roots `4,8` passed. These successes do not clear the center, size, and boundary failures.

- [ ] Implement finite cylinder side intersections.
- [x] Clip side hits to the cylinder's height. Evidence: `intersect_walls()` tests both roots against the current local interval `0 < y < height`. This only confirms clipping exists; the world-space center convention and boundary behavior remain open.
- [ ] Implement end-cap intersections and normals for the closed finite cylinder expected by the evaluation.
- [ ] Implement side normals and handle rays starting inside the cylinder.
- [ ] Respect the parsed center, normalized axis, diameter, and height when preparing the object transform.
- [ ] Support translation, arbitrary axis orientation, and changes to both diameter and height.
- [ ] Handle tangency, axis-parallel rays, cap-parallel rays, and the side/cap boundary without invalid arithmetic or inconsistent hits.
- [x] Integrate cylinders into the existing dispatch and nearest-hit pipeline; do not leave their presence causing `intersect_world()` to fail and the renderer to return black. Evidence: mixed-shape nearest-hit probe selected the cylinder, and actual cylinder/mixed scenes displayed.
- [ ] Verify cylinder-only and mixed sphere/plane/cylinder scenes through the actual executable, not just isolated geometry helpers. Both supplied scenes were opened and visually inspected; the confirmed center/edge defects prevent correctness sign-off.

## 4. P1 — Correct camera and transformation behavior

Files: `src/camera.c`, `src/main.c` (`world_setup()`), `src/matrix/`, `src/hooks.c`.

Fresh results: `+X` gives `-X`, `-X` gives `+X`, and `+Y` with the application's fallback up vector gives `-Y`; `+Z/-Z` pass. A near-up requested direction produced approximately `(0,-.7071,-.7071)` instead. All seven tested translated origins remained `(3,4,5)`. Requested horizontal FOV 90 degrees produced 90 in landscape/square and 53.130102 in portrait. The singular inverse of scaling `(0,1,1)` contained zero finite entries out of 16. The ordinary window resize smoke passed presentation, not camera correctness.

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

Fresh probes, with specular and patterns disabled: white ambient 0.2/direct 0 gives black instead of `(0.2,0.2,0.2)`; black ambient at strength 0/direct 1 gives black instead of `(0.9,0.9,0.9)`; red ambient 0.2/direct 1 gives `(1.1,0,0)` instead of `(1.1,0.9,0.9)`. A shadow with direct brightness 0.5 gives `(0.1,0.1,0.1)` instead of `(0.2,0.2,0.2)`. `main_helper_2.c:66-73` tints the whole material by ambient color, and `objects_features_2.c:55-56` scales ambient by the point light.

Finite pixel clamping/rounding passed both debug and production-flag probes: `(-1,0.5,2)` packed to `0x0080ffff`, `(0,1,0)` to `0x00ff00ff`. The non-finite diagnostic case also returned the expected bytes, but `-ffast-math` explicitly invalidates reliance on NaN/Inf behavior. Lighting tint/endpoints still prevent checking the combined color/lighting item below.

- [ ] Keep the object's base color independent of the ambient-light color. Do not permanently multiply the whole material color by ambient color in `prepare_parsed_scene()`.
- [ ] Compute ambient illumination from object color, ambient color, and ambient ratio independently of point-light brightness.
- [ ] Compute diffuse illumination from object color, point-light brightness, and the surface/light angle independently of ambient color.
- [ ] Verify that point-light brightness zero does not erase nonzero ambient lighting. With a white object and white ambient strength `0.2`, the audit observed black instead of RGB `(0.2, 0.2, 0.2)`.
- [ ] Verify that black ambient color at zero ambient strength does not erase direct diffuse lighting. In the audit's white-object/white-light check with specular disabled, the result was black instead of RGB `(0.9, 0.9, 0.9)` for the current material's diffuse coefficient.
- [ ] Verify ambient tinting, brightness endpoints, surfaces facing away from the light, and color conversion at the image boundary.
- [x] Test mandatory ambient/diffuse behavior with optional specular and pattern effects disabled so bonus behavior cannot mask a failure. Evidence: all dedicated lighting probes disabled both; the failures above are mandatory-lighting failures.

### Hard shadows and inside hits

- [x] Cast shadow rays toward the light and count only blockers between the surface and the light, not objects beyond the light or behind the ray origin. Evidence: sphere blockers at distances 5, 15, and -5 for a light at 10 passed on three plane orientations. This verifies distance selection, not all cylinder intersections or ambient brightness.
- [ ] Preserve ambient illumination in shadow while removing direct illumination.
- [x] Calculate `over_point` after the inside/outside normal has been finalized. Evidence: source and fresh sphere/cylinder inside-hit probes; the earlier redundant calculation remains.
- [x] Verify the displacement points along the final normal. Sphere and cylinder inside hits produced `dot(over_point-point, normal)=9.99999999995e-6`, matching `+EPSILON`.
- [ ] Verify self-shadow avoidance from both outside and inside objects, including scenes with a light inside a sphere/cylinder. Ordinary inside sphere/cylinder cases passed with the light at the ray origin; near-rim cylinder normals still make a universal sign-off unsafe.
- [x] Retest cast shadows between different objects and on differently oriented planes. Evidence: sphere occluders on horizontal, vertical, and tilted planes passed the ordinary placement checks. This action does not clear the ambient/cylinder defects or the user's reported shadow problem.
- [ ] Check and propagate a failed `intersect_world()` call from shadow calculation.

## 6. P2 — Preserve responsive window behavior and cleanup

Files: `src/app.c`, `src/hooks.c`, `src/render.c`.

- [ ] Preserve successful window creation and image presentation on the evaluation platform. Passed on this Mac for supplied sphere/plane/cylinder/mixed scenes; the school's evaluation platform is not established.
- [x] Preserve Escape closing the window and exiting successfully. Actual ordinary sphere and mixed-scene runs exited 0.
- [x] Preserve the native window close button closing the program successfully. Actual plane-scene run exited 0 after clicking `AXCloseButton`.
- [x] Preserve switching windows, minimization/restoration, and resizing without losing the rendered image or corrupting state. Actual sphere scene survived Finder switching, minimize/restore, portrait/landscape resize cycles, and returned to an 800x650 window with the image visible. Camera FOV correctness is separate.
- [ ] Verify responsiveness while rendering a demanding scene, not only after rendering finishes. A 128-sphere startup stalled the accessibility request for 20 seconds and required termination. The request did not establish Escape delivery; `render_step()` still renders the full frame in one hook.
- [ ] Verify that repeated resize/render cycles and both close paths release application-owned resources. Runtime interaction passed; graphical exit leak output contained 287 leaks / 18,720 bytes rooted in framework XPC cycles. Ownership could not be fully attributed under restricted inspection.
- [ ] Verify graphics initialization/allocation failures exit with an explicit error and correct cleanup. Source has error returns/cleanup calls, but individual MLX allocation failures were not injected; no runtime sign-off.

## 7. P2 — Meet build, library, and Norm requirements

Files: `Makefile`, `inc/libft/Makefile`, `src/`, `inc/`.

### Build and dependencies

- [ ] Build the required executable name `miniRT` using `cc` and `-Wall -Wextra -Werror` for project sources. The main Makefile currently omits `-Werror`.
- [ ] Fix all required-flag compilation errors. Seven diagnostics remain: unused `shape` in `intersection_features_5.c`, unused `k` in `matrix_features_3.c`, function-address guard in `matrix_features_4.c`, three discarded-const calls in `mlx_features.c`, and the scene const mismatch in `shade.c`. The old missing normal return is no longer a compile blocker.
- [ ] Provide working `$(NAME)`, `all`, `clean`, `fclean`, and `re` targets. These targets passed in a disposable tracked-source copy, but the PDF-listed `bonus` target still fails with “No rule to make target”.
- [x] Preserve the verified no-unnecessary-relink behavior. `make -n all` after the full build scheduled nothing.
- [ ] Verify rebuilds after source/header changes, including changes inside libft, rather than relying on an already existing `libft.a`. `make -n -W src/main.c all` and `-W inc/scene.h` scheduled compilation; `-W inc/libft/ft_strlen.c` scheduled nothing, and `-W inc/libft/libft.h` did not rebuild libft.
- [x] Compile libft through its own Makefile and ensure the required library sources are part of the submitted repository. Fresh source-only build invoked libft's Makefile; the library sources are tracked. Root-to-libft change propagation fails as described above.
- [ ] Confirm with the school that MLX42 is accepted for this subject. The supplied PDF explicitly names MiniLibX; this approval was not established by the audit.
- [ ] Ensure the approved graphics library and required build dependencies are available on the evaluation machine. The current build clones MLX42 from the network when absent.
- [ ] Review `fclean`: it currently deletes the entire `MLX42` directory. Confirmed by executing it in the disposable copy. `re` succeeded only after downloading/building MLX42 again; do not rely on unavailable evaluation-network access.
- [ ] Verify project code uses only the authorized external functions. Fresh non-LTO project/libft object-symbol review found authorized I/O/allocation/math calls and MLX calls, plus compiler-generated stack/memory helpers (no explicit libc `memcpy`/`memset` calls in source). No additional direct function violation was found, but MLX42 approval remains unresolved.
- [ ] Keep optional bonus behavior/build rules separate as required by the subject. Do not treat patterns, specular reflection, or colored/multiple lights as completion of missing mandatory features.

### Norm

- [x] Make production source files pass Norminette. Current `norminette src inc` reports every production `.c` file under `src/` as OK, including the split main helpers and parser loader.
- [ ] Make all project headers pass Norminette: missing headers, indentation/alignment, long lines, macros, and declaration formatting still failed in multiple `inc/*.h` files.
- [ ] Apply the applicable Norm requirements to libft and any submitted bonus code as well.
- [ ] Decide which development-only test utilities to submit; the subject says tests need not be submitted or graded. Do not assume ungraded test code proves the submitted renderer is compliant.
- [x] Re-run `norminette src inc` after the fixes, plus any additional submitted project-code paths. Recheck executed: source and libft files passed, project headers still failed. This action checkmark does not mean overall Norm compliance.

## 8. P2 — Add the required root README

`README.md` now exists at the repository root, is tracked, and meets the supplied PDF's documentation requirements. The documented sample scene commands were exercised; known limitations are disclosed rather than presented as completed mandatory features.

- [x] Create `README.md` at the repository root and write it in English.
- [x] Use the subject's required italicized first line, with the actual 42 logins: `This project has been created as part of the 42 curriculum by sdarius-, rnauke.`
- [x] Add a **Description** section explaining the project and its purpose.
- [x] Add an **Instructions** section covering prerequisites, compilation, execution with an `.rt` file, and exit controls.
- [x] Add a **Resources** section containing the references actually used. The Ray Tracer Challenge and project/library documentation are identified; supplementary references are labeled.
- [x] Explain how AI was used, including the tasks and project parts it assisted with.
- [x] Document the supported scene format and working example commands without claiming unsupported features are implemented. The README explicitly discloses incomplete mandatory compliance.

## 9. P2 — Prepare a focused defense scene set

The subject recommends scenes that make each feature easy to inspect. Current `scenes/` contains four files: varied spheres, axis-aligned planes, three cardinal-axis cylinders all with the same dimensions, and a mixed scene that also contains cone/cube extensions. These were inspected and opened, but do not cover every category below. Temporary probes exercised many missing cases and were removed; they do not substitute for a persistent defense scene set.

- [ ] Spheres: different centers/diameters, overlapping objects, tangent/miss cases, and a camera inside a sphere.
- [ ] Planes: horizontal, vertical, tilted, translated, and viewed from either side.
- [ ] Cylinders: side views, both caps, different diameters/heights, arbitrary axes, and inside views.
- [ ] Mixed scene: spheres, planes, and cylinders together with nearest-hit visibility and cast shadows.
- [ ] Cameras: translated viewpoints, `+X`/`-X`/`+Z`/`-Z` and tilted directions, a near-up direction, different FOVs, and landscape/portrait resizing.
- [ ] Lighting: zero/nonzero point brightness, zero/nonzero ambient strength, colored ambient light, and surfaces facing toward/away from the light.
- [ ] Shadows: occluders between the surface and light, occluders beyond the light, and self-shadow checks inside/outside objects.
- [ ] Invalid inputs: missing arguments/files, wrong extension, directory input, empty files, missing required records, duplicate uppercase elements, unknown identifiers, wrong field counts, malformed/out-of-range numbers, invalid colors, invalid axes, and FOV boundary cases.
- [ ] Check memory safety and leaks on both successful and rejected inputs and after both window-close paths.

## 10. Historical audit baseline — not current executable sign-off

These checkmarks retain the original successful baseline, not additional current evidence. The current build now succeeds; the fresh audit and its narrower pass/fail results are recorded above. Historical success never overrides a current failure.

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
- [x] The root README satisfies every required section and disclosure. Verified against the supplied version-10.0 PDF.
- [ ] Required files, including library sources, are actually included in the submission. README, project sources, scenes, and libft are tracked. MLX42 remains downloaded rather than submitted; required-library approval/availability remains unresolved.
- [ ] A fresh checkout builds and runs on the evaluation platform without depending on stale local objects or unsubmitted files. A tracked working-tree source-only snapshot built and ran on this Mac after downloading MLX42; this does not establish school-platform, committed-tree, or offline availability.
- [ ] Review the implementation with a peer and be able to explain and modify the code during evaluation.

**Do not mark mandatory complete based only on a working sphere screenshot, passing pattern checks, or the existing parser suite.**
