#include "openzap.h"

struct helper {
	int fd;
};

zap_status_t my_write_sample(int16_t *buf, zap_size_t buflen, void *user_data)
{
	int x ;

	struct helper *foo = (struct helper *) user_data;
	for (x = 0; x < buflen; x++) {
		printf("%x ", buf[x]);
	}
	printf("\n");
	write(foo->fd, buf, buflen * 2);
}

int main(int argc, char *argv[])
{
	struct zap_fsk_modulator fsk_trans;
	zap_fsk_data_state_t fsk_data = {0};
	int fd = -1;
	int16_t buf[160] = {0};
	ssize_t len = 0;
	int type, mlen;
	char *sp;
	char str[128] = "";
	char fbuf[256];
	uint8_t databuf[1024] = "";
	struct helper foo;
	
	
	
	if (argc < 2) {
		int x;
		char *url = "sip:cool@rad.com";

		if ((fd = open("tone.raw", O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR)) < 0) {
			fprintf(stderr, "File Error!\n", strerror(errno));
			exit(-1);
		}


		zap_fsk_data_init(&fsk_data, databuf, sizeof(databuf));
#if 1
		zap_fsk_data_add_mdmf(&fsk_data, MDMF_DATETIME, "06061234", 8);
		zap_fsk_data_add_mdmf(&fsk_data, MDMF_PHONE_NUM, "5551212", 7);
		zap_fsk_data_add_mdmf(&fsk_data, MDMF_PHONE_NAME, "Fred Smith", 10);
		//zap_fsk_data_add_mdmf(&fsk_data, MDMF_ALT_ROUTE, url, strlen(url));
#else
		zap_fsk_data_add_sdmf(&fsk_data, "06061234", "0");
		//zap_fsk_data_add_sdmf(&state, "06061234", "5551212");
#endif
		zap_fsk_data_add_checksum(&fsk_data);

		foo.fd = fd;


		zap_fsk_modulator_init(&fsk_trans, FSK_BELL202, 8000, &fsk_data, -14, 180, 5, 300, my_write_sample, &foo);
		zap_fsk_modulator_send_all((&fsk_trans));

		if (fd > -1) {
			close (fd);
		}

		return 0;
	}

	if (zap_fsk_demod_init(&fsk_data, 8000, fbuf, sizeof(fbuf))) {
		printf("wtf\n");
		return 0;
	}

	if ((fd = open(argv[1], O_RDONLY)) < 0) {
		fprintf(stderr, "cant open file %s\n", argv[1]);
		exit (-1);
	}

	while((len = read(fd, buf, sizeof(buf))) > 0) {
		if (zap_fsk_demod_feed(&fsk_data, buf, len / 2) != ZAP_SUCCESS) {
			break;
		}
	}

	while(zap_fsk_data_parse(&fsk_data, &type, &sp, &mlen) == ZAP_SUCCESS) {
		zap_copy_string(str, sp, mlen+1);
		*(str+mlen) = '\0';
		zap_clean_string(str);
		printf("TYPE %d (%s) LEN %d VAL [%s]\n", type, zap_mdmf_type2str(type), mlen, str);
	}

	zap_fsk_demod_destroy(&fsk_data);

	close(fd);
}
