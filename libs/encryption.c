#include "./3rdPartyLibs/aes.h"
#include "./encryption.h"

void encrypt_data(char *input, int len) {
  struct AES_ctx ctx;
  AES_init_ctx_iv(&ctx, (const uint8_t *)"9876543210101112", (const uint8_t *)"0123456789101112");
  AES_CTR_xcrypt_buffer(&ctx, (uint8_t *)input, len);
}
