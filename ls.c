#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>

/* helper function to test mode type and permissions */
void mode_string(mode_t mode, char *str)
{
    if (S_ISDIR(mode))       str[0] = 'd';
    else if (S_ISLNK(mode))  str[0] = 'l';
    else if (S_ISCHR(mode))  str[0] = 'c';
    else if (S_ISBLK(mode))  str[0] = 'b';
    else if (S_ISFIFO(mode)) str[0] = 'p';
    else if (S_ISSOCK(mode)) str[0] = 's';
    else                     str[0] = '-';

    str[1] = (mode & S_IRUSR) ? 'r' : '-';
    str[2] = (mode & S_IWUSR) ? 'w' : '-';
    str[3] = (mode & S_IXUSR) ? 'x' : '-';
    str[4] = (mode & S_IRGRP) ? 'r' : '-';
    str[5] = (mode & S_IWGRP) ? 'w' : '-';
    str[6] = (mode & S_IXGRP) ? 'x' : '-';
    str[7] = (mode & S_IROTH) ? 'r' : '-';
    str[8] = (mode & S_IWOTH) ? 'w' : '-';
    str[9] = (mode & S_IXOTH) ? 'x' : '-';
    str[10] = '\0';
}

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

