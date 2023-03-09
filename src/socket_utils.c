/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 00:11:00 by edelage           #+#    #+#             */
/*   Updated: 2023/03/09 00:11:00 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "my_socket.h"

struct sockaddr_in	set_socket_address(const char *ip, int port,
						sa_family_t family)
{
	struct sockaddr_in	addr_socket;

	addr_socket.sin_addr.s_addr = inet_addr(ip);
	addr_socket.sin_family = family;
	addr_socket.sin_port = htons(port);
	return (addr_socket);
}
