#include "minirt.h"

static bool	has_rt_ext(const char *path)
{
	size_t	len;

	len = ft_strlen(path);
	return (len > 3 && ft_strncmp(path + len - 3, ".rt", 4) == 0);
}

int	main(int argc, char **argv)
{
	t_app		app;
	const char	*error;

	if (argc != 2 || !has_rt_ext(argv[1]))
		return (print_error("Usage: ./miniRT <scene.rt>"));
	ft_bzero(&app, sizeof(app));
	error = app_init(&app);
	if (!error)
	{
		app_run(&app);
		error = app.error;
	}
	app_cleanup(&app);
	if (error)
		return (print_error(error));
	return (0);
}
