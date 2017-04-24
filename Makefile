CXX=c++
NAME=Hex
OBJECTS=MacApp.o Application.o AbstractResource.o AbstractScene.o GameObject.o AssetManager.o HexGameScene.o Shader.o GLProgram.o Mesh.o testCube.o Camera.o GameCam.o Hex.o Texture.o
LFLAGS= -framework cocoa -framework Appkit -framework GLKit  -framework OpenGl 
CFLAGS= -Wall -g -O3 -std=c++11 


%.o : %.mm
	$(CXX) $(CFLAGS)  -c -o $@ $^

%.o : %.cpp
	$(CXX) $(CFLAGS) -c -o $@ $^

all: $(OBJECTS)
	$(CXX) $(OBJECTS) -g $(LFLAGS) -o $(NAME)

clean:
	-rm $(OBJECTS) $(NAME)
