/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cstefany <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 20:18:10 by cstefany          #+#    #+#             */
/*   Updated: 2021/11/06 20:18:15 by cstefany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <stdio.h>

char	*read_line(int fd, t_list **list)
{
	ssize_t	res;
	char	buf[BUFFER_SIZE + 1];
	char	*tmp;

	while (1)
	{
		res = read(fd, buf, BUFFER_SIZE);
		buf[res] = '\0';
		tmp = ft_strjoin((*list) -> next_line, buf);
		if (tmp == NULL)
			return (NULL);
		free((*list) -> next_line);
		(*list) -> next_line = tmp;
		if (res < BUFFER_SIZE || ft_strchr(buf, '\n'))
			break ;
	}
	return ((*list) -> next_line);
}



char	*cut_line(t_list **list)
{
	char	*eol;
	char	*reminder;
	char	*n;

	n = ft_strchr((*list)->next_line, '\n');
	if (n && n[1] != '\0')
	{
		reminder = ft_strdup(n + 1);
		if (reminder == NULL)
			return (NULL);
		*(n + 1) = '\0';
		eol = (*list)->next_line;
		(*list)->next_line = reminder;
		reminder = NULL;
	}
	else
	{
		eol = ft_strdup((*list)->next_line);
		if (eol == NULL)
			return (NULL);
		free((*list)->next_line);
		(*list)->next_line = NULL;
	}
	return (eol);
}



t_list *search_fd(t_list **head ,int fd)
{
	t_list *tmp;
	t_list *new_node;
	if (!*head)
	{
		*head = ft_lstnew(fd);
		if (!*head)
			return NULL;
		return (*head);
	}
	tmp = *head;
	while (tmp != NULL)
	{
		if (tmp -> fd == fd)
			return tmp;
		tmp = tmp -> next;
	}
	new_node = ft_lstnew(fd);
	if (!new_node)
		return NULL;
	ft_lstadd_back(head, new_node);
	return (ft_lstlast(*head));
}



char	*get_next_line(int fd)
{
	static	t_list	*head = NULL;

	t_list	*desired_fd ;
	char buf[0];
	t_list *tmp;

	desired_fd = NULL;
	tmp = NULL;
	if (read(fd, buf, 0) == -1)
		return NULL;
	desired_fd = search_fd(&head, fd);

	printf("\033[1;33m");
	printf("%p", desired_fd);
	printf("\033[0m");

	if (!(desired_fd -> next_line))
	{
		desired_fd -> next_line = ft_strdup("");
		if (desired_fd -> next_line == NULL)
			return (NULL);
	}
	desired_fd -> next_line = read_line(fd, &desired_fd);
	if (desired_fd -> next_line == NULL)
		return (NULL);

	if (desired_fd -> next_line[0] == '\0')
	{
		tmp = head;
		if (head == desired_fd)
		{
			free(desired_fd->next_line);
			free(desired_fd);
			desired_fd = NULL;
			head = NULL;
		}
		else
		{
			while (tmp->next != desired_fd)
				tmp = tmp->next;
			tmp = desired_fd->next;
			free(desired_fd->next_line);
			free(desired_fd);
		}
		return (NULL);
	}
	return (cut_line(&desired_fd));
}
