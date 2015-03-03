void	ft_arg_alpha(const t_arg **begin, t_arg *tmp, t_arg *t)
{
	char		*arg;
	struct stat	*stt;
	int			err;
	int			lg;

	if (*begin)
	{
		if (tmp && t && ft_strcmp(tmp->arg, t->arg) > 0)
		{
			arg = t->arg;
			stt = t->stt;
			err = t->err;
			lg = t->lg;
			t->arg = tmp->arg;
			t->stt = tmp->stt;
			t->err = tmp->err;
			t->lg = tmp->lg;
			tmp->arg = arg;
			tmp->stt = stt;
			tmp->err = err;
			tmp->lg = lg;
			ft_arg_alpha(begin, (t_arg *)*begin, (t_arg *)*begin);
		}
		else if (tmp && t)
			ft_arg_alpha(begin, tmp, t->next);
		else if (tmp && !t)
			ft_arg_alpha(begin, tmp->next, tmp->next);
	}
}

void	ft_arg_time(const t_arg **begin, t_arg *tmp, t_arg *t)
{
	char		*arg;
	struct stat	*stt;
	int			err;
	int			lg;

	if (begin && *begin && (ft_parse_sgl(-1) & CHAR_T))
	{
		if (tmp && t && (tmp->stt->st_mtime > t->stt->st_mtime))
		{
			arg = t->arg;
			stt = t->stt;
			err = t->err;
			lg = t->lg;
			t->arg = tmp->arg;
			t->stt = tmp->stt;
			t->err = tmp->err;
			t->lg = tmp->lg;
			tmp->arg = arg;
			tmp->stt = stt;
			tmp->err = err;
			tmp->lg = lg;
			ft_arg_time(begin, (t_arg *)*begin, (t_arg *)*begin);
		}
		else if (tmp && t)
			ft_arg_time(begin, tmp, t->next);
		else if (tmp && !t)
			ft_arg_time(begin, tmp->next, tmp->next);
	}
}

void	ft_arg_revolve(t_arg **begin, t_arg *save, t_arg *head)
{
	if (save && save->next)
	{
		head = save->next;
		ft_arg_revolve(&(save->next), save->next, NULL);
		head->next = save;
		*begin = save->next;
		head->next->next = NULL;
	}
}

char	ft_arg_dump_errors(t_arg **cur, t_arg *tmp, char chip)
{
	if (*cur)
	{
		chip = ((*cur)->err == ENOENT) ? ft_pstr((*cur)->arg, 2)
			+ ft_pendl(" : No such file or directory", 2) : chip;
		chip = ((*cur)->err == EACCES) ? ft_pstr((*cur)->arg, 2)
			+ ft_pendl(" : Permission denied", 2) : chip;
		if (chip)
		{
			free((*cur)->arg);
			free((*cur)->stt);
			free(*cur);
			*cur = NULL;
			cur = &tmp;
		}
		chip = (tmp) ? ft_arg_dump_errors(&tmp, tmp->next, 0) : 0;
	}
	return (chip);
}
