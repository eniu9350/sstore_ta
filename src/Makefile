#Makefile
#
# Created on: 2012-9-20
#     Author: realjin

CC=gcc
BINDIR=../bin
BINNAME=sstore

sstore: clean
	$(CC) --std=c99 -g -o $(BINDIR)/$(BINNAME) -I/usr/include -I/usr/local/include/gsl -I/usr/local/include/atddtree -I../include -L. -L/usr/local/lib  -L/opt/lib adt_atddtree.c column.c sstore.c -lm -lgsl -lgslcblas


clean:
	rm $(BINDIR)/* -rf