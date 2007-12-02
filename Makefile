default: message

COYOTOS_SRC=..

include $(COYOTOS_SRC)/build/make/makerules.mk

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

#$(MAKE) -C SPECS TARGETS=$(TARGETS)

all:

install: all

clean: clean-local
clean-local:
	$(MAKE) -C SPECS clean
	@if [ -r coytools/Makefile ]; then \
	  $(MAKE) -C coytools distclean; \
	fi
