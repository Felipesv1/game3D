/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felperei <felperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 14:09:33 by fmontes           #+#    #+#             */
/*   Updated: 2024/10/29 13:21:40 by felperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void calculate_line_height(t_mlx *mlx,  double perpWallDist) {
    mlx->dt->lineHeight = (int)(S_H / perpWallDist);
    mlx->dt->drawStart = -(mlx->dt->lineHeight) / 2 + S_H / 2;
    if (mlx->dt->drawStart < 0)
        mlx->dt->drawStart = 0;
    mlx->dt->drawEnd = (mlx->dt->lineHeight) / 2 + S_H / 2;
    if (mlx->dt->drawEnd >= S_H)
        mlx->dt->drawEnd = S_H - 1;
}

// void render_column(int x, int drawStart, int drawEnd, int texX, void *tex_ptr, int *buffer, int lineHeight) {
//     for (int y = 0; y < S_H; y++) {
//         if (y < drawStart)
//             buffer[y * S_W + x] = 0x87CEEB; // Sky color
//         else if (y >= drawStart && y <= drawEnd) {
//             int d = y * 256 - S_H * 128 + lineHeight * 128;
//             int texY = ((d * TEX_HEIGHT) / lineHeight) / 256;
//             int color = get_texture_color(tex_ptr, texX, texY);
//             buffer[y * S_W + x] = color;
//         } else {
//             buffer[y * S_W + x] = 0x8B4513; // Ground color
//         }
//     }
// }

void raycasting(t_mlx *mlx) {
    mlx->rc->posX = mlx->ply->plyr_x;
     mlx->rc->posY = mlx->ply->plyr_y;

    for (int x = 0; x < S_W; x++) {
        // Initialize raycasting values
        mlx->rc->rayDirX = mlx->ray->dirX + mlx->ray->planeX * (2 * x / (double)S_W - 1);
         mlx->rc->rayDirY = mlx->ray->dirY + mlx->ray->planeY * (2 * x / (double)S_W - 1);
         mlx->rc->hit = 0;

        int mapX = (int)mlx->rc->posX;
        int mapY = (int)mlx->rc->posY;

        // Calculate delta distances
         mlx->rc->deltaDistX = (mlx->rc->rayDirX == 0) ? 1e30 :fabs(1 / mlx->rc->rayDirX);
         mlx->rc->deltaDistY = (mlx->rc->rayDirY == 0) ? 1e30 :fabs(1 / mlx->rc->rayDirY);

        // Calculate step and side distances
        calculate_step_and_side_dist(mlx->rc, mapX, mapY);
        
        // Perform DDA
        perform_dda(&mapX, &mapY, mlx->rc, mlx);

        // Calculate perpendicular wall distance
        mlx->rc->perpWallDist = calculate_perp_wall_dist( mapX, mapY, mlx->rc);

        // Calculate line height
        calculate_line_height(mlx, mlx->rc->perpWallDist);
    
        // Determine texture X coordinate
        mlx->dt->texX = (int)((mlx->rc->side == 0 ? mlx->rc->posY + mlx->rc->perpWallDist  * mlx->rc->rayDirY : mlx->rc->posX + mlx->rc->perpWallDist  * mlx->rc->rayDirX) * TEX_WIDTH) % TEX_WIDTH;

//    double wallX; // where exactly the wall was hit
//         if (mlx->rc->side == 0)
//             wallX = mlx->rc->posY + mlx->rc->perpWallDist * mlx->rc->rayDirY;
//         else
//             wallX = mlx->rc->posX + mlx->rc->perpWallDist * mlx->rc->rayDirX;
//         wallX -= floor((wallX));

//         // Determine texture X coordinate
//         mlx->dt->texX = (int)wallX * (double)TEX_WIDTH;
//         if (mlx->rc->side == 0 && mlx->rc->rayDirX > 0)
//             mlx->dt->texX = TEX_WIDTH - mlx->dt->texX - 1;
//         if (mlx->rc->side == 1 && mlx->rc->rayDirX < 0)
//             mlx->dt->texX = TEX_WIDTH - mlx->dt->texX - 1;

        // Render the column
    //     for (int y = 0; y < S_H; y++) {
    //     if (y < drawStart)
    //         buffer[y * S_W + x] = 0x87CEEB; // Sky color
    //     else if (y >= drawStart && y <= drawEnd) {
    //         int d = y * 256 - S_H * 128 + lineHeight * 128;
    //         int texY = ((d * TEX_HEIGHT) / lineHeight) / 256;
    //         int color = get_texture_color(mlx->textures->north, texX, texY);
    //         buffer[y * S_W + x] = color;
    //     } else {
    //         buffer[y * S_W + x] = 0x8B4513; // Ground color
    //     }
    // }
        draw_buffer(mlx, x);
    }
}