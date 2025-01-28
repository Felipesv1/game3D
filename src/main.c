/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felperei <felperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 13:19:59 by felperei          #+#    #+#             */
/*   Updated: 2025/01/28 15:58:41 by felperei         ###   ########.fr       */
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

void	verify_ac(int ac, char **av)
{
	if (ac != 2)
	{
		printf("Usage: %s <map_file>\n", av[0]);
		exit(1);
	}
}

static void	condition_square_map(int j, int i, char **map, char **new_map)
{
	if (j < (int)ft_strlen(map[i]))
		new_map[i][j] = map[i][j];
	else
		new_map[i][j] = '0';
}

char static	**square_map(char **map, t_data *dt)
{
	int		i;
	int		j;
	int		max_row;
	char	**new_map;

	max_row = ft_strlen(map[dt->max_row]);
	new_map = malloc(sizeof(char *) * (dt->rows + 1));
	if (!new_map)
		exit(1);
	i = 0;
	while (i < dt->rows)
	{
		new_map[i] = malloc(sizeof(char) * (max_row + 1));
		if (!new_map[i])
			exit(1);
		j = 0;
		while (j < max_row)
		{
			condition_square_map(j, i, map, new_map);
			j++;
		}
		new_map[i][j] = '\0';
		i++;
	}
	return (new_map);
}

int	main(int ac, char **av)
{
	t_mlx	mlx;
	int		i;
	int		j;
	char	**map;

	verify_ac(ac, av);
	initialize_mlx_structures(&mlx);
	mlx.dt->backup = read_map(av[1]);
	is_format_valid(av[1], mlx);
	mlx.dt->map2d = get_map(mlx.dt->backup);
	size_map(mlx.dt);
	find_player(&mlx);
	initialize_graphics(&mlx);
	load_textures(&mlx, &i, &j);
	validate_path(mlx);
	is_valid_rgb(mlx.dt->map_texts->ceiling, mlx);
	is_valid_rgb(mlx.dt->map_texts->floor, mlx);
	free_matrix(mlx.dt->backup);
	map = square_map(mlx.dt->map2d, mlx.dt);
	flood_fill(mlx.ply->plyr_x, mlx.ply->plyr_y, map);
	validate_map(map, mlx);
	free_matrix(map);
	loop_main(mlx);
	return (0);
}
