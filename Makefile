# Detect OS
OS := $(shell uname)

# Zig binary
ZIG := zig

# Default target
all:
ifeq ($(OS), Windows_NT)
	@echo "Building for Windows (x86_64-windows-msvc)"
	$(ZIG) build -Dtarget=x86_64-windows-msvc
else ifeq ($(OS), Linux)
	@echo "Building for Linux"
	$(ZIG) build -Dtarget=x86_64-linux-gnu
else ifeq ($(OS), Darwin)
	@echo "Building for macOS"
	$(ZIG) build -Dtarget=x86_64-macos
else
	@echo "Unsupported OS: $(OS)"
endif