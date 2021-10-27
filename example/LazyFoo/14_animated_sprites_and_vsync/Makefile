include ../../../Makefile
include ../Makefile

#CC specifies which compiler we're using
CC = g++

BuildPath =$(g_g_BuildPath)

#INCLUDE_PATHS specifies the additional include paths we'll need
IncludeOptions = -I$(g_SDL_IncludePath) \
				 -I$(g_STB_IncludePath) \
				 -I$(g_LIB_IncludePath)

#LIBRARY_PATHS specifies the additional library paths we'll need
LibOptions = -L$(g_SDL_LibPath)

CompilerOptions = $(g_CompilerOptions)

#LINKER_FLAGS specifies the libraries we're linking against
LinkOptions = $(g_LinkOptions)

#OBJS specifies which files to compile as part of the project
OBJS = 14_animated_sprites_and_vsync.cpp

GetFileName = $(basename $(OBJS))
#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = $(BuildPath)/$(GetFileName)

#This is the target that compiles our executable
all : $(OBJS)
	$(CC) $(OBJS) 				\
	$(CompilerOptions)			\
	$(IncludeOptions) 			\
	$(LibOptions) 				\
	$(LinkOptions) 				\
	-o $(OBJ_NAME)