/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allutils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 21:06:29 by dgarizad          #+#    #+#             */
/*   Updated: 2023/05/25 19:23:48 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_data	g_data;

// int	ft_error(char *err)
// {
// 	ft_putstr_fd(err, 2);
// 	return (errno);
// }

// /**
//  * @brief Prints the error message and exits with the ret value.
//  * 
//  * @param s1 
//  * @param s2 
//  * @param s3 
//  * @param ret 
//  * @return int 
//  */
// int	ft_error_in(char *s1, char *s2, char *s3, int ret)
// {
// 	ft_putstr_fd(s1, 2);
// 	if (s2)
// 		ft_putstr_fd(s2, 2);
// 	ft_putstr_fd(s3, 2);
// 	exit (ret);
// }

/**
 * @brief Checks if there is any infile with 
 * more than two '<' characters.
 * 
 * @param i 
 * @return int 
 */
int	aux_dell(int i)
{
	while (g_data.redics[i])
	{
		if (g_data.redics[i][1] == '<' && g_data.redics[i][2] == '<')
		{
			printf(RED"minishell: syntax error near unexpected token `<'\n"RST_CLR);
			g_data.flags.here_doc_ret = 258;
			g_data.flags.here_doc_aux = i;
			break ;
		}
		if (g_data.redics[i][1] == '>' && g_data.redics[i][2] == '>')
		{
			printf(RED"minishell: syntax error near unexpected token `>'\n"RST_CLR);
			g_data.flags.here_doc_ret = 258;
			g_data.flags.here_doc_aux = i;
			break ;
		}
		i++;
	}
	return (i);
}

/**
 * @brief Replace with a space the specific characters from i 
 * to j of the str.
 * 
 * @param i 
 * @param j 
 * @param str 
 * @return int 
 */
// int	delete_str(int i, int j, char *str)
// {
// 	while (i <= j && str[i] != '\0')
// 	{
// 		str[i] = ' ';
// 		i++;
// 	}
// 	return (0);
// }