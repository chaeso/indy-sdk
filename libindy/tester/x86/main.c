#include <stdio.h>
#include "libindy.h"

unsigned char sec_key = 0xfa;

const unsigned char *simple_xor(unsigned char *msg) {
	for(int i=0; msg[i] != '\0'; i++) {
		msg[i] = msg[i] ^ sec_key;
	}
	return msg;
}

const unsigned char *secure_enclave_enc(const unsigned char *msg) {
	unsigned char buf[10240];
	strncpy(buf, msg, 10240);

	printf("Encrypt msg using Secure Enclave (iOS) %s with len = %d\n", buf, strlen(buf));

	return simple_xor(buf);
}

const unsigned char *secure_enclave_dec(const unsigned char *msg) {
	unsigned char buf[10240];
	strncpy(buf, msg, 10240);

	printf("Decrypt msg using Secure Enclave (iOS) %s\n", buf);
	return simple_xor(buf);
}

void key_gen() {
	sec_key = 0xa1;
}

int main()
{
	indy_register_tee_method(key_gen, secure_enclave_enc, secure_enclave_dec);
	unsigned char* result = indy_tee_test();
	printf("result = %s", result);
}
