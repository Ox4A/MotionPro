#include <openssl/evp.h>
#include <openssl/err.h>
#include<openssl/sha.h>
#include <ctime>
#include<cstdint>
#include <vector>
#include <string>
#include<cstring>
#include<cmath>
using namespace std;
#define N 6
int Tc = 30;
const unsigned char key1[17] = "A04579D683E4A2CF";
const unsigned char key2[17] = "7D624A3C8F193B0E";
uint32_t Truncate(const vector<uint8_t>& hash) {
    uint32_t result = 0;
    for (size_t i = 0; i < sizeof(result); ++i) {
        result <<= 8;
        result |= hash[i];
    }
    return result;
}

// 生成动态口令
uint32_t GenerateDynamicPassword(const string& user_name) {
    // T 是参与运算的时间因子
    auto currentTime = time(nullptr);
    uint64_t T0 = static_cast<uint64_t>(currentTime);
    uint64_t T = T0 / Tc;

    // 使用OpenSSL的SHA-256算法代替SM3算法
    vector<uint8_t> hash(SHA256_DIGEST_LENGTH);
    EVP_MD_CTX* SHA256_token = EVP_MD_CTX_new();
    EVP_DigestInit_ex(SHA256_token, EVP_sha256(), NULL);
    if (user_name == "user1") EVP_DigestUpdate(SHA256_token, key1, strlen((char*)key1));
    else if (user_name == "root") EVP_DigestUpdate(SHA256_token, key2, strlen((char*)key2));
    EVP_DigestUpdate(SHA256_token, &T, sizeof(T));
    EVP_DigestFinal_ex(SHA256_token, hash.data(), NULL);
    EVP_MD_CTX_free(SHA256_token);

    // 截位函数
    uint32_t OD = Truncate(hash);

    uint32_t P = OD % (uint32_t)pow(10, N);
    return P;
}