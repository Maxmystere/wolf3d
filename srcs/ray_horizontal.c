/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_horizontal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 19:35:12 by tbottini          #+#    #+#             */
/*   Updated: 2019/04/25 21:02:24 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		init_ray_hor(t_wolf *w, t_ray *r)
{
	if (r->angle < 180)
	{
		r->ratio.y = 1;
		r->ratio.x = r->ratio.y / tan(r->angle * PI180);
		r->inter_h.y = (int)w->pos.y + 1;
		r->inter_h.x = w->pos.x + r->ratio.x * fabs(r->inter_h.y - w->pos.y);
		return ;
	}
	r->ratio.y = -1;
	r->ratio.x = r->ratio.y / tan(r->angle * PI180);
	r->inter_h.y = (int)w->pos.y - 1;
	r->inter_h.x = w->pos.x + r->ratio.x * fabs(r->inter_h.y - w->pos.y + 1);
}

float		hor_detection(t_wolf *wolf, t_ray *ray)
{
	t_fvct2		dist;

	init_ray_hor(wolf, ray);
	while ((ray->hor = iswall(wolf, ray->inter_h)) == 0)
	{
		ray->inter_h.y += ray->ratio.y;
		ray->inter_h.x += ray->ratio.x;
	}
	if (ray->hor == 1)
	{
		dist.x = ray->inter_h.x - wolf->pos.x;
		dist.y = ray->inter_h.y - wolf->pos.y;
		if (ray->angle > 180)
			dist.y++;
		ray->hor = sqrt(dist.x * dist.x + dist.y * dist.y);
	}
	return (ray->hor);
}
