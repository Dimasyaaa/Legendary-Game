CXX       := g++
CXX_FLAGS := -std=c++17 -ggdb

BIN     := bin
SRC     := src
INCLUDE := include
DOCS    := docs

FILES   := gamedata
CONFIG  := config.ini
RECORDS := records.txt

LIBRARIES   :=
EXECUTABLE  := Labika.exe

init: create-dirs create-files

create-dirs:
	-mkdir $(BIN)
	-mkdir $(FILES)
	-mkdir $(DOCS)
	cls

create-files: create-dirs
ifeq ("$(wildcard $(FILES)\$(CONFIG))","")
	-. > $(FILES)\$(CONFIG)
	echo username = >> $(FILES)\$(CONFIG)
	echo color = >> $(FILES)\$(CONFIG)
endif
ifeq ("$(wildcard $(FILES)\$(RECORDS))","")
	-. > $(FILES)\$(RECORDS)
endif
	cls

all: $(BIN)\$(EXECUTABLE)

build: init clean all

build-run: init clean all
	.\$(BIN)\$(EXECUTABLE)

run:
ifneq ("$(wildcard $(BIN)\$(EXECUTABLE))","")
	cls
	-.\$(BIN)\$(EXECUTABLE)
else
	@echo "make build" first
endif

$(BIN)\$(EXECUTABLE): $(SRC)/*.cpp
	$(CXX) $(CXX_FLAGS) -I $(INCLUDE) $^ -o $@ $(LIBRARIES) 

menu: $(SRC)/Labika.cpp $(SRC)/Menu.cpp
	$(CXX) $(CXX_FLAGS) -I $(INCLUDE) $^ -o $@ $(LIBRARIES)

clean:
	-del $(BIN)\$(EXECUTABLE)
	cls
