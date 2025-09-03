NAME        := serialize
CXX         := c++
CXXFLAGS    := -Wall -Wextra -Werror -std=c++98
RM          := rm -f

SRCS        := main.cpp Serializer.cpp
OBJS        := $(SRCS:.cpp=.o)

INCS        := Data.hpp Serializer.hpp

all: $(NAME)

$(NAME): $(OBJS) $(INCS)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS)

%.o: %.cpp $(INCS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re