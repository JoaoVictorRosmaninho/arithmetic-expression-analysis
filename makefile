# Name of the project
PROJ_NAME=Analyser
 
# .c files
C_SOURCE=$(wildcard /*.c)
 
# .h files
H_SOURCE=$(wildcard /*.h)
 
# Object files
OBJ=$(subst .c,.o,$(subst libMath,libMemory,Stack$(C_SOURCE)))
 
# Compiler and linker
CC=gcc
 
# Flags for compiler
CC_FLAGS=-c         \
         -W         \
         -Wall      \
         -Wextra      \
         -Werror
 
# Command used at clean target
RM = rm -rf
 
#
# Compilation and linking
#
all:$(PROJ_NAME)
 
$(PROJ_NAME): $(OBJ)
    @ echo 'Building binary using GCC linker: $@'
    $(CC) $^ -o $@
    @ echo 'Finished building binary: $@'
    @ echo ' '
 
./%.o: ./libMath/%.c ./libMath/%.h ./Stack/%.c ./Stack/%.h ./libMemory/%.c ./libMemory/%.h
    @ echo 'Building target using GCC compiler: $<'
    $(CC) $< $(CC_FLAGS) -o $@
    @ echo ' '

./main.o: ./Analyser.c $(H_SOURCE)
    @ echo 'Building target using GCC compiler: $<'
    $(CC) $< $(CC_FLAGS) -o $@
    @ echo ' '
 
clean:
    @ $(RM) ./*.o $(PROJ_NAME) *~
 
.PHONY: all clean