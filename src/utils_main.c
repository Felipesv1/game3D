/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboxuser <vboxuser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:08:27 by felperei          #+#    #+#             */
/*   Updated: 2025/01/17 17:31:55 by vboxuser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	initialize_mlx_structures(t_mlx *mlx)
{
	mlx->ply = malloc(sizeof(t_player));
	mlx->ray = malloc(sizeof(t_ray));
	mlx->rc = malloc(sizeof(t_raycast));
	mlx->textures = malloc(sizeof(t_textures));
	mlx->textures->north = malloc(sizeof(t_texture));
	mlx->textures->east = malloc(sizeof(t_texture));
	mlx->textures->south = malloc(sizeof(t_texture));
	mlx->textures->west = malloc(sizeof(t_texture));
	mlx->dt = malloc(sizeof(t_data));
	mlx->dt->map_texts = malloc(sizeof(t_map_texture));
}

void	initialize_graphics(t_mlx *mlx)
{
	mlx->mlx_p = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx_p, S_W, S_H, "Cub3d");
	mlx->img_ptr = mlx_new_image(mlx->mlx_p, S_W, S_H);
	mlx->dt->data = mlx_get_data_addr(mlx->img_ptr, &mlx->dt->bits_per_pixel,
			&mlx->dt->size_line, &mlx->dt->endian);
}

void	load_textures(t_mlx *mlx, int *i, int *j)
{
	get_textures(mlx->dt);
	get_floor_ceiling(mlx->dt);
	mlx->dt->map_texts->f = rgb_to_hex(mlx->dt->map_texts->floor);
	mlx->dt->map_texts->c = rgb_to_hex(mlx->dt->map_texts->ceiling);
	mlx->textures->north->ptr = mlx_xpm_file_to_image(mlx->mlx_p,
			mlx->dt->map_texts->text_no, i, j);
	mlx->textures->south->ptr = mlx_xpm_file_to_image(mlx->mlx_p,
			mlx->dt->map_texts->text_so, i, j);
	mlx->textures->west->ptr = mlx_xpm_file_to_image(mlx->mlx_p,
			mlx->dt->map_texts->text_we, i, j);
	mlx->textures->east->ptr = mlx_xpm_file_to_image(mlx->mlx_p,
			mlx->dt->map_texts->text_ea, i, j);
	/* printf("|%s|\n", mlx->dt->map_texts->text_no);
	printf("|%s|\n", mlx->dt->map_texts->text_so);
	printf("|%s|\n", mlx->dt->map_texts->text_we);
	printf("|%s|\n", mlx->dt->map_texts->text_ea);
	printf("%s\n", mlx->dt->map_texts->floor);
	printf("%s\n", mlx->dt->map_texts->ceiling); */
}

void	cleanup(t_mlx *mlx)
{
	free(mlx->ply);
	free(mlx->ray);
	free(mlx->rc);
	free(mlx->textures->north);
	free(mlx->textures->south);
	free(mlx->textures->west);
	free(mlx->textures->east);
	free(mlx->textures);
	free(mlx->dt);
}

int	check_path(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (1);
	close(fd);
	return (0);
}
