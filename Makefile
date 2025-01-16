NAME        = ircserv

CXX         = c++
CXXFLAGS    = -Wall -Wextra -Werror -std=c++98 -g -I $(INCDIR)

SRCDIR      = src
INCDIR      = inc
OBJDIR      = obj

SRC         = main Channel Client Tokenisation Server Errors
SRC_CMDS    = join kick mode msg nick part pass ping quit topic user cap

SRCS        = $(addprefix $(SRCDIR)/, $(addsuffix .cpp, $(SRC)))
SRCS_CMDS   = $(addprefix $(SRCDIR)/commands/, $(addsuffix .cpp, $(SRC_CMDS)))
OBJS        = $(addprefix $(OBJDIR)/, $(SRC:=.o)) $(addprefix $(OBJDIR)/commands/, $(SRC_CMDS:=.o))

all: $(NAME) uc

$(NAME): $(OBJS)
	@$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)
	@echo "Compilation success !\n"

$(OBJDIR):
	@mkdir -p $(OBJDIR) $(OBJDIR)/commands

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	@echo "Compiling $<"
	@$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/commands/%.o: $(SRCDIR)/commands/%.cpp | $(OBJDIR)/commands
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
	@echo "./$(NAME) <port> <password>"

bearhate:
	compiledb make

debug: CXXFLAGS += -g
debug: re

.PHONY: all clean fclean re debug uc
