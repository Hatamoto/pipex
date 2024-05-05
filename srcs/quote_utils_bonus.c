/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 17:29:55 by mburakow          #+#    #+#             */
/*   Updated: 2024/02/26 15:46:31 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	remove_slashes(char *input)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (input[i] != '\0')
	{
		if (input[i] == '\\')
		{
			i++;
			continue ;
		}
		input[j] = input[i];
		i++;
		j++;
	}
	input[j] = '\0';
}

void	init_q(char *str, t_qsplit *q)
{
	q->str = str;
	q->p = str;
	q->start = NULL;
	q->c = 0;
	q->count = 0;
	q->result = NULL;
	q->state = check_state(q);
	return ;
}

t_state	check_state(t_qsplit *q)
{
	int	c;

	c = (unsigned char)*q->p;
	if (c == 32 || (c >= 9 && c <= 13))
		return (BASIC);
	if (c == 34 || c == 39)
	{
		q->start = q->p + 1;
		if (c == 34)
			return (DSTRING);
		if (c == 39)
			return (SSTRING);
	}
	q->start = q->p;
	return (WORD);
}

void	count_words(t_qsplit *q)
{
	while (1)
	{
		q->c = (unsigned char)*q->p;
		if (q->state == BASIC)
			q->state = check_state(q);
		else if (q->c == 34 && q->state == DSTRING)
			q->count++;
		else if (q->c == 39 && q->state == SSTRING)
			q->count++;
		else if ((q->c == 32 || (q->c >= 9 && q->c <= 13)) && q->state == WORD)
			q->count++;
		else if (q->c == 0 && q->state == WORD)
			q->count++;
		if (q->c == 0)
			break ;
		q->p++;
	}
}
