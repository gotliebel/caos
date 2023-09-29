#include <inttypes.h>
#include <limits.h>
#include <openssl/err.h>
#include <openssl/evp.h>
#include <openssl/sha.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    unsigned char buffer[1000000];
    int sum_bytes = 0;
    int read_result = read(0, buffer, sizeof(buffer));
    sum_bytes += read_result;
    while (read_result > 0) {
        read_result = read(0, buffer + sum_bytes, sizeof(buffer) - sum_bytes);
        sum_bytes += read_result;
    }
    unsigned char key[10000];
    unsigned char iv[10000];
    unsigned char* salt = buffer + 8;
    EVP_BytesToKey(
        EVP_aes_256_cbc(),
        EVP_sha256(),
        salt,
        argv[1],
        strlen(argv[1]),
        1,
        key,
        iv);
    EVP_DecryptInit(ctx, EVP_aes_256_cbc(), key, iv);
    unsigned char result[1000000];
    int result_size = sum_bytes - 16;
    int len = 0;
    EVP_DecryptUpdate(ctx, result, &result_size, buffer + 16, result_size);
    EVP_DecryptFinal_ex(ctx, result + result_size, &len);
    result_size += len;
    for (int i = 0; i < result_size; ++i) {
        printf("%c", result[i]);
    }
    EVP_CIPHER_CTX_free(ctx);
    return 0;
}