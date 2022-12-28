COMPILER = clang++
FLAGS = -g -std=c++17 -Wall -pedantic -arch x86_64 -fmessage-length=0
INCLUDE = -I /usr/local/include
LIBRARIES = -l glfw -l GLEW
FRAMEWORKS = -framework OpenGL
SRC = *.cpp
OUTPUT = app

all:
	${COMPILER} ${FLAGS} ${INCLUDE} ${LIBRARIES} ${FRAMEWORKS} ${SRC} -o ${OUTPUT}
