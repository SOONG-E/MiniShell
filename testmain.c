#include <stdio.h>
#include <sys/stat.h>
# include <sys/errno.h>	

int main()
{
	struct stat sb;

	printf("%d\n", stat("/sbin/-l", &sb));
	printf("%d", errno);
	
}