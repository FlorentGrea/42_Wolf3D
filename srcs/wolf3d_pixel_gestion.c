/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d_pixel_gestion.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrea <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 06:17:55 by fgrea             #+#    #+#             */
/*   Updated: 2017/03/30 05:38:28 by fgrea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

static void		wolf3d_put_pixel(t_pxl *p, int x, int y, int color)
{
	int			*tmp;

	if (y >= RESY || x >= RESX || x < 0 || y < 0)
		return ;
	tmp = (int *)&p->img.imc[(y * p->img.imlen) + (x * (p->img.bpp / 8))];
	*tmp = color;
}

void			wolf3d_fill_columns(t_pxl *p, int x)
{
	int			y;

	y = 0;
	while (y < p->wstart)
		wolf3d_put_pixel(p, x, y++, 0xC00000A0);
	while (y >= p->wstart && y <= p->wend)
		wolf3d_put_pixel(p, x, y++, p->color);
	while (y < RESY)
		wolf3d_put_pixel(p, x, y++, 0xA0A0A0);
}

static void		wolf3d_put_map_to_img(t_pxl *p, int x, int y, int color)
{
	int			i;
	int			j;

	i = -1;
	while (++i <= 5)
	{
		j = -1;
		while (++j <= 5)
			wolf3d_put_pixel(p, x + i, y + j, color);
	}
}

void			wolf3d_put_map(t_pxl *p)
{
	int			i;
	int			j;

	if (p->cmap.x * 5 > RESX / 2 || p->cmap.y * 5 > RESY / 2)
		return ;
	i = -1;
	while (++i < p->cmap.x)
	{
		j = -1;
		while (++j < p->cmap.y)
		{
			if (p->map[j][i] == 1)
				wolf3d_put_map_to_img(p, i + (5 * (i + 1)), j + (5 * (j + 1)),
						0x00FF00);
			else if ((int)p->pos.x == j && (int)p->pos.y == i)
				wolf3d_put_map_to_img(p, i + (5 * (i + 1)), j + (5 * (j + 1)),
						0x000000);
			else
				wolf3d_put_map_to_img(p, i + (5 * (i + 1)), j + (5 * (j + 1)),
						0xFFFFFF);
		}
	}
}
