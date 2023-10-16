# http://t.zoukankan.com/weichao975-p-8276448.html
# 修改已有的Makefile，使输出路径为codeblocks默认路径，否则会一直提示你没有build

# 进入下级目录编译，make文件默认应该使用 cd c0misc; $(MAKE) 书写格式，
# 但cmd分隔符是 &，而不是“;” 应该使用：cd c0misc & $(MAKE);
# 为了可移植性，使用make -C参数。-C表示进入目录。

test_one:default
	gcc main.c -o bin\Debug\coasep
	$(MAKE) -C c3CPU

default:
	gcc main.c -o bin\Debug\coasep

all: main.c
	gcc main.c -o bin\Debug\coasep
	gcc main.c -o coasep
	$(MAKE) -C c0misc
	$(MAKE) -C c2data


#cmd中没有rm,使用del替换
clean:
	del -f *.exe
	$(MAKE) -C c0misc clean


