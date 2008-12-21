/*
 * Copyright (c) 2007, Anthony Minessale II
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 
 * * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 * 
 * * Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 * 
 * * Neither the name of the original author; nor the names of any contributors
 * may be used to endorse or promote products derived from this software
 * without specific prior written permission.
 * 
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER
 * OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <esl.h>
#ifndef WIN32
#define closesocket(x) close(x)
#endif

#ifndef HAVE_GETHOSTBYNAME_R
extern int gethostbyname_r (const char *__name,
                            struct hostent *__result_buf,
                            char *__buf, size_t __buflen,
                            struct hostent **__result,
                            int *__h_errnump);
#endif



/* Written by Marc Espie, public domain */
#define ESL_CTYPE_NUM_CHARS       256

const short _esl_C_toupper_[1 + ESL_CTYPE_NUM_CHARS] = {
	EOF,
	0x00,	0x01,	0x02,	0x03,	0x04,	0x05,	0x06,	0x07,
	0x08,	0x09,	0x0a,	0x0b,	0x0c,	0x0d,	0x0e,	0x0f,
	0x10,	0x11,	0x12,	0x13,	0x14,	0x15,	0x16,	0x17,
	0x18,	0x19,	0x1a,	0x1b,	0x1c,	0x1d,	0x1e,	0x1f,
	0x20,	0x21,	0x22,	0x23,	0x24,	0x25,	0x26,	0x27,
	0x28,	0x29,	0x2a,	0x2b,	0x2c,	0x2d,	0x2e,	0x2f,
	0x30,	0x31,	0x32,	0x33,	0x34,	0x35,	0x36,	0x37,
	0x38,	0x39,	0x3a,	0x3b,	0x3c,	0x3d,	0x3e,	0x3f,
	0x40,	0x41,	0x42,	0x43,	0x44,	0x45,	0x46,	0x47,
	0x48,	0x49,	0x4a,	0x4b,	0x4c,	0x4d,	0x4e,	0x4f,
	0x50,	0x51,	0x52,	0x53,	0x54,	0x55,	0x56,	0x57,
	0x58,	0x59,	0x5a,	0x5b,	0x5c,	0x5d,	0x5e,	0x5f,
	0x60,	'A',	'B',	'C',	'D',	'E',	'F',	'G',
	'H',	'I',	'J',	'K',	'L',	'M',	'N',	'O',
	'P',	'Q',	'R',	'S',	'T',	'U',	'V',	'W',
	'X',	'Y',	'Z',	0x7b,	0x7c,	0x7d,	0x7e,	0x7f,
	0x80,	0x81,	0x82,	0x83,	0x84,	0x85,	0x86,	0x87,
	0x88,	0x89,	0x8a,	0x8b,	0x8c,	0x8d,	0x8e,	0x8f,
	0x90,	0x91,	0x92,	0x93,	0x94,	0x95,	0x96,	0x97,
	0x98,	0x99,	0x9a,	0x9b,	0x9c,	0x9d,	0x9e,	0x9f,
	0xa0,	0xa1,	0xa2,	0xa3,	0xa4,	0xa5,	0xa6,	0xa7,
	0xa8,	0xa9,	0xaa,	0xab,	0xac,	0xad,	0xae,	0xaf,
	0xb0,	0xb1,	0xb2,	0xb3,	0xb4,	0xb5,	0xb6,	0xb7,
	0xb8,	0xb9,	0xba,	0xbb,	0xbc,	0xbd,	0xbe,	0xbf,
	0xc0,	0xc1,	0xc2,	0xc3,	0xc4,	0xc5,	0xc6,	0xc7,
	0xc8,	0xc9,	0xca,	0xcb,	0xcc,	0xcd,	0xce,	0xcf,
	0xd0,	0xd1,	0xd2,	0xd3,	0xd4,	0xd5,	0xd6,	0xd7,
	0xd8,	0xd9,	0xda,	0xdb,	0xdc,	0xdd,	0xde,	0xdf,
	0xe0,	0xe1,	0xe2,	0xe3,	0xe4,	0xe5,	0xe6,	0xe7,
	0xe8,	0xe9,	0xea,	0xeb,	0xec,	0xed,	0xee,	0xef,
	0xf0,	0xf1,	0xf2,	0xf3,	0xf4,	0xf5,	0xf6,	0xf7,
	0xf8,	0xf9,	0xfa,	0xfb,	0xfc,	0xfd,	0xfe,	0xff
};

const short *_esl_toupper_tab_ = _esl_C_toupper_;

int esl_toupper(int c)
{
	if ((unsigned int)c > 255)
		return(c);
	if (c < -1)
		return EOF;
	return((_esl_toupper_tab_ + 1)[c]);
}

const short _esl_C_tolower_[1 + ESL_CTYPE_NUM_CHARS] = {
	EOF,
	0x00,	0x01,	0x02,	0x03,	0x04,	0x05,	0x06,	0x07,
	0x08,	0x09,	0x0a,	0x0b,	0x0c,	0x0d,	0x0e,	0x0f,
	0x10,	0x11,	0x12,	0x13,	0x14,	0x15,	0x16,	0x17,
	0x18,	0x19,	0x1a,	0x1b,	0x1c,	0x1d,	0x1e,	0x1f,
	0x20,	0x21,	0x22,	0x23,	0x24,	0x25,	0x26,	0x27,
	0x28,	0x29,	0x2a,	0x2b,	0x2c,	0x2d,	0x2e,	0x2f,
	0x30,	0x31,	0x32,	0x33,	0x34,	0x35,	0x36,	0x37,
	0x38,	0x39,	0x3a,	0x3b,	0x3c,	0x3d,	0x3e,	0x3f,
	0x40,	'a',	'b',	'c',	'd',	'e',	'f',	'g',
	'h',	'i',	'j',	'k',	'l',	'm',	'n',	'o',
	'p',	'q',	'r',	's',	't',	'u',	'v',	'w',
	'x',	'y',	'z',	0x5b,	0x5c,	0x5d,	0x5e,	0x5f,
	0x60,	0x61,	0x62,	0x63,	0x64,	0x65,	0x66,	0x67,
	0x68,	0x69,	0x6a,	0x6b,	0x6c,	0x6d,	0x6e,	0x6f,
	0x70,	0x71,	0x72,	0x73,	0x74,	0x75,	0x76,	0x77,
	0x78,	0x79,	0x7a,	0x7b,	0x7c,	0x7d,	0x7e,	0x7f,
	0x80,	0x81,	0x82,	0x83,	0x84,	0x85,	0x86,	0x87,
	0x88,	0x89,	0x8a,	0x8b,	0x8c,	0x8d,	0x8e,	0x8f,
	0x90,	0x91,	0x92,	0x93,	0x94,	0x95,	0x96,	0x97,
	0x98,	0x99,	0x9a,	0x9b,	0x9c,	0x9d,	0x9e,	0x9f,
	0xa0,	0xa1,	0xa2,	0xa3,	0xa4,	0xa5,	0xa6,	0xa7,
	0xa8,	0xa9,	0xaa,	0xab,	0xac,	0xad,	0xae,	0xaf,
	0xb0,	0xb1,	0xb2,	0xb3,	0xb4,	0xb5,	0xb6,	0xb7,
	0xb8,	0xb9,	0xba,	0xbb,	0xbc,	0xbd,	0xbe,	0xbf,
	0xc0,	0xc1,	0xc2,	0xc3,	0xc4,	0xc5,	0xc6,	0xc7,
	0xc8,	0xc9,	0xca,	0xcb,	0xcc,	0xcd,	0xce,	0xcf,
	0xd0,	0xd1,	0xd2,	0xd3,	0xd4,	0xd5,	0xd6,	0xd7,
	0xd8,	0xd9,	0xda,	0xdb,	0xdc,	0xdd,	0xde,	0xdf,
	0xe0,	0xe1,	0xe2,	0xe3,	0xe4,	0xe5,	0xe6,	0xe7,
	0xe8,	0xe9,	0xea,	0xeb,	0xec,	0xed,	0xee,	0xef,
	0xf0,	0xf1,	0xf2,	0xf3,	0xf4,	0xf5,	0xf6,	0xf7,
	0xf8,	0xf9,	0xfa,	0xfb,	0xfc,	0xfd,	0xfe,	0xff
};

const short *_esl_tolower_tab_ = _esl_C_tolower_;

int esl_tolower(int c)
{
	if ((unsigned int)c > 255)
		return(c);
	if (c < -1)
		return EOF;
	return((_esl_tolower_tab_ + 1)[c]);
}

const char *esl_stristr(const char *instr, const char *str)
{
/*
** Rev History:  16/07/97  Greg Thayer		Optimized
**               07/04/95  Bob Stout		ANSI-fy
**               02/03/94  Fred Cole		Original
**               09/01/03  Bob Stout		Bug fix (lines 40-41) per Fred Bulback
**
** Hereby donated to public domain.
*/
	const char *pptr, *sptr, *start;

	if (!str || !instr)
		return NULL;

	for (start = str; *start; start++) {
		/* find start of pattern in string */
		for (; ((*start) && (esl_toupper(*start) != esl_toupper(*instr))); start++);

		if (!*start)
			return NULL;

		pptr = instr;
		sptr = start;

		while (esl_toupper(*sptr) == esl_toupper(*pptr)) {
			sptr++;
			pptr++;

			/* if end of pattern then pattern was found */
			if (!*pptr)
				return (start);

			if (!*sptr)
				return NULL;
		}
	}
	return NULL;
}


static void null_logger(const char *file, const char *func, int line, int level, const char *fmt, ...)
{
	if (file && func && line && level && fmt) {
		return;
	}
	return;
}


static const char *LEVEL_NAMES[] = {
	"EMERG",
	"ALERT",
	"CRIT",
	"ERROR",
	"WARNING",
	"NOTICE",
	"INFO",
	"DEBUG",
	NULL
};

static int esl_log_level = 7;

static const char *cut_path(const char *in)
{
	const char *p, *ret = in;
	char delims[] = "/\\";
	char *i;

	for (i = delims; *i; i++) {
		p = in;
		while ((p = strchr(p, *i)) != 0) {
			ret = ++p;
		}
	}
	return ret;
}


static void default_logger(const char *file, const char *func, int line, int level, const char *fmt, ...)
{
	const char *fp;
	char data[1024];
	va_list ap;

	if (level < 0 || level > 7) {
		level = 7;
	}
	if (level > esl_log_level) {
		return;
	}
	
	fp = cut_path(file);

	va_start(ap, fmt);

	vsnprintf(data, sizeof(data), fmt, ap);


	fprintf(stderr, "[%s] %s:%d %s() %s", LEVEL_NAMES[level], file, line, func, data);

	va_end(ap);

}

esl_logger_t esl_log = null_logger;

void esl_global_set_logger(esl_logger_t logger)
{
	if (logger) {
		esl_log = logger;
	} else {
		esl_log = null_logger;
	}
}

void esl_global_set_default_logger(int level)
{
	if (level < 0 || level > 7) {
		level = 7;
	}

	esl_log = default_logger;
	esl_log_level = level;
}

size_t esl_url_encode(const char *url, char *buf, size_t len)
{
	const char *p;
	size_t x = 0;
	const char urlunsafe[] = "\r\n \"#%&+:;<=>?@[\\]^`{|}";
	const char hex[] = "0123456789ABCDEF";

	if (!buf) {
		return 0;
	}

	if (!url) {
		return 0;
	}

	len--;

	for (p = url; *p; p++) {
		if (x >= len) {
			break;
		}
		if (*p < ' ' || *p > '~' || strchr(urlunsafe, *p)) {
			if ((x + 3) >= len) {
				break;
			}
			buf[x++] = '%';
			buf[x++] = hex[*p >> 4];
			buf[x++] = hex[*p & 0x0f];
		} else {
			buf[x++] = *p;
		}
	}
	buf[x] = '\0';

	return x;
}

char *esl_url_decode(char *s)
{
	char *o;
	unsigned int tmp;

	for (o = s; *s; s++, o++) {
		if (*s == '%' && strlen(s) > 2 && sscanf(s + 1, "%2x", &tmp) == 1) {
			*o = (char) tmp;
			s += 2;
		} else {
			*o = *s;
		}
	}
	*o = '\0';
	return s;
}

esl_status_t esl_attach_handle(esl_handle_t *handle, esl_socket_t socket, struct sockaddr_in addr)
{
	handle->sock = socket;
	handle->addr = addr;

	if (handle->sock == ESL_SOCK_INVALID) {
		return ESL_FAIL;
	}
	
	
	if (!handle->mutex) {
		esl_mutex_create(&handle->mutex);
	}

	handle->connected = 1;

	esl_send_recv(handle, "connect\n\n");
	

	if (handle->last_sr_event) {
		handle->info_event = handle->last_sr_event;
		handle->last_sr_event = NULL;
		return ESL_SUCCESS;
	}
	
	handle->connected = 0;

	return ESL_FAIL;
}

esl_status_t esl_sendevent(esl_handle_t *handle, esl_event_t *event)
{
	char *txt;

	esl_event_serialize(handle->last_ievent, &txt, ESL_TRUE);

	if (handle->debug) {
		esl_log(ESL_LOG_DEBUG, "SEND EVENT\n%s\n", txt);
	}
	
	send(handle->sock, "sendevent\n", 10, 0);
	send(handle->sock, txt, strlen(txt), 0);
	send(handle->sock, "\n\n", 2, 0);

	free(txt);

	return ESL_SUCCESS;
}

esl_status_t esl_execute(esl_handle_t *handle, const char *app, const char *arg, const char *uuid)
{
	char cmd_buf[128] = "sendmsg";
	char app_buf[512] = "";
	char arg_buf[512] = "";
	char send_buf[1292] = "";
	
	if (uuid) {
		snprintf(cmd_buf, sizeof(cmd_buf), "sendmsg %s", uuid);
	}
	
	if (app) {
		snprintf(app_buf, sizeof(app_buf), "execute-app-name: %s\n", app);
	}

	if (arg) {
		snprintf(arg_buf, sizeof(arg_buf), "execute-app-arg: %s\n", arg);
	}

	snprintf(send_buf, sizeof(send_buf), "%s\ncall-command: execute\n%s%s\n", cmd_buf, app_buf, arg_buf);

	return esl_send_recv(handle, send_buf);
}

esl_status_t esl_listen(const char *host, esl_port_t port, esl_listen_callback_t callback)
{
	esl_socket_t server_sock = ESL_SOCK_INVALID;
	int reuse_addr = 1;
	struct sockaddr_in addr;
	esl_status_t status = ESL_SUCCESS;
	
	if ((server_sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
		return ESL_FAIL;
	}

	setsockopt(server_sock, SOL_SOCKET, SO_REUSEADDR, &reuse_addr, sizeof(reuse_addr));
			   
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(port);
	
    if (bind(server_sock, (struct sockaddr *) &addr, sizeof(addr)) < 0) {
		status = ESL_FAIL;
		goto end;
	}

    if (listen(server_sock, 10000) < 0) {
		status = ESL_FAIL;
		goto end;
	}

	for (;;) {
		int client_sock;                    
		struct sockaddr_in echoClntAddr; 
		unsigned int clntLen;            

		clntLen = sizeof(echoClntAddr);
    
		if ((client_sock = accept(server_sock, (struct sockaddr *) &echoClntAddr, &clntLen)) == ESL_SOCK_INVALID) {
			status = ESL_FAIL;
			goto end;
		}

		callback(server_sock, client_sock, echoClntAddr);
	}

 end:

	if (server_sock != ESL_SOCK_INVALID) {
		closesocket(server_sock);
		server_sock = ESL_SOCK_INVALID;
	}

	return status;

}

esl_status_t esl_connect(esl_handle_t *handle, const char *host, esl_port_t port, const char *password)
{

	struct hostent *result;
	char sendbuf[256];
	int rval;
	const char *hval;

	if (!handle->mutex) {
		esl_mutex_create(&handle->mutex);
	}
	
	handle->sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	
	if (handle->sock == ESL_SOCK_INVALID) {
		snprintf(handle->err, sizeof(handle->err), "Socket Error");
		return ESL_FAIL;
	}

    memset(&handle->sockaddr, 0, sizeof(handle->sockaddr));
	handle->sockaddr.sin_family = AF_INET;
    handle->sockaddr.sin_port = htons(port);

    memset(&handle->hostent, 0, sizeof(handle->hostent));

#ifdef HAVE_GETHOSTBYNAME_R_FIVE
	rval = gethostbyname_r(host, &handle->hostent, handle->hostbuf, sizeof(handle->hostbuf), &handle->errnum);
	result = handle->hostent;
#else
	rval = gethostbyname_r(host, &handle->hostent, handle->hostbuf, sizeof(handle->hostbuf), &result, &handle->errnum);
#endif
	
	if (rval) {
		strerror_r(handle->errnum, handle->err, sizeof(handle->err));
		goto fail;
	}

	memcpy(&handle->sockaddr.sin_addr, result->h_addr, result->h_length);
	
	rval = connect(handle->sock, (struct sockaddr *) &handle->sockaddr, sizeof(handle->sockaddr));
	
	if (rval) {
		snprintf(handle->err, sizeof(handle->err), "Socket Connection Error");
		goto fail;
	}

	handle->connected = 1;

	if (esl_recv(handle)) {
		snprintf(handle->err, sizeof(handle->err), "Connection Error");
		goto fail;
	}

	hval = esl_event_get_header(handle->last_event, "content-type");

	if (strcasecmp(hval, "auth/request")) {
		snprintf(handle->err, sizeof(handle->err), "Connection Error");
		goto fail;
	}

	snprintf(sendbuf, sizeof(sendbuf), "auth %s\n\n", password);
	esl_send(handle, sendbuf);

	
	if (esl_recv(handle)) {
		snprintf(handle->err, sizeof(handle->err), "Connection Error");
		goto fail;
	}
	

	hval = esl_event_get_header(handle->last_event, "reply-text");

	if (strcasecmp(hval, "+OK accepted")) {
		snprintf(handle->err, sizeof(handle->err), "Connection Error");
		goto fail;
	}

	return ESL_SUCCESS;

 fail:
	
	esl_disconnect(handle);

	return ESL_FAIL;
}

esl_status_t esl_disconnect(esl_handle_t *handle)
{
	esl_event_safe_destroy(&handle->last_event);
	esl_event_safe_destroy(&handle->last_sr_event);
	esl_event_safe_destroy(&handle->last_ievent);
	esl_event_safe_destroy(&handle->info_event);

	if (handle->mutex) {
		esl_mutex_destroy(&handle->mutex);
	}

	if (handle->sock != ESL_SOCK_INVALID) {
		closesocket(handle->sock);
		handle->sock = ESL_SOCK_INVALID;
		return ESL_SUCCESS;
	}
	
	handle->connected = 0;

	return ESL_FAIL;
}

esl_status_t esl_recv_event_timed(esl_handle_t *handle, uint32_t ms, esl_event_t **save_event)
{
	fd_set rfds, efds;
	struct timeval tv = { 0, ms * 1000 };
	int max, activity;
	esl_status_t status = ESL_SUCCESS;

	esl_mutex_lock(handle->mutex);
	FD_ZERO(&rfds);
	FD_ZERO(&efds);
	FD_SET(handle->sock, &rfds);
	FD_SET(handle->sock, &efds);
	
	max = handle->sock + 1;
	
	if ((activity = select(max, &rfds, NULL, &efds, &tv)) < 0) {
		status = ESL_FAIL;
		goto done;
	}

	if (activity && FD_ISSET(handle->sock, &rfds)) {
		if (esl_recv_event(handle, save_event)) {
			status = ESL_FAIL;
			goto done;
		}
	} else {
		status = ESL_BREAK;
	}

 done:

	esl_mutex_unlock(handle->mutex);

	return status;

}


esl_status_t esl_recv_event(esl_handle_t *handle, esl_event_t **save_event)
{
	char *c;
	esl_ssize_t rrval;
	int crc = 0;
	esl_event_t *revent = NULL;
	char *beg;
	char *hname, *hval;
	char *col;
	char *cl;
	esl_ssize_t len;
	int zc = 0;
	
	esl_mutex_lock(handle->mutex);

	esl_event_safe_destroy(&handle->last_event);
	memset(handle->header_buf, 0, sizeof(handle->header_buf));

	c = handle->header_buf;
	beg = c;

	while(handle->connected) {
		rrval = recv(handle->sock, c, 1, 0);

		if (rrval == 0) {
			if (++zc >= 100) {
				esl_disconnect(handle);
				esl_mutex_unlock(handle->mutex);
				return ESL_FAIL;
			}
		} else if (rrval < 0) {
			strerror_r(handle->errnum, handle->err, sizeof(handle->err));
			goto fail;
		} else {
			zc = 0;
			
			if (*c == '\n') {
				if (++crc == 2) {
					break;
				}
				
				if (!revent) {
					esl_event_create(&revent, ESL_EVENT_COMMAND);
				}
				
				hname = beg;
				hval = col = NULL;
				
				if (hname && (col = strchr(hname, ':'))) {
					hval = col + 1;
					*col = '\0';
					while(*hval == ' ') hval++;
				}
			
				*c = '\0';
				
				if (hname && hval) {
					esl_url_decode(hval);
					if (handle->debug > 1) {
						esl_log(ESL_LOG_DEBUG, "RECV HEADER [%s] = [%s]\n", hname, hval);
					}
					esl_event_add_header_string(revent, ESL_STACK_BOTTOM, hname, hval);
				}

				beg = c+1;
				
				
			} else {
				crc = 0;
			}

			c++;
		}
	}

	if (!revent) {
		goto fail;
	}

	if ((cl = esl_event_get_header(revent, "content-length"))) {
		char *body;
		esl_ssize_t sofar = 0;
		
		len = atol(cl);
		body = malloc(len+1);
		esl_assert(body);
		*(body + len) = '\0';
		
		do {
			esl_ssize_t r;
			if ((r = recv(handle->sock, body + sofar, len - sofar, 0)) < 0) {
				strerror_r(handle->errnum, handle->err, sizeof(handle->err));	
				goto fail;
			}
			sofar += r;
		} while (sofar < len);
		
		revent->body = body;
	}

	if (save_event) {
		*save_event = revent;
	} else {
		handle->last_event = revent;
	}
	
	if (revent) {
		const char *hval = esl_event_get_header(revent, "reply-text");

		if (!esl_strlen_zero(hval)) {
			strncpy(handle->last_reply, hval, sizeof(handle->last_reply));
		}

		hval = esl_event_get_header(revent, "content-type");

		if (!esl_strlen_zero(hval) && !strcasecmp(hval, "text/event-plain") && revent->body) {
			const char *en;
			esl_event_types_t et = ESL_EVENT_COMMAND;
			char *body = strdup(revent->body);
			char *beg;
			char *hname, *hval;
			char *col;
			char *cl;
			esl_ssize_t len;
			char *c;
			
			esl_event_safe_destroy(&handle->last_ievent);

			if ((en = esl_stristr("event-name:", body))) {
				en++;
				while(*en == ' ') en++;
				if (en) {
					esl_name_event(en, &et);
				}
			}
			
			esl_event_create(&handle->last_ievent, et);

			beg = body;

			while(beg) {
				if (!(c = strchr(beg, '\n'))) {
					break;
				}

				hname = beg;
				hval = col = NULL;
			
				if (hname && (col = strchr(hname, ':'))) {
					hval = col + 1;
					*col = '\0';
					while(*hval == ' ') hval++;
				}
				
				*c = '\0';
			
				if (hname && hval) {
					esl_url_decode(hval);

					if (handle->debug > 1) {
						esl_log(ESL_LOG_DEBUG, "RECV INNER HEADER [%s] = [%s]\n", hname, hval);
					}
					esl_event_add_header_string(handle->last_ievent, ESL_STACK_BOTTOM, hname, hval);
				}
				
				beg = c + 1;
			}

			free(body);

			if ((cl = esl_event_get_header(handle->last_ievent, "content-length"))) {
				esl_ssize_t sofar = 0;
		
				len = atol(cl);
				body = malloc(len+1);
				esl_assert(body);
				*(body + len) = '\0';
				
				do {
					esl_ssize_t r;
					if ((r = recv(handle->sock, body + sofar, len - sofar, 0)) < 0) {
						strerror_r(handle->errnum, handle->err, sizeof(handle->err));	
						goto fail;
					}
					sofar += r;
				} while (sofar < len);
				
				handle->last_ievent->body = body;
			}


			if (handle->debug) {
				char *foo;
				esl_event_serialize(handle->last_ievent, &foo, ESL_FALSE);
				esl_log(ESL_LOG_DEBUG, "RECV EVENT\n%s\n", foo);
				free(foo);
			}
		}
		
		if (handle->debug) {
			char *foo;
			esl_event_serialize(revent, &foo, ESL_FALSE);
			esl_log(ESL_LOG_DEBUG, "RECV MESSAGE\n%s\n", foo);
			free(foo);
		}
	}

	esl_mutex_unlock(handle->mutex);

	return ESL_SUCCESS;

 fail:

	esl_disconnect(handle);
	return ESL_FAIL;

}

esl_status_t esl_send(esl_handle_t *handle, const char *cmd)
{
	const char *e = cmd + strlen(cmd) -1;
	
	if (handle->debug) {
		esl_log(ESL_LOG_DEBUG, "SEND\n%s\n", cmd);
	}
	
	if (send(handle->sock, cmd, strlen(cmd), 0)) {
		strerror_r(handle->errnum, handle->err, sizeof(handle->err));
		return ESL_FAIL;
	}

	if (!(*e == '\n' && *(e-1) == '\n')) {
		if (send(handle->sock, "\n\n", 2, 0)) {
			strerror_r(handle->errnum, handle->err, sizeof(handle->err));
			return ESL_FAIL;
		}
	}
	
	return ESL_SUCCESS;

}


esl_status_t esl_send_recv(esl_handle_t *handle, const char *cmd)
{
	const char *hval;
	esl_status_t status;
	
	esl_mutex_lock(handle->mutex);
	esl_send(handle, cmd);
	status = esl_recv_event(handle, &handle->last_sr_event);
	
	if (handle->last_sr_event) {
		hval = esl_event_get_header(handle->last_sr_event, "reply-text");

		if (!esl_strlen_zero(hval)) {
			strncpy(handle->last_sr_reply, hval, sizeof(handle->last_sr_reply));
		}
	}
	
	esl_mutex_unlock(handle->mutex);

	return status;
}




