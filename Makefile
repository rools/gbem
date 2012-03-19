ifeq ($(shell uname), Darwin)
	LIBS = -framework Cocoa -framework OpenGL -lglfw
else
	LIBS = `pkg-config --cflags --libs libglfw` -lGLU
endif

gbem: gbem.c gb_machine.c gb_cpu.c gb_mem.c gb_screen.c
	cc -o gbem gbem.c gb_machine.c gb_cpu.c gb_mem.c gb_screen.c $(LIBS)
	
clean:
	rm -f gbem
