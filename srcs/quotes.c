/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 10:07:46 by mburakow          #+#    #+#             */
/*   Updated: 2024/02/28 12:38:18 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	write_word(t_qsplit *q)
{
	int	len;
	int	i;

	len = (int)(q->p - q->start);
	q->result[q->count] = malloc((int)(len + 1) * sizeof(char));
	if (!q->result[q->count])
		errexit("ssplit :", " malloc failure", NULL, 1);
	i = 0;
	while (i < len)
	{
		q->result[q->count][i] = q->start[i];
		i++;
	}
	q->result[q->count][len] = '\0';
	q->count++;
	q->state = BASIC;
	return ;
}

static void	write_split_array(t_qsplit *q)
{
	q->p = q->str;
	q->result = ft_calloc(1, (sizeof(char *) * q->count + 1));
	if (!q->result)
		errexit("ssplit :", " malloc failure", NULL, 1);
	q->result[q->count] = NULL;
	q->count = 0;
	while (1)
	{
		q->c = (unsigned char)*q->p;
		if (q->state == BASIC)
			q->state = check_state(q);
		else if ((q->c == 34 && q->state == DSTRING)
			|| (q->c == 39 && q->state == SSTRING))
			write_word(q);
		else if ((q->c == 32 || (q->c >= 9 && q->c <= 13)) && q->state == WORD)
			write_word(q);
		else if (q->c == 0 && q->state == WORD)
			write_word(q);
		++q->p;
		if (q->c == 0)
			break ;
	}
	return ;
}

char	**parse_quotes(char *str)
{
	t_qsplit	q;

	if (!str || str[0] == '\0')
	{
		q.result = ft_calloc(1, sizeof(char *) * 2);
		q.result[0] = ft_strdup("");
		q.result[1] = NULL;
		return (q.result);
	}
	remove_slashes(str);
	init_q(str, &q);
	count_words(&q);
	q.state = BASIC;
	q.start = q.str;
	write_split_array(&q);
	return (q.result);
}
