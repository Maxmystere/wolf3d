/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 18:01:30 by magrab            #+#    #+#             */
/*   Updated: 2019/04/26 18:26:36 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static int		secure_wolf(t_wolf *wolf)
{
	int fd;

	if ((fd = open(TTFWOLF, O_RDONLY | O_NOFOLLOW)) < 0)
		return (-1);
	close(fd);
	if ((fd = open(TTFIMPACT, O_RDONLY | O_NOFOLLOW)) < 0)
		return (-1);
	close(fd);
	if ((fd = open(WALLBLUE, O_RDONLY | O_NOFOLLOW)) < 0)
		return (-1);
	close(fd);
	if ((fd = open(WALL, O_RDONLY | O_NOFOLLOW)) < 0)
		return (-1);
	close(fd);
	if ((fd = open(GOLD, O_RDONLY | O_NOFOLLOW)) < 0)
		return (-1);
	close(fd);
	if ((fd = open(TEST, O_RDONLY | O_NOFOLLOW)) < 0)
		return (-1);
	close(fd);
	ft_bzero(wolf, sizeof(t_wolf));
	return (0);
}

static t_wall	load_texture(t_wolf *wolf, const char *file)
{
	SDL_RWops	*rwop;
	SDL_Surface	*surf;
	SDL_Surface	*tmp;
	t_wall		wall;

	rwop = SDL_RWFromFile(file, "rb");
	if (!(tmp = IMG_LoadXPM_RW(rwop)))
	{
		ft_printf("IMG_LoadXPM_RW: %s\n", IMG_GetError());
		prog_quit(wolf);
	}
	if (!(surf = SDL_ConvertSurface(tmp, wolf->sdl.format, 0)))
	{
		ft_printf("SDL_ConvertSurface: failed\n");
		prog_quit(wolf);
	}
	SDL_FreeSurface(tmp);
	SDL_RWclose(rwop);
	wall.txture = surf->pixels;
	wall.surf = surf;
	wall.w = surf->w;
	wall.h = surf->h;
	return (wall);
}

void			lil_wolf_init(t_wolf *wolf)
{
	wolf->wall[0] = load_texture(wolf, WALLBLUE);
	wolf->wall[1] = load_texture(wolf, WALL);
	wolf->wall[2] = load_texture(wolf, GOLD);
	wolf->wall[3] = load_texture(wolf, TEST);
}

t_wolf			*wolf_init(void)
{
	t_wolf *wolf;

	if (!(wolf = (t_wolf *)malloc(sizeof(t_wolf))))
		return (NULL);
	if (secure_wolf(wolf))
		return (NULL);
	if (sdl_start(wolf, "Wolf 3D"))
		return (NULL);
	wolf->ui.btnarr[0] = add_wolf_button(wolf);
	wolf->ui.btnarr[1] = add_start_button(wolf);
	wolf->ui.btnarr[2] = add_opt_button(wolf);
	wolf->ui.btnarr[3] = add_quit_button(wolf, " Quit ");
	wolf->ui.btnmap[0] = add_quit_button(wolf, " Return ");
	wolf->ui.btnmap[1] = add_mapmenu_button(wolf);
	wolf->ui.btnopt[0] = wolf->ui.btnmap[0];
	wolf->ui.btnopt[1] = wolf->ui.btnarr[0];
	lil_wolf_init(wolf);
	wolf->ui.slidopt[0] = add_fov_slider(wolf);
	wolf->pos.x = 0;
	wolf->pos.y = 0;
	wolf->fov = 90;
	wolf->rot = 90;
	wolf->map = NULL;
	return (wolf);
}
