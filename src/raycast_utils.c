/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felperei <felperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 14:08:39 by fmontes           #+#    #+#             */
/*   Updated: 2024/12/19 11:13:47 by felperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void draw_buffer(t_mlx *mlx, int x)
{
    int y;
    int color;
    for (y = 0; y < S_H; y++)
    {

        if (y < mlx->dt->drawStart)
            color = 0x87CEEB; // Sky color
        else if ( y < mlx->dt->drawEnd)
        {
           
            int d = y * 256 - S_H * 128 + mlx->dt->lineHeight * 128;
            int texY = ((d * TEX_HEIGHT) / mlx->dt->lineHeight) / 256;
            color = get_texture_color(mlx, mlx->dt->texX, texY);
        }
        else
            color = 0x8B4513; // Ground color
        mlx->dt->data[(y * S_W + x) * 4] = color & 0xFF;
        mlx->dt->data[(y * S_W + x) * 4 + 1] = (color >> 8) & 0xFF;
        mlx->dt->data[(y * S_W + x) * 4 + 2] = (color >> 16) & 0xFF;
    }
}

int get_texture_color(t_mlx *mlx, int x, int y)
{

    char *data;
    int bpp, size_line, endian;
    void *img_ptr;
    if(mlx->rc->side && mlx->rc->rayDirY > 0)
        img_ptr = mlx->textures->east->ptr;
    else if (mlx->rc->side && mlx->rc->rayDirY < 0)
        img_ptr = mlx->textures->west->ptr;
    else if (!mlx->rc->side && mlx->rc->rayDirX > 0)
        img_ptr = mlx->textures->south->ptr;
    else 
        img_ptr = mlx->textures->north->ptr;
    data = mlx_get_data_addr(img_ptr, &bpp, &size_line, &endian);
    return *(int *)(data + (y * size_line + x * (bpp / 8)));
}

void calculate_step_and_side_dist(t_raycast *rc, int mapX, int mapY)
{
    if (rc->rayDirX < 0)
    {
        rc->stepX = -1;
        rc->sideDistX = (rc->posX - mapX) * rc->deltaDistX;
    }
    else
    {
        rc->stepX = 1;
        rc->sideDistX = (mapX + 1.0 - rc->posX) * rc->deltaDistX;
    }
    if (rc->rayDirY < 0)
    {
        rc->stepY = -1;
        rc->sideDistY = (rc->posY - mapY) * rc->deltaDistY;
    }
    else
    {
        rc->stepY = 1;
        rc->sideDistY = (mapY + 1.0 - rc->posY) * rc->deltaDistY;
    }
}

void perform_dda(int *mapX, int *mapY, t_raycast *rc, t_mlx *mlx)
{

    while (!(rc->hit))
    {
        if (rc->sideDistX < rc->sideDistY)
        {
            rc->sideDistX += rc->deltaDistX;
            *mapX += rc->stepX;
            rc->side = 0;
        }
        else
        {
            rc->sideDistY += rc->deltaDistY;
            *mapY += rc->stepY;
            rc->side = 1;
        }
        if (mlx->dt->map[*mapX][*mapY] > 0)
            rc->hit = 1;
    }
}

double calculate_perp_wall_dist(int mapX, int mapY, t_raycast *rc)
{
    if (rc->side == 0)
        return (mapX - rc->posX + (1 - rc->stepX) / 2) / rc->rayDirX;
    else
        return (mapY - rc->posY + (1 - rc->stepY) / 2) / rc->rayDirY;
}