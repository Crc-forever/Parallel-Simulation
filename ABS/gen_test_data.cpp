#include "rtwtypes.h"
#include <fstream>
#include <iostream>

int main() {
    const int64_T STEPS = 10000000;
    const int LEN = 32;
    std::ofstream out("test_data.bin", std::ios::binary);
    if (!out) return 1;

    int32_T U_Speed[LEN];
    int32_T U_FilterValue[LEN];
    int16_T U_Acc[LEN];
    int16_T U_P_i[LEN];
    int32_T U_Q[LEN];
    int32_T U_H[LEN];
    int32_T U_R[LEN];

    for (int64_T i = 0; i < STEPS; ++i) {
        for (int j = 0; j < LEN; ++j) {
            U_Speed[j] = (int32_T)((i % 1000) + j);
            U_FilterValue[j] = (int32_T)((i % 500) + j * 2);
            U_Acc[j] = (int16_T)(((i + j) % 30000) - 15000);
            U_P_i[j] = (int16_T)(((i * 2 + j) % 30000) - 15000);
            U_Q[j] = (int32_T)((i % 100000) + j);
            U_H[j] = (int32_T)(-(int32_T)(i % 100000) + j);
            U_R[j] = (int32_T)((int32_T)((i ^ j) & 0x7FFFFFFF));
        }

        out.write(reinterpret_cast<const char*>(U_Speed), sizeof(U_Speed));
        out.write(reinterpret_cast<const char*>(U_FilterValue), sizeof(U_FilterValue));
        out.write(reinterpret_cast<const char*>(U_Acc), sizeof(U_Acc));
        out.write(reinterpret_cast<const char*>(U_P_i), sizeof(U_P_i));
        out.write(reinterpret_cast<const char*>(U_Q), sizeof(U_Q));
        out.write(reinterpret_cast<const char*>(U_H), sizeof(U_H));
        out.write(reinterpret_cast<const char*>(U_R), sizeof(U_R));
    }

    out.close();
    std::cout << "test_data.bin generated" << std::endl;
    return 0;
}
