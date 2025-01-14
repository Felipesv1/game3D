/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felperei <felperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 13:56:51 by felperei          #+#    #+#             */
/*   Updated: 2025/01/14 11:31:21 by felperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void find_player(t_mlx *mlx)
{
    int x = 0;
    int y = 0;
    while (mlx->dt->map2d[x])
    {
        y = 0;
        while (mlx->dt->map2d[x][y])
        {
            
            if (mlx->dt->map2d[x][y] == 'N' || mlx->dt->map2d[x][y] == 'S' || mlx->dt->map2d[x][y] == 'W' || mlx->dt->map2d[x][y] == 'E')
            {
                mlx->ply->plyr_x = x + 0.5;
                mlx->ply->plyr_y = y + 0.5;
                if (mlx->dt->map2d[x][y] == 'N')
                {
                    mlx->ray->dirX = -1.0;
                    mlx->ray->dirY = 0.0;
                    mlx->ray->planeX = 0.0;
                    mlx->ray->planeY = 0.66;
                    mlx->ply->n_player++;
                }
                else if (mlx->dt->map2d[x][y] == 'S')
                {
                    mlx->ray->dirX = 1.0;
                    mlx->ray->dirY = 0.0;
                    mlx->ray->planeX = 0.0;
                    mlx->ray->planeY = -0.66;
                    mlx->ply->n_player++;
                }
                else if (mlx->dt->map2d[x][y] == 'E')
                {
                    mlx->ray->dirX = 0.0;
                    mlx->ray->dirY = 1.0;
                    mlx->ray->planeX = 0.66;
                    mlx->ray->planeY = 0.0;
                    mlx->ply->n_player++;
                }
                else if (mlx->dt->map2d[x][y] == 'W')
                {
                    mlx->ray->dirX = 0.0;
                    mlx->ray->dirY = -1.0;
                    mlx->ray->planeX = -0.66;
                    mlx->ray->planeY = 0.0;
                    mlx->ply->n_player++;
                }
                mlx->dt->map2d[x][y] = '0';
            }
            y++;
        }
        x++;
    }
    if (mlx->ply->n_player != 1)
    {
        printf("Error\n");
        exit(1);
    }
}