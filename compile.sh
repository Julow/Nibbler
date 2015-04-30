rm -f a.out
echo "Compiling OpenGL.so"

clang++ -std=c++14 -Wall -Werror -Wextra -O2 -fPIC -shared\
		OpenGL/Window.class.cpp \
		OpenGL/Window.draw.cpp \
		-I ~/.brew/include/ \
		-I . \
		-L ~/.brew/lib/ -lglfw3 -lGLEW -framework OpenGL\
		        -o OpenGL.so || exit

echo "Compiling a.out"

clang++ -std=c++14 -Wall -Werror -Wextra -O2\
		main.cpp\
		-I . || exit

./a.out
