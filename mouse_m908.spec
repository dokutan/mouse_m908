# Don't put rpm package in subdir see: https://stackoverflow.com/questions/2565509/rpmbuild-generates-rpm-in-which-subdirectory
%define _build_name_fmt %{NAME}-%{VERSION}-%{RELEASE}.%{ARCH}.rpm

Name: mouse_m908
Version: 3.3
Release: 1%{?dist}
Summary: Control Redragon gaming mice from Linux, BSD and Haiku

License: GPL v3
URL:     https://github.com/dokutan/mouse_m908
BuildRequires: gcc-c++ libusb1 libusb1-devel make
Requires: libusb
ExclusiveArch: x86_64

%description
Control Redragon gaming mice from Linux, BSD and Haiku

%build
make -C %{_sourcedir}

%install
mkdir -p %{buildroot}%{_bindir}
mkdir -p %{buildroot}%{_docdir}
mkdir -p %{buildroot}%{_mandir}/man1
mkdir -p %{buildroot}%{_sysconfdir}/udev/rules.d

make \
     PREFIX=%{buildroot} \
     BIN_DIR=%{buildroot}/%{_bindir} \
     ETC_DIR=%{buildroot}/etc \
     DOC_DIR=%{buildroot}%{_docdir} \
     MAN_DIR=%{buildroot}%{_mandir}/man1 install

%clean
rm -rf %{buildroot}

%pre

%post

%files
%{_bindir}/%{name}
%{_docdir}/%{name}
%{_mandir}/man1/%{name}.1.gz
%{_sysconfdir}/udev/rules.d/%{name}.rules

%changelog
%autochangelog
