#include "../cub3d.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>





void print_int_map(int **map, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", map[i][j]);
        }
        printf("\n");
    }
}

int main(int ac, char **av) {
	  if (ac < 2) {
        fprintf(stderr, "Usage: %s <map_file>\n", av[0]);
        return 1;
    }

    t_mlx mlx;
    mlx.ply = calloc(1, sizeof(t_player));
    mlx.ray = calloc(1, sizeof(t_ray));
    mlx.rc = calloc(1, sizeof(t_raycast));
    mlx.textures = calloc(1, sizeof(t_textures));
    mlx.textures->north = calloc(1, sizeof(t_texture));
    mlx.textures->east = calloc(1, sizeof(t_texture));
    mlx.textures->south = calloc(1, sizeof(t_texture));
    mlx.textures->west = calloc(1, sizeof(t_texture));
    mlx.dt = calloc(1, sizeof(t_data));
    mlx.dt->map_texts = calloc(1, sizeof(t_map_texture));
    mlx.dt->backup = read_map(av[1]);
    mlx.dt->map2d = get_map( mlx.dt->backup);
    size_map(mlx.dt);
    // mlx.dt->map = copy_char_to_int(mlx.dt->map2d, 20, 20);
    mlx.mlx_p = mlx_init();
    mlx.win = mlx_new_window(mlx.mlx_p, S_W, S_H, "Cub3d");
    mlx.img_ptr = mlx_new_image(mlx.mlx_p, S_W, S_H); 
    mlx.dt->data = mlx_get_data_addr(mlx.img_ptr, &mlx.dt->bits_per_pixel, &mlx.dt->size_line, &mlx.dt->endian);
    int i, j;
    get_textures(mlx.dt);
    get_floor_ceiling(mlx.dt);
    mlx.dt->map_texts->f = rgb_to_hex(mlx.dt->map_texts->floor);
    mlx.dt->map_texts->c = rgb_to_hex(mlx.dt->map_texts->ceiling);
    mlx.textures->north->ptr = mlx_xpm_file_to_image(mlx.mlx_p, mlx.dt->map_texts->text_no, &i, &j);
    mlx.textures->south->ptr = mlx_xpm_file_to_image(mlx.mlx_p, mlx.dt->map_texts->text_so, &i, &j);
    mlx.textures->west->ptr = mlx_xpm_file_to_image(mlx.mlx_p, mlx.dt->map_texts->text_we, &i, &j);
    mlx.textures->east->ptr = mlx_xpm_file_to_image(mlx.mlx_p, mlx.dt->map_texts->text_ea, &i, &j);


    printf("|%s|\n",  mlx.dt->map_texts->text_no);
    printf("|%s|\n",  mlx.dt->map_texts->text_so);
    printf("|%s|\n",  mlx.dt->map_texts->text_we);
    printf("|%s|\n",  mlx.dt->map_texts->text_ea);
    printf("%s\n",  mlx.dt->map_texts->floor);
    printf("%s\n",  mlx.dt->map_texts->ceiling);

    find_player(&mlx);
    // Main loop
    int done = 0;
    while (!done) {
        // Handle events
        mlx_hook(mlx.win, 17, 0L, (int (*)())exit, NULL); // Close window
        mlx_hook(mlx.win, KeyPress, KeyPressMask, keypress, &mlx);
        raycasting(&mlx);
        mlx_put_image_to_window(mlx.mlx_p, mlx.win, mlx.img_ptr, 0, 0);
        mlx_loop(mlx.mlx_p);
    }
    mlx_destroy_image(mlx.mlx_p, mlx.img_ptr);
    mlx_destroy_window(mlx.mlx_p, mlx.win);
    mlx_destroy_display(mlx.mlx_p);
    free(mlx.mlx_p);
    free(mlx.ply);
    free(mlx.ray);
    free(mlx.textures);

    free(mlx.rc);

    return 0;
}