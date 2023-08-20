/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkmap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelhafia <eelhafia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 22:44:31 by eelhafia          #+#    #+#             */
/*   Updated: 2023/06/04 22:41:30 by eelhafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

int check_correct_word(char *word, char *len_map)
{
    int i;

    i = 0;
    while (word[i] && i < 2)
    {
        if (word[i] == len_map[i])
            i++;
        else
            return (write(2, "Error in identify \n", 19), 1);
    }
    if (len_map[i++] != ' ')
        return (write(2, "Error in identify \n", 19), 1);
    while (len_map[i] == ' ' || len_map[i] == '\t')
        i++;
    if (len_map[i++] != '.')
        return (write(2, "Error in identify \n", 19), 1);
    if (len_map[i] != '/')
        return (write(2, "Error in identify \n", 19), 1);
    return (0);
}

void    check_norm(char **map, int index , int i, int num)
{
    num = ft_atoi(map[index] + i);
    if (num < 0 || num > 255)
        return (write(1, "Error in F or C  numbers !\n", 27), exit(1));
    while (ft_isdigit(map[index][i]))
        i++;
    if (map[index][i] != ',')
        return (write(1, "Error in F or c numbers !\n", 26), exit(1));
    else 
        i++;
    num = ft_atoi(map[index] + i);
    if (num < 0 || num > 255)
        return (write(1, "Error in F or C   numbers !\n", 28), exit(1));
    while (ft_isdigit(map[index][i]))
        i++;
    while (map[index][i] == '\n' || map[index][i] == ' ' || map[index][i] == '\t')
        i++;
    if (map[index][i])
        return (write(1, "Error in F or C numbers !\n", 26), exit(1));
}

void    check_f_c(char **map, int index, int c)
{
    int i;
    int num;

    i = 0;
    if (map[index][i++] != c)
        return (write(1, "Error in F or C  or F not fond !\n", 33), exit(1));
    if (!map[index][i] || map[index][i] != ' ')
        return (write(1, "Error in F or C or F not fond !\n", 32), exit(1));
    i++;
    while (map[index][i] && (map[index][i] == ' ' ||map[index][i] == '\t'))
        i++;
    num = ft_atoi(map[index] + i);
    if (num < 0 || num > 255)
        return (write(1, "Error in F or C  numbers !\n", 27), exit(1));
    while (ft_isdigit(map[index][i]))
        i++;
    if (map[index][i] != ',')
        return (write(1, "Error in F or C  numbers !\n", 27), exit(1));
    else 
        i++;
   check_norm(map, index , i, num);
}

int check_identify(char **map)
{
    int i;
    
    i = -1;
    if (check_correct_word("NO", map[0]))
        return (1);
    if (check_correct_word("SO", map[1]))
        return (1);
    if (check_correct_word("WE", map[2]))
        return (1);
    if (check_correct_word("EA", map[3]))
        return (1);
    while (map[4][++i])
        if (map[4][i] != '\n' && map[4][i] != ' ' && map[4][i] != '\t')
            return (write(2, "Error in line 5 will be empty \n", 31), 1);
    check_f_c(map, 5, 'F');
    check_f_c(map, 6, 'C');
    // while (map[7][++i])
    //     if (map[7][i] != '\n' && map[7][i] != ' ' && map[7][i] != '\t')
    //         return (write(2, "Error in line 7 will be empty \n", 31), 1);
    return (0);
}
void chack_env_0(char **map, int i , int j)
{
    if (map[i - 1] && map[i - 1][j] != '0' && map[i -1][j] != '1')
        return(write(2, "Error in Wall \n", 15), exit(1));
    if (map[i + 1] && map[i + 1][j] != '0' && map[i + 1][j] != '1')
        return(write(2, "Error in Wall \n", 15), exit(1));
    if (map[i][j - 1] && map[i][j - 1] != '0' && map[i][j - 1] != '1')
        return(write(2, "Error in Wall \n", 15), exit(1));
    if (map[i][j + 1] && map[i][j + 1] != '0' && map[i][j +1 ] != '1')
        return(write(2, "Error in Wall \n", 15), exit(1));
}
int check_map(char **map)
{
    int i;
    int j;
    
    i = 7;
    if (check_identify(map))
        return (1);
    while (map[++i])
    {
        j = 0;
        while (map[i][j])
        {
            if (map[i][j] == '0')
                chack_env_0(map, i , j);
            j++;
        }
    }
    return (0);
}
