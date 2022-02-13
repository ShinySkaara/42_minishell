/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_stat.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalonzo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 11:24:27 by alalonzo          #+#    #+#             */
/*   Updated: 2019/02/26 12:28:14 by alalonzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

void	sh_error(char *a, char *b, char *c)
{
	ft_putstr(a);
	ft_putstr(": ");
	ft_putstr(b);
	if (c)
	{
		ft_putstr(": ");
		ft_putstr(c);
	}
	ft_putchar('\n');
}

int		sh_stat(char *path, char *cmd, int mode)
{
	struct stat	buf;

	if (stat(path, &buf) == 0)
	{
		if (mode == 1)
		{
			if (S_ISDIR(buf.st_mode))
				return (2);
			sh_error(cmd, SH_ER_NO_DIR, path);
		}
		return (1);
	}
	sh_error(cmd, SH_ER_NO_FILE_DIR, path);
	return (0);
}

int		sh_access(char *path, char *cmd)
{
	if (access(path, X_OK) == 0)
		return (1);
	sh_error(cmd, SH_ER_NO_ACCESS, path);
	return (0);
}
