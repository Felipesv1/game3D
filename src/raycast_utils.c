/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felperei <felperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 14:08:39 by fmontes           #+#    #+#             */
/*   Updated: 2025/01/14 13:17:11 by felperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_buffer(t_mlx *mlx, int x)
{
	int	y;
	int	color;
	int	d;
	int	texY;

	for (y = 0; y < S_H; y++)
	{
		if (y < mlx->dt->draw_start)
			color = mlx->dt->map_texts->c; // Sky color
		else if (y < mlx->dt->draw_end)
		{
			d = y * 256 - S_H * 128 + mlx->dt->line_height * 128;
			texY = ((d * TEX_HEIGHT) / mlx->dt->line_height) / 256;
			color = get_texture_color(mlx, mlx->dt->tex_x, texY);
		}
		else
			color = mlx->dt->map_texts->f; // Ground color
		mlx->dt->data[(y * S_W + x) * 4] = color & 0xFF;
		mlx->dt->data[(y * S_W + x) * 4 + 1] = (color >> 8) & 0xFF;
		mlx->dt->data[(y * S_W + x) * 4 + 2] = (color >> 16) & 0xFF;
	}
}

int	get_texture_color(t_mlx *mlx, int x, int y)
{
	char	*data;
	void	*img_ptr;

	int bpp, size_line, endian;
	if (mlx->rc->side && mlx->rc->raydir_y > 0)
		img_ptr = mlx->textures->east->ptr;
	else if (mlx->rc->side && mlx->rc->raydir_y < 0)
		img_ptr = mlx->textures->west->ptr;
	else if (!mlx->rc->side && mlx->rc->raydir_x > 0)
		img_ptr = mlx->textures->south->ptr;
	else
		img_ptr = mlx->textures->north->ptr;
	data = mlx_get_data_addr(img_ptr, &bpp, &size_line, &endian);
	return (*(int *)(data + (y * size_line + x * (bpp / 8))));
}

void	calculate_step_and_side_dist(t_raycast *rc, int mapX, int mapY)
{
	if (rc->raydir_x < 0)
	{
		rc->step_x = -1;
		rc->side_dist_x = (rc->pos_x - mapX) * rc->delta_dist_x;
	}
	else
	{
		rc->step_x = 1;
		rc->side_dist_x = (mapX + 1.0 - rc->pos_x) * rc->delta_dist_x;
	}
	if (rc->raydir_y < 0)
	{
		rc->step_y = -1;
		rc->side_dist_y = (rc->pos_y - mapY) * rc->delta_dist_y;
	}
	else
	{
		rc->step_y = 1;
		rc->side_dist_y = (mapY + 1.0 - rc->pos_y) * rc->delta_dist_y;
	}
}

void	perform_dda(int *mapX, int *mapY, t_raycast *rc, t_mlx *mlx)
{
	while (!(rc->hit))
	{
		if (rc->side_dist_x < rc->side_dist_y)
		{
			rc->side_dist_x += rc->delta_dist_x;
			*mapX += rc->step_x;
			rc->side = 0;
		}
		else
		{
			rc->side_dist_y += rc->delta_dist_y;
			*mapY += rc->step_y;
			rc->side = 1;
		}
		if (mlx->dt->map2d[*mapX][*mapY] != '0')
			rc->hit = 1;
	}
}

double	calculate_perp_wall_dist(int mapX, int mapY, t_raycast *rc)
{
	if (rc->side == 0)
		return ((mapX - rc->pos_x + (1 - rc->step_x) / 2) / rc->raydir_x);
	else
		return ((mapY - rc->pos_y + (1 - rc->step_y) / 2) / rc->raydir_y);
}