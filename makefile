# paths for the installation
PREFIX = /usr
BIN_DIR = $(PREFIX)/bin
DOC_DIR = $(PREFIX)/share/doc
MAN_DIR = $(PREFIX)/share/man/man1

# compiler options
CC = g++
CC_OPTIONS := -Wall -Wextra -O2 `pkg-config --cflags libusb-1.0`
LIBS != pkg-config --libs libusb-1.0

# version string
VERSION_STRING = "\"2.0\""

# compile
build: constructor.o data.o getters.o helpers.o load_config.o setters.o writers.o readers.o mouse_m908.o
	$(CC) *.o -o mouse_m908 $(LIBS) $(CC_OPTIONS)

# copy all files to their correct location
install:
	cp ./mouse_m908 $(BIN_DIR)/mouse_m908 && \
	cp ./mouse_m908.rules /etc/udev/rules.d && \
	mkdir $(DOC_DIR)/mouse_m908 | true && \
	cp ./example.ini $(DOC_DIR)/mouse_m908/ && \
	cp ./example.macro $(DOC_DIR)/mouse_m908/ && \
	cp ./README.md $(DOC_DIR)/mouse_m908/ && \
	cp ./keymap.md $(DOC_DIR)/mouse_m908/ && \
	cp ./mouse_m908.1 $(MAN_DIR)/

install-bsd:
	cp ./mouse_m908 $(BIN_DIR)/mouse_m908 && \
	mkdir $(DOC_DIR)/mouse_m908 | true && \
	cp ./example.ini $(DOC_DIR)/mouse_m908/ && \
	cp ./example.macro $(DOC_DIR)/mouse_m908/ && \
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
	rm -f /etc/udev/rules.d/mouse_m908.rules && \
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
	cp example.ini Haiku/documentation/packages/mouse_m908
	cp example.macro Haiku/documentation/packages/mouse_m908
	cp README.md Haiku/documentation/packages/mouse_m908
	cp keymap.md Haiku/documentation/packages/mouse_m908
	cd Haiku; \
	package create -b mouse_m908.hpkg; \
	package add mouse_m908.hpkg bin documentation

# individual files
mouse_m908.o:
	$(CC) -c mouse_m908.cpp $(CC_OPTIONS) -D VERSION_STRING=$(VERSION_STRING)

constructor.o:
	$(CC) -c include/constructor.cpp $(CC_OPTIONS)

data.o:
	$(CC) -c include/data.cpp $(CC_OPTIONS)

getters.o:
	$(CC) -c include/getters.cpp $(CC_OPTIONS)

helpers.o:
	$(CC) -c include/helpers.cpp $(CC_OPTIONS)

load_config.o:
	$(CC) -c include/load_config.cpp $(CC_OPTIONS)

setters.o:
	$(CC) -c include/setters.cpp $(CC_OPTIONS)

writers.o:
	$(CC) -c include/writers.cpp $(CC_OPTIONS)

readers.o:
	$(CC) -c include/readers.cpp $(CC_OPTIONS)
