/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkmap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelhafia <eelhafia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 22:44:31 by eelhafia          #+#    #+#             */
/*   Updated: 2023/08/23 00:25:24 by eelhafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void error_message(char *str)
{
	write(2, str, ft_strlen(str));
	exit(1);
}

int compare_indentifier(char *word,char *len_map , int *i , int j)
{
	while(word[j] && j < 2 && len_map[*i + j])
	{
		if(word[j] == len_map[*i + j])
		j++;
		else
			return 0;
	}
	if(len_map[*i + j] == '\0')
		return (0);
	return 1;
}

void    check_norm(char *map, int i, int *f)
{
	f[1] = ft_atoi(map + i);
	if (f[1] < 0 || f[1] > 255)
		error_message ("Error in F or C  numbers ! \n");
	while (ft_isdigit(map[i]))
		i++;
	if (map[i] != ',')
		error_message ("Error in F or C  numbers ! \n");
	else 
		i++;
	f[2] = ft_atoi(map + i);
	if (f[2] < 0 || f[2] > 255)
		error_message ("Error in F or C  numbers ! \n");
	while (ft_isdigit(map[i]))
		i++;
	while (map[i] == '\n' || map[i] == ' ' || map[i] == '\t')
		i++;
	if (map[i])
		error_message ("Error in F or C  numbers ! \n");
}

void    check_f_c(char *map,char c,int *f)
{
	int i;
	int num;

	i = 0;
	while(map[i] && (map[i] == ' ' || map[i] == '\t'))
	i++;
	if (map[i++] != c)
		error_message ("1Error in F or C  or F not fond ! \n");
	if (!map[i] || (map[i] != ' ' && map[i] != '\t'))
		  error_message ("2Error in F or C  or F not fond ! \n");
	while (map[i]&& (map[i] == ' ' || map[i] == '\t'))
		i++;
	f[0] = ft_atoi(map + i);
	if (f[0] < 0 || f[0] > 255)
		error_message ("Error in F or C  numbers ! \n");
	while (ft_isdigit(map[i]))
		i++;
	if (map[i] != ',')
		error_message("Error in F or C  numbers ! \n");
	else 
		i++;
   check_norm(map , i, f);
}

void path_allocation(t_path *p,int i ,int j , char *len_map)
{
	printf("|%s" , len_map);
	printf("%d\n",p->flg);
	if(p->flg == 1)
		p->no = ft_substr(len_map ,j , i - j);
	if(p->flg == 2)
		p->so = ft_substr(len_map ,j , i - j);
	if(p->flg == 3)
		p->we = ft_substr(len_map ,j , i - j);
	if(p->flg == 4)
		p->ea = ft_substr(len_map ,j , i - j);
}

void check_idefifier_data(char *len_map ,  t_path *p , int i)
{
	int j;

	j = 0;
	i = i + 2;
	if (len_map[i++] != ' ')
		error_message ("Error in identify \n");
	while (len_map[i] == ' ' || len_map[i] == '\t')
		i++;
	j = i;
	if (len_map[i] == '\n')
		error_message ("Error in identify \n");
	while (len_map[i] && len_map[i] != ' ' && len_map[i] != '\t' && len_map[i] != '\n')
		i++;
	path_allocation(p, i ,j , len_map);
	while (len_map[i] == ' ' || len_map[i] == '\t')
		i++;
	if(len_map[i] != '\n')
		error_message ("Error in identify \n");
}

int  type_identifier(char *len_map ,  t_path *p , int *i)
{
	int j;

	j = 0;
	if(p->no == NULL)
		if (compare_indentifier("NO" , len_map , i , j))
			return (p->flg = 1 , check_idefifier_data(len_map ,p ,*i), 0);
	if(p->so == NULL)
		if (compare_indentifier("SO" , len_map , i , j))  
			return ( p->flg = 2,check_idefifier_data(len_map ,p ,*i) ,  0);
	if(p->we == NULL)
		if (compare_indentifier("WE" , len_map, i , j))
			return (p->flg = 3 , check_idefifier_data(len_map ,p ,*i), 0);
	if(p->ea == NULL)
		if (compare_indentifier("EA" , len_map, i , j))
			return (p->flg = 4,  check_idefifier_data(len_map ,p ,*i), 0);
	if(p->ff == 0)
		if (compare_indentifier("F " , len_map, i , j))
			return (check_f_c(len_map, 'F', p->f), p->ff = 1, 0);
	if (p->cc == 0)
		if (compare_indentifier("C ", len_map, i, j))
			return (check_f_c(len_map, 'C', p->c), p->cc = 1, 0);
	return (write(2, "1Error in identify \n", 19), 1);
}

int check_correct_word(char *len_map , t_path *p)
{
	int i;
	i = 0;
	while(len_map[i] && (len_map[i] == ' ' || len_map[i] == '\t'))
		i++;
	if(type_identifier(len_map,p,&i))
		return (1);
	return (0);
}


int chose_line(int *i, char **map)
{
	int j;

	while(map[*i])
	{
		j = 0;
		while(map[*i][j] && (map[*i][j] == ' ' || map[*i][j] == '\n' || map[*i][j] == '\t'))
			j++;
		if(j == ft_strlen(map[*i]))
			(*i)+= 1;
		else
			return(*i);
	}
	return(*i);
}
void check_error_map(char **map)
{
	int i;
	int j;

	i = 0;
	while (map[i])
	{
		j = 0;
		if (map[i][j] && (map[i][j] == ' ' || map[i][j] == '\t' || map[i][j] =='\n'))
		{	
			while(map[i][j] && (map[i][j] == ' ' || map[i][j] == '\t' || map[i][j] =='\n'))
				j++;
		}
		else
			break;
		i++;
	}
	if(!map[i] || !map[i][j])
		return (write(2, "Error in map\n", 13), exit(1));
	
}

int check_identify(char **map , t_path *p, int len)
{
	int i;
	int a;

	i = 0;
	a = 0;
	check_error_map(map);
	while(++a < 7)
	{
		if (check_correct_word(map[chose_line(&i,map)] , p))
			return (1);
		i++;
	}
	p->only_map = (char **) malloc(sizeof(char *) * (len - i + 1));
	if (!p->only_map)
		error_message ("Error in alocation map !\n");
	a = 0;
	while (map[i])
		p->only_map[a++] = ft_strdup(map[i++]);
	p->only_map[a] = NULL;
	return (0);
}

int empty_space(char c)
{
	if (c == '0' || c == '1' || c == 'W' || c == 'S' || c == 'N' ||  c == 'E')
		return (0);
	return (1);
}

void chack_env_0(char **map, int i , int j)
{
	int len;

	if(i > 0 && map[i - 1]) 
		len = ft_strlen(map[i - 1]);
	else
	   return(write(2, "1Error in Wall \n", 15), exit(1)); 
	if (len < j || (map[i - 1] && empty_space(map[i - 1][j])))
	{
		return(write(2, "2Error in Wall \n", 15), exit(1));
	}
	if(i > 0 && map[i + 1]) 
		len = ft_strlen(map[i + 1]);
	else
	   return(write(2, "3Error in Wall \n", 15), exit(1));
	if (len < j || (map[i + 1] && empty_space(map[i + 1][j])))
		return(write(2, "4Error in Wall \n", 15), exit(1));
	if (map[i][j - 1] && empty_space(map[i][j - 1]))
		return(write(2, "5Error in Wall \n", 15), exit(1));
	if (map[i][j + 1] && empty_space(map[i][j + 1]))
		return(write(2, "6Error in Wall \n", 15), exit(1));
}

void is_player(char **map, int i , int j, t_path *p)
{
	if(map[i][j] == 'W'  || map[i][j] == 'E' || map[i][j] == 'N' || map[i][j] == 'S')
	{
		if(p->p == 1)
			error_message("1error in player \n");
		p->p = 1;
	if( ft_strlen (map[i - 1])  <  j || map[i + 1] == NULL ||ft_strlen (map[i + 1]) < j || j == 0)
		error_message("2error in player \n");
	if((map[i - 1] [j] != '0' && map[i - 1] [j] != '1') 
		|| (map[i + 1] [j] != '0' && map[i + 1] [j] != '1' ) ||
		(map[i ] [j + 1] != '0' && map[i ] [j + 1] != '1') ||
		(map[i ] [j - 1] != '0' && map[i ] [j - 1] != '1'))
		error_message("3error in player\n");
	}
}

void check_element(char c)
{
	if (c != '0' && c != '1' && c != 'W' && c != 'S'
		&& c != 'N' &&  c != 'E' && c != '\n' && c!= ' ' && c != '\t')
		error_message("error in element\n");
}

int check_map(char **map , t_path *p, int len)
{
	int i;
	int j;
	
	i = -1;
	if (check_identify(map , p, len))
		return (1);
	while (p->only_map[++i])
	{
		j = 0;
		while (p->only_map[i][j])
		{
			is_player(p->only_map , i , j , p);
			if (p->only_map[i][j] == '0')
				chack_env_0(p->only_map, i , j);
			check_element(p->only_map[i][j]);
			j++;
		}
	}
	if(p->p == 0)
	   error_message("4error in player \n"); 
	return (0);
}
