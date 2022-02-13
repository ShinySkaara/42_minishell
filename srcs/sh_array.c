/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_array.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalonzo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 11:11:46 by alalonzo          #+#    #+#             */
/*   Updated: 2019/02/26 12:15:27 by alalonzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		sh_array_count(char **row)
{
	int		i;

	i = 0;
	while (row[i])
		i++;
	return (i);
}

char	**sh_array_new(int size)
{
	char	**new;

	if ((new = (char **)malloc(sizeof(char *) * (size + 1))))
		new[size] = NULL;
	return (new);
}

char	**sh_array_dup(char **row)
{
	int		i;
	char	**new;

	i = 0;
	if ((new = sh_array_new(sh_array_count(row))))
		while (row[i] && (new[i] = ft_strdup(row[i])))
			i++;
	return (new);
}

char	**sh_array_realloc(char **row, int count)
{
	int		i;
	char	**new;

	if ((new = sh_array_new(count)))
	{
		i = 0;
		while (row[i])
		{
			new[i] = row[i];
			i++;
		}
	}
	free(row);
	return (new);
}

char	**sh_array_del(char **row)
{
	int		i;

	i = 0;
	while (row[i])
		free(row[i++]);
	free(row);
	return (NULL);
}
