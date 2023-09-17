# for release mode
g++ -Wall -Wextra -std=c++17  -O2 dsa.cc main.cc -o dsa-sort
# for debug mode
# g++ -Wall -Wextra -std=c++17 -g -fsanitize=undefined -fsanitize=address    dsa.cc main.cc -o dsa-sort
