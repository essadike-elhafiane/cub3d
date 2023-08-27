/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_identifier.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelhafia <eelhafia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 18:35:54 by eelhafia          #+#    #+#             */
/*   Updated: 2023/08/27 19:00:25 by eelhafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	check_norm(char *map, int i, int *f, t_path *p)
{
	if (!ft_isdigit(map[i]))
		error_message("Error is not digit !\n", p);
	f[1] = ft_atoi(map + i);
	if (f[1] < 0 || f[1] > 255)
		error_message ("Error in F or C  numbers ! \n", p);
	while (ft_isdigit(map[i]))
		i++;
	if (map[i] != ',')
		error_message ("Error in F or C  numbers ! \n", p);
	else 
		i++;
	if (!ft_isdigit(map[i]))
		error_message("Error is not digit !\n", p);
	f[2] = ft_atoi(map + i);
	if (f[2] < 0 || f[2] > 255)
		error_message ("Error in F or C  numbers ! \n", p);
	while (ft_isdigit(map[i]))
		i++;
	while (map[i] == '\n' || map[i] == ' ' || map[i] == '\t')
		i++;
	if (map[i])
		error_message ("Error in F or C  numbers ! \n", p);
}

void	check_f_c(char *map, char c, int *f, t_path *p)
{
	int	i;

	i = 0;
	while (map[i] && (map[i] == ' ' || map[i] == '\t'))
		i++;
	if (map[i++] != c)
		error_message ("1Error in F or C  or F not fond ! \n", p);
	if (!map[i] || (map[i] != ' ' && map[i] != '\t'))
		error_message ("2Error in F or C  or F not fond ! \n", p);
	while (map[i] && (map[i] == ' ' || map[i] == '\t'))
		i++;
	if (!ft_isdigit(map[i]))
		error_message("Error is not digit !\n", p);
	f[0] = ft_atoi(map + i);
	if (f[0] < 0 || f[0] > 255)
		error_message ("Error in F or C  numbers ! \n", p);
	while (ft_isdigit(map[i]))
		i++;
	if (map[i] != ',')
		error_message("Error in F or C  numbers ! \n", p);
	else 
		i++;
	check_norm(map, i, f, p);
}

void	check_idefifier_data(char *len_map, t_path *p, int i)
{
	int	j;

	j = 0;
	i = i + 2;
	if (len_map[i++] != ' ')
		error_message ("Error in identify \n", p);
	while (len_map[i] == ' ' || len_map[i] == '\t')
		i++;
	j = i;
	if (len_map[i] == '\n')
		error_message ("Error in identify \n", p);
	while (len_map[i] && len_map[i] != '\n')
		i++;
	path_allocation(p, i, j, len_map);
	while (len_map[i] && (len_map[i] == ' ' || len_map[i] == '\t'))
		i++;
	if (len_map[i] != '\n')
		error_message ("Error in identify \n", p);
}

int	compare_indentifier(char *word, char *len_map, int *i, int j)
{
	while (word[j] && j < 2 && len_map[*i + j])
	{
		if (word[j] == len_map[*i + j])
			j++;
		else
			return (0);
	}
	if (len_map[*i + j] == '\0')
		return (0);
	return (1);
}

int	type_identifier(char *len_map, t_path *p, int *i)
{
	int	j;

	j = 0;
	if (p->no == NULL)
		if (compare_indentifier("NO", len_map, i, j))
			return (p->flg = 1, check_idefifier_data(len_map, p, *i), 0);
	if (p->so == NULL)
		if (compare_indentifier("SO", len_map, i, j))
			return (p->flg = 2, check_idefifier_data(len_map, p, *i), 0);
	if (p->we == NULL)
		if (compare_indentifier("WE", len_map, i, j))
			return (p->flg = 3, check_idefifier_data(len_map, p, *i), 0);
	if (p->ea == NULL)
		if (compare_indentifier("EA", len_map, i, j))
			return (p->flg = 4, check_idefifier_data(len_map, p, *i), 0);
	if (p->ff == 0)
		if (compare_indentifier("F ", len_map, i, j))
			return (check_f_c(len_map, 'F', p->f, p), p->ff = 1, 0);
	if (p->cc == 0)
		if (compare_indentifier("C ", len_map, i, j))
			return (check_f_c(len_map, 'C', p->c, p), p->cc = 1, 0);
	return (write(2, "Error in identify \n", 19), 1);
}
