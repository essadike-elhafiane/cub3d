/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelhafia <eelhafia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 22:17:53 by eelhafia          #+#    #+#             */
/*   Updated: 2023/08/27 18:56:30 by eelhafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	check_cub(char *name)
{
	int		len;
	char	*str;

	len = ft_strlen(name);
	str = ft_substr(name, len - 4, 4);
	if (len < 5 || ft_strncmp(".cub", str, 4))
	{
		write(2, "Error map dos'nt have .cub \n", 28);
		free(str);
		exit(1);
	}
	free(str);
}

void	ft_free(char **map, char **only_map)
{
	int	i;

	i = 0;
	while (map[i])
		free(map[i++]);
	free(map);
	i = 0;
	if (only_map)
	{
		while (only_map[i])
			free(only_map[i++]);
		free(only_map);
	}
}
void v()
{
	system("leaks cub");
}

void	init_struct(t_path *p)
{
	p->only_map = NULL;
	p->map = NULL;
	p->ea = NULL;
	p->we = NULL;
	p->no = NULL;
	p->so = NULL;
	p->ff = 0;
	p->cc = 0;
	p->len = 0;
	p->i = 0;
}

void	len_map(t_path *p)
{
	char	*str;

	while (1)
	{
		str = get_next_line(p->fd);
		if (!str)
			break ;
		free(str);
		p->len++;
	}
}

int	main(int ac, char **av)
{
	char	**map;
	t_path	p;

	init_struct(&p);
	atexit(v);
	if (ac != 2)
		return (write(1, "Error in arg \n", 14), 1);
	check_cub(av[1]);
	p.fd = open(av[1], O_RDWR, 0777);
	if (p.fd < 0)
		return (write(2, "Error open file\n", 16), 1);
	len_map(&p);
	map = (char **) malloc(sizeof(char *) * (p.len + 1));
	if (!map)
		return (write(2, "Error in malloc \n", 17), 1);
	close(p.fd);
	p.fd = open(av[1], O_RDONLY, 0777);
	while (p.i <= p.len)
		map[p.i++] = get_next_line(p.fd); 
	if (check_map(map, &p, p.len))
		return (1);
	graphic(p.only_map, &p);
	ft_free(map, p.only_map);
	return (0);
}
