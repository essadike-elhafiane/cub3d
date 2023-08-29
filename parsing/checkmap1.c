/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkmap1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelhafia <eelhafia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 14:28:26 by eelhafia          #+#    #+#             */
/*   Updated: 2023/08/29 21:50:20 by eelhafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	path_allocation(t_path *p, int i, int j, char *len_map)
{
	if (p->flg == 1)
		p->no = ft_substr(len_map, j, i - j - count_space_tap(len_map));
	if (p->flg == 2)
		p->so = ft_substr(len_map, j, i - j - count_space_tap(len_map));
	if (p->flg == 3)
		p->we = ft_substr(len_map, j, i - j - count_space_tap(len_map));
	if (p->flg == 4)
		p->ea = ft_substr(len_map, j, i - j - count_space_tap(len_map));
}

int	check_correct_word(char *len_map, t_path *p)
{
	int	i;

	i = 0;
	while (len_map[i] && (len_map[i] == ' ' || len_map[i] == '\t'))
		i++;
	if (type_identifier(len_map, p, &i))
		return (1);
	return (0);
}

void	check_error_map(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		if (map[i][j] && (map[i][j] == ' '
			|| map[i][j] == '\t' || map[i][j] == '\n'))
		{
			while (map[i][j] && (map[i][j] == ' '
				|| map[i][j] == '\t' || map[i][j] == '\n'))
				j++;
		}
		else
			break ;
		i++;
	}
	if (!map[i] || !map[i][j])
		return (write(2, "Error in map\n", 13), exit(1));
}

int	chose_line(int *i, char **map, t_path *p)
{
	int	j;

	if (!map[*i])
		error_message("error \n", p);
	while (map[*i])
	{
		j = 0;
		while (map[*i] && map[*i][j] && (map[*i][j] == ' '
			|| map[*i][j] == '\n' || map[*i][j] == '\t'))
			j++;
		if (j == (int)ft_strlen(map[*i]))
			(*i) += 1;
		else
			return (*i);
	}
	if (!map[*i])
		error_message("error \n", p);
	return (*i);
}

int	check_identify(char **map, t_path *p, int len)
{
	int	i;
	int	a;

	i = 0;
	a = 0;
	check_error_map(map);
	while (++a < 7)
	{
		if (check_correct_word(map[chose_line(&i, map, p)], p))
			return (1);
		i++;
	}
	p->only_map = (char **) malloc(sizeof(char *) * (len - i + 1));
	if (!p->only_map)
		error_message ("Error in alocation map !\n", p);
	a = 0;
	while (map[i])
		p->only_map[a++] = ft_strdup(map[i++]);
	p->only_map[a] = NULL;
	return (0);
}
