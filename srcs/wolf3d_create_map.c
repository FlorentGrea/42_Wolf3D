/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d_create_map.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrea <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 03:41:51 by fgrea             #+#    #+#             */
/*   Updated: 2017/03/30 05:11:44 by fgrea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

static void		wolf3d_freestr2d(t_pxl *p)
{
	int			i;

	i = 0;
	while (p->line[i])
	{
		ft_strdel(&(p->line[i]));
		++i;
	}
	ft_strdel(&(p->line[i]));
	free(p->line);
}

static int		wolf3d_split_line(t_pxl *p)
{
	char		*line;
	int			ret;

	ret = 0;
	if (get_next_line(p->fd, &line) == 1)
	{
		p->line = ft_strsplit(line, ' ');
		free(line);
		++ret;
	}
	else
		free(line);
	return (ret);
}

static void		wolf3d_int2d(t_pxl *p, char *file)
{
	char		*line;
	int			len;

	p->cmap.x = 0;
	p->cmap.y = 0;
	while (get_next_line(p->fd, &line) == 1)
	{
		++p->cmap.y;
		len = ft_strlen(line);
		free(line);
	}
	free(line);
	if (p->cmap.y == 0 || len == 0)
		wolf3d_error("read has failed");
	p->map = (int **)ft_memalloc(sizeof(int *) * p->cmap.y);
	close(p->fd);
	p->fd = open(file, O_RDONLY);
	wolf3d_split_line(p);
	while (p->line[p->cmap.x])
		++p->cmap.x;
	while (p->cmap.y > 0)
	{
		p->map[p->cmap.y - 1] = (int*)ft_memalloc(sizeof(int) * p->cmap.x);
		--p->cmap.y;
	}
}

void			wolf3d_parsing(t_pxl *p, char *file)
{
	int			map_x;

	map_x = 0;
	if ((p->fd = open(file, O_RDONLY)) <= 0)
		wolf3d_error("open has failed");
	wolf3d_int2d(p, file);
	while (map_x < p->cmap.x)
	{
		p->map[0][map_x] = ft_atoi(p->line[map_x]);
		++map_x;
	}
	wolf3d_freestr2d(p);
	while (wolf3d_split_line(p) == 1)
	{
		++p->cmap.y;
		map_x = -1;
		while (p->line[++map_x])
			p->map[p->cmap.y][map_x] = ft_atoi(p->line[map_x]);
		wolf3d_freestr2d(p);
		if (map_x != p->cmap.x)
			wolf3d_error("invalid map");
	}
	++p->cmap.y;
	p->check = 1;
}
