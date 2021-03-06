/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_loader.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 18:19:51 by magrab            #+#    #+#             */
/*   Updated: 2019/04/26 18:21:55 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void		free_btnmap(t_wolf *wolf, int y)
{
	SDL_DestroyTexture(wolf->ui.btnmap[y].txture);
	wolf->ui.btnmap[y].txture = NULL;
	free(wolf->ui.btnmap[y].data);
}

static int		read_directory(t_wolf *wolf, DIR *maps, int y)
{
	struct dirent	*mapdata;
	char			tmp[512];

	while ((mapdata = readdir(maps)) && y < 9)
	{
		ft_strcpy(tmp, "ressources/map/");
		ft_strcpy(&(tmp[15]), mapdata->d_name);
		if (mapdata->d_reclen == 32 && map_check(wolf, tmp))
		{
			if (wolf->ui.btnmap[y].txture)
				free_btnmap(wolf, y);
			wolf->ui.btnmap[y] = add_map_button(wolf, &(tmp[15]));
			wolf->ui.btnmap[y].data = ft_strdup(tmp);
			y++;
		}
	}
	return (y);
}

int				load_map_btns(t_wolf *wolf)
{
	DIR				*maps;
	int				y;

	y = 2;
	if (!(maps = opendir("ressources/map")))
	{
		if (wolf->ui.btnmap[y].txture)
			free_btnmap(wolf, y);
		ft_printf("Error loading folder 'map'\n");
		return (0);
	}
	y = read_directory(wolf, maps, y);
	closedir(maps);
	if (wolf->ui.btnmap[y].txture)
		free_btnmap(wolf, y);
	return (0);
}
