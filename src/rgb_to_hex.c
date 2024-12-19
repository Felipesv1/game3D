/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_to_hex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felperei <felperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 13:15:18 by felperei          #+#    #+#             */
/*   Updated: 2024/12/19 13:26:15 by felperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"


int rgb_to_hex(char *texture)
{
    int r;
    int g;
    int b;
    int color;
    char **rgb;
    rgb = ft_split(texture, ',');
    r = ft_atoi(rgb[0]);
    g = ft_atoi(rgb[1]);
    b = ft_atoi(rgb[2]);
    color = (r << 16) + (g << 8) + b;
    return (color);
    
}