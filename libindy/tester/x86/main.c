#include <stdio.h>
#include "libindy.h"

unsigned char sec_key = 0xfa;
char *config = "{\"id\":\"x4461xx11234\"}";
char *cred = "{\"key\": \"x4461xx11234\"}";

unsigned char buf1[10240];
unsigned char buf2[10240];

const unsigned char *simple_xor(unsigned char *msg, int len) {
	for(int i=0; i<len; i++) {
		msg[i] = msg[i] ^ sec_key;
	}
	return msg;
}

const unsigned char *secure_enclave_enc(int handle, const unsigned char *msg, unsigned int l, unsigned int *resultLen) {
	memset(buf1, 0, 10240);
	memcpy(buf1, msg, l);
        printf("[ExternalEnc] l=%d\n", l);

        printf("\n msg= ...\n");
	for(int i=0; i<l; i++) {
            printf("(%x), ", buf1[i]);  
	}

 	*resultLen = l;
	printf("Encrypt %s with len = %d\n", buf1, l);
        return msg;
}

const unsigned char *secure_enclave_dec(int handle, const unsigned char *msg, unsigned int l, unsigned int *resultLen) {
	memset(buf2, 0, 10240);
	memcpy(buf2, msg, l);
        printf("[ExternalEnc] l=%d\n", l);

        printf("\n buf2= ...\n");
	for(int i=0; i<l; i++) {
            printf("(%x), ", buf2[i]);  
	}

 	*resultLen = l;
	printf("Decrypt %s with len = %d\n", buf2, l);
        return msg;
}

void key_gen() {
	sec_key = 0xa1;
}


void handle_result2(indy_handle_t command_handle_, indy_error_t err) {
    printf("handle_result2 !!! called");
}

void handle_result(indy_handle_t command_handle_, indy_error_t err) {
    printf("handle_result !!! start");
    indy_error_t ret2 = indy_delete_wallet(command_handle_,
            config,
            cred,
            handle_result2
    );
    printf("handle_result !!! called");
}


int main()
{
	indy_register_tee_method(key_gen, secure_enclave_enc, secure_enclave_dec);
	//unsigned char* result = indy_tee_test();
	//printf("result = %s", result);
 
        indy_handle_t handle = 1;

	indy_error_t ret = indy_create_wallet(handle,
			config,
			cred,
			handle_result	
			);
	while(1) {};
}
