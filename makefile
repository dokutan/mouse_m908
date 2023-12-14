# paths for the installation
PREFIX = /usr
BIN_DIR = $(PREFIX)/bin
DOC_DIR = $(PREFIX)/share/doc
MAN_DIR = $(PREFIX)/share/man/man1
ETC_DIR = /etc

# compiler options
CC = c++
CC_OPTIONS := -std=c++17 -Wall -Wextra -O2 `pkg-config --cflags libusb-1.0`
LIBS != pkg-config --libs libusb-1.0

# version string
VERSION_STRING = "\"3.3\""

# compile
build: m601 m607 m686 m908 m709 m711 m715 m719 m721 m913 m990 m990chroma generic data_rd.o rd_mouse.o rd_mouse_wireless.o load_config.o mouse_m908.o
	$(CC) *.o -o mouse_m908 $(LIBS) $(CC_OPTIONS)

# copy all files to their correct location
install:
	cp ./mouse_m908 $(BIN_DIR)/mouse_m908 && \
	cp ./mouse_m908.rules $(ETC_DIR)/udev/rules.d && \
	mkdir $(DOC_DIR)/mouse_m908 | true && \
	cp ./examples/* $(DOC_DIR)/mouse_m908/ && \
	cp ./README.md $(DOC_DIR)/mouse_m908/ && \
	cp ./keymap.md $(DOC_DIR)/mouse_m908/ && \
	cp ./mouse_m908.1 $(MAN_DIR)/

install-bsd:
	cp ./mouse_m908 $(BIN_DIR)/mouse_m908 && \
	mkdir $(DOC_DIR)/mouse_m908 | true && \
	cp ./examples/* $(DOC_DIR)/mouse_m908/ && \
	cp ./README.md $(DOC_DIR)/mouse_m908/ && \
	cp ./keymap.md $(DOC_DIR)/mouse_m908/ && \
	cp ./mouse_m908.1 $(MAN_DIR)/

# remove binary
clean:
	rm -f mouse_m908 *.o mouse_m908*.rpm
	rm -rf Haiku/bin Haiku/documentation Haiku/mouse_m908.hpkg

# remove all installed files
uninstall:
	rm -f $(BIN_DIR)/mouse_m908 && \
	rm -f $(ETC_DIR)/udev/rules.d/mouse_m908.rules && \
	rm -rf $(DOC_DIR)/mouse_m908 && \
	rm -f $(MAN_DIR)/mouse_m908.1

# this is an alias to install for backwards compatibility
upgrade: install

# this builds a .rpm for Fedora/RHEL systems
rpm:
	+rpmbuild --buildroot $(PWD)/rpmbuild/BUILDROOT --define "_topdir $(PWD)/rpmbuild" -bb mouse_m908.spec

# this builds .src.rpm for Fedora/RHEL systems
src-rpm:
	rpmbuild --buildroot $(PWD)/rpmbuild/BUILDROOT --define "_topdir $(PWD)/rpmbuild" -bs mouse_m908.spec

# this builds a .hpkg package on Haiku
hpkg:
	mkdir Haiku/bin
	mkdir -p Haiku/documentation/man/man1
	mkdir -p Haiku/documentation/packages/mouse_m908
	cp mouse_m908 Haiku/bin
	cp mouse_m908.1 Haiku/documentation/man/man1
	cp examples/* Haiku/documentation/packages/mouse_m908
	cp README.md Haiku/documentation/packages/mouse_m908
	cp keymap.md Haiku/documentation/packages/mouse_m908
	cd Haiku; \
	package create -b mouse_m908.hpkg; \
	package add mouse_m908.hpkg bin documentation

# targets for the different mice
m601: constructor_m601.o data_m601.o getters_m601.o helpers_m601.o setters_m601.o writers_m601.o readers_m601.o

m607: constructor_m607.o data_m607.o getters_m607.o helpers_m607.o setters_m607.o writers_m607.o readers_m607.o

m686: constructor_m686.o data_m686.o getters_m686.o helpers_m686.o setters_m686.o writers_m686.o readers_m686.o

m908: constructor_m908.o data_m908.o getters_m908.o helpers_m908.o setters_m908.o writers_m908.o readers_m908.o

m709: constructor_m709.o data_m709.o getters_m709.o helpers_m709.o setters_m709.o writers_m709.o readers_m709.o

m711: constructor_m711.o data_m711.o getters_m711.o helpers_m711.o setters_m711.o writers_m711.o readers_m711.o

m715: constructor_m715.o data_m715.o getters_m715.o helpers_m715.o setters_m715.o writers_m715.o readers_m715.o

m719: constructor_m719.o data_m719.o getters_m719.o helpers_m719.o setters_m719.o writers_m719.o readers_m719.o

m721: constructor_m721.o data_m721.o getters_m721.o helpers_m721.o setters_m721.o writers_m721.o readers_m721.o

m913: constructor_m913.o data_m913.o getters_m913.o helpers_m913.o setters_m913.o writers_m913.o readers_m913.o

m990: constructor_m990.o data_m990.o getters_m990.o helpers_m990.o setters_m990.o writers_m990.o readers_m990.o

m990chroma: constructor_m990chroma.o data_m990chroma.o getters_m990chroma.o helpers_m990chroma.o setters_m990chroma.o writers_m990chroma.o readers_m990chroma.o

generic: constructor_generic.o data_generic.o getters_generic.o helpers_generic.o setters_generic.o writers_generic.o readers_generic.o

# individual files
mouse_m908.o:
	$(CC) -c mouse_m908.cpp $(CC_OPTIONS) -D VERSION_STRING=$(VERSION_STRING)

load_config.o:
	$(CC) -c include/load_config.cpp $(CC_OPTIONS)

data_rd.o:
	$(CC) -c include/data.cpp $(CC_OPTIONS)

rd_mouse.o:
	$(CC) -c include/rd_mouse.cpp $(CC_OPTIONS)

rd_mouse_wireless.o:
	$(CC) -c include/rd_mouse_wireless.cpp $(CC_OPTIONS)

constructor_m601.o:
	$(CC) -c include/m601/constructor.cpp $(CC_OPTIONS) -o constructor_m601.o

data_m601.o:
	$(CC) -c include/m601/data.cpp $(CC_OPTIONS) -o data_m601.o

getters_m601.o:
	$(CC) -c include/m601/getters.cpp $(CC_OPTIONS) -o getters_m601.o

helpers_m601.o:
	$(CC) -c include/m601/helpers.cpp $(CC_OPTIONS) -o helpers_m601.o

setters_m601.o:
	$(CC) -c include/m601/setters.cpp $(CC_OPTIONS) -o setters_m601.o

writers_m601.o:
	$(CC) -c include/m601/writers.cpp $(CC_OPTIONS) -o writers_m601.o

readers_m601.o:
	$(CC) -c include/m601/readers.cpp $(CC_OPTIONS) -o readers_m601.o

constructor_m607.o:
	$(CC) -c include/m607/constructor.cpp $(CC_OPTIONS) -o constructor_m607.o

data_m607.o:
	$(CC) -c include/m607/data.cpp $(CC_OPTIONS) -o data_m607.o

getters_m607.o:
	$(CC) -c include/m607/getters.cpp $(CC_OPTIONS) -o getters_m607.o

helpers_m607.o:
	$(CC) -c include/m607/helpers.cpp $(CC_OPTIONS) -o helpers_m607.o

setters_m607.o:
	$(CC) -c include/m607/setters.cpp $(CC_OPTIONS) -o setters_m607.o

writers_m607.o:
	$(CC) -c include/m607/writers.cpp $(CC_OPTIONS) -o writers_m607.o

readers_m607.o:
	$(CC) -c include/m607/readers.cpp $(CC_OPTIONS) -o readers_m607.o

constructor_m686.o:
	$(CC) -c include/m686/constructor.cpp $(CC_OPTIONS) -o constructor_m686.o

data_m686.o:
	$(CC) -c include/m686/data.cpp $(CC_OPTIONS) -o data_m686.o

getters_m686.o:
	$(CC) -c include/m686/getters.cpp $(CC_OPTIONS) -o getters_m686.o

helpers_m686.o:
	$(CC) -c include/m686/helpers.cpp $(CC_OPTIONS) -o helpers_m686.o

setters_m686.o:
	$(CC) -c include/m686/setters.cpp $(CC_OPTIONS) -o setters_m686.o

writers_m686.o:
	$(CC) -c include/m686/writers.cpp $(CC_OPTIONS) -o writers_m686.o

readers_m686.o:
	$(CC) -c include/m686/readers.cpp $(CC_OPTIONS) -o readers_m686.o

constructor_m908.o:
	$(CC) -c include/m908/constructor.cpp $(CC_OPTIONS) -o constructor_m908.o

data_m908.o:
	$(CC) -c include/m908/data.cpp $(CC_OPTIONS) -o data_m908.o

getters_m908.o:
	$(CC) -c include/m908/getters.cpp $(CC_OPTIONS) -o getters_m908.o

helpers_m908.o:
	$(CC) -c include/m908/helpers.cpp $(CC_OPTIONS) -o helpers_m908.o

setters_m908.o:
	$(CC) -c include/m908/setters.cpp $(CC_OPTIONS) -o setters_m908.o

writers_m908.o:
	$(CC) -c include/m908/writers.cpp $(CC_OPTIONS) -o writers_m908.o

readers_m908.o:
	$(CC) -c include/m908/readers.cpp $(CC_OPTIONS) -o readers_m908.o

constructor_m709.o:
	$(CC) -c include/m709/constructor.cpp $(CC_OPTIONS) -o constructor_m709.o

data_m709.o:
	$(CC) -c include/m709/data.cpp $(CC_OPTIONS) -o data_m709.o

getters_m709.o:
	$(CC) -c include/m709/getters.cpp $(CC_OPTIONS) -o getters_m709.o

helpers_m709.o:
	$(CC) -c include/m709/helpers.cpp $(CC_OPTIONS) -o helpers_m709.o

setters_m709.o:
	$(CC) -c include/m709/setters.cpp $(CC_OPTIONS) -o setters_m709.o

writers_m709.o:
	$(CC) -c include/m709/writers.cpp $(CC_OPTIONS) -o writers_m709.o

readers_m709.o:
	$(CC) -c include/m709/readers.cpp $(CC_OPTIONS) -o readers_m709.o

constructor_m711.o:
	$(CC) -c include/m711/constructor.cpp $(CC_OPTIONS) -o constructor_m711.o

data_m711.o:
	$(CC) -c include/m711/data.cpp $(CC_OPTIONS) -o data_m711.o

getters_m711.o:
	$(CC) -c include/m711/getters.cpp $(CC_OPTIONS) -o getters_m711.o

helpers_m711.o:
	$(CC) -c include/m711/helpers.cpp $(CC_OPTIONS) -o helpers_m711.o

setters_m711.o:
	$(CC) -c include/m711/setters.cpp $(CC_OPTIONS) -o setters_m711.o

writers_m711.o:
	$(CC) -c include/m711/writers.cpp $(CC_OPTIONS) -o writers_m711.o

readers_m711.o:
	$(CC) -c include/m711/readers.cpp $(CC_OPTIONS) -o readers_m711.o

constructor_m715.o:
	$(CC) -c include/m715/constructor.cpp $(CC_OPTIONS) -o constructor_m715.o

data_m715.o:
	$(CC) -c include/m715/data.cpp $(CC_OPTIONS) -o data_m715.o

getters_m715.o:
	$(CC) -c include/m715/getters.cpp $(CC_OPTIONS) -o getters_m715.o

helpers_m715.o:
	$(CC) -c include/m715/helpers.cpp $(CC_OPTIONS) -o helpers_m715.o

setters_m715.o:
	$(CC) -c include/m715/setters.cpp $(CC_OPTIONS) -o setters_m715.o

writers_m715.o:
	$(CC) -c include/m715/writers.cpp $(CC_OPTIONS) -o writers_m715.o

readers_m715.o:
	$(CC) -c include/m715/readers.cpp $(CC_OPTIONS) -o readers_m715.o

constructor_m719.o:
	$(CC) -c include/m719/constructor.cpp $(CC_OPTIONS) -o constructor_m719.o

data_m719.o:
	$(CC) -c include/m719/data.cpp $(CC_OPTIONS) -o data_m719.o

getters_m719.o:
	$(CC) -c include/m719/getters.cpp $(CC_OPTIONS) -o getters_m719.o

helpers_m719.o:
	$(CC) -c include/m719/helpers.cpp $(CC_OPTIONS) -o helpers_m719.o

setters_m719.o:
	$(CC) -c include/m719/setters.cpp $(CC_OPTIONS) -o setters_m719.o

writers_m719.o:
	$(CC) -c include/m719/writers.cpp $(CC_OPTIONS) -o writers_m719.o

readers_m719.o:
	$(CC) -c include/m719/readers.cpp $(CC_OPTIONS) -o readers_m719.o

constructor_m721.o:
	$(CC) -c include/m721/constructor.cpp $(CC_OPTIONS) -o constructor_m721.o

data_m721.o:
	$(CC) -c include/m721/data.cpp $(CC_OPTIONS) -o data_m721.o

getters_m721.o:
	$(CC) -c include/m721/getters.cpp $(CC_OPTIONS) -o getters_m721.o

helpers_m721.o:
	$(CC) -c include/m721/helpers.cpp $(CC_OPTIONS) -o helpers_m721.o

setters_m721.o:
	$(CC) -c include/m721/setters.cpp $(CC_OPTIONS) -o setters_m721.o

writers_m721.o:
	$(CC) -c include/m721/writers.cpp $(CC_OPTIONS) -o writers_m721.o

readers_m721.o:
	$(CC) -c include/m721/readers.cpp $(CC_OPTIONS) -o readers_m721.o

constructor_generic.o:
	$(CC) -c include/generic/constructor.cpp $(CC_OPTIONS) -o constructor_generic.o

data_generic.o:
	$(CC) -c include/generic/data.cpp $(CC_OPTIONS) -o data_generic.o

getters_generic.o:
	$(CC) -c include/generic/getters.cpp $(CC_OPTIONS) -o getters_generic.o

helpers_generic.o:
	$(CC) -c include/generic/helpers.cpp $(CC_OPTIONS) -o helpers_generic.o

setters_generic.o:
	$(CC) -c include/generic/setters.cpp $(CC_OPTIONS) -o setters_generic.o

writers_generic.o:
	$(CC) -c include/generic/writers.cpp $(CC_OPTIONS) -o writers_generic.o

readers_generic.o:
	$(CC) -c include/generic/readers.cpp $(CC_OPTIONS) -o readers_generic.o

constructor_m913.o:
	$(CC) -c include/m913/constructor.cpp $(CC_OPTIONS) -o constructor_m913.o

data_m913.o:
	$(CC) -c include/m913/data.cpp $(CC_OPTIONS) -o data_m913.o

getters_m913.o:
	$(CC) -c include/m913/getters.cpp $(CC_OPTIONS) -o getters_m913.o

helpers_m913.o:
	$(CC) -c include/m913/helpers.cpp $(CC_OPTIONS) -o helpers_m913.o

setters_m913.o:
	$(CC) -c include/m913/setters.cpp $(CC_OPTIONS) -o setters_m913.o

writers_m913.o:
	$(CC) -c include/m913/writers.cpp $(CC_OPTIONS) -o writers_m913.o

readers_m913.o:
	$(CC) -c include/m913/readers.cpp $(CC_OPTIONS) -o readers_m913.o

constructor_m990.o:
	$(CC) -c include/m990/constructor.cpp $(CC_OPTIONS) -o constructor_m990.o

data_m990.o:
	$(CC) -c include/m990/data.cpp $(CC_OPTIONS) -o data_m990.o

getters_m990.o:
	$(CC) -c include/m990/getters.cpp $(CC_OPTIONS) -o getters_m990.o

helpers_m990.o:
	$(CC) -c include/m990/helpers.cpp $(CC_OPTIONS) -o helpers_m990.o

setters_m990.o:
	$(CC) -c include/m990/setters.cpp $(CC_OPTIONS) -o setters_m990.o

writers_m990.o:
	$(CC) -c include/m990/writers.cpp $(CC_OPTIONS) -o writers_m990.o

readers_m990.o:
	$(CC) -c include/m990/readers.cpp $(CC_OPTIONS) -o readers_m990.o

constructor_m990chroma.o:
	$(CC) -c include/m990chroma/constructor.cpp $(CC_OPTIONS) -o constructor_m990chroma.o

data_m990chroma.o:
	$(CC) -c include/m990chroma/data.cpp $(CC_OPTIONS) -o data_m990chroma.o

getters_m990chroma.o:
	$(CC) -c include/m990chroma/getters.cpp $(CC_OPTIONS) -o getters_m990chroma.o

helpers_m990chroma.o:
	$(CC) -c include/m990chroma/helpers.cpp $(CC_OPTIONS) -o helpers_m990chroma.o

setters_m990chroma.o:
	$(CC) -c include/m990chroma/setters.cpp $(CC_OPTIONS) -o setters_m990chroma.o

writers_m990chroma.o:
	$(CC) -c include/m990chroma/writers.cpp $(CC_OPTIONS) -o writers_m990chroma.o

readers_m990chroma.o:
	$(CC) -c include/m990chroma/readers.cpp $(CC_OPTIONS) -o readers_m990chroma.o
