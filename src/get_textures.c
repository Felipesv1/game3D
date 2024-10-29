/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felperei <felperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 11:02:17 by felperei          #+#    #+#             */
/*   Updated: 2024/10/29 14:24:18 by felperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void get_textures( t_data *data)
{
    int i; 
    int j;

    i = 0;
    while (data->backup[i])
    {
        j = 0;
        while (data->backup[i][j])
        {
            if (i == 4)
                break;
            if (data->backup[i][j] == 'N' && data->backup[i][j + 1] == 'O')
                data->map_texts->text_no = ft_strdup(data->backup[i] + 3);
            else if (data->backup[i][j] == 'S' && data->backup[i][j + 1] == 'O')
                 data->map_texts->text_so = ft_strdup(data->backup[i] + 3);
            else if (data->backup[i][j] == 'W' && data->backup[i][j + 1] == 'E')
                 data->map_texts->text_we = ft_strdup(data->backup[i] + 3);
            else if (data->backup[i][j] == 'E' && data->backup[i][j + 1] == 'A')
                 data->map_texts->text_ea = ft_strdup(data->backup[i] + 3);
            j++;
        }
        i++;
    }
}

void get_floor_ceiling(t_data *data)
{
    int i;
    int j;

    i = 4;
    while (data->backup[i])
    {
        j = 0;
        while (data->backup[i][j])
        {
            if (i == 7)
                break;          
            if (data->backup[i][j] == 'F')
                data->map_texts->floor = ft_strdup(data->backup[i] + 2);
            else if (data->backup[i][j] == 'C')
                data->map_texts->ceiling = ft_strdup(data->backup[i] + 2);
            j++;
        }
        i++;
    }
}
