/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkmap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelhafia <eelhafia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 22:44:31 by eelhafia          #+#    #+#             */
/*   Updated: 2023/08/27 18:43:23 by eelhafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

int	empty_space(char c)
{
	if (c == '0' || c == '1' || c == 'W' || c == 'S' || c == 'N' || c == 'E')
		return (0);
	return (1);
}

void	chack_env_0(char **map, int i, int j)
{
	int	len;

	if (i > 0 && map[i - 1]) 
		len = ft_strlen(map[i - 1]);
	else
		return (write(2, "1Error in Wall \n", 15), exit(1));
	if (len < j || (map[i - 1] && empty_space(map[i - 1][j])))
	{
		return (write(2, "2Error in Wall \n", 15), exit(1));
	}
	if (i > 0 && map[i + 1]) 
		len = ft_strlen(map[i + 1]);
	else
		return (write(2, "3Error in Wall \n", 15), exit(1));
	if (len < j || (map[i + 1] && empty_space(map[i + 1][j])))
		return (write(2, "4Error in Wall \n", 15), exit(1));
	if (map[i][j - 1] && empty_space(map[i][j - 1]))
		return (write(2, "5Error in Wall \n", 15), exit(1));
	if (map[i][j + 1] && empty_space(map[i][j + 1]))
		return (write(2, "6Error in Wall \n", 15), exit(1));
}

void	is_player(char **map, int i, int j, t_path *p)
{
	if (map[i][j] == 'W' || map[i][j] == 'E' ||
		map[i][j] == 'N' || map[i][j] == 'S')
	{
		if (p->p == 1)
			error_message("1error in player \n", p);
		p->p = 1;
		if ((int)ft_strlen (map[i - 1]) < j 
			|| map[i + 1] == NULL || (int)ft_strlen (map[i + 1]) < j || j == 0)
			error_message("2error in player \n", p);
		if ((map[i - 1][j] != '0' && map[i - 1][j] != '1')
			|| (map[i + 1][j] != '0' && map[i + 1][j] != '1') ||
			(map[i][j + 1] != '0' && map[i][j + 1] != '1') ||
			(map[i][j - 1] != '0' && map[i][j - 1] != '1'))
			error_message("3error in player\n", p);
	}
}

void	check_element(char c, t_path *p)
{
	if (c != '0' && c != '1' && c != 'W' && c != 'S'
		&& c != 'N' && c != 'E' && c != '\n' && c != ' ' && c != '\t')
		error_message("error in element\n", p);
}

int	check_map(char **map, t_path *p, int len)
{
	int	i;
	int	j;

	i = -1;
	p->map = map;
	if (check_identify(map, p, len))
		error_message("", p);
	while (p->only_map[++i])
	{
		j = 0;
		while (p->only_map[i][j])
		{
			is_player(p->only_map, i, j, p);
			if (p->only_map[i][j] == '0')
				chack_env_0(p->only_map, i, j);
			check_element(p->only_map[i][j], p);
			j++;
		}
	}
	if (p->p == 0)
		error_message("4error in player \n", p);
	return (0);
}
