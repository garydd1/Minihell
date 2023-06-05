/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcereced <vcereced@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 19:28:47 by vcereced          #+#    #+#             */
/*   Updated: 2023/06/05 20:39:43 by vcereced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_data	g_data;

static int	ft_execve(char **arr)
{
	char	*str_path;
	char	**matriz_command;

	str_path = NULL;
	matriz_command = NULL;
	gen_command_and_path(arr, g_data.env, &str_path, &matriz_command);
	//ft_printf_arr(matriz_command);
	//printf("\n path -> %s\n", str_path);
	execve(str_path, matriz_command, g_data.env); //OJO!!
	if(str_path != NULL)
	{
		free(str_path);
		str_path = NULL;
	}
	if(matriz_command != NULL)
	{
		ft_free_split(matriz_command);
		matriz_command = NULL;
	}
	return (str_error(arr[0], "command not found"));
	//return(127);
}

static int	ft_built_in(char **arr)
{
	if (!ft_strncmp(arr[0], "echo", ft_strlen("echo")))
		return(ft_echo(arr));
	else if (!ft_strncmp(arr[0], "export", ft_strlen("export")))
		return(ft_export(arr));
	else if (!ft_strncmp(arr[0], "unset", ft_strlen("unset")))
		return(ft_unset(arr));
	else if (!ft_strncmp(arr[0], "cd", ft_strlen("cd")))
		return(ft_cd(arr));
	else if (!ft_strncmp(arr[0], "pwd", ft_strlen("pwd")))
		return(ft_pwd(arr));
	else if (!ft_strncmp(arr[0], "env", ft_strlen("env")))
		return(ft_env());
	else if (!ft_strncmp(arr[0], "exit", ft_strlen("exit")))
	{
		//printf(RED"input ex HERE :%p\n"RST_CLR"\n"RST_CLR, g_data.input_ex);
		//ft_free_split(arr);
		//free(g_data.input_ex);
		// printf(RED"exited HERE\n"RST_CLR"\n"RST_CLR);	
		// printf(RED"input and its addres %s : %p\n"RST_CLR"\n"RST_CLR, g_data.input, g_data.input);
		return(ft_exit());
	}
	else
		return (-1);
}

int	ft_execute(char **arr)
{
	int status;
	
	if (!arr || !(arr[0]))
		return (str_error(arr[0], "missing arg"));
	status = ft_built_in(arr);
	if (status != -1)
	{
		//ft_abort(arr, ft_arrlen(arr));
		return (status);
	}
	else
	{
		//ft_abort(arr, ft_arrlen(arr));
		return (ft_execve(arr));
	}
}
/*
int main(int argc, char **argv, char **env)
{
	char *arr[3];
	arr[0] = "env";
	arr[1] = NULL;
	arr[2] = NULL;
	
	g_data.env = env;
	ft_execute(arr);
	return(0);
}*/