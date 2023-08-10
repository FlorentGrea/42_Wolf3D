/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d_collision_detector.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrea <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 05:52:40 by fgrea             #+#    #+#             */
/*   Updated: 2017/03/30 06:10:42 by fgrea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

static void		wolf3d_ray_setup(t_pxl *p, int x)
{
	p->r.cam = 2 * x / (double)(RESX) - 1;
	p->r.pos.x = p->pos.x;
	p->r.pos.y = p->pos.y;
	p->r.dir.x = p->dir.x + p->rplane.x * p->r.cam;
	p->r.dir.y = p->dir.y + p->rplane.y * p->r.cam;
	p->rmap.x = (int)p->r.pos.x;
	p->rmap.y = (int)p->r.pos.y;
	p->r.disd.x = sqrt(1 + (p->r.dir.y * p->r.dir.y) / \
			(p->r.dir.x * p->r.dir.x));
	p->r.disd.y = sqrt(1 + (p->r.dir.x * p->r.dir.x) / \
			(p->r.dir.y * p->r.dir.y));
	p->hit = 0;
}

static void		wolf3d_ray_parsing(t_pxl *p)
{
	if (p->r.dir.x < 0)
	{
		p->step.x = -1;
		p->r.dist.x = (p->r.pos.x - p->rmap.x) * p->r.disd.x;
	}
	else
	{
		p->step.x = 1;
		p->r.dist.x = (p->rmap.x + 1.0 - p->r.pos.x) * p->r.disd.x;
	}
	if (p->r.dir.y < 0)
	{
		p->step.y = -1;
		p->r.dist.y = (p->r.pos.y - p->rmap.y) * p->r.disd.y;
	}
	else
	{
		p->step.y = 1;
		p->r.dist.y = (p->rmap.y + 1.0 - p->r.pos.y) * p->r.disd.y;
	}
}

static void		wolf3d_ray_hit(t_pxl *p)
{
	while (p->hit == 0)
	{
		if (p->r.dist.x < p->r.dist.y)
		{
			p->r.dist.x += p->r.disd.x;
			p->rmap.x += p->step.x;
			p->wall = 0;
		}
		else
		{
			p->r.dist.y += p->r.disd.y;
			p->rmap.y += p->step.y;
			p->wall = 1;
		}
		if (p->map[p->rmap.x][p->rmap.y] == 1)
			p->hit = 1;
	}
}

static void		wolf3d_ray_sizing(t_pxl *p)
{
	double		dist;

	if (p->wall == 0)
		dist = fabs((p->rmap.x - p->r.pos.x
					+ (1 - p->step.x) / 2) / p->r.dir.x);
	else
		dist = fabs((p->rmap.y - p->r.pos.y
					+ (1 - p->step.y) / 2) / p->r.dir.y);
	p->rh = abs((int)(RESY / dist));
	p->wstart = (-1 * (p->rh)) / 2 + RESY / 2;
	if (p->wstart < 0)
		p->wstart = 0;
	p->wend = p->rh / 2 + RESY / 2;
	if (p->wend >= RESY)
		p->wend = RESY - 1;
}

void			wolf3d_ray_study(t_pxl *p)
{
	int			x;

	x = 0;
	while (x < RESX)
	{
		wolf3d_ray_setup(p, x);
		wolf3d_ray_parsing(p);
		wolf3d_ray_hit(p);
		wolf3d_ray_sizing(p);
		if (p->wall == 0)
			p->color = (p->step.x < 0 ? 0x99004C : 0xFF0000);
		else
			p->color = (p->step.y > 0 ? 0x0000FF : 0xFF9933);
		wolf3d_fill_columns(p, x++);
	}
}
