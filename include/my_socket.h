/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_socket.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 21:17:00 by edelage           #+#    #+#             */
/*   Updated: 2023/03/08 21:17:00 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#ifndef MY_SOCKET_H
# define MY_SOCKET_H

# include "libft.h"
# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>

# define SOCKET_ERROR	(-1)

struct sockaddr_in	set_socket_address(const char *ip, int port,
						sa_family_t family);

#endif