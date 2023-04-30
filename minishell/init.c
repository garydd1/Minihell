/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 22:34:31 by dgarizad          #+#    #+#             */
/*   Updated: 2023/04/30 21:32:48 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
extern t_data g_data;

int	operators(void)
{
	g_data.redirector[INFILE] = '<';
	//g_data.redirector[DELIMITER] = '<<';
	g_data.redirector[OUTFILE] = '>';
	//g_data.redirector[APPEND] = '>>';
	g_data.separator[PIPE] = '|';
	//data.separator[AND] = '&&';
	//data.separator[OR] = '||';
	return (0);
}

int	init(void)
{
	ft_memset(&g_data, '0', sizeof(g_data));
	operators();
	return (0);
}