/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 21:42:00 by edelage           #+#    #+#             */
/*   Updated: 2023/03/08 21:42:00 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "my_socket.h"

static ssize_t 	receive_msg(int socket_fd);

int	main(void)
{
	const char			*ip = "10.12.11.2";
	const int			port = 14319;
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
	char			buf[1000];
	const size_t	buf_size = 1000;

	ft_memset(buf, 0, buf_size);
	len = read(socket_fd, buf, buf_size - 1);
	if (len == -1)
	{
		perror("recv");
		return (-1);
	}
	printf("%s\n", buf);
	return (len);
}
