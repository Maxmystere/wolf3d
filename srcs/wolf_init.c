/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrab <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 18:01:30 by magrab            #+#    #+#             */
/*   Updated: 2019/04/19 18:01:31 by magrab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void		void_wolf(t_wolf *wolf)
{
	ft_bzero(wolf, sizeof(t_wolf));
}

t_wolf			*wolf_init(void)
{
	t_wolf *wolf;

	if (!(wolf = (t_wolf *)malloc(sizeof(t_wolf))))
		return (NULL);
	void_wolf(wolf);
	if (sdl_start(wolf, "Wolf 3D"))
		return (NULL);
	wolf->sdl.btnarr[0] = add_wolf_button(wolf);
	wolf->sdl.btnarr[1] = add_start_button(wolf);
	wolf->sdl.btnarr[2] = add_opt_button(wolf);
	wolf->sdl.btnarr[3] = add_quit_button(wolf, " Quit ");
	wolf->sdl.btnarr[4].txture = NULL;
	wolf->pos.x = 0;
	wolf->pos.y = 0;
	wolf->fov = 90;
	wolf->rot = 90;
	return (wolf);
}