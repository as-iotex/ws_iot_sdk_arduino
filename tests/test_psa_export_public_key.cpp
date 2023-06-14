#include <gtest/gtest.h>
#include "WSIoTSDK.h"
#include "test_helpers.h"

class PsaExportPublicKey : public ::testing::Test {
    protected:
        void SetUp() override 
        {
        }
        void TearDown() override
        {
            reset_global_data();
            crypto_slot_management_reset_global_data();
        }
        
        uint8_t private_key[32] = {0xb8, 0x88, 0xa3, 0x71, 0xb8, 0x25, 0xa0, 0x05, 0x1b, 0x2a, 0xd1, 0x6f, 0x03, 0xc4, 0xfd, 0x7b, 0xcf, 0x86, 0x58, 0x92, 0x73, 0x06, 0x11, 0xe9, 0xae, 0x79, 0x4a, 0x16, 0xba, 0xa2, 0xaf, 0xe5};
        uint8_t public_key[65] = {0x04, 0x77, 0x9b, 0x4b, 0x4a, 0xc8, 0x75, 0xd4, 0xed, 0xd7, 0x3e, 0xc5, 0xf8, 0x7a, 0xb9, 0x09, 0x43, 0xc7, 0x14, 0x47, 0x2f, 0x8d, 0x9b, 0xad, 0xfa, 0x29, 0x6b, 0xd3, 0x0c, 0x97, 0x4d, 0x3c, 0xc2, 0x60, 0xc0, 0x51, 0xd7, 0x33, 0x88, 0x24, 0xdb, 0x9c, 0xf2, 0x75, 0xa3, 0x54, 0x00, 0xbc, 0xac, 0x1d, 0xa2, 0x11, 0xd4, 0xc8, 0x79, 0xa9, 0x31, 0xe0, 0x82, 0xa3, 0x85, 0xbc, 0x21, 0xb1, 0x0c};

        void ImportEccKey(psa_key_id_t *source_key, psa_key_attributes_t *attr, bool allowExport = true)
        {
            psa_crypto_init();
            psa_set_key_algorithm(attr, PSA_ALG_ECDSA_ANY);
            psa_set_key_type(attr, PSA_KEY_TYPE_ECC_KEY_PAIR(PSA_ECC_FAMILY_SECP_R1));
            psa_set_key_bits(attr, 256);
            psa_set_key_lifetime(attr, PSA_KEY_LIFETIME_VOLATILE);
            if(allowExport) { psa_set_key_usage_flags(attr, PSA_KEY_USAGE_EXPORT); }
            psa_status_t status = psa_import_key(attr, private_key, sizeof(private_key), source_key);
            ASSERT_EQ(status, PSA_SUCCESS);
        }
};

TEST_F(PsaExportPublicKey, BadState) {
    psa_key_id_t source_key = 0;
    psa_key_attributes_t attr = PSA_KEY_ATTRIBUTES_INIT;
    uint8_t buffer[65] = {0};
    size_t buffer_size = 0;
    psa_status_t status = psa_export_public_key(source_key, buffer, sizeof(buffer), &buffer_size);
    EXPECT_EQ(status, PSA_ERROR_BAD_STATE);
}

TEST_F(PsaExportPublicKey, BadHandle) {
    psa_key_id_t source_key = 0;
    psa_key_attributes_t attr = PSA_KEY_ATTRIBUTES_INIT;
    uint8_t buffer[65] = {0};
    size_t buffer_size = 0;
    psa_status_t status = psa_export_public_key(source_key, buffer, sizeof(buffer), &buffer_size);
    EXPECT_EQ(status, PSA_ERROR_BAD_STATE);
}

TEST_F(PsaExportPublicKey, ExportFlagNotSet) {
    psa_key_id_t source_key = 0;
    psa_key_attributes_t attr = PSA_KEY_ATTRIBUTES_INIT;
    uint8_t buffer[65] = {0};
    size_t buffer_size = 0;
    ImportEccKey(&source_key, &attr, false);
    psa_status_t status = psa_export_public_key(source_key, buffer, sizeof(buffer), &buffer_size);
    // Exporting a public key does not require usage flags. So this should succeed.
    EXPECT_EQ(status, PSA_SUCCESS);
}

TEST_F(PsaExportPublicKey, BufferSizeTooSmall) {
    psa_key_id_t source_key = 0;
    psa_key_attributes_t attr = PSA_KEY_ATTRIBUTES_INIT;
    uint8_t buffer[65] = {0};
    size_t buffer_size = 0;
    ImportEccKey(&source_key, &attr);
    auto expected_size = PSA_EXPORT_PUBLIC_KEY_OUTPUT_SIZE(PSA_KEY_TYPE_ECC_KEY_PAIR(PSA_ECC_FAMILY_SECP_R1), 256);
    psa_status_t status = psa_export_public_key(source_key, buffer, expected_size-1, &buffer_size);
    EXPECT_EQ(status, PSA_ERROR_BUFFER_TOO_SMALL);
}

TEST_F(PsaExportPublicKey, EccKey) {
    psa_key_id_t source_key = 0;
    psa_key_attributes_t attr = PSA_KEY_ATTRIBUTES_INIT;
    uint8_t buffer[65] = {0};
    size_t buffer_size = 0;
    ImportEccKey(&source_key, &attr);
    psa_status_t status = psa_export_public_key(source_key, buffer, sizeof(buffer), &buffer_size);
    EXPECT_EQ(status, PSA_SUCCESS);
    EXPECT_EQ(buffer_size, sizeof(public_key));
    // printf("Exported private key: ");
    // for (size_t i = 0; i < sizeof(private_key); i++) {
    //     printf("%02x", private_key[i]);
    // }
    // printf("\n");
    // // Print buffer as a hex string
    // printf("Exported public key: ");
    // for (size_t i = 0; i < buffer_size; i++) {
    //     printf("%02x", buffer[i]);
    // }
    // printf("\n");
    // // Print public_key as a hex string
    // printf("Expected public key: ");
    // for (size_t i = 0; i < sizeof(public_key); i++) {
    //     printf("%02x", public_key[i]);
    // }
    // printf("\n");
    EXPECT_EQ(memcmp(buffer, public_key, sizeof(public_key)), 0);
}