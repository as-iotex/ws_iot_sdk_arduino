#include "wsiotsdk.h"

#define KEY_BITS  256

void serial_init(void)
{
    Serial.begin(115200);
    delay(1000);
    Serial.println();
}

void wsiotsdk_test_generate_key(void)
{
    psa_status_t status;
    psa_key_id_t key_id;
    psa_key_attributes_t attributes = PSA_KEY_ATTRIBUTES_INIT;

    uint8_t exported[PSA_KEY_EXPORT_ECC_PUBLIC_KEY_MAX_SIZE(KEY_BITS)];
	uint8_t exported_pairkey[PSA_KEY_EXPORT_ECC_KEY_PAIR_MAX_SIZE(KEY_BITS)];
	
	size_t exported_length = 0;

    Serial.printf("Generate a key pair...\n");
		
	psa_set_key_usage_flags(&attributes, PSA_KEY_USAGE_SIGN_HASH | PSA_KEY_USAGE_VERIFY_HASH | PSA_KEY_USAGE_EXPORT);
	psa_set_key_algorithm(&attributes, PSA_ALG_ECDSA(PSA_ALG_SHA_256));
	psa_set_key_type(&attributes, PSA_KEY_TYPE_ECC_KEY_PAIR(PSA_ECC_FAMILY_SECP_R1));
	psa_set_key_bits(&attributes, KEY_BITS);
		
	status = psa_generate_key(&attributes, &key_id);
	if (status != PSA_SUCCESS) {
		Serial.printf("Failed to generate key %d\n", status);
        return;
	}
	
	printf("Success to generate a key pair: key id : %x\n", key_id);

    status = psa_export_key(key_id, exported_pairkey, sizeof(exported_pairkey), &exported_length);
	if (status != PSA_SUCCESS) {
		Serial.printf("Failed to export pair key %d\n", status);
        return;
	}

	printf("Exported a pair key len %d\n", exported_length);	
	
    for (int i = 0; i < exported_length; i++)
    {
        Serial.printf("%x ", exported_pairkey[i]);
    }
    Serial.println();

    status = psa_export_public_key(key_id, exported, sizeof(exported), &exported_length);
	if (status != PSA_SUCCESS) {
		printf("Failed to export public key %d\n", status);
        return;
	}

	printf("Exported a public key len %d\n", exported_length);	
	
	for (int i = 0; i < exported_length; i++)
	{
        Serial.printf("%x ", exported[i]);
	}
	Serial.println();

}

void setup() {
  
    serial_init();

    psa_crypto_init(); 
}

void loop() {
    
  wsiotsdk_test_generate_key();

  delay(1000);

}
