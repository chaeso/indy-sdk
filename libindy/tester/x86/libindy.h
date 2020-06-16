extern void indy_register_tee_method(void *(*key_gen)(),
				      const unsigned char *(*enc)(const unsigned char *msg),
                                      const unsigned char *(*dec)(const unsigned char *msg));
extern unsigned char *indy_tee_test();
