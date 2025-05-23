CXX       := g++
CXX_FLAGS := -std=c++20 -ggdb

BIN     := 
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
	-mkdir $(FILES)
	-mkdir $(DOCS)

create-files: create-dirs
ifeq ("$(wildcard $(FILES)\$(CONFIG))","")
	-. > $(FILES)\$(CONFIG)
	echo username = >> $(FILES)\$(CONFIG)
	echo color = >> $(FILES)\$(CONFIG)
endif
ifeq ("$(wildcard $(FILES)\$(RECORDS))","")
	-. > $(FILES)\$(RECORDS)
endif

all: $(EXECUTABLE)

build: init clean all

build-run: init clean all
	.\$(EXECUTABLE)

run:
ifneq ("$(wildcard $(BIN)\$(EXECUTABLE))","")
	-.\$(EXECUTABLE)
else
	@echo "make build" first
endif

$(EXECUTABLE): $(SRC)/*.cpp
	$(CXX) $(CXX_FLAGS) -I $(INCLUDE) $^ -o $@ $(LIBRARIES) 

menu: $(SRC)/Labika.cpp $(SRC)/Menu.cpp
	$(CXX) $(CXX_FLAGS) -I $(INCLUDE) $^ -o $(EXECUTABLE) $(LIBRARIES)

clean:
	-del $(EXECUTABLE)
	cls
