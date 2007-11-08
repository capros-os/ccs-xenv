default: message

COYOTOS_SRC=..

include $(COYOTOS_SRC)/build/make/makerules.mk

BINUTILS_DIR=binutils-2.17
GCC_DIR=gcc-3.4.6
CONFIGURE_TARGET=i686-unknown-elf
PREFIX=/coyotos

ifeq "$(TARGETS)" ""
TARGETS=$(COYOTOS_GCC_ARCH)
endif

RPMBUILD=rpmbuild --rcfile SPECS/rpmrc

message:
	@echo "####################################################"
	@echo "#                                                  #"
	@echo "#   The ccs-xenv subtree does not use the normal   #"
	@echo "#  Coyotos build conventions. See ccs-xenv/README. #"
	@echo "#                                                  #"
	@echo "####################################################"

# Naturalized coyotos packages publish libs and interfaces. This one
# does not, but we need dummy targets so that typing "make" here will
# behave sensibly.
libs:
interfaces:

build:
	./make-xenv.sh --stopat binutils 2>&1 | tee binutils.out
	find /coyotos -type f |sort > binutils.files
	find /coyotos -type d |sort > binutils.dirs
	./make-xenv.sh --skip binutils --stopat pregcc 2>&1 | tee pregcc.out
	find /coyotos -type f |sort > pregcc.files
	find /coyotos -type d |sort > pregcc.dirs
	./make-xenv.sh --skip binutils --skip pregcc --stopat newlib 2>&1 | tee newlib.out
	find /coyotos -type f |sort > newlib.files
	find /coyotos -type d |sort > newlib.dirs
	./make-xenv.sh --skip binutils --skip pregcc --skip newlib 2>&1 | tee gcc.out
	find /coyotos -type f |sort > gcc.files
	find /coyotos -type d |sort > gcc.dirs

#$(MAKE) -C SPECS TARGETS=$(TARGETS)

all:

install: all

clean: clean-local
clean-local:
	$(MAKE) -C SPECS clean
	@if [ -r coytools/Makefile ]; then \
	  $(MAKE) -C coytools distclean; \
	fi
