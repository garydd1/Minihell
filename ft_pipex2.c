/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcereced <vcereced@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 18:32:29 by vcereced          #+#    #+#             */
/*   Updated: 2023/06/05 18:32:37 by vcereced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//extern t_data	g_data;
t_data	g_data;

void	close_all_pipes(void)
{
	//int	n;

	//n = 0;
	//while (n <= g_data.n_pipe)
	///while (n < g_data.tmp_n_pipes)
	//{
		//close(g_data.pipes[n][STDIN_FILENO]);
	//	close(g_data.pipes[n][STDOUT_FILENO]);
	//	n++;
	//}
	if (g_data.fd_infile)
		close(g_data.fd_infile);
	if (g_data.fd_outfile)
		close(g_data.fd_outfile);
}

void	receive_from_send_to_pipe(char *str)
{
	int status;
	
	dup2(g_data.pipes[g_data.n_pipe - 1][STDIN_FILENO], STDIN_FILENO);
	dup2(g_data.pipes[g_data.n_pipe][STDOUT_FILENO], STDOUT_FILENO);
	status = ft_program(str);
	//freelancer();
	exit(status);
}

void sent_to_pipe(char *str)
{
	int status;
	
	dup2(g_data.pipes[g_data.n_pipe][STDOUT_FILENO], STDOUT_FILENO);
	status = ft_program(str);
	//freelancer();
	exit(status);
}

void	receive_from_pipe(char *str)
{
	int status;
	
	dup2(g_data.pipes[g_data.n_pipe][STDIN_FILENO], STDIN_FILENO);
	status = ft_program(str);
	//freelancer();
	exit(status);
}