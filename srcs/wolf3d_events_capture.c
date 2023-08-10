/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d_events_capture.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrea <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 05:54:53 by fgrea             #+#    #+#             */
/*   Updated: 2017/03/30 05:17:26 by fgrea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

static void			wolf3d_vision(t_pxl *p, double i)
{
	double			dir;
	double			plane;
	double			c;
	double			s;

	dir = p->dir.x;
	plane = p->rplane.x;
	c = cos(i);
	s = sin(i);
	p->dir.x = p->dir.x * c - p->dir.y * s;
	p->dir.y = dir * s + p->dir.y * c;
	p->rplane.x = p->rplane.x * c - p->rplane.y * s;
	p->rplane.y = plane * s + p->rplane.y * c;
}

void				wolf3d_move(t_pxl *p)
{
	double			newposx;
	double			newposy;

	newposx = p->dir.x * p->speed;
	newposy = p->dir.y * p->speed;
	if (p->up == 1)
	{
		if (!(p->map[(int)(p->pos.x + newposx)][(int)p->pos.y]))
			p->pos.x += newposx;
		if (!(p->map[(int)p->pos.x][(int)(p->pos.y + newposy)]))
			p->pos.y += newposy;
	}
	if (p->left == 1)
		wolf3d_vision(p, 0.1);
	if (p->right == 1)
		wolf3d_vision(p, -0.1);
	if (p->down == 1)
	{
		if (!(p->map[(int)(p->pos.x - newposx)][(int)(p->pos.y)]))
			p->pos.x -= newposx;
		if (!(p->map[(int)(p->pos.x)][(int)(p->pos.y - newposy)]))
			p->pos.y -= newposy;
	}
}

int					wolf3d_key_release(int keycode, t_pxl *p)
{
	if (keycode == 126 || keycode == 13)
		p->up = 0;
	if (keycode == 125 || keycode == 1)
		p->down = 0;
	if (keycode == 123 || keycode == 0)
		p->left = 0;
	if (keycode == 124 || keycode == 2)
		p->right = 0;
	return (0);
}

int					wolf3d_key_press(int keycode, t_pxl *p)
{
	if (!p->check && (keycode == 18 || keycode == 19))
		keycode == 18 ? wolf3d_parsing(p, MAP1) : wolf3d_parsing(p, MAP2);
	if (!p->check && keycode == 20)
		wolf3d_parsing(p, MAP3);
	if (keycode == 126 || keycode == 13)
		p->up = 1;
	if (keycode == 125 || keycode == 1)
		p->down = 1;
	if (keycode == 123 || keycode == 0)
		p->left = 1;
	if (keycode == 124 || keycode == 2)
		p->right = 1;
	if ((keycode == 78 && p->speed > 0.02)
			|| (keycode == 69 && p->speed < 0.3))
		p->speed += (keycode == 69 ? 0.01 : -0.01);
	if (keycode == 82 || keycode == 29)
		wolf3d_setup(p);
	if (keycode == 53)
		exit(1);
	return (0);
}
