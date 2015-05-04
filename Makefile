# LOL

NAME := nibbler
C_DIR := srcs
H_DIRS := include
O_DIR := o
LIBS := lib/OpenGL
CC := clang++
FLAGS := -std=c++14 -Wall -Wextra -Werror -g
LINKS := -Llib/OpenGL 
HEADS := -I include

all: $(NAME)

o/Event.cpp.o: srcs/Event.cpp include/nibbler.h include/Event.hpp include/Game.hpp
	@$(COMPILE)
o/Game.cpp.o: srcs/Game.cpp include/nibbler.h include/Game.hpp include/Event.hpp include/IUI.hpp
	@$(COMPILE)
o/GrowBonus.cpp.o: srcs/GrowBonus.cpp include/GrowBonus.hpp
	@$(COMPILE)
o/main.cpp.o: srcs/main.cpp include/nibbler.h include/IUI.hpp include/Game.hpp
	@$(COMPILE)
o/Snake.cpp.o: srcs/Snake.cpp include/Snake.hpp
	@$(COMPILE)
lib/OpenGL:
	@make -C lib/OpenGL


MSG_0 := printf '\033[0;32m%-18.18s\033[0;0m\r'
MSG_1 := printf '\033[0;31m%-18.18s\033[0;0m\n'

COMPILE = $(MSG_0) $< ; $(CC) $(FLAGS) $(HEADS) -c -o $@ $< || $(MSG_1) $<

O_FILES := o/Event.cpp.o \
		o/Game.cpp.o \
		o/GrowBonus.cpp.o \
		o/main.cpp.o \
		o/Snake.cpp.o

$(NAME): o/ $(LIBS) $(O_FILES)
	@$(MSG_0) $@ ; $(CC) $(FLAGS) -o $@ $(O_FILES) $(LINKS) && echo || $(MSG_1) $@

o/:
	@mkdir -p $@ 2> /dev/null || true

o/%:
	@mkdir -p $@ 2> /dev/null || true

clean:
	@rm -f $(O_FILES) 2> /dev/null || true
	@rmdir -p o 2> /dev/null || true

fclean: clean
	@rm -f nibbler 2> /dev/null || true

re: fclean all

make:
	@bash './makemake.sh' re

.PHONY: all clean fclean re make lib/OpenGL
