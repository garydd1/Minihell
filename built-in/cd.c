/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 14:06:28 by vcereced          #+#    #+#             */
/*   Updated: 2023/05/17 21:16:42 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*join_path_desktop(char *username)
{
	char	*path;

	path = ft_strjoin("/Users/", username);
	if (path)
		return (path);
	else
		return (NULL);
}

static char	*gen_path_desktop(void)
{
	char	*username;
	char	*path;

	username = getenv("USER");
	if (username)
	{
		path = join_path_desktop(username);
		return (path);
	}
	else
		return (NULL);
}

static int	ch_desktop(char **arr)
{
	char	*path_desktop;
	int		status;

	path_desktop = gen_path_desktop();
	status = chdir(path_desktop);
	if (path_desktop)
		free(path_desktop);
	if (status == 0)
		return (0);
	else
		return (msg_error(arr[0], arr[1]));
}

static int	count_args(char **arr)
{
	int	n;

	n = 0;
	while (arr[n])
		n++;
	return (n);
}

int	ft_cd(char **arr)
{

	if (!arr || !*arr)
		return (127);
	else if (count_args(arr) > 3)
		return (str_error(arr[0], "too many arguments"));
	else if (count_args(arr) == 3)
		return (chdir_swap(swap_arg(arr[1], arr[2]), arr));
	else if (!arr[1])
		return (ch_desktop(arr));
	else if (chdir(arr[1]) == 0)
		return (0);
	else
		return (msg_error(arr[0], arr[1]));
}
/*
void	swap_argv(int argc, char **argv)
{
	int	i;

	i = 0;
	while (i < argc -1)
	{
		argv[i] = argv[i + 1];
		i++;
	}
	argv[argc - 1] = NULL;
}

int	main(int argc, char **argv)
{
	char	vector[256];
	int		status;
	swap_argv(argc, argv);
	printf("\n****DIRECCION before  %s\n", getcwd(vector, sizeof(vector)));
	status = ft_cd(argv);
	printf("DIRECCION afteeerr  %s\n", getcwd(vector, sizeof(vector)));
	printf("****salida STATUS %d\n\n", status);
	atexit(check);
	return (0);
}*/
