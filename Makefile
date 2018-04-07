.PHONY: all install uninstall clean

CPPC = g++
CFLAGS = -c -Wall
TARGET = statemachine
SRC = $(TARGET).cpp
OBJ = $(SRC:.cpp=.o)
INSTALL_PATH = ~/bin

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CPPC) -o $(TARGET) $(OBJ)
	
$(OBJ): $(SRC)
	$(CPPC) $(CFLAGS) $(SRC)
	
install: $(TARGET)
	install -D -m 744 $(TARGET) $(INSTALL_PATH)/$(TARGET)
	make clean
	
uninstall: $(TARGET)
	rm -rf $(INSTALL_PATH)/$(TARGET)
	
clean:
	rm -rf $(TARGET) *.o 
