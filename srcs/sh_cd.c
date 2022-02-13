/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalonzo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 11:23:18 by alalonzo          #+#    #+#             */
/*   Updated: 2019/02/26 12:20:16 by alalonzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <limits.h>

static void	sh_chdir(char *path, t_env *env)
{
	char	*tab[4];
	char	buf_old[PATH_MAX];
	char	buf_new[PATH_MAX];

	getcwd(buf_old, PATH_MAX);
	if (chdir(path) == 0)
	{
		getcwd(buf_new, PATH_MAX);
		tab[1] = ft_strjoin("OLDPWD=", buf_old);
		tab[2] = ft_strjoin("PWD=", buf_new);
		tab[3] = NULL;
		if (tab[1] && tab[2])
			env->fun[SETENV](tab, env);
		free(tab[1]);
		free(tab[2]);
		return ;
	}
	sh_error("cd", SH_ER_NO_FILE_DIR, path);
}

void		sh_cd(char **row, t_env *env)
{
	char	*tmp;
	int		ret;

	if (sh_array_count(row) < 3)
	{
		tmp = row[1] == NULL ? "~" : row[1];
		tmp = ft_strcmp(tmp, "~") == 0 ? "$HOME" : tmp;
		tmp = ft_strcmp(tmp, "-") == 0 ? "$OLDPWD" : tmp;
		if (tmp[0] == '$')
			if ((ret = sh_find_env_key(tmp + 1, env, '\0')) > -1)
				tmp = ft_strchr(env->env[ret], '=') + 1;
		if (sh_stat(tmp, "cd", 1) == 2 && sh_access(tmp, "cd"))
			sh_chdir(tmp, env);
		return ;
	}
	sh_error("cd", SH_ER_MANY_ARGS, NULL);
}
