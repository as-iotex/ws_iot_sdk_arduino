#include "wsiotsdk.h"
  
enum {
    key_bits = 256,
};

psa_key_id_t key_id = 0;

void serial_init(void)
{
    Serial.begin(115200);
    delay(1000);
    Serial.println();
}

void sdk_ecdsa_test(void)
{   
    psa_status_t status;
    
    psa_key_attributes_t attributes = PSA_KEY_ATTRIBUTES_INIT;

    unsigned char inbuf[] = "iotex_ecdsa_test_only";
	unsigned char buf[65] = {0};
    unsigned int  sinlen   = 0;

    psa_crypto_init();

    if ( key_id == 0) {
        printf("Generate a key pair...\n");
		
	    psa_set_key_usage_flags(&attributes, PSA_KEY_USAGE_SIGN_HASH | PSA_KEY_USAGE_VERIFY_HASH | PSA_KEY_USAGE_EXPORT);
	    psa_set_key_algorithm(&attributes, PSA_ALG_ECDSA(PSA_ALG_SHA_256));
	    psa_set_key_type(&attributes, PSA_KEY_TYPE_ECC_KEY_PAIR(PSA_ECC_FAMILY_SECP_K1));
	    psa_set_key_bits(&attributes, key_bits);

        status = psa_generate_key(&attributes, &key_id);
	    if (status != PSA_SUCCESS) {
		    printf("Failed to generate key %d\n", status);
	    }
    }
    
	printf("Success to generate a key pair: key id : %x\n", key_id);

    status = psa_sign_message( key_id, PSA_ALG_ECDSA(PSA_ALG_SHA_256), inbuf, strlen((const char *)inbuf) + 1, (unsigned char *)buf, 65, &sinlen);
    if (status != PSA_SUCCESS) {
		printf("Failed to sign message %x\n", status);
	}else{
        printf("Success to sign message %d\n", sinlen);
    }

    status = psa_verify_message( key_id, PSA_ALG_ECDSA(PSA_ALG_SHA_256), inbuf, strlen((const char *)inbuf) + 1, (unsigned char *)buf, sinlen);
    if (status != PSA_SUCCESS) {
		printf("Failed to verify message %d\n", status);
	}else{
        printf("Success to verify message\n");
    }
}

void setup() {
  
    serial_init();

    psa_crypto_init(); 
}

void loop() {
    
  sdk_ecdsa_test();

  delay(1000);

}
