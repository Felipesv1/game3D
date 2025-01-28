/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felperei <felperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 13:17:57 by felperei          #+#    #+#             */
/*   Updated: 2025/01/28 13:24:10 by felperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	move_player_forward(t_mlx *mlx)
{
	if (mlx->dt->map2d[(int)(mlx->rc->pos_x + mlx->ray->dir_x
			* PLAYER_SPEED)][(int)mlx->rc->pos_y] == '0')
		mlx->ply->plyr_x += mlx->ray->dir_x * PLAYER_SPEED;
	if (mlx->dt->map2d[(int)mlx->rc->pos_x][(int)(mlx->rc->pos_y
		+ mlx->ray->dir_y * PLAYER_SPEED)] == '0')
		mlx->ply->plyr_y += mlx->ray->dir_y * PLAYER_SPEED;
}

void	move_player_backward(t_mlx *mlx)
{
	if (mlx->dt->map2d[(int)(mlx->rc->pos_x - mlx->ray->dir_x
			* PLAYER_SPEED)][(int)(mlx->rc->pos_y)] == '0')
		mlx->ply->plyr_y -= mlx->ray->dir_y * PLAYER_SPEED;
	if (mlx->dt->map2d[(int)mlx->rc->pos_x][(int)(mlx->rc->pos_y
		- mlx->ray->dir_y * PLAYER_SPEED)] == '0')
		mlx->ply->plyr_x -= mlx->ray->dir_x * PLAYER_SPEED;
}

void	move_player_left(t_mlx *mlx)
{
	if (mlx->dt->map2d[(int)(mlx->rc->pos_x - mlx->ray->dir_y
			* PLAYER_SPEED)][(int)mlx->rc->pos_y] == '0')
		mlx->ply->plyr_x -= mlx->ray->dir_y * PLAYER_SPEED;
	if (mlx->dt->map2d[(int)mlx->rc->pos_x][(int)(mlx->rc->pos_y
		+ mlx->ray->dir_x * PLAYER_SPEED)] == '0')
		mlx->ply->plyr_y += mlx->ray->dir_x * PLAYER_SPEED;
}

void	move_player_right(t_mlx *mlx)
{
	if (mlx->dt->map2d[(int)(mlx->rc->pos_x - mlx->ray->dir_y
			* PLAYER_SPEED)][(int)mlx->rc->pos_y] == '0')
		mlx->ply->plyr_x += mlx->ray->dir_y * PLAYER_SPEED;
	if (mlx->dt->map2d[(int)mlx->rc->pos_x][(int)(mlx->rc->pos_y
		+ mlx->ray->dir_x * PLAYER_SPEED)] == '0')
		mlx->ply->plyr_y -= mlx->ray->dir_x * PLAYER_SPEED;
}
