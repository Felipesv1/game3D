/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felperei <felperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 13:19:59 by felperei          #+#    #+#             */
/*   Updated: 2025/01/14 15:50:13 by felperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	loop_main(t_mlx mlx)
{
	int	done;

	done = 0;
	while (!done)
	{
		mlx_hook(mlx.win, 17, 0L, (int (*)())exit, NULL);
		mlx_hook(mlx.win, KeyPress, KeyPressMask, keypress, &mlx);
		raycasting(&mlx);
		mlx_put_image_to_window(mlx.mlx_p, mlx.win, mlx.img_ptr, 0, 0);
		mlx_loop(mlx.mlx_p);
	}
}
// Função de Flood Fill
static int	is_valid(int x, int y, char **map)
{
	if (x >= 0 && map[x] && y >= 0 && map[x][y] && (map[x][y] == '0'
			|| map[x][y] == ' ' || map[x][y] == 'N' || map[x][y] == 'S'
			|| map[x][y] == 'W' || map[x][y] == 'E'))
		return (1);
	return (0);
}

int	flood_fill(int x, int y, char **map)
{
	if (!is_valid(x, y, map) || map[x][y] == 'F')
		return (0);
	map[x][y] = 'F';
	if (flood_fill(x + 1, y, map))
		return (1);
	if (flood_fill(x - 1, y, map))
		return (1);
	if (flood_fill(x, y + 1, map))
		return (1);
	if (flood_fill(x, y - 1, map))
		return (1);
	return (0);
}

int	main(int ac, char **av)
{
	t_mlx	mlx;
	int		i;
	int		j;

	if (ac < 2)
	{
		fprintf(stderr, "Usage: %s <map_file>\n", av[0]);
		return (1);
	}
	initialize_mlx_structures(&mlx);
	mlx.dt->backup = read_map(av[1]);
	mlx.dt->map2d = get_map(mlx.dt->backup);
	char **teste = get_map(mlx.dt->backup);
	size_map(mlx.dt);
	initialize_graphics(&mlx);
	find_player(&mlx);
	load_textures(&mlx, &i, &j);
	int a = 0;
	while (teste[a])
	{
		printf("%s\n", teste[a]);
		a++;
	}
	ft_printf("\n");
	flood_fill(mlx.ply->plyr_x, mlx.ply->plyr_y, teste);
	 a = 0;
	while (teste[a])
	{
		printf("%s\n", teste[a]);
		a++;
	}
	loop_main(mlx);
	cleanup(&mlx);
	return (0);
}
