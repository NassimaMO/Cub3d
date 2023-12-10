#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <time.h>
#include "libft/include/vanilla.h"

void    write_file(char *str, int fd)
{
    write(fd, str, ft_strlen(str));
}

void        create_map(int height, int width, int fd)
{
    int	i;
	int	j;

    i = 0;
	while (i < height)
	{
		j = 0;
		while (j < width && (i == 0 || i == height - 1))
        {
            write_file("1", fd);
			j++;
        }
        if (j == 0)
        {
            write_file("1", fd);
            j++;
        }     
        while (j < width - 1)
        {
            if (rand() % 5 == 0)
                write_file("1", fd);
            else
                write_file("0", fd);
            j++;
        }
        if (j == width - 1)
            write_file("1", fd);
        write_file("\n", fd);
		i++;
	}
}

int main(int argc, char **argv)
{
    // ./executable height width

    int fd;

    fd = open("../map_generated.cub", O_CREAT | O_RDWR);

    if (argc > 3 || !argv[1] || !argv[2] || read(fd, "", 0) == -1)
        return (0);

    write_file("NO ./pics/bluestone.xpm\n\n", fd);
    write_file("SO ./pics/colorstone.xpm\n\n", fd);
    write_file("WE ./pics/greystone.xpm\n\n", fd);
    write_file("EA ./pics/redbrick.xpm\n\n", fd);
    write_file("F 220, 100, 0\n\n", fd);
    write_file("C 225, 30, 0\n\n", fd);

    srand(time(NULL));
    
    create_map(ft_atoi(argv[1]), ft_atoi(argv[2]), fd);

}