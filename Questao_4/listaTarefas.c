#include <linux/list.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/device.h> 
#include <linux/uaccess.h> 
#include <linux/string.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Miller Raycell");
MODULE_DESCRIPTION("Lista encadeada usando list.h");
MODULE_VERSION("0.1");

typedef struct k_list {
	struct list_head list;
	int identificador;
	char descricao[250];
}lista_tarefas;

static lista_tarefas *tmp = kmalloc (sizeof(lista_tarefas), GFP_KERNEL);
static lista_tarefas lista;
static struct list_head *ptr;

static int __init list_init(void) {
	int i;
	printk(KERN_INFO "TESTE DO FUNCIONAMENTO");

	printk(KERN_INFO "Starting ...\n");
	
	INIT_LIST_HEAD(&lista.list);

	printk(KERN_INFO "Starting list...\n");

	
	for(i = 0; i <= 10; i++)
	{
		printk(KERN_INFO "INICIANDO LACO");
		tmp->identificador = i;
		strcpy(tmp->descricao,"TESTE INSERCAO");
		list_add(&tmp->list, &lista.list);
		printk(KERN_INFO "adding to list...\n");
	}
	/*
	
	list_for_each(ptr, &lista.list)
	{
		lista_tarefas * tmp2;
		tmp2 = list_entry(ptr, lista_tarefas, list);
		printk(KERN_INFO "IDENTIFICADOR: %d\n",tmp2->identificador);
		printk(KERN_INFO "DESCRICAO: %s\n\n",tmp2->descricao);
	}
	*/
	
	return 0;

}

static void __exit list_exit(void) {
	printk(KERN_INFO "Saindo do bagulho\n");
}

module_init(list_init);
module_exit(list_exit);
