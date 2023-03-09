/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 21:42:00 by edelage           #+#    #+#             */
/*   Updated: 2023/03/09 03:19:50 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "my_socket.h"
#include <sys/time.h>

static ssize_t 	receive_msg(int socket_fd);
static size_t	diff_time(struct timeval start_time, struct timeval current_time);

int	main(void)
{
	const char			*ip = "192.168.1.134";
	const int			port = 3000;
	int					socket_server;
	struct sockaddr_in	addr_server;
	int					socket_client;
	socklen_t			addr_len_client;
	struct sockaddr_in	addr_client;

	socket_server = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_server == SOCKET_ERROR)
	{
		perror("socket");
		return (errno);
	}
	addr_server = set_socket_address(ip, port, AF_INET);
	if (bind(socket_server, (struct sockaddr *) &addr_server,
			sizeof(struct sockaddr_in)) == SOCKET_ERROR)
	{
		perror("bind");
		close(socket_server);
		return (errno);
	}
	if (listen(socket_server, 4) == SOCKET_ERROR)
	{
		perror("listen");
		close(socket_server);
		return (errno);
	}
	addr_len_client = sizeof(struct sockaddr_in);
	socket_client = accept(socket_server, (struct sockaddr *)&addr_client,
			&addr_len_client);
	if (socket_client == SOCKET_ERROR)
	{
		perror("accept");
		close(socket_server);
		return (errno);
	}
	printf("Client connected\n");
	if (receive_msg(socket_client) == -1)
	{
		close(socket_server);
		close(socket_client);
		return (errno);
	}
	close(socket_server);
	close(socket_client);
	return (0);
}

static ssize_t 	receive_msg(int socket_fd)
{
	ssize_t			len;
	struct timeval	time;
	struct timeval	time_at_end;

	memset(&time, 0, sizeof(struct timeval));
	len = read(socket_fd, &time, sizeof(struct timeval));
	if (len == -1)
	{
		perror("recv");
		return (-1);
	}
	gettimeofday(&time_at_end, NULL);
	printf("%zu ms\n", diff_time(time, time_at_end));
	return (len);
}

static size_t	diff_time(struct timeval start_time, struct timeval current_time)
{
	return ((size_t)(current_time.tv_sec - start_time.tv_sec) * 1000
			+ (current_time.tv_usec - start_time.tv_usec) / 1000);
}
