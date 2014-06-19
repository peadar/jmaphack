CFLAGS += -D_GNU_SOURCE -D_USE_LARGEFILE64 -m32
# Don't define _FILE_OFFSET_BITS

libjmaphack.so: lib.c
	cc -shared -o $@ $(CFLAGS) lib.c
