CC=icc
CFLAGS=-O3 -Wall -fPIC -I.
LDFLAGS=-ldl -rdynamic 

all: libmeasure.so

measure.o: measure.c
	$(CC) $(CFLAGS) -c -g $^ -o $@

libmeasure.so.1: measure.o
	ld -shared -soname $(notdir $@) -o $(dir $@)/libmeasure.so.1.0 $^
	ldconfig -n $(dir $@)

libmeasure.so: libmeasure.so.1
	ln -s $< $@

clean:
	rm -f *.o *.so */*.so *.so.* */*.so.*

distclean: clean
	rm -f *.a test

