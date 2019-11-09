BIN_DIR = /usr/bin

install:
	g++ mouse_m908.cpp -o mouse_m908 -lusb-1.0 && \
	cp ./rgb_keyboard $(BIN_DIR)/mouse_m908 && \
	cp ./mouse_m908.rules /etc/udev/rules.d
	
