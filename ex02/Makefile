NAME := identify
CXX  := c++
CXXFLAGS := -Wall -Wextra -Werror -std=c++98

SRCS := main.cpp Base.cpp Utils.cpp
OBJS := $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS) A.hpp B.hpp C.hpp Base.hpp Utils.hpp
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
