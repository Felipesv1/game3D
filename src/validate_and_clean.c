/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_and_clean.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felperei <felperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 14:42:40 by vboxuser          #+#    #+#             */
/*   Updated: 2025/01/30 11:01:53 by felperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	clean_path(t_mlx *mlx)
{
	free_matrix(mlx->dt->backup);
	free_matrix(mlx->dt->map2d);
	free_matrix(mlx->dt->map_copy);
	free(mlx->dt->map_texts->text_no);
	free(mlx->dt->map_texts->text_so);
	free(mlx->dt->map_texts->text_we);
	free(mlx->dt->map_texts->text_ea);
	free(mlx->dt->map_texts->floor);
	free(mlx->dt->map_texts->ceiling);
	free(mlx->dt->map_texts);
	free(mlx->textures->north);
	free(mlx->textures->south);
	free(mlx->textures->west);
	free(mlx->textures->east);
	free(mlx->textures);
	mlx_destroy_image(mlx->mlx_p, mlx->img_ptr);
	mlx_destroy_window(mlx->mlx_p, mlx->win);
	mlx_destroy_display(mlx->mlx_p);
	free(mlx->mlx_p);
	free(mlx->ply);
	free(mlx->ray);
	free(mlx->rc);
	free(mlx->dt);
}

static void	clean_map(t_mlx *mlx)
{
	free(mlx->ply);
	free(mlx->ray);
	free(mlx->rc);
	free(mlx->dt->map_texts->text_no);
	free(mlx->dt->map_texts->text_so);
	free(mlx->dt->map_texts->text_we);
	free(mlx->dt->map_texts->text_ea);
	free(mlx->dt->map_texts->floor);
	free(mlx->dt->map_texts->ceiling);
	free(mlx->dt->map_texts);
	free_matrix(mlx->dt->map2d);
	free_matrix(mlx->dt->map_copy);
	free(mlx->dt);
	destroy_image(mlx);
	mlx_destroy_window(mlx->mlx_p, mlx->win);
	mlx_destroy_display(mlx->mlx_p);
	free(mlx->textures->north);
	free(mlx->textures->south);
	free(mlx->textures->west);
	free(mlx->textures->east);
	free(mlx->textures);
	free(mlx->mlx_p);
}

void	validate_path(t_mlx mlx)
{
	if (check_path(mlx.dt->map_texts->text_no) == 1)
	{
		clean_path_no(mlx);
		exit(1);
	}
	else if (check_path(mlx.dt->map_texts->text_so) == 1)
	{
		clean_path_so(mlx);
		exit(1);
	}
	if (check_path(mlx.dt->map_texts->text_we) == 1)
	{
		clean_path_we(mlx);
		exit(1);
	}
	if (check_path(mlx.dt->map_texts->text_ea) == 1)
	{
		clean_path_ea(mlx);
		exit(1);
	}
}

void	validate_map(char **map, t_mlx mlx)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'F')
			{
				if (i == 0 || j == 0 || !map[i + 1] || !map[i][j + 1] || map[i
					- 1][j] == ' ' || map[i + 1][j] == ' ' || map[i][j
					- 1] == ' ' || map[i][j + 1] == ' ')
				{
					printf("Error\n");
					free_matrix(map);
					clean_map(&mlx);
					exit(1);
				}
			}
			j++;
		}
		i++;
	}
}
