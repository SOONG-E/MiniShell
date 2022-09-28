#include <dirent.h>
#include <stdio.h>

int main()
{
	DIR	*dir;
	struct dirent *dir_ent;

	dir = opendir(".");
	if (!dir)		
		printf("open 실패\n");
	else
		printf("성공\n");
	dir_ent = readdir(dir);
	while (dir_ent)
	{
		printf("(%hhu)", dir_ent->d_type);
		printf("%s\n", dir_ent->d_name);
		dir_ent = readdir(dir);
	}
}