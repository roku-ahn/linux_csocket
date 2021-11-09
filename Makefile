#define personal variables here.
override HOME=$(CURDIR)/..
override MAKE_DIR=$(CURDIR)
override INSTALL_DIR=$(HOME)/release

# It must include Makefile in last.
include Makefile.mk