# FILES

#OBJECTS += $(patsubst %, Basics/%, Json Ruller Log Writer Mathematics)
OBJECTS += $(patsubst %, %, gui audio background button value label labelIcon options menu submenu  history player  entity naval arrow marine ship layer fleet battle battleGUI region good settlement gameData gameGUI labelSett labelPlayer labelFleet labelDip node map game campaign Konio)

NAME     = Konio

EXTERNS  = SFML nlohmann


# DIRECTORIES

DIRECTORY_EXT   = extern
DIRECTORY_SRC   = src
DIRECTORY_INC   = -Iinclude $(patsubst %,-I$(DIRECTORY_EXT)/%/include, $(EXTERNS))
DIRECTORY_LIB   = $(patsubst %,-L$(DIRECTORY_EXT)/%/lib, $(EXTERNS))

DIRECTORY_OBJ   = obj
DIRECTORY_BUILD = build
DIRECTORY_LOGS  = logs

SYSTEM = Linux

include $(SYSTEM).make


# COMMANDS FOR TESTING

beginSection:
	@echo
	@echo "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<"
	@echo

endSection: 
	@echo
	@echo ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"
	@echo

viewFiles:
	@echo NAME: $(NAME)
	@echo OBJECTS: $(OBJECTS)
	@echo 

viewDirectories:
	@echo DIRECTORY_EXT: $(DIRECTORY_EXT)
	@echo DIRECTORY_SRC: $(DIRECTORY_SRC)
	@echo DIRECTORY_INC: $(DIRECTORY_INC)
	@echo 
	@echo DIRECTORY_OBJ: $(DIRECTORY_OBJ)
	@echo DIRECTORY_BUILD: $(DIRECTORY_BUILD)
	@echo DIRECTORY_LOGS: $(DIRECTORY_LOGS)
	@echo TARGET: $(TARGET)
	@echo 

viewCompiler:
	@echo COMPILER: $(COMPILER)
	@echo FLAGS: $(FLAGS)
	@echo LIBS: $(LIBS)
	@echo 

test: beginSection viewFiles viewDirectories viewCompiler endSection


# COMMANDS FOR CLEANING

clearForBuild: clearLogs clearTarget
clearForBuildAll: clearLogs clearTarget clearObjects


# COMMANDS FOR BUILDING

$(DIRECTORY_OBJ)/%$(EXTENSION_OBJ): $(DIRECTORY_SRC)/%.cpp
	$(COMPILER) $(FLAGS) $(DIRECTORY_INC) -c $^ -o $@

$(TARGET): $(OBJECTS)
	$(COMPILER) $(OBJECTS) $(LIBS) $(FLAGS) -o $@

build: beginSection clearForBuild $(TARGET) endSection
buildAll: beginSection clearForBuildAll $(TARGET) endSection


# COMMANDS FOR RUN

run: runCommand