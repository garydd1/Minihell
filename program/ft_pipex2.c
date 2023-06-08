/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcereced <vcereced@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 18:32:29 by vcereced          #+#    #+#             */
/*   Updated: 2023/06/07 22:16:44 by vcereced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern t_data	g_data;

void	receive_from_send_to_pipe(char *str)
{
	dup2(g_data.pipes[g_data.n_pipe - 1][STDIN_FILENO], STDIN_FILENO);
	dup2(g_data.pipes[g_data.n_pipe][STDOUT_FILENO], STDOUT_FILENO);
	//exit(ft_program(str));
	exit(ft_prompt_launcher(str));
}

void	sent_to_pipe(char *str)
{
	dup2(g_data.pipes[g_data.n_pipe][STDOUT_FILENO], STDOUT_FILENO);
	//exit(ft_program(str));
	exit(ft_prompt_launcher(str));
}

void	receive_from_pipe(char *str)
{
	dup2(g_data.pipes[g_data.n_pipe][STDIN_FILENO], STDIN_FILENO);
	//exit(ft_program(str));
	exit(ft_prompt_launcher(str));
}
