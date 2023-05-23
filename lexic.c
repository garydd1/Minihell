/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcereced <vcereced@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 16:22:19 by dgarizad          #+#    #+#             */
/*   Updated: 2023/05/21 13:57:44 by vcereced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	g_data;

void check(void)
{
	system("leaks ./minishell");
}
/**
 * @brief Splits the already expanded input into words and 
 * stores it in data.token2.
 * Splits the expanded input by pipes so each program
 * can be identified. Stores it in data.pipes.
 * @return int 
 */
int	ft_parcerito(void)
{
	g_data.flags.token1 = 1;
	g_data.token2 = specialsplit(g_data.input_ex, ' '); //NEEDS PROPER FREE
	g_data.flags.token1 = 0;
	g_data.pipess = ft_split(g_data.input_ex, '|'); //NEEDS PROPER FREE
	return (0);
}

/**
 * @brief Returns true if it is enclosed by '
 * fasle if not.
 * @param str 
 * @param idx 
 * @return true 
 * @return false 
 */ //CHECKPOINT
bool	is_enclosed(const char *str, int idx)
{
	bool	inside_quotes;
	int		i;

	inside_quotes = false;
	i = 0;
	while (i < idx)
	{
		if (str[i] == '\'')
		{
			inside_quotes = !inside_quotes;
		}
		i++;
	}
	return (inside_quotes);
}

/**
 * @brief checks if the " or ' has 
 * a partner that closes it. If not
 * returns 1 and its considered an error. or not?
 * @param str 
 * @param index 
 * @param c 
 * @return int 
 */
int	ft_is_closed(char *str, int *index, char c)
{
	(*index)++;
	while (str[*index] != '\0')
	{
		if (str[*index] == c)
			return (0);
		(*index)++;
	}
	return (1);
}

/**
 * @brief Check if there are pipes not enclosed in '' or "".
 * 
 * @return int 0 OK, 1 NO
 */
static int	ft_check_pipes(void)
{
	char	**arr;
	int		n;
	
	arr = specialsplit(g_data.input_ex, '|');	
	if (ft_arrlen(arr) > 1)
		n = 0;
	else
		n = 1;
	ft_abort(arr, ft_arrlen(arr));
	return (n);
}

/**
 * @brief Check to execute unset, export, cd
 * Check is alone or in pipes
 * execute ft_program in main followed to skip init_promt().
 * So we dont loose the changes in env and the path of the procees.
 * 
 * @return int 0 OK, 1 NO
 */
static int	ft_check_exe(void)
{
	if (ft_strncmp((g_data.token1[0]), "exit", 4) == 0 || \
	ft_strncmp((g_data.token1[0]), "export", 7) == 0 || \
	ft_strncmp((g_data.token1[0]), "unset", 6) == 0 || \
	ft_strncmp((g_data.token1[0]), "cd", 2) == 0)
	{
		return(0);
	}
	return (1);
}

/**
 * @brief Checks if there are unclosed  ' or ""
 * and performs a first tokenization(split by spaces) in order
 * to facilitate the expand function. The Expansion 
 * is also done here. 
 * @param input 
 * @return int if execute program return status, if not return -1 means to continue to init_promt()
 */
int	ft_lexic(char *input)
{
	int	i;
	int status;

	if (input == NULL)
		return (0);
	i = 0;
	while (input[i] != '\0')
	{
		if (input[i] == '\'' || input[i] == '\"' )
		{
			if (ft_is_closed(input, &i, input[i]) == 1)
				ft_error("\nunclosed quotes!\n"); 
		}
		i++;
	}
	printf("\n----ENTRADA STR -> LEXIC------\n%s\n", g_data.input); 
	g_data.token1 = specialsplit((g_data.input), ' ');//for check_expand //ERROOR INTO SPLIT
	write(1, "\n--------ARR SPECIALSPLIT YES '' FIRST SPLIT INTO LEXIC -------\n",65); 
	ft_printf_arr(g_data.token1);
	ft_check_expand();
	g_data.input_ex = ft_untoken();
//	printf("\n%s\n", g_data.input_ex);
	if(ft_check_exe() == 0 && ft_check_pipes() == 1) //MEMORY LEAKS,WHEN ITS EXECUTED IS ALWAYS MAIN EXCEPT OCURR IN p1 | p2 | p3!!!
	{
		//g_data.input_ex = ft_untoken();
		status = ft_program(g_data.input_ex);
		//free(g_data.input_ex);
		//ft_abort(g_data.token1, ft_arrlen(g_data.token1));
		return(status);
	}
	return (-1);
}
