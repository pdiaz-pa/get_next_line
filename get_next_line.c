/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdiaz-pa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 12:40:47 by pdiaz-pa          #+#    #+#             */
/*   Updated: 2020/01/23 14:40:31 by pdiaz-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t		ft_strlen(const char *cadena)
{
	int	i;

	i = 0;
	while (cadena[i] != '\0')
	{
		i++;
	}
	return (i);
}

char		*ft_strcpy(char *dest, const char *src)
{
	int i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i += 1;
	}
	dest[i] = '\0';
	return (dest);
}

static int	check(char **s, char **line, int ret)
{
	char	*nl;
	char	*tmp;

	if (ret < 0)
		return (-1);
	if (!ret && !*s)
	{
		*line = ft_strdup("");
		return (0);
	}
	else if ((nl = ft_strchr(*s, '\n')))
	{
		*nl = 0;
		*line = ft_strdup(*s);
		tmp = ft_strdup(++nl);
		free(*s);
		*s = tmp;
	}
	else
	{
		*line = *s;
		*s = NULL;
		return (0);
	}
	return (1);
}

int			get_next_line(int fd, char **line)
{
	int				ret;
	char			buff[BUFFER_SIZE + 1];
	static char		*s[4096];
	char			*tmp;

	if (fd < 0 || !line || BUFFER_SIZE < 1)
		return (-1);
	while ((ret = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[ret] = 0;
		if (!s[fd])
			s[fd] = ft_strdup(buff);
		else
		{
			tmp = ft_strjoin(s[fd], buff);
			free(s[fd]);
			s[fd] = tmp;
		}
		if (ft_strchr(s[fd], '\n'))
			break ;
	}
	return (check(&s[fd], line, ret));
}
