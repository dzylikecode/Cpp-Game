include ../../../Makefile
include ../Makefile

#CC specifies which compiler we're using
CC = g++

BuildPath =$(g_g_BuildPath)

#INCLUDE_PATHS specifies the additional include paths we'll need
IncludeOptions = -I$(g_SDL_IncludePath)

#LIBRARY_PATHS specifies the additional library paths we'll need
LibOptions = -L$(g_SDL_LibPath)

CompilerOptions = $(g_CompilerOptions)

#LINKER_FLAGS specifies the libraries we're linking against
LinkOptions = $(g_LinkOptions)

#OBJS specifies which files to compile as part of the project
OBJS = 03_event_driven_programming.cpp

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = $(BuildPath)/03_event_driven_programming

#This is the target that compiles our executable
all : $(OBJS)
	$(CC) $(OBJS) 				\
	$(CompilerOptions)			\
	$(IncludeOptions) 			\
	$(LibOptions) 				\
	$(LinkOptions) 				\
	-o $(OBJ_NAME)