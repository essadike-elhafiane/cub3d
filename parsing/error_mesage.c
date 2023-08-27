/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_mesage.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelhafia <eelhafia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 18:40:56 by eelhafia          #+#    #+#             */
/*   Updated: 2023/08/27 18:41:40 by eelhafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	error_message(char *str, t_path *p)
{
	ft_free(p->map, p->only_map);
	if (p->so)
		free(p->so);
	if (p->ea)
		free(p->ea);
	if (p->no)
		free(p->no);
	if (p->we)
		free(p->we);
	write(2, str, ft_strlen(str));
	exit(1);
}
