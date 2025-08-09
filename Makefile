# Compile
all:
	g++ difference.cpp -o diff 

# Install system-wide
install: all
	sudo install diff /usr/local/bin/differentiate

# Remove from system
uninstall:
	sudo rm -f /usr/local/bin/differentiate
