#include "wsiotsdk.h"

#define BUFFER_SIZE 64
#define TEST_PLAINTEXT_LEN  24

void serial_init(void)
{
    Serial.begin(115200);
    delay(1000);
    Serial.println();
}

psa_key_id_t key_id = 0;

void sdk_aes_test(void)
{   
    psa_status_t status;
  
    psa_key_attributes_t    attributes    = PSA_KEY_ATTRIBUTES_INIT;
    psa_cipher_operation_t  operation     = PSA_CIPHER_OPERATION_INIT;
    psa_cipher_operation_t  operation_d   = PSA_CIPHER_OPERATION_INIT;
    uint8_t key_bits = 128;

    uint8_t expected_output[BUFFER_SIZE] = {0};
    uint8_t expected_output_d[BUFFER_SIZE] = {0};
    size_t  expected_output_length, expected_output_length_finish;

    const unsigned char iv[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F};

    const uint8_t plaintext[] = {
            0x45, 0x35, 0xd1, 0x2b, 0x43, 0x77, 0x92, 0x8a,
            0x7c, 0x0a, 0x61, 0xc9, 0xf8, 0x25, 0xa4, 0x86,
            0x71, 0xea, 0x05, 0x91, 0x07, 0x48, 0xc8, 0xef};

    if (key_id == 0) {
 	    psa_set_key_usage_flags(&attributes, PSA_KEY_USAGE_ENCRYPT | PSA_KEY_USAGE_DECRYPT);
        psa_set_key_algorithm(&attributes, PSA_ALG_CBC_PKCS7);
        psa_set_key_type(&attributes, PSA_KEY_TYPE_AES);
        psa_set_key_bits(&attributes, key_bits);

        psa_generate_key(&attributes, &key_id);
    }

    status = psa_cipher_encrypt_setup( &operation, key_id, PSA_ALG_CBC_PKCS7 );
    if (status != PSA_SUCCESS) {
		printf("Failed to encrypt setup %d\n", status);
        return;
	}

    printf("success to encrypt setup\n");

    status = psa_cipher_set_iv( &operation, iv, 16 );
    if (status != PSA_SUCCESS) {
	    printf("Failed to setup iv %d\n", status);
        return;
	}

    status = psa_cipher_update( &operation, plaintext, TEST_PLAINTEXT_LEN, expected_output, BUFFER_SIZE, &expected_output_length );
    if (status != PSA_SUCCESS) {
        printf("Failed to update %d\n", status);
        return;
	}

    printf("Success to update expected_output_length %d\n", expected_output_length);

    status = psa_cipher_finish( &operation, expected_output + expected_output_length , BUFFER_SIZE - expected_output_length, &expected_output_length_finish );
    if (status != PSA_SUCCESS) {
        printf("Failed to finish %d\n", status);
        return;
	}

    expected_output_length_finish += expected_output_length;
    printf("Success to finish expected_output_length %d\n", expected_output_length_finish);

    for(int i = 0; i < BUFFER_SIZE; i++) {
        Serial.print(expected_output[i]);
        Serial.print(" ");
    }
    Serial.print("\n");
  
    status = psa_cipher_decrypt_setup( &operation_d, key_id, PSA_ALG_CBC_PKCS7 );
    if (status != PSA_SUCCESS) {
	 	printf("Failed to decrypt setup %d\n", status);
        return;
	}
    printf("Success to decrypt setup\n");

    status = psa_cipher_set_iv( &operation_d, iv, 16 );
    if (status != PSA_SUCCESS) {
	    printf("Failed to setup iv %d\n", status);
        return;
	}
    printf("Success to decrypt set iv\n");

    status = psa_cipher_update( &operation_d, expected_output, expected_output_length_finish, expected_output_d, BUFFER_SIZE, &expected_output_length );
    if (status != PSA_SUCCESS) {
        printf("Failed to update %d\n", status);
        return;
	}

    status = psa_cipher_finish( &operation_d, expected_output_d + expected_output_length, BUFFER_SIZE - expected_output_length, &expected_output_length_finish );
    if (status != PSA_SUCCESS) {
        printf("Failed to finish %d\n", status);
        return;
	}

    expected_output_length_finish += expected_output_length;
    printf("Success to finish expected_output_length %d\n", expected_output_length_finish);

    for(int i = 0; i < BUFFER_SIZE; i++) {
        Serial.print(expected_output_d[i]); 
        Serial.print(" ");
    }
    Serial.print("\n"); 
}

void setup() {
  
    serial_init();

    psa_crypto_init(); 
}

void loop() {
    
    sdk_aes_test();

    delay(1000);

}
