# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gkehren <gkehren@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/17 16:50:58 by gkehren           #+#    #+#              #
#    Updated: 2022/08/17 02:45:29 by gkehren          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FILES:=	pipex pipex_utils tools split
FILES_BONUS:= bonus_pipex bonus_pipex_utils bonus_tools bonus_split bonus_other

NAME:= pipex
BONUS:= pipex_bonus

# ------------------
CC:=gcc
SRCPATH:=srcs/
BONUSPATH:=bonus_srcs/
HDRPATH:=include/
CCHPATH:=obj/
CCHPATH_BONUS:=obj/
IFLAGS:=-I ${HDRPATH}
CFLAGS:=-Wall -Wextra -Werror -g3 ${IFLAGS}
# ==================

# ----- Colors -----
BLACK:="\033[1;30m"
RED:="\033[1;31m"
GREEN:="\033[1;32m"
CYAN:="\033[1;35m"
PURPLE:="\033[1;36m"
WHITE:="\033[1;37m"
EOC:="\033[0;0m"
# ==================

# ------ Auto ------
SRC:=$(addprefix $(SRCPATH),$(addsuffix .c,$(FILES)))
SRC_BONUS:=$(addprefix $(BONUSPATH),$(addsuffix .c,$(FILES_BONUS)))
OBJ:=$(addprefix $(CCHPATH),$(addsuffix .o,$(FILES)))
OBJ_BONUS:=$(addprefix $(CCHPATH_BONUS),$(addsuffix .o,$(FILES_BONUS)))
# ==================
CCHF:=.cache_exists

all: ${NAME}

${NAME}: ${OBJ}
	@echo ${CYAN} " - Compiling $@" $(RED)
	@${CC} ${CFLAGS} ${SRC} -o ${NAME}
	@echo $(GREEN) " - OK" $(EOC)

${CCHPATH}%.o: ${SRCPATH}%.c | ${CCHF}
	@echo ${PURPLE} " - Compiling $< into $@" ${EOC}
	@${CC} ${CFLAGS} -c $< -o $@

bonus:	${BONUS}

${BONUS}: ${OBJ_BONUS}
	@echo ${CYAN} " - Compiling $@" $(RED)
	@${CC} ${CFLAGS} ${SRC_BONUS} -o ${BONUS}
	@echo $(GREEN) " - OK" $(EOC)

${CCHPATH_BONUS}%.o: ${BONUSPATH}%.c | ${CCHF}
	@echo ${PURPLE} " - Compiling $< into $@" ${EOC}
	@${CC} ${CFLAGS} -c $< -o $@

%.c:
	@echo ${RED}"Missing file : $@" ${EOC}

$(CCHF):
	@mkdir $(CCHPATH)
	@touch $(CCHF)

clean:
	@rm -rf ${CCHPATH}
	@rm -f ${CCHF}

fclean:	clean
	@rm -f ${NAME}
	@rm -f ${BONUS}
	@rm -rf ${NAME}.dSYM/
	@rm -rf ${BONUS}.dSYM/

re:	fclean
	@${MAKE} all

.PHONY:	all clean fclean re bonus
