# SYSTEM

SYSTEM_NAME   = Linux
EXTENSION_OBJ = .o


# DIRECTORIES AND FILES

DIRECTORY_OBJ   := $(DIRECTORY_OBJ)/$(SYSTEM_NAME)
DIRECTORY_BUILD := $(DIRECTORY_BUILD)/$(NAME)
DIRECTORY_LOGS  := $(DIRECTORY_BUILD)/$(DIRECTORY_LOGS)
TARGET           = $(DIRECTORY_BUILD)/$(NAME)


# COMPILER FLAGS

OBJECTS := $(patsubst %, $(DIRECTORY_OBJ)/%$(EXTENSION_OBJ), $(OBJECTS))
COMPILER = g++
FLAGS    = -Wall -std=gnu++0x
LIBS     = $(DIRECTORY_LIB) -lpthread -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system


# CLEAR COMMANDS

clearLogs:
	-rm -r $(DIRECTORY_LOGS); mkdir $(DIRECTORY_LOGS)

clearTarget:
	-rm -f $(TARGET)

clearObjects:
	-rm -f $(OBJECTS)


# COMMANDS FOR RUN

runCommand:
	cd $(DIRECTORY_BUILD); sh $(NAME).sh; cd ../..