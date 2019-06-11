obj-m+=lista_tarefas.o

all:
	make -C /lib/modules/$(shell uname -r)/build/ M=$(PWD) modules
	$(CC) teste.c -o teste
clean:
	make -C /lib/modules/$(shell uname -r)/build/ M=$(PWD) clean
	rm teste