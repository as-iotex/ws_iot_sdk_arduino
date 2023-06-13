#include "wsiotsdk.h"

void serial_init(void)
{
    Serial.begin(115200);
    delay(1000);
    Serial.println();
}

void gen_and_set_seed(void)
{
    uint32_t seed;
    randomSeed(analogRead(1));

    Serial.print("Generate Seed:\n");
    seed = random(255);
    Serial.printf("Seed: %d\n", seed);

    default_SetSeed(seed);
}

void sdk_gen_rand(void)
{   
    uint32_t rand = 0; 

    Serial.print("Generate 10 random:\n");

    for(int i = 0; i < 10; i++)
    {
        psa_generate_random( (uint8_t *)&rand, 4 );

        Serial.printf("%d ", rand);
    }

    Serial.println();
}

void setup() {
  
    serial_init();

    psa_crypto_init();

    gen_and_set_seed();
}

void loop() {
    
  sdk_gen_rand();

  delay(1000);

}
