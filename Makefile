CFLAGS += -D_GNU_SOURCE -D_USE_LARGEFILE64
# Don't define _FILE_OFFSET_BITS

libjmaphack.so: lib.c
	cc -shared -o $@ -D_GNU_SOURCE -D_USE_LARGEFILE64 lib.c
