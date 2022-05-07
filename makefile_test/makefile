target=main
src=$(wildcard *.c)
obj=$(patsubst %.c,%.o,$(src))

$(target):$(obj)
	gcc $^ -o $@

%.o:%.c
	gcc $< -c

clean:
	rm $(target) $(obj) -rf
