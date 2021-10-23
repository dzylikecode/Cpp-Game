g_workspace =F:/Git_WorkSpace/LaCpp/SDL_Game
g_SDL_IncludePath =F:/user/La_Library/MinGW/SDL2-devel-2.0.16-mingw.tar/SDL2-devel-2.0.16-mingw/SDL2-2.0.16/x86_64-w64-mingw32/include/SDL2
g_SDL_LibPath =F:/user/La_Library/MinGW/SDL2-devel-2.0.16-mingw.tar/SDL2-devel-2.0.16-mingw/SDL2-2.0.16/x86_64-w64-mingw32/lib
#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
# -Wl,-subsystem,windows gets rid of the console window
s_OutputWindow ?=#-w -Wl,-subsystem,windows
g_CompilerOptions =$(s_OutputWindow) -fdiagnostics-color=always -g 
g_LinkOptions =-lmingw32 -lSDL2main -lSDL2