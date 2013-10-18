#include <dlfcn.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <sys/types.h>

typedef int (*openfn)(const char *, int, mode_t mode);
typedef int (*preadfn)(int fd, void *buf, size_t bytes, off64_t off);

openfn real_open;
preadfn real_pread;


static int inited;

static void init()
{
    if (inited)
        return;
    inited = 1;
    real_open = (openfn)dlsym(RTLD_NEXT, "open");
    real_pread = (preadfn)dlsym(RTLD_NEXT, "pread64");
    fprintf(stderr, "real open: %p, real pread: %p\n", real_open, real_pread);
}

int open(const char *file, int flags, ...)
{
    va_list args;

    init();
    va_start(args, flags);
    mode_t m = va_arg(args, mode_t);
    va_end(args);
    return real_open(file, flags | O_LARGEFILE, m);
}


int pread(int fd, void *buf, size_t count, off_t off)
{
    init();
    return real_pread(fd, buf, count, (unsigned long)off);
}

