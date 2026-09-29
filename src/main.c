#include "../inc/minirt.h"

static bool	has_rt_ext(char *path)
{
	size_t	len;

	len = ft_strlen(path);
	return (len > 3 && ft_strncmp(path + len - 3, ".rt", 4) == 0);
}

int	main(int argc, char **argv)
{
	t_app		app;
	const char	*err;

	if (argc != 2 || !has_rt_ext(argv[1]))
		return (print_error("Usage: ./miniRT <scene.rt>"));
	ft_bzero(&app, sizeof(app));
	err = app_init(&app);
	if (!err)
	{
		app_run(&app);
		err = app.error;
	}
	app_cleanup(&app);
	if (err)
		return (print_error(err));
	return (0);
}
