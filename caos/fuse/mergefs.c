#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define FUSE_USE_VERSION 30
#include <fuse.h>

typedef struct {
    char directory[1000][1000];
    int size;
} file_system_t;

typedef struct {
    char file_name[1000];
    bool is_directory;
    int error;
    struct stat stat_info;
} my_file_t;

file_system_t fs;

void open_filesystem(char* src)
{
    char* ptr = strtok(src, ":");
    char dir[1000];
    int count_dir = 0;
    getcwd(dir, 1000);
    while (ptr) {
        sprintf(fs.directory[count_dir], "%s/%s", dir, ptr);
        count_dir++;
        ptr = strtok(NULL, ":");
    }
    fs.size = count_dir;
}

int check(char file_system[1000][1000], char* path)
{
    for (int i = 0; i < 1000; i++) {
        if (!file_system[i][0]) {
            strcpy(file_system[i], path);
            return 1;
        } else if (strncmp(file_system[i], path, strlen(path) + 1) == 0) {
            return 0;
        }
    }
    return 0;
}

int my_readdir(
    const char* path,
    void* out,
    fuse_fill_dir_t filler,
    off_t off,
    struct fuse_file_info* fi,
    enum fuse_readdir_flags flags)
{
    filler(out, ".", NULL, 0, 0);
    filler(out, "..", NULL, 0, 0);
    char cur_path[1000];
    char file_system[1000][1000];
    strcpy(cur_path, path);
    if (strlen(cur_path) == 1) {
        cur_path[0] = 0;
    }
    char cur_dir[1000];
    getcwd(cur_dir, 1000);
    for (int i = 0; i < fs.size; i++) {
        char full[10000];
        sprintf(full, "%s%s", fs.directory[i], cur_path);
        DIR* dir;
        struct dirent* dire;
        if ((dir = opendir(full)) != NULL) {
            while ((dire = readdir(dir)) != NULL) {
                if (check(file_system, dire->d_name) &&
                    dire->d_name[0] != '.') {
                    filler(out, dire->d_name, NULL, 0, 0);
                }
            }
            closedir(dir);
        }
    }
    return 0;
}

int my_stat(const char* path, struct stat* st, struct fuse_file_info* fi)
{
    if (strcmp("/", path) == 0) {
        st->st_nlink = 2;
        st->st_mode = 0555 | S_IFDIR;
        return 0;
    }
    char cur_path[1000];
    my_file_t my_file;
    my_file.is_directory = false;
    my_file.error = ENOENT;
    bool exists = false;
    struct stat stat_info;
    for (int i = 0; i < fs.size; i++) {
        sprintf(cur_path, "%s%s", fs.directory[i], path);
        if (stat(cur_path, &stat_info) == 0) {
            if (stat_info.st_mtime > my_file.stat_info.st_mtime || !exists) {
                if ((stat_info.st_mode & S_IFDIR) == 0) {
                    my_file.is_directory = false;
                } else {
                    my_file.is_directory = true;
                }
                my_file.stat_info = stat_info;
                my_file.error = 0;
                exists = true;
                sprintf(my_file.file_name, "%s", cur_path);
            }
        } else if (!exists) {
            my_file.error = errno;
        }
    }

    if (my_file.error) {
        return -my_file.error;
    }
    if (my_file.is_directory) {
        *st = my_file.stat_info;
        st->st_mode = 0555 | S_IFDIR;
    } else {
        *st = my_file.stat_info;
        st->st_mode = 0444 | S_IFREG;
    }
    return 0;
}

int my_read(
    const char* path,
    char* out,
    size_t size,
    off_t off,
    struct fuse_file_info* fi)
{
    char cur_path[1000];
    my_file_t my_file;
    my_file.is_directory = false;
    my_file.error = ENOENT;
    bool exists = false;
    struct stat stat_info;
    for (int i = 0; i < fs.size; i++) {
        sprintf(cur_path, "%s%s", fs.directory[i], path);
        if (stat(cur_path, &stat_info) == 0) {
            if (stat_info.st_mtime > my_file.stat_info.st_mtime || !exists) {
                if ((stat_info.st_mode & S_IFDIR) == 0) {
                    my_file.is_directory = false;
                } else {
                    my_file.is_directory = true;
                }
                my_file.stat_info = stat_info;
                my_file.error = 0;
                exists = true;
                sprintf(my_file.file_name, "%s", cur_path);
            }
        } else if (!exists) {
            my_file.error = errno;
        }
    }
    int op = open(my_file.file_name, O_RDONLY);
    lseek(op, off, SEEK_SET);
    size = read(op, out, size);
    return size;
}

struct fuse_operations operations = {
    .readdir = my_readdir,
    .getattr = my_stat,
    .read = my_read};

int main(int argc, char* argv[])
{
    struct fuse_args args = FUSE_ARGS_INIT(argc, argv);
    typedef struct {
        char* src;
        int help;
    } my_options_t;

    my_options_t my_options;
    memset(&my_options, 0, sizeof(my_options));
    struct fuse_opt opt_specs[] = {
        {"--src %s", offsetof(my_options_t, src), 0}, {NULL, 0, 0}};
    fuse_opt_parse(&args, &my_options, opt_specs, NULL);

    if (my_options.src) {
        open_filesystem(my_options.src);
    }

    int ret = fuse_main(args.argc, args.argv, &operations, NULL);

    return ret;
}