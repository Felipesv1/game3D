/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felperei <felperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 13:19:59 by felperei          #+#    #+#             */
/*   Updated: 2025/01/28 11:24:32 by felperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	exit_wrapper(void *param)
{
	(void)param;
	exit(0);
	return (0);
}

void	loop_main(t_mlx mlx)
{
	int	done;

	done = 0;
	while (!done)
	{
		mlx_hook(mlx.win, 17, 0L, exit_wrapper, NULL);
		mlx_hook(mlx.win, KeyPress, KeyPressMask, keypress, &mlx);
		raycasting(&mlx);
		mlx_put_image_to_window(mlx.mlx_p, mlx.win, mlx.img_ptr, 0, 0);
		mlx_loop(mlx.mlx_p);
	}
}

static int	is_valid(int x, int y, char **map)
{
	if (x >= 0 && map[x] && y >= 0 && map[x][y] && (map[x][y] == '0'
			|| map[x][y] == ' ' || map[x][y] == 'N' || map[x][y] == 'S'
			|| map[x][y] == 'W' || map[x][y] == 'E'))
		return (1);
	return (0);
}

void	verify_ac(int ac, char **av)
{
	if (ac < 2)
	{
		printf("Usage: %s <map_file>\n", av[0]);
		exit(1);
	}
}

int	main(int ac, char **av)
{
	t_mlx	mlx;
	int		i;
	int		j;

	verify_ac(ac, av);
	initialize_mlx_structures(&mlx);
	mlx.dt->backup = read_map(av[1]);
	is_format_valid(av[1], mlx);
	mlx.dt->map2d = get_map(mlx.dt->backup);
	mlx.dt->map_copy = get_map(mlx.dt->backup);
	size_map(mlx.dt);
	find_player(&mlx);
	initialize_graphics(&mlx);
	load_textures(&mlx, &i, &j);
	validate_path(mlx);
	is_valid_rgb(mlx.dt->map_texts->ceiling, mlx);
	is_valid_rgb(mlx.dt->map_texts->floor, mlx);
	free_matrix(mlx.dt->backup);
	flood_fill(mlx.ply->plyr_x, mlx.ply->plyr_y, mlx.dt->map_copy);
	validate_map(mlx.dt->map_copy, mlx);
	loop_main(mlx);
	return (0);
}
