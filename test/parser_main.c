/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdarius- <sdarius-@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+          */
/*   Created: 2026/10/06 14:30:00 by sdarius-          #+#    #+#             */
/*   Updated: 2026/10/06 14:30:00 by sdarius-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "math_local.h"
#include <stdio.h>
#include <string.h>

static int	passed;
static int	failed;

static void	check_str(const char *name, const char *got, const char *want)
{
	if ((got == want) || (got && want && strcmp(got, want) == 0))
		passed++;
	else
	{
		failed++;
		printf("FAIL %s: got \"%s\", want \"%s\"\n", name,
			got ? got : "(null)", want ? want : "(null)");
	}
}

static void	check_int(const char *name, long got, long want)
{
	if (got == want)
		passed++;
	else
	{
		failed++;
		printf("FAIL %s: got %ld, want %ld\n", name, got, want);
	}
}

static void	check_dbl(const char *name, double got, double want)
{
	if (d_equality(got, want))
		passed++;
	else
	{
		failed++;
		printf("FAIL %s: got %g, want %g\n", name, got, want);
	}
}

static void	run(const char *name, t_rt_scene *scene, const char *path,
	const char *want_error, int want_line)
{
	const char	*error;

	memset(scene, 0, sizeof(*scene));
	error = scene_load(scene, path);
	if (want_error)
	{
		check_str(name, error, want_error);
		check_int(name, scene->err_line, want_line);
	}
	else
	{
		check_str(name, error, NULL);
		check_int(name, scene->err_line, 0);
	}
}

static void	test_valid_basic(void)
{
	t_rt_scene	s;

	run("valid_basic", &s, "test/scenes/valid_basic.rt", NULL, 0);
	check_int("basic object_count", s.object_count, 3);
	check_int("basic light_count", s.light_count, 1);
	check_int("basic has_ambient", s.has_ambient, 1);
	check_int("basic has_camera", s.has_camera, 1);
	check_dbl("basic ambient ratio", s.ambient.ratio, 0.4);
	check_dbl("basic ambient color r", s.ambient.color.r, 1.0);
	check_dbl("basic camera pos x", s.camera.pos.x, -50.0);
	check_dbl("basic camera pos w", s.camera.pos.w, 1.0);
	check_dbl("basic camera dir y", s.camera.dir.y, 0.0);
	check_dbl("basic camera dir w", s.camera.dir.w, 0.0);
	check_dbl("basic camera fov", s.camera.fov, 70.0);
	check_dbl("basic light intensity r", s.lights[0].intensity.r, 0.8);
	check_dbl("basic light intensity g", s.lights[0].intensity.g, 0.8);
	check_int("basic sphere type", s.objects[0].type, OBJ_SPHERE);
	check_dbl("basic sphere radius", s.objects[0].radius, 10.0);
	check_dbl("basic sphere pos z", s.objects[0].pos.z, 20.0);
	check_dbl("basic sphere pos w", s.objects[0].pos.w, 1.0);
	check_dbl("basic sphere color r", s.objects[0].color.r, 1.0);
	check_int("basic plane type", s.objects[1].type, OBJ_PLANE);
	check_dbl("basic plane axis y", s.objects[1].axis.y, 1.0);
	check_dbl("basic plane axis w", s.objects[1].axis.w, 0.0);
	check_dbl("basic plane color b", s.objects[1].color.b, 1.0);
	check_int("basic cylinder type", s.objects[2].type, OBJ_CYLINDER);
	check_dbl("basic cylinder radius", s.objects[2].radius, 7.0);
	check_dbl("basic cylinder height", s.objects[2].height, 30.0);
	check_dbl("basic cylinder color g", s.objects[2].color.g, 1.0);
	scene_free(&s);
}

static void	test_valid_minimal(void)
{
	t_rt_scene	s;

	run("valid_minimal", &s, "test/scenes/valid_minimal.rt", NULL, 0);
	check_int("minimal object_count", s.object_count, 1);
	check_int("minimal light_count", s.light_count, 0);
	check_int("minimal has_ambient", s.has_ambient, 1);
	check_int("minimal has_camera", s.has_camera, 1);
	check_dbl("minimal sphere radius", s.objects[0].radius, 5.0);
	scene_free(&s);
}

static void	test_valid_crlf(void)
{
	t_rt_scene	s;

	run("valid_crlf", &s, "test/scenes/valid_crlf.rt", NULL, 0);
	check_int("crlf object_count", s.object_count, 1);
	check_dbl("crlf sphere color b", s.objects[0].color.b, 1.0);
	scene_free(&s);
}

static void	test_errors(void)
{
	t_rt_scene	s;

	run("err_unknown_id", &s, "test/scenes/err_unknown_id.rt",
		"unknown element identifier", 4);
	check_int("err_unknown_id cleared", s.object_count, 0);
	run("err_dup_ambient", &s, "test/scenes/err_dup_ambient.rt",
		"ambient: 'A' can only be declared once", 2);
	run("err_bad_color", &s, "test/scenes/err_bad_color.rt",
		"sphere: color must be r,g,b integers in [0, 255]", 1);
	run("err_bad_ratio", &s, "test/scenes/err_bad_ratio.rt",
		"ambient: ratio must be a number in [0.0, 1.0]", 1);
	run("err_zero_diameter", &s, "test/scenes/err_zero_diameter.rt",
		"sphere: diameter must be a number > 0", 2);
	run("err_nonunit_normal", &s, "test/scenes/err_nonunit_normal.rt",
		"plane: normal must be a unit vector x,y,z", 1);
	run("err_bad_fov", &s, "test/scenes/err_bad_fov.rt",
		"camera: fov must be a number in ]0, 180[", 1);
	run("err_too_many_fields", &s, "test/scenes/err_too_many_fields.rt",
		"too many fields on this line", 1);
	run("err_missing_file", &s, "test/scenes/does_not_exist.rt",
		"cannot read the scene file", 0);
}

int	main(void)
{
	test_valid_basic();
	test_valid_minimal();
	test_valid_crlf();
	test_errors();
	printf("parser tests: %d passed, %d failed\n", passed, failed);
	if (failed > 0)
		return (1);
	return (0);
}
