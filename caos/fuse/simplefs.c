#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FUSE_USE_VERSION 30
#include <fuse.h>

typedef struct {
    char file_name[1000];
    size_t size;
    char* contents;
} my_file_t;

size_t file_count;
my_file_t* fs;

void open_filesystem(const char* src)
{
    FILE* file = fopen(src, "r");
    fscanf(file, "%lu\n", &file_count);
    fs = calloc(file_count, sizeof(my_file_t));
    for (size_t i = 0; i < file_count; ++i) {
        fscanf(file, "%s %lu\n", fs[i].file_name, &fs[i].size);
    }
    size_t sum_bytes_read = 0;
    char data[10000];
    while (sum_bytes_read < 10000) {
        size_t bytes =
            fread(data + sum_bytes_read, 1, 10000 - sum_bytes_read, file);
        sum_bytes_read += bytes;
        if (bytes == 0) {
            break;
        }
    }
    char* contents = data;
    for (size_t i = 0; i < file_count; ++i) {
        fs[i].contents = contents;
        contents += fs[i].size;
    }
    fclose(file);
}

int my_readdir(
    const char* path,
    void* out,
    fuse_fill_dir_t filler,
    off_t offset,
    struct fuse_file_info* fi,
    enum fuse_readdir_flags flags)
{
    if (strcmp(path, "/") != 0) {
        return -ENOENT;
    }

    filler(out, ".", NULL, 0, 0);
    filler(out, "..", NULL, 0, 0);

    for (size_t i = 0; i < file_count; ++i) {
        filler(out, fs[i].file_name, NULL, 0, 0);
    }
    return 0;
}

int my_stat(const char* path, struct stat* st, struct fuse_file_info* fi)
{
    if (strcmp(path, "/") == 0) {
        st->st_mode = 0555 | S_IFDIR;
        st->st_nlink = 2;
        return 0;
    }

    const char* need = path + 1;
    for (size_t i = 0; i < file_count; ++i) {
        if (strcmp(fs[i].file_name, need) == 0) {
            st->st_mode = S_IFREG | 0444;
            st->st_nlink = 1;
            st->st_size = fs[i].size;
            return 0;
        }
    }

    return -ENOENT;
}

int my_open(const char* path, struct fuse_file_info* fi)
{
    if (O_RDONLY != (fi->flags & O_ACCMODE)) {
        return -EACCES;
    }

    const char* need = path + 1;
    for (size_t i = 0; i < file_count; ++i) {
        if (strcmp(fs[i].file_name, need) == 0) {
            fi->fh = (uint64_t)(&fs[i]);
            return 0;
        }
    }

    return -ENOENT;
}

int my_read(
    const char* path,
    char* out,
    size_t size,
    off_t offset,
    struct fuse_file_info* fi)
{
    my_file_t* file = (my_file_t*)(fi->fh);

    if (offset >= file->size) {
        return 0;
    }
    if (offset + size > file->size) {
        size = file->size - offset;
    }
    const void* data1 = file->contents + offset;
    memcpy(out, data1, size);
    return size;
}

struct fuse_operations operations = {
    .readdir = my_readdir,
    .getattr = my_stat,
    .open = my_open,
    .read = my_read,
};

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
        {"--src %s", offsetof(my_options_t, src), 0},
        {"--help", offsetof(my_options_t, help), true},
        {NULL, 0, 0}};
    fuse_opt_parse(&args, &my_options, opt_specs, NULL);

    if (my_options.src) {
        open_filesystem(my_options.src);
    }

    int ret = fuse_main(args.argc, args.argv, &operations, NULL);

    return ret;
}