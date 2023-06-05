/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 22:56:47 by vcereced          #+#    #+#             */
/*   Updated: 2023/06/05 20:23:49 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_data	g_data;

static int	ft_count_to_clear(char **arr)
{
	int	nvar_to_clear;
	int	i;
	int	n;

	i = 0;
	nvar_to_clear = 0;
	while (g_data.env[i])
	{
		n = 1;
		while (arr[n])
		{
			if (ft_get_var(arr[n], i) == 1)
				nvar_to_clear++;
			n++;
		}
		i++;
	}
	return (nvar_to_clear);
}

static char	**ft_gen_new_arr(char **arr)
{
	char	**new_arr_env;
	int		len_new_env;
	int		i;
	int		n;
	
	if (!ft_count_to_clear(arr))
		return (NULL);
	len_new_env = ft_arrlen(g_data.env) - ft_count_to_clear(arr);
	new_arr_env = (char **)malloc(sizeof(char *) * len_new_env + 1);
	i = 0;
	n = 0;
	while (i < ft_arrlen(g_data.env))
	{
		ft_copy(new_arr_env, arr, i, &n);
		i++;
	}
	new_arr_env[n] = NULL;
	return (new_arr_env);
}

static void ft_gen_new_env2(char **arr)//posible error abort antes de tiempo
{
	char	**new_arr_env;

	new_arr_env = ft_gen_new_arr(arr);
	if (new_arr_env)
	{
		//if (g_data.flag_env != 0)
			ft_abort(g_data.env, ft_arrlen(g_data.env));
		g_data.flag_env++;
		g_data.env = new_arr_env;
	}
}

//When kill the main thread free the g_data.env
int	ft_unset(char **arr)
{	
	if (!g_data.env)
	{
		str_error("unset", "env not found");
		return (EXIT_FAILURE);
	}
	else if (!arr[1])
	{
		str_error("unset", "not enough arguments");
		return (EXIT_SUCCESS);
	}
	else
		ft_gen_new_env2(arr);
	return (errno);
}

/*
static void sswap_arg(char **arg)
{
	int i;
	char *swap;

	i = 1;
	arg[0] = arg[1];
	while(arg[i - 1])
	{
		arg[i] = arg[i +1];
		i++;
	}
	arg[i] = NULL;
	
}

int main(int argc, char **arg, char **env)
{
	g_data.flag_env = 0;
	g_data.env = env;
	//ft_printf_arr(g_data.env);
	sswap_arg(arg);
	ft_unset(arg);
	ft_printf_arr(g_data.env);
	atexit(check);
	return(0);
}*/