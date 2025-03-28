/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguelmo <miguelmo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 18:48:42 by miguelmo          #+#    #+#             */
/*   Updated: 2025/03/17 19:01:37 by miguelmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

ssize_t	ft_strlen(const char *s)
{
	size_t	len;

	if (!s)
		return (0);
	len = 0;
	while (s[len])
		len++;
	return (len);
}

void	set_zero(char *str, ssize_t len)
{
	ssize_t	cont;

	if (!str)
		return ;
	cont = 0;
	while (cont < len)
	{
		str[cont] = 0;
		cont++;
	}
}

void	reset_str_sta(char *str_sta, int pos_nl)
{
	char	*aux;
	ssize_t	iter;

	if (pos_nl == -1)
		return (set_zero(str_sta, BUFFER_SIZE));
	aux = (char *)malloc(ft_strlen(str_sta) + 1);
	if (!aux)
		return (set_zero(str_sta, BUFFER_SIZE));
	set_zero(aux, ft_strlen(str_sta) + 1);
	iter = -1;
	while ((iter++) < (ft_strlen(str_sta) - pos_nl))
		aux[iter] = str_sta[iter + pos_nl];
	set_zero(str_sta, BUFFER_SIZE);
	iter = -1;
	while ((iter++) < ft_strlen(aux))
		str_sta[iter] = aux[iter];
	free (aux);
}

void	ft_strcat(char *str1, char *str2, ssize_t len)
{
	ssize_t	cont;

	cont = 0;
	if (!str1 || !str2)
		return ;
	while (*str1)
		str1++;
	while (cont < len && str2[cont] != '\0')
	{
		str1[cont] = str2[cont];
		cont++;
	}
	str1[cont] = 0;
}
