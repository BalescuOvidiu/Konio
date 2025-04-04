# SYSTEM

SYSTEM_NAME   = Windows
EXTENSION_OBJ = .obj


# DIRECTORIES AND FILES

DIRECTORY_OBJ   := $(DIRECTORY_OBJ)/$(SYSTEM_NAME)
DIRECTORY_BUILD := $(DIRECTORY_BUILD)/$(NAME)
DIRECTORY_LOGS  := $(DIRECTORY_BUILD)/$(DIRECTORY_LOGS)
TARGET           = $(DIRECTORY_BUILD)/$(NAME)


# COMPILER FLAGS

OBJECTS := $(patsubst %, $(DIRECTORY_OBJ)/%$(EXTENSION_OBJ), $(OBJECTS))
COMPILER = i686-w64-mingw32-g++
FLAGS    = -std=c++11 -static -mwindows -DSFML_SHARED
LIBS     = $(DIRECTORY_LIB) -L/usr/i686-w64-mingw32/lib -lsfml-audio-s -lsfml-graphics-s -lsfml-window-s -lsfml-system-s


# CLEAR COMMANDS

clearLogs:
	-rm -r $(DIRECTORY_LOGS); mkdir $(DIRECTORY_LOGS)

clearTarget:
	-rm -f $(TARGET)

clearObjects:
	-rm -f $(OBJECTS)


# COMMANDS FOR RUN

runCommand:
	cd $(DIRECTORY_BUILD); $(NAME).exe; cd ../..