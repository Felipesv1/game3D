/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felperei <felperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:08:27 by felperei          #+#    #+#             */
/*   Updated: 2025/01/30 11:17:15 by felperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	initialize_mlx_structures(t_mlx *mlx)
{
	mlx->ply = ft_calloc(1, sizeof(t_player));
	mlx->ray = ft_calloc(1, sizeof(t_ray));
	mlx->rc = ft_calloc(1, sizeof(t_raycast));
	mlx->textures = ft_calloc(1, sizeof(t_textures));
	mlx->textures->north = ft_calloc(1, sizeof(t_texture));
	mlx->textures->east = ft_calloc(1, sizeof(t_texture));
	mlx->textures->south = ft_calloc(1, sizeof(t_texture));
	mlx->textures->west = ft_calloc(1, sizeof(t_texture));
	mlx->dt = ft_calloc(1, sizeof(t_data));
	mlx->dt->map_texts = ft_calloc(1, sizeof(t_map_texture));
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
	free(mlx->dt->map_texts->text_no);
	free(mlx->dt->map_texts->text_so);
	free(mlx->dt->map_texts->text_we);
	free(mlx->dt->map_texts->text_ea);
	free(mlx->dt->map_texts->floor);
	free(mlx->dt->map_texts->ceiling);
	free(mlx->dt->map_texts);
	free_matrix(mlx->dt->backup);
	free_matrix(mlx->dt->map2d);
	free_matrix(mlx->dt->map_copy);
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
