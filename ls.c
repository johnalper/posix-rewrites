#include <stdio.h>
#include <dirent.h>

/* argc: character count and argv string array (pointers) */
int main (int argc, char *argv[])
{
    /* check argument count */
    const char *path = (argc > 1) ? argv[1] : ".";

    /* open stream */
    DIR *dir = opendir(path);
    
    /* non-existant directory: return error */
    if (!dir) {
	perror("opendir");

	return 1;
    }

    return 0;
}

