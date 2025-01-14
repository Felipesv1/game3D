/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felperei <felperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:08:27 by felperei          #+#    #+#             */
/*   Updated: 2025/01/14 14:08:38 by felperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	initialize_mlx_structures(t_mlx *mlx)
{
	mlx->ply = calloc(1, sizeof(t_player));
	mlx->ray = calloc(1, sizeof(t_ray));
	mlx->rc = calloc(1, sizeof(t_raycast));
	mlx->textures = calloc(1, sizeof(t_textures));
	mlx->textures->north = calloc(1, sizeof(t_texture));
	mlx->textures->east = calloc(1, sizeof(t_texture));
	mlx->textures->south = calloc(1, sizeof(t_texture));
	mlx->textures->west = calloc(1, sizeof(t_texture));
	mlx->dt = calloc(1, sizeof(t_data));
	mlx->dt->map_texts = calloc(1, sizeof(t_map_texture));
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
	printf("|%s|\n", mlx->dt->map_texts->text_no);
	printf("|%s|\n", mlx->dt->map_texts->text_so);
	printf("|%s|\n", mlx->dt->map_texts->text_we);
	printf("|%s|\n", mlx->dt->map_texts->text_ea);
	printf("%s\n", mlx->dt->map_texts->floor);
	printf("%s\n", mlx->dt->map_texts->ceiling);
}

void	cleanup(t_mlx *mlx)
{
	mlx_destroy_image(mlx->mlx_p, mlx->img_ptr);
	mlx_destroy_window(mlx->mlx_p, mlx->win);
	mlx_destroy_display(mlx->mlx_p);
	free(mlx->mlx_p);
	free(mlx->ply);
	free(mlx->ray);
	free(mlx->textures);
	free(mlx->rc);
}
