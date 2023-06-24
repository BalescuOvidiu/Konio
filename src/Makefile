NAME = Konio
OBJECTS = gui.o audio.o background.o button.o value.o label.o labelIcon.o options.o menu.o submenu.o  history.o player.o  entity.o naval.o arrow.o marine.o ship.o layer.o fleet.o battle.o battleGUI.o region.o good.o settlement.o gameData.o gameGUI.o labelSett.o labelPlayer.o labelFleet.o labelDip.o node.o map.o game.o campaign.o Konio.o


# DIRECTORIES

DIRECTORY_SRC = src
DIRECTORY_INC = include
DIRECTORY_LIB = -Llib

DIRECTORY_BIN_LINUX = bin/linux
DIRECTORY_BIN_MAC = bin/mac
DIRECTORY_BIN_WINDOWS = bin/windows

LOGS_LINUX = $(DIRECTORY_BIN_LINUX)/logs
LOGS_MAC = $(DIRECTORY_BIN_MAC)/logs
LOGS_WINDOW = $(DIRECTORY_BIN_WINDOW)/logs


# COMPILER FLAGS

CPP = g++
CPP_MAC = g++
MINGW = i686-w64-mingw32-g++

FLAGS_LINUX =  -Wall -std=gnu++0x
FLAGS_MAC =  -Wall -std=gnu++0x
FLAGS_WINDOWS = -std=c++11 -static -mwindows -DSFML_SHARED

LIBS_LINUX = $(DIRECTORY_LIB) -lpthread -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system
LIBS_MAC = $(DIRECTORY_LIB) -lpthread -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system
LIBS_WINDOWS = $(DIRECTORY_LIB) -L/usr/i686-w64-mingw32/lib -lsfml-audio-s -lsfml-graphics-s -lsfml-window-s -lsfml-system-s


# EXECUTABLES FILES

TARGET_LINUX = $(DIRECTORY_BIN_LINUX)/$(NAME)
TARGET_MAC = $(DIRECTORY_BIN_LINUX)/$(NAME)
TARGET_WINDOWS = $(DIRECTORY_BIN_WINDOWS)/$(NAME).exe

DEPS_LINUX = $(patsubst %, $(DIRECTORY_BIN_LINUX)/%, $(OBJECTS))
DEPS_MAC = $(patsubst %, $(DIRECTORY_BIN_LINUX)/%, $(OBJECTS))
DEPS_WINDOWS = $(patsubst %, $(DIRECTORY_BIN_WINDOWS)/%, $(OBJECTS))


# CLEAR LOGS

clearConsole:
	-clear;

clearLogsForLinux: clearConsole
	-rm -r $(LOGS_LINUX); mkdir $(LOGS_LINUX);

clearLogsForMac: clearConsole
	-rm -r $(LOGS_MAC); mkdir $(LOGS_MAC);

clearLogsForWindow: clearConsole
	-rm -r $(LOGS_WINDOW); mkdir $(LOGS_WINDOW);


# CLEAR OBJECT FILES

clearObjectsForLinux:
	-rm -f $(DEPS_LINUX)

clearObjectsForMac:
	-rm -f $(DEPS_MAC)

clearObjectsForWindows:
	-rm -f $(DEPS_WINDOWS)


# CLEAR BINARY FILES

clearTargetForLinux: clearConsole
	-rm -f $(TARGET_LINUX)

clearTargetForMac: clearConsole
	-rm -f $(TARGET_MAC)

clearTargetForWindows: clearConsole
	-rm -f $(TARGET_WINDOWS)

runForLinux: clearConsole
	sh ./RunForLinux.sh


# BUILD FOR LINUX

$(DIRECTORY_BIN_LINUX)/%.o: $(DIRECTORY_SRC)/%.cpp
	$(CPP) $(FLAGS_LINUX) -I$(DIRECTORY_INC) -c $^ -o $@

$(TARGET_LINUX): $(DEPS_LINUX)
	$(CPP) $(DEPS_LINUX) $(LIBS_LINUX) $(FLAGS_LINUX) -o $@

buildForLinux: clearTargetForLinux $(TARGET_LINUX)


# BUILD FOR MAC

$(DIRECTORY_BIN_MAC)/%.o: $(DIRECTORY_SRC)/%.cpp
	$(CPP_MAC) $(FLAGS_MAC) -I$(DIRECTORY_INC) -c $^ -o $@

$(TARGET_MAC): $(DEPS_MAC)
	$(CPP_MAC) $(DEPS_MAC) $(LIBS_MAC) $(FLAGS_MAC) -o $@

buildForMac: clearTargetForMac $(TARGET_MAC)


#BUILD FOR WINDOWS

$(DIRECTORY_BIN_WINDOWS)/%.o: $(DIRECTORY_SRC)/%.cpp
	$(MINGW) $(FLAGS_WINDOWS) -I$(DIRECTORY_INC) -c $^ -o $@

$(TARGET_WINDOWS): $(DEPS_WINDOWS)
	$(MINGW) $(DEPS_WINDOWS) $(LIBS_WINDOWS) $(FLAGS_WINDOWS) -o $@

buildForWindows: clearTargetForWindows $(TARGET_WINDOWS)