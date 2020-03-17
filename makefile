PREFIX = /usr
BIN_DIR = $(PREFIX)/bin
DOC_DIR = $(PREFIX)/share/doc
MAN_DIR = $(PREFIX)/share/man/man1

build:
	g++ mouse_m908.cpp -o mouse_m908 -lusb-1.0 -Wall -O2

install:
	g++ mouse_m908.cpp -o mouse_m908 -lusb-1.0 -Wall -O2 && \
	cp ./mouse_m908 $(BIN_DIR)/mouse_m908 && \
	cp ./mouse_m908.rules /etc/udev/rules.d && \
	mkdir $(DOC_DIR)/mouse_m908 | true && \
	cp ./example.ini $(DOC_DIR)/mouse_m908/ && \
	cp ./example.macro $(DOC_DIR)/mouse_m908/ && \
	cp ./README.md $(DOC_DIR)/mouse_m908/ && \
	cp ./mouse_m908.1 $(MAN_DIR)/

clean:
	rm ./mouse_m908

uninstall:
	rm -f $(BIN_DIR)/mouse_m908 && \
	rm -f /etc/udev/rules.d/mouse_m908.rules && \
	rm -rf $(DOC_DIR)/mouse_m908 && \
	rm -f $(MAN_DIR)/mouse_m908.1

upgrade: install

