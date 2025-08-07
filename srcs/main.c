/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanflous <yanflous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 09:46:35 by yanflous          #+#    #+#             */
/*   Updated: 2025/08/01 10:06:43 by yanflous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_game	*g_game(void)
{
	static t_game	game;

	return (&game);
}

void	game_init(t_game *game)
{
	t_player	*player;
	t_cast_data	*cast_data;

	player = &game->player;
	cast_data = &game->cast_data;
	player->fov = degrees_to_radians(FOV);
	cast_data->ray_nbr = SCREEN_WIDTH;
	cast_data->angle_step = (double)player->fov / cast_data->ray_nbr;
	cast_data->proj_plane_dist = (
			SCREEN_WIDTH / 2) / tan(player->fov / 2);
	init_floor_ceiling_rgb(game);
	init_mlx_window(game);
	init_textures(game);
	set_game_textures(game);
	init_player_dir(game);
}

int	main(int argc, char **argv)
{
	t_game	*game;

	game = g_game();
	if (parsing(argc, argv, game))
		return (1);
	game_init(game);
	mlx_hook(game->window.win_ptr, KeyPress, 1L << 0, key_press, NULL);
	mlx_hook(game->window.win_ptr, KeyRelease, 1L << 1, key_release, NULL);
	mlx_hook(game->window.win_ptr, DestroyNotify, 0L, close_window, NULL);
	mlx_loop_hook(game->window.mlx_ptr, game_loop, game);
	mlx_loop(game->window.mlx_ptr);
	return (0);
}
