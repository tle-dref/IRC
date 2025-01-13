NAME		= ircserv

CXX			= c++
CXXFLAGS	= -Wall -Wextra -Werror -std=c++98 -I $(INCDIR)

SRCDIR		= src
INCDIR		= inc
OBJDIR		= obj

SRC			= main Channel Client Command Tokenisation
SRCS		= $(addprefix $(SRCDIR)/, $(addsuffix .cpp, $(SRC)))
OBJS		= $(addprefix $(OBJDIR)/, $(SRC:=.o))

all: $(NAME) uc

$(NAME): $(OBJS)
	@$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)
	@echo "Compilation success !\n"

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	@echo "Compiling $<"
	@$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJDIR)
	@echo "Remove objects."

fclean: clean
	@rm -f $(NAME)
	@echo "Full clear."

re: fclean all

uc:
	@echo "===== Use case ====="
	@echo "./$(NAME)"

debug: CXXFLAGS += -g
debug: re

.PHONY: all clean fclean re debug uc
