# Maintainer: dokutan <dokutan at tutanota dot com>
# Contributor: Esdras Tarsis <esdrastarsis@gmail.com>
pkgname=mouse_m908
pkgver=3.3
pkgrel=1
pkgdesc="Control Redragon gaming mice from Linux, BSD and Haiku"
arch=(x86_64)
url="https://github.com/dokutan/$pkgname"
license=('GPL3')
source=("https://github.com/dokutan/$pkgname/archive/v$pkgver.tar.gz")
sha256sums=('e7232fe1a20948ecf6f40efde43b19656b2b64faad46fd824786ff33bceab3ee')
depends=('libusb' 'gcc-libs')
makedepends=(make)
provides=($pkgname)

build() {
   cd "$pkgname-$pkgver"
   make
}

package() {
   mkdir -p $pkgdir/usr/bin \
            $pkgdir/usr/share/doc \
            $pkgdir/usr/share/man/man1 \
            $pkgdir/etc \
            $pkgdir/usr/share/doc/mouse_m908 \
            $pkgdir/etc/udev/rules.d

	cp ./$pkgname-$pkgver/mouse_m908 $pkgdir/usr/bin/mouse_m908 && \
	cp ./$pkgname-$pkgver/mouse_m908.rules $pkgdir/etc/udev/rules.d && \
	cp ./$pkgname-$pkgver/examples/* $pkgdir/usr/share/doc/mouse_m908/ && \
	cp ./$pkgname-$pkgver/README.md $pkgdir/usr/share/doc/mouse_m908/ && \
	cp ./$pkgname-$pkgver/keymap.md $pkgdir/usr/share/doc/mouse_m908/ && \
	cp ./$pkgname-$pkgver/mouse_m908.1 $pkgdir/usr/share/man/man1/
}
