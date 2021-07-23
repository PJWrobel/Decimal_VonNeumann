PROJECT_NAME ?= von_build
VERSION ?= 0.1
CC ?= gcc
BUILD ?= alpha #debug
FLAGS += -Wall -Werror -O2
LINKS ?= card.c
SOURCE ?= comp.c

ifeq ($(BUILD), debug)
	flags += -g
endif

$(PROJECT_NAME): $(SOURCE)
	$(CC) -o $(PROJECT_NAME) $(SOURCE) $(FLAGS) $(LINKS)
