CUR_DIR = $(shell pwd)

src = $(wildcard ../src/*.cpp)
obj = $(patsubst %.cpp, %.o, $(src))
target = process
XX = g++


$(target):$(obj)
	$(XX) $(obj) -o $(target) -std=c++11

%.o:%.cpp
	$(XX) -c $< -o $@ -std=c++11

.PHONY:clean
.PHONY:mymv
clean:
	rm $(obj) && rm $(CUR_DIR)/$(target)
mymv:
	mv $(obj) $(CUR_DIR)