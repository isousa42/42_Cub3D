#include <unistd.h>

int main(int argc, char **argv)
{
    int i;
    int j;
    char array[255];

    if (argc == 3)
    {
        i = 0;
        while(i <= 255)
        {
            array[i] = 0;
            i++;
        }
        i = 1;
        while(i < 3)
        {
            j = 0;
            while(argv[i][j])
            {
                if (!array[(unsigned char)argv[i][j]])
                {
                    write(1, &argv[i][j], 1);
                    array[(unsigned char)argv[i][j]] = 1;
                }
                j++;
            }
            i++;
        }
    }
    write(1, "\n", 1);
    return (0);
}