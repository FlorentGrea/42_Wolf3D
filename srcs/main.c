/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrea <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 01:43:11 by fgrea             #+#    #+#             */
/*   Updated: 2017/03/30 06:10:05 by fgrea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void			wolf3d_error(char *c)
{
	ft_putendl(c);
	exit(0);
}

static int		wolf3d_key_quit(void)
{
	exit(0);
}

static void		wolf3d_begin(t_pxl p)
{
	int			x;
	int			y;
	int			i;

	x = 510;
	y = 300;
	i = 0x00FF00;
	mlx_string_put(p.mlx, p.win, x, y, i, "      Wolf3D      ");
	mlx_string_put(p.mlx, p.win, x, y + 50, i, "    Maps: 1/2/3   ");
}

int				main(void)
{
	t_pxl		p;

	p.check = 0;
	p.mlx = mlx_init();
	p.win = mlx_new_window(p.mlx, RESX, RESY, "wolf3d");
	p.img.im = mlx_new_image(p.mlx, RESX, RESY);
	p.img.imc = mlx_get_data_addr(p.img.im, &p.img.bpp, &p.img.imlen,
			&p.img.endi);
	wolf3d_begin(p);
	wolf3d_setup(&p);
	mlx_hook(p.win, 2, 1L << 0, wolf3d_key_press, &p);
	mlx_hook(p.win, 3, 1L << 1, wolf3d_key_release, &p);
	mlx_hook(p.win, 17, 1L << 15, wolf3d_key_quit, NULL);
	mlx_loop_hook(p.mlx, wolf3d_launcher, &p);
	mlx_loop(p.mlx);
	return (0);
}
