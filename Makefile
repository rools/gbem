ifeq ($(shell uname), Darwin)
	LIBS = -framework Cocoa -framework OpenGL -lglfw
else
	LIBS = `pkg-config --cflags --libs libglfw` -lGLU
endif

gbem: src/*.c
	cc -Isrc -o gbem src/*.c $(LIBS)
	
clean:
	rm -f gbem
