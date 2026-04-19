#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>

void check_file(char* arg_n[], char* argv[])
{
    int sum_flag = 0;

    for (int i = 0; i <= 2; i++)
    {
        int flag = access(argv[i + 1], 0);
        if (flag != -1)
        {
            arg_n[i] = argv[i + 1];
        }
        else
        {
            printf("file is not exists : %s\n", argv[i + 1]);
            sum_flag += flag;
        }
        // DEBUG CODE
        //printf("arg_n[%d] : %s\n", i, arg_n[i]);
    }

    if (sum_flag != 0)
    {
        // DEBUG CODE
        //printf("%d flags captured.\n", sum_flag);
        exit(1);
    }
}

void read_file(uint32_t bins[], char* arg_n[])
{
    int sum_flag = 0;

    for (int i = 0; i <= 2; i++)
    {
        int size = 0;
        FILE* fp = fopen(arg_n[i], "rb");
        if (fp == NULL)
        {
            perror("fopen");
            exit(1);
        }

        size = fread(&bins[i], 1, sizeof(uint32_t), fp);
        // DEBUG CODE
        //printf("%s : 0x%08x\n", arg_n[i], bins[i]);

        if (size != 4)
        {
            printf("size is not 4 bytes of file : %s\n", arg_n[i]);
        }
        sum_flag += size;
        fclose(fp);
    }
    
    if (sum_flag != (4 * 3))
    {
        // DEBUG CODE
        //printf("%d size captured.\n", sum_flag);
        exit(1);
    }
}

uint32_t sum_nums(uint32_t nums[])
{
    uint32_t sum = 0;
    
    for (int i = 0; i <= 2; i++)
    {
        sum += nums[i];
        //printf("sum_bins : %x\n", *(nums[i]));
    }
    // DEBUG CODE
    //printf("sum : %d(0x%08x)\n", sum);

    return sum;
}

int main(int argc, char* argv[])
{
    // argv verify
    if (argc != 4)
    {
        printf("usage : sum-nbo a.bin b.bin c.bin\n");
        return 1;
    }
    
    // argv exception
    // - file existing check
    char* arg_n[3] = { 0 };

    check_file(arg_n, argv);

    // - file byte check and read file contents
    uint32_t bins[3] = { 0 };

    read_file(bins, arg_n);
    
    // change byte oreder
    uint32_t nums[3] = { 0 };

    for (int i = 0; i <= 2; i++)
    {
        nums[i] = ntohl(bins[i]);
        // DEBUG CODE
        //printf("ntohl %d : %d(0x%08x)\n", i, nums[i], nums[i]);
    }

    // print result
    uint32_t result = 0;

    result = sum_nums(nums);
    
    printf("%d(0x%08x) + %d(0x%08x) + %d(0x%08x) = %d(0x%08x)\n", 
            nums[0], nums[0],
            nums[1], nums[1],
            nums[2], nums[2],
            result, result
    );

    return 0;
}
