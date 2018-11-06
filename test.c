#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>

int main (int ac, char **av)

{
	DIR *dstr = opendir("/dev/block/7:1");
	struct dirent *d;

	closedir(dstr);
	return (0);


}
