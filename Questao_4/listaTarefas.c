#include <linux/list.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/device.h> 
#include <linux/uaccess.h> 
#include <linux/string.h>
#include <linux/slab.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Miller Raycell");
MODULE_DESCRIPTION("Lista encadeada usando list.h");
MODULE_VERSION("0.1");

typedef struct k_list {
	struct list_head list;
	int identificador;
	char descricao[250];
}lista_tarefas;

lista_tarefas *tmp;
lista_tarefas lista;
struct list_head *ptr, *q;

static int __init list_init(void) {
	int i;	
	INIT_LIST_HEAD(&lista.list);

	printk(KERN_INFO "INICIANDO EXECUCAO LISTA ENCADEADA\n\n");

	for(i = 0; i <= 10; i++)
	{
		tmp = kmalloc (sizeof(lista_tarefas), GFP_ATOMIC);
		tmp->identificador = i;
		strcpy(tmp->descricao,"TESTE INSERCAO");
		list_add(&tmp->list, &lista.list);
	}

	list_for_each(ptr, &lista.list)
	{
		tmp = list_entry(ptr, lista_tarefas, list);
		printk(KERN_INFO "IDENTIFICADOR: %d\n",tmp->identificador);
		printk(KERN_INFO "DESCRICAO: %s\n\n",tmp->descricao);
	}

	list_for_each_safe(ptr, q, &lista.list){
		tmp = list_entry(ptr, lista_tarefas, list);
		printk(KERN_INFO "REMOVENDO ITEM:\n");
		printk(KERN_INFO "IDENTIFICADOR: %d\n",tmp->identificador);
		printk(KERN_INFO "DESCRICAO: %s\n\n",tmp->descricao);
		list_del(ptr);
	}
	kfree(tmp);
	return 0;

}

static void __exit list_exit(void) {

	printk(KERN_INFO "FINALIZANDO LISTA ENCADEADA\n");
}

module_init(list_init);
module_exit(list_exit);
