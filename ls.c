#include <stdio.h>
#include <dirent.h>
#include <unistd.h>

/* our boolean to show all in the directory */
int show_all = 0;

/* argc: character count and argv string array (pointers) */
int main (int argc, char *argv[])
{
    int opt;
    while ((opt = getopt(argc, argv, "a")) != -1) {
        switch (opt) {
            case 'a':
                show_all = 1;
                break;
            default:
                /* for invalid arguments */
                fprintf(stderr, "usage: %s [-a] [path]\n", argv[0]);
                return 1;
        }
    }

    /* test if a custom path is passed */
    const char *path = (optind < argc) ? argv[optind] : ".";

    /* open stream */
    DIR *dir = opendir(path);
    
    /* non-existant directory: return error */
    if (!dir) {
        perror("opendir");

        return 1;
    }

    /* list contents */
    struct dirent *entry;
    while((entry = readdir(dir)) != NULL) {
        /* skip the dot files if not 'show all' */
        if (!show_all && entry->d_name[0] == '.') continue;
        printf("%s \n", entry->d_name);
    }

    /* close the stream */
    closedir(dir);

    return 0;
}

