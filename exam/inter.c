#include <unistd.h>

int main(int argc, char **argv)
{
    int i;
    int j;
    char array[255];

    if (argc == 3)
    {
        i = 0;
        while (i < 256)
        {
            array[i] = 0;
            i++;
        }
        i = 2;
        while (i >= 1)
        {
            j = 0;
            while (argv[i][j])
            {
                if (i == 2 && !array[(unsigned char)argv[i][j]])
                    array[(unsigned char)argv[i][j]] = 1;
                else if (i == 1 && array[(unsigned char)argv[i][j]] == 1)
                {
                    write(1, &argv[i][j], 1);
                    array[(unsigned char)argv[i][j]] = 2;
                }
                j++;
            }
            i--;
        }
    }
    write(1, "\n", 1);
    return (0);
}