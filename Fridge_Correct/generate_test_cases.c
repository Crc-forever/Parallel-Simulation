#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <string.h>

#define MAX_PATH 260

typedef double real_T;

int main() {
    const long long STEPS = 100000000;
    const int INPUTS_PER_STEP = 3;
    const char* filename = "test_data.bin";
    
    // Prepare to open file for writing
    FILE* fp = fopen(filename, "wb");
    if (fp == NULL) {
        perror("Unable to open file");
        return 1;
    }
    
    // Initialize random number generator
    srand(time(NULL));
    
    // Generate test data
    for (long long i = 0; i < STEPS; i++) {
        // Generate input values
        real_T door_sensor = (rand() % 2) == 0 ? 0.0 : 1.0; // Door state: 0=closed, 1=open
        real_T temperature = 2.0 + (rand() % 100) / 10.0; // Temperature: between 2.0 and 12.0
        real_T ref = 4.0 + (rand() % 20) / 10.0; // Reference temperature: between 4.0 and 6.0
        
        // Write input data to file
        fwrite(&door_sensor, sizeof(real_T), 1, fp);
        fwrite(&temperature, sizeof(real_T), 1, fp);
        fwrite(&ref, sizeof(real_T), 1, fp);
        
        // Print progress every 1 million steps
        if (i % 1000000 == 0) {
            printf("Progress: %lld / %lld steps\n", i, STEPS);
        }
    }
    
    // Close file
    fclose(fp);
    
    // Calculate and print file size
    long long total_bytes = STEPS * INPUTS_PER_STEP * sizeof(real_T);
    printf("Test data generation completed!\n");
    printf("Total steps: %lld\n", STEPS);
    printf("Inputs per step: %d\n", INPUTS_PER_STEP);
    printf("Bytes per input value: %zu\n", sizeof(real_T));
    printf("Expected file size: %lld bytes (%.2f MB)\n", total_bytes, (double)total_bytes / (1024 * 1024));
    
    // Use absolute path to copy file
    char currentDir[MAX_PATH];
    char srcPath[MAX_PATH];
    char dstPath[MAX_PATH];
    
    // Get current directory
    if (GetCurrentDirectoryA(MAX_PATH, currentDir) == 0) {
        printf("Failed to get current directory!\n");
        return 1;
    }
    
    // Construct source and destination file paths
    sprintf(srcPath, "%s\\Fridge_Correct_test_data.bin", currentDir);
    sprintf(dstPath, "%s\\..\\Fridge_Correct_origin\\Fridge_Correct_test_data.bin", currentDir);
    
    // Copy file
    BOOL success = CopyFileA(srcPath, dstPath, FALSE);
    if (success) {
        printf("File copied successfully!\n");
    } else {
        printf("File copy failed, error code: %d\n", GetLastError());
    }

    return 0;
}