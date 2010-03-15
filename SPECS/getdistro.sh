DISTPFX="un"
DISTRO="unknown"
RELEASEVER=0

if [ -r /etc/redhat-release ]
then
    FEDORA_DISTRO=`sed 's/\(Fedora\).*/\1/' /etc/redhat-release`
    CENTOS_DISTRO=`sed 's/\(CentOS\).*/\1/' /etc/redhat-release`
    REDHAT_DISTRO=`sed 's/\(Red Hat Enterprise\).*/\1/' /etc/redhat-release`

    if [ "${FEDORA_DISTRO}" = "Fedora" ]
    then
	DISTRO="Fedora"
    elif [ "${CENTOS_DISTRO}" = "CentOS" ]
    then
	DISTRO="CentOS"
    elif [ "${REDHAT_DISTRO}" = "Red Hat Enterprise" ]
    then
	DISTRO="RedHat"
    else
	DISTRO="unknown"
    fi

    RELEASEVER=`sed 's/.*release \([0-9.]*\).*/\1/' /etc/redhat-release`
    MAJORVER=`echo ${RELEASEVER} | sed 's/\([0-9]*\).*/\1/'`
fi

case ${DISTRO} in
    Fedora)       DISTPFX="fc";;
    CentOS)       DISTPFX="el";;
    RedHat)	  DISTPFX="el";;
esac


echo "${DISTPFX}${MAJORVER}"
