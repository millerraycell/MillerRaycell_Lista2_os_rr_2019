#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/list.h>
#include<linux/slab.h>
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

static int __init list_init(void) {
	lista_tarefas lista;
	struct list_head *ptr;
	int i;
	
	INIT_LIST_HEAD(&lista.list);

	for(i = 0; i <= 10; i++)
	{
		lista_tarefas tmp;
		tmp.identificador = i;
		strcpy(tmp.descricao,"TESTE INSERCAO");

		list_add(&tmp.list, &lista.list);
		i++;
		//vfree(tmp);
	}
	
	list_for_each(ptr, &lista.list)
	{
		lista_tarefas * tmp2;
		tmp2 = list_entry(ptr, lista_tarefas, list);
		printk(KERN_INFO "IDENTIFICADOR: %d\n",tmp2->identificador);
		printk(KERN_INFO "DESCRICAO: %s\n\n",tmp2->descricao);
		vfree(tmp2);
	}
	
	return 0;

}

static void __exit list_exit(void) {
	printk(KERN_INFO "Saindo do bagulho\n");
}

module_init(list_init);
module_exit(list_exit);