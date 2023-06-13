#include "wsiotsdk.h"

void serial_init(void)
{
    Serial.begin(115200);
    delay(1000);
    Serial.println();
}

void sdk_hash_test(void)
{   
    psa_status_t status;

    uint8_t sha256_input[7]   = "123456";
    uint8_t sha256_output[32] = {0};
    uint8_t sha256_result[32] = {0x8d, 0x96, 0x9e, 0xef, 0x6e, 0xca, 0xd3, 0xc2, 0x9a, 0x3a, 0x62, 0x92, 0x80, 0xe6, 0x86, 0xcf, 0x0c, 0x3f, 0x5d, 0x5a, 0x86, 0xaf, 0xf3, 0xca, 0x12, 0x02, 0x0c, 0x92, 0x3a, 0xdc, 0x6c, 0x92};

    size_t hash_length = 0;
    
    Serial.printf("Computing Hash\n");
    psa_hash_compute( 0x02000009, sha256_input, 6, sha256_output, 32, &hash_length );
    Serial.printf("Compute Hash finish\n");
    status = psa_hash_compare( 0x02000009, sha256_input, 6, sha256_result, 32 );

    Serial.printf("Compare Hash result:(0 success, non-zero fail) %d\n", status);
}

void setup() {
  
    serial_init();

    psa_crypto_init(); 
}

void loop() {
    
  sdk_hash_test();

  delay(1000);

}
