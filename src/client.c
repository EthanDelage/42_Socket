/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 21:43:00 by edelage           #+#    #+#             */
/*   Updated: 2023/03/08 21:43:00 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "my_socket.h"
#include <netdb.h>
#include <string.h>

int	main(int argc, char **argv)
{
	struct hostent		*hostinfo;
	const char			*ip = "10.12.11.2";
	const int			port = 14319;
	int					socket_client;
	struct sockaddr_in	addr;

	socket_client = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_client == SOCKET_ERROR)
	{
		perror("socket_client");
		return (errno);
	}
	hostinfo = gethostbyname(ip);
	if (hostinfo == NULL)
	{
		dprintf(STDERR_FILENO, "Unknown host\n");
		close(socket_client);
		return (1);
	}
	addr.sin_addr = *(struct in_addr *) hostinfo->h_addr;
	addr.sin_port = htons(port);
	addr.sin_family = AF_INET;
	if (connect(socket_client, (struct sockaddr *)&addr, sizeof(struct sockaddr_in)) == SOCKET_ERROR)
	{
		perror("connect");
		close(socket_client);
		return (errno);
	}
	printf("Connected\n");
	if (argc == 2)
	{
		if (send(socket_client, argv[1], strlen(argv[1]), 0) == -1)
		{
			perror("send");
			close(socket_client);
			return (errno);
		}
	}
	else
	{
		if (write(socket_client, "No arg", 6) == -1)
		{
			perror("send");
			close(socket_client);
			return (errno);
		}
	}
	close(socket_client);
	return (0);
}
