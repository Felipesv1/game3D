/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_main2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboxuser <vboxuser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 14:42:40 by vboxuser          #+#    #+#             */
/*   Updated: 2025/01/15 15:12:54 by vboxuser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int validate_path(t_mlx mlx)
{
    if (check_path(mlx.dt->map_texts->text_no) == 1)
	{
		printf("Error na imagem NO\n");
		return (1);
	}
    else if (check_path(mlx.dt->map_texts->text_so) == 1)
    {
        printf("Error na imagem SO\n");
        return (1);
    }
    if (check_path(mlx.dt->map_texts->text_we) == 1)
	{
		printf("Error na imagem WE\n");
		return (1);
	}
    if (check_path(mlx.dt->map_texts->text_ea) == 1)
	{
		printf("Error na imagem EA\n");
		return (1);
	}
    return (0);
}