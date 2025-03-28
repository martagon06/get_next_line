/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguelmo <miguelmo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 18:47:58 by miguelmo          #+#    #+#             */
/*   Updated: 2025/03/18 10:30:43 by miguelmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

static int	contains_new_line(char *buffer)
{
	int	cont;

	cont = 0;
	if (!buffer)
		return (-1);
	while (buffer[cont])
	{
		if (buffer[cont] == '\n')
			return (cont + 1);
		cont ++;
	}
	return (-1);
}

static	char	*final_ret(char **ptr, char *str_sta, int pos_nl, ssize_t cont)
{
	int		ptr_len;
	char	*aux;

	if ((!ft_strlen(*ptr) && !ft_strlen(str_sta)) || cont == -1)
	{
		free(*ptr);
		return (NULL);
	}
	if (pos_nl != -1)
		ptr_len = (pos_nl);
	else
		ptr_len = (ft_strlen(str_sta));
	aux = (char *)malloc(ft_strlen(*ptr) + ptr_len + 1);
	if (!aux)
	{
		free(*ptr);
		return (NULL);
	}
	set_zero(aux, ft_strlen(*ptr) + ptr_len + 1);
	ft_strcat(aux, *ptr, ft_strlen(*ptr));
	ft_strcat(aux, str_sta, ptr_len);
	free(*ptr);
	reset_str_sta(str_sta, pos_nl);
	return (aux);
}

static void	ft_realloc(char **ptr, char *str_sta, int pos_nl)
{
	int		len;
	char	*aux;

	if (pos_nl == -1)
		len = ft_strlen(str_sta);
	else
		len = pos_nl;
	if (*ptr)
		len += ft_strlen(*ptr);
	aux = (char *)malloc(len + 1);
	if (!aux)
		return ;
	set_zero(aux, len + 1);
	ft_strcat(aux, *ptr, ft_strlen(*ptr));
	ft_strcat(aux, str_sta, len - ft_strlen(*ptr));
	free(*ptr);
	reset_str_sta(str_sta, pos_nl);
	*ptr = aux;
}

char	*get_next_line(int fd)
{
	static char	str_read[BUFFER_SIZE];
	char		*ptr;
	ssize_t		cont;

	ptr = NULL;
	cont = 1;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (contains_new_line(str_read) != -1)
		return (final_ret(&ptr, str_read, contains_new_line(str_read), 0));
	else if (ft_strlen(str_read) > 0)
		ft_realloc(&ptr, str_read, -1);
	while ((cont > 0) && (contains_new_line(ptr) == -1))
	{
		cont = read(fd, str_read, BUFFER_SIZE);
		ft_realloc(&ptr, str_read, contains_new_line(str_read));
		if (!ptr)
			return (NULL);
	}
	if (contains_new_line(ptr) != -1)
		return (ptr);
	return (final_ret(&ptr, str_read, contains_new_line(str_read), cont));
}
