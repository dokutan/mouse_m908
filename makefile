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
VERSION_STRING = "\"3.1\""

# compile
build: m908 m709 m711 m715 m990 m990chroma generic data_rd.o rd_mouse.o load_config.o mouse_m908.o
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
	rm mouse_m908 *.o
	rm -r Haiku/bin Haiku/documentation Haiku/mouse_m908.hpkg | true

# remove all installed files
uninstall:
	rm -f $(BIN_DIR)/mouse_m908 && \
	rm -f $(ETC_DIR)/udev/rules.d/mouse_m908.rules && \
	rm -rf $(DOC_DIR)/mouse_m908 && \
	rm -f $(MAN_DIR)/mouse_m908.1

# this is an alias to install for backwards compatibility
upgrade: install

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
m908: constructor_m908.o data_m908.o getters_m908.o helpers_m908.o setters_m908.o writers_m908.o readers_m908.o

m709: constructor_m709.o data_m709.o getters_m709.o helpers_m709.o setters_m709.o writers_m709.o readers_m709.o

m711: constructor_m711.o data_m711.o getters_m711.o helpers_m711.o setters_m711.o writers_m711.o readers_m711.o

m715: constructor_m715.o data_m715.o getters_m715.o helpers_m715.o setters_m715.o writers_m715.o readers_m715.o

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
