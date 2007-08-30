SPEC_OUT=$1

OS=`echo ${SPEC_OUT}|sed 's/^\([^-]*\)-\([^-]*\)-\(.*\.spec\)$/\1/'`
ARCH=`echo ${SPEC_OUT}|sed 's/^\([^-]*\)-\([^-]*\)-\(.*\.spec\)$/\2/'`
PKG=`echo ${SPEC_OUT}|sed 's/^\([^-]*\)-\([^-]*\)-\(.*\.spec\)$/\3/'`

case $OS in
  coyotos) OSNAME="Coyotos";;
  capros)  OSNAME="CapROS";;
  *)       echo "Unknown operating system.";
           exit 1;;
esac

case $ARCH in
  common) ;;
  host)   ;;
  arm)    ;;
  m68k)   ;;
  i386)   ;;
  *)       echo "Unknown architecture.";
           exit 1;;
esac

if [ "$ARCH" = "common" ]
then
    INARCH="common"
elif [ "$ARCH" = "host" ]
then
    INARCH="host"
else
    INARCH="ARCH"
fi

SPEC_IN="OS-${INARCH}-${PKG}.in"

#echo "$SPEC_IN => $SPEC_OUT"
#echo "OS: ${OS}"
#echo "OSNAME: ${OSNAME}"
#echo "ARCH: ${ARCH}"


cat $SPEC_IN | sed \
  -e '/define CROSSOSNAME /s/^.*$/%define CROSSOSNAME '${OSNAME}'/' \
  -e '/define CROSSOS /s/^.*$/%define CROSSOS '${OS}'/' \
  -e '/define CROSSARCH /s/^.*$/%define CROSSARCH '${ARCH}'/'
