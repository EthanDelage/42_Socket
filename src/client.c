/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 21:43:00 by edelage           #+#    #+#             */
/*   Updated: 2023/03/09 03:19:35 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "my_socket.h"
#include <netdb.h>
#include <sys/time.h>

int	main(void)
{
	struct hostent		*hostinfo;
	const char			*ip = "91.160.127.73";
	const int			port = 3000;
	int					socket_client;
	struct sockaddr_in	addr;
	struct timeval		time;

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
	gettimeofday(&time, NULL);
	if (send(socket_client, (void *) &time, sizeof(struct timeval), 0) == -1)
	{
		perror("send");
		close(socket_client);
		return (errno);
	}
	close(socket_client);
	return (0);
}
