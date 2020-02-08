BIN_DIR = /usr/bin

install:
	g++ mouse_m908.cpp -o mouse_m908 -lusb-1.0 -Wall -O2 && \
	cp ./mouse_m908 $(BIN_DIR)/mouse_m908 && \
	cp ./mouse_m908.rules /etc/udev/rules.d

clean:
	rm ./mouse_m908

uninstall:
	rm  /etc/udev/rules.d/mouse_m908.rules && \
	rm $(BIN_DIR)/mouse_m908

upgrade:
	g++ mouse_m908.cpp -o mouse_m908 -lusb-1.0 -Wall -O2 && \
	cp ./mouse_m908 $(BIN_DIR)/mouse_m908 

build:
	g++ mouse_m908.cpp -o mouse_m908 -lusb-1.0 -Wall -O2
