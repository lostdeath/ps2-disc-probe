#include <cstdio>
#include <cstring>
#include <unistd.h>

static void check_path(const char* path)
{
    if (access(path, F_OK) == 0)
        printf("[FOUND] %s\n", path);
    else
        printf("[NOT FOUND] %s\n", path);
}

int main()
{
    printf("PS2 Disc Access Diagnostic\n");
    printf("==========================\n\n");

    check_path("/mnt/disc");
    check_path("/mnt/dvd");
    check_path("/mnt/disc/SYSTEM.CNF");
    check_path("/mnt/disc/SLUS_211.99");

    FILE* file = fopen("/mnt/disc/SYSTEM.CNF", "r");

    if (file != nullptr)
    {
        char line[256];

        printf("\nSYSTEM.CNF contents:\n");

        while (fgets(line, sizeof(line), file))
            printf("%s", line);

        fclose(file);
    }
    else
    {
        printf("\nCould not read SYSTEM.CNF.\n");
    }

    printf("\nDiagnostic finished.\n");
    return 0;
}
