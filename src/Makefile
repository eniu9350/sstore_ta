#Makefile
#
# Created on: 2012-9-20
#     Author: realjin

CC=gcc
BINDIR=../bin
BINNAME=sstore
BINNAME_PERF=perf

sstore: clean
	$(CC) --std=c99 -g -o $(BINDIR)/$(BINNAME) -I/usr/include -I/usr/local/include/gsl -I/usr/local/include/atddtree -I../include -L. -L/usr/local/lib  -L/opt/lib adt_atddtree.c column.c sstore.c -lm -lgsl -lgslcblas

perf: clean
	$(CC)  -g -o $(BINDIR)/$(BINNAME_PERF) -I/usr/include -I/usr/local/include/gsl -I../include -L. -L/usr/local/lib adt_atddtree.c key.c adtvalue.c perf.c -lm -lgsl -lgslcblas -lrt

clean:
	rm $(BINDIR)/* -rf