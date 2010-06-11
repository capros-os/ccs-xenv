# NOTE: This makefile does NOT follow the rest of the Coyotos build
# pattern!!
 
default: all

FCRELEASEVER=$(shell sed 's/.*release \([0-9.]*\).*/\1/' /etc/redhat-release)
DISTSUFFIX=$(shell ./getdistro.sh)
DIST=.${DISTSUFFIX}

#BINUTILS_VERSION=2.18
BINUTILS_VERSION=2.20.1
BINUTILS_SPEC=OS-ARCH-binutils-$(BINUTILS_VERSION).spec

#NEWLIB_VERSION=1.16.0
NEWLIB_VERSION=1.18.0
NEWLIB_SPEC=OS-ARCH-newlib-$(NEWLIB_VERSION).spec

#GCC_VERSION=4.4.3
GCC_VERSION=4.2.4
GCC_SPEC=OS-ARCH-gcc-$(GCC_VERSION).spec
GCCMAJOR=gcc$(firstword $(subst ., ,$(GCC_VERSION)))
#GCCMAJOR=gcc4

BUILD_PLATFORM=`rpm --showrc | grep '^build arch' | sed 's/.*: //'`

GDB_VERSION=7.0.1
GDB_SPEC=OS-ARCH-gdb-$(GDB_VERSION).spec

WITHGCC=--with $(GCCMAJOR)


ALL_OS=coyotos capros
TARGETS=\
	capros-arm \
	capros-i386 \
	coyotos-arm \
	coyotos-i386 \
	coyotos-m68k

OSTARGETS=\
  $(sort $(foreach os,$(ALL_OS),$(patsubst $(os)-%,$(os),$(filter $(os)-%,$(TARGETS)))))

XENV_SPECS=\
	$(foreach T,$(TARGETS),$(patsubst OS-ARCH%,$(T)%,OS-ARCH-xenv.spec))

HOST_XENV_SPECS=\
	$(foreach os,$(OSTARGETS),$(patsubst OS%,$(os)%,OS-host-xenv.spec))

FS_SPECS=\
  $(foreach T,$(TARGETS),$(patsubst OS-ARCH%,$(T)%,OS-ARCH-filesystem.spec))\
  $(foreach os,$(OSTARGETS),$(patsubst OS%,$(os)%,OS-common-filesystem.spec))

BINUTILS_SPECS=\
  $(foreach T,$(TARGETS),$(patsubst OS-ARCH%,$(T)%,$(BINUTILS_SPEC)))

GDB_SPECS=\
  $(foreach T,$(TARGETS),$(patsubst OS-ARCH%,$(T)%,$(GDB_SPEC)))

NEWLIB_SPECS=\
  $(foreach T,$(TARGETS),$(patsubst OS-ARCH%,$(T)%,$(NEWLIB_SPEC)))

GCC_SPECS=\
  $(foreach T,$(TARGETS),$(patsubst OS-ARCH%,$(T)%,$(GCC_SPEC)))

CRTFILES_SPECS=\
  $(foreach T,$(TARGETS),$(patsubst OS-ARCH%,$(T)%,OS-ARCH-crtfiles.spec))

ALL_SPECS=\
	$(XENV_SPECS) \
	$(HOST_XENV_SPECS) \
	$(FS_SPECS) \
	$(BINUTILS_SPECS) \
	$(GDB_SPECS) \
	$(NEWLIB_SPECS) \
	$(CRTFILES_SPECS) \
	$(GCC_SPECS)

ifndef TARGETS
TARGETS=coyotos-i386
endif

RPMBUILD=rpmbuild

../RPMS:
	mkdir ../RPMS

../SRPMS:
	mkdir ../SRPMS

../BUILD:
	mkdir ../BUILD

$(ALL_SPECS): $(wildcard OS*.spec.in)
	./makespec.sh $@ > $@

specs: $(ALL_SPECS)

filesystem: ../BUILD ../RPMS ../SRPMS $(FS_SPECS)
	(set -x; for spec in $(FS_SPECS); do \
	  $(RPMBUILD) -bb \
		--define "dist $(DIST)" \
		--define "_topdir $(PWD)/.." \
		$${spec};\
	done)

binutils: ../BUILD ../RPMS ../SRPMS $(BINUTILS_SPECS)
	(set -x; for spec in $(BINUTILS_SPECS); do \
	  $(RPMBUILD) -bb \
		--define "dist $(DIST)" \
		--define "_topdir $(PWD)/.." \
		$${spec};\
	done)

gdb: ../BUILD ../RPMS ../SRPMS $(GDB_SPECS)
	(set -x; for spec in $(GDB_SPECS); do \
	  $(RPMBUILD) -bb \
		--define "dist $(DIST)" \
		--define "_topdir $(PWD)/.." \
		$${spec};\
	done)

newlib: ../BUILD ../RPMS ../SRPMS $(NEWLIB_SPECS)
	(set -x; for spec in $(NEWLIB_SPECS); do \
	  $(RPMBUILD) $(WITHGCC) -bb \
		--define "dist $(DIST)" \
		--define "_topdir $(PWD)/.." \
		$${spec};\
	done)

gcc: ../BUILD ../RPMS ../SRPMS $(GCC_SPECS)
	(set -x; for spec in $(GCC_SPECS); do \
	  $(RPMBUILD) $(WITHGCC) -bb \
		--define "dist $(DIST)" \
		--define "_topdir $(PWD)/.." \
		$${spec};\
	done)

crtfiles: ../BUILD ../RPMS ../SRPMS $(CRTFILES_SPECS)
	(set -x; for spec in $(CRTFILES_SPECS); do \
	  $(RPMBUILD) $(WITHGCC) -bb \
		--define "dist $(DIST)" \
		--define "_topdir $(PWD)/.." \
		$${spec};\
	done)

pregcc: ../BUILD ../RPMS ../SRPMS $(GCC_SPECS)
	(set -x; for spec in $(GCC_SPECS); do \
	  $(RPMBUILD) $(WITHGCC) --without headers -bb \
		--define "dist $(DIST)" \
		--define "_topdir $(PWD)/.." \
		$${spec};\
	done)

host_xenv: ../BUILD ../RPMS ../SRPMS $(HOST_XENV_SPECS)
	(set -x; for spec in $(HOST_XENV_SPECS); do \
	  $(RPMBUILD) -bb \
		--define "dist $(DIST)" \
		--define "_topdir $(PWD)/.." \
		$${spec};\
	done)

xenv: ../BUILD ../RPMS ../SRPMS $(XENV_SPECS)
	(set -x; for spec in $(XENV_SPECS); do \
	  $(RPMBUILD) $(WITHGCC) -bb \
		--define "dist $(DIST)" \
		--define "_topdir $(PWD)/.." \
		$${spec};\
	done)

build:
	(COYPKGS=`rpm -q -a |egrep '(coyotos|capros)'`; \
	if [ "$${COYPKGS}" != "" ]; then \
	  rpm -e $${COYPKGS}; \
	fi)
	$(MAKE) host_xenv
	$(MAKE) xenv
	$(MAKE) filesystem
	rpm -ivh ../RPMS/$(BUILD_PLATFORM)/*filesystem*.rpm
	$(MAKE) binutils
	rpm -ivh ../RPMS/$(BUILD_PLATFORM)/*binutils*.rpm
	$(MAKE) pregcc
	rpm -ivh ../RPMS/$(BUILD_PLATFORM)/*$(GCCMAJOR)*.rpm
	$(MAKE) newlib
	rpm -ivh ../RPMS/$(BUILD_PLATFORM)/*newlib*.rpm;
	# Deinstall in reverse order because of dependencies:
	rpm -e `rpm -q -a | egrep '(coyotos|capros)' |grep $(GCCMAJOR)`
	$(MAKE) gcc
	rpm -ivh ../RPMS/$(BUILD_PLATFORM)/*$(GCCMAJOR)*.rpm
	$(MAKE) crtfiles
	rpm -ivh ../RPMS/$(BUILD_PLATFORM)/*crtfiles*.rpm
	$(MAKE) gdb
	rpm -ivh ../RPMS/$(BUILD_PLATFORM)/*gdb*.rpm

clean:
	-rm -f $(foreach os,$(ALL_OS),$(patsubst OS-%,$(os)-%,OS-*.spec)) *~
	-rm -rf ../BUILD ../SRPMS ../RPMS ../BUILDROOT
