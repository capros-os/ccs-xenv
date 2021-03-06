Summary: General-purpose utility library for C++
Name: coytools
Version: 0.3.8
Release: 1%{?dist}
License: BSD
Group: System Environment/Libraries
Source0: %{name}-%{version}-%{release}.tar.gz
BuildRoot: %{_tmppath}/%{name}-%{version}-%{release}-root
Requires: libsherpa
Requires: astmaker
Requires: boost >= 1.34.1
BuildRequires: libicu-devel boost-devel >= 1.34.1

%define debug_package %{nil}

%description
Dummy description -- all files are packaged into explicit projects.

%prep
%setup -q

%build
%configure
make

%install
rm -rf $RPM_BUILD_ROOT
%makeinstall
# Hand-generate the debuginfo so that we can package it in the proper
# subpackages:
%{__debug_install_post}

# Work-around to F8 build-id madness until I understand what the heck
# it does:
rm -rf $RPM_BUILD_ROOT/usr/lib/debug/.build-id

%clean
rm -rf $RPM_BUILD_ROOT

%package -n libsherpa
Summary: General-purpose utility library for C++
Group: System Environment/Libraries

%description -n libsherpa
A library of miscellaneous utility functions and classes that have
been useful in our various compilers, and may be useful for 
other applications as well.

%files -n libsherpa
%defattr(-,root,root,-)
%{_libdir}/libsherpa.a
%dir %{_includedir}/libsherpa
%{_includedir}/libsherpa/*.hxx

%package -n libsherpa-debuginfo
Summary: Debug information for package libsherpa-debuginfo
Group: Development/Debug
AutoReqProv: 0

%description -n libsherpa-debuginfo
This package provides debug information for package %{name}.\
Debug information is useful when developing applications that use this\
package or when debugging this package.\

%files -n libsherpa-debuginfo
%defattr(-,root,root,-)
/usr/src/debug/%{name}-%{version}/src/libsherpa/*

%package -n astmaker
Summary: Language for generating AST classes in C++
Group: Development/Languages

%description -n astmaker
Astmaker is a compiler that accepts a language describing ASTs and
emits corresponding C++ AST classes. The classes have various
consistency checking functions that assist in constructing robust
compilers.

%files -n astmaker
%defattr(-,root,root,-)
%{_bindir}/astmaker

%package -n astmaker-debuginfo
Summary: Debug information for package libsherpa-debuginfo
Group: Development/Debug
AutoReqProv: 0

%description -n astmaker-debuginfo
This package provides debug information for package %{name}.\
Debug information is useful when developing applications that use this\
package or when debugging this package.\

%files -n astmaker-debuginfo
%defattr(-,root,root,-)
/usr/src/debug/%{name}-%{version}/src/astmaker/*
/usr/lib/debug/usr/bin/astmaker.debug


%changelog
* Thu Jan 27 2007 Jonathan S. Shapiro <shap@eros-os.com> - 
- Revised to be a master spec file for all coyotos tools.

* Thu Jan 18 2007 Jonathan S. Shapiro <shap@eros-os.com> - 
- Initial build.

