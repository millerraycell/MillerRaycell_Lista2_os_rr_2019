#include <linux/list.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/device.h> 
#include <linux/uaccess.h> 

#define  DEVICE_NAME "lista_tarefas"
#define  CLASS_NAME  "lista_tarefas_mensagem"


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Miller Monteiro");
MODULE_DESCRIPTION("Module using linked lists, with list.h.");
MODULE_VERSION("0.1");

static int majorNumber;

typedef struct{
    int identificador;
    struct list_head list;
    char descricao[100];
}lista_tarefas;

struct list_head *head_list, *q;

static lista_tarefas *lista;
static int i = 1;

static struct class*  lista_tarefas_class  = NULL;
static struct device* lista_tarefas_device = NULL;

static ssize_t dev_write(struct file *filep, const char *buffer, size_t len, loff_t *offset);
static ssize_t dev_read(struct file *, char *, size_t, loff_t *);
static int dev_release(struct inode *inodep, struct file *filep);


static struct file_operations fops =
{
    .owner = THIS_MODULE,
    .read = dev_read,
    .write = dev_write,
    .release = dev_release,
};

static int __init lista_tarefas_init(void){
    printk(KERN_INFO "Inicializando Lista de Tarefas LKM\n");
    
    majorNumber = register_chrdev(0, DEVICE_NAME, &fops);
    if (majorNumber<0){
        printk(KERN_ALERT "Não conseguiu criar Lista de Tarefas com major number\n");
        return majorNumber;
    }
    printk(KERN_INFO "Lista de tarefas registrada como driver com major number %d\n", majorNumber);
    
    lista_tarefas_class = class_create(THIS_MODULE, CLASS_NAME);
    
    if (IS_ERR(lista_tarefas_class)){           
        unregister_chrdev(majorNumber, DEVICE_NAME);
        printk(KERN_ALERT "Falha ao registrar classe\n");
        return PTR_ERR(lista_tarefas_class);
    }
    printk(KERN_INFO "Classe criada corretamente\n");
    
    lista_tarefas_device = device_create(lista_tarefas_class, NULL, MKDEV(majorNumber, 0), NULL, DEVICE_NAME);
    
    if (IS_ERR(lista_tarefas_device)){
        class_destroy(lista_tarefas_class);
        unregister_chrdev(majorNumber, DEVICE_NAME);
        printk(KERN_ALERT "Falha ao criar o dispositivo\n");
        return PTR_ERR(lista_tarefas_device);
    }
    printk(KERN_INFO "Classe do dispositivo criada corretamente\n");
    INIT_LIST_HEAD(&lista->list);

    return 0;
}

static void __exit lista_tarefas_exit(void){
   device_destroy(lista_tarefas_class, MKDEV(majorNumber, 0));
   class_unregister(lista_tarefas_class);
   class_destroy(lista_tarefas_class);
   unregister_chrdev(majorNumber, DEVICE_NAME);
   printk(KERN_INFO "Lista de Tarefas dando tchau ao kernel\n");
}

static ssize_t dev_write(struct file *filep, const char *buffer, size_t len, loff_t *offset){
    lista_tarefas *tmp = (lista_tarefas*)vmalloc(sizeof(lista_tarefas));
    printk(KERN_INFO "ENTROU NA FUNCAO\n");
    tmp->identificador = i;
    sprintf(tmp->descricao, "%s", buffer, len);
    printk(KERN_INFO "LEU DO ARQUIVO");
    list_add_tail(&(tmp->list),&(lista->list));
    printk(KERN_INFO "INSERIU FINAL DA LISTA");
    i++;
  
    return len;
}

static int dev_release(struct inode *inodep, struct file *filep){
	printk(KERN_INFO "ENCERRANDO TODAS AS TAREFAS DA LISTA\n");
	lista_tarefas *tmp = (lista_tarefas *) vmalloc(sizeof(lista_tarefas));
    list_for_each(head_list, &lista->list)
    {
        tmp = list_entry(head_list, lista_tarefas, list);
        list_del(head_list);
        //free(tmp);
    }
    printk(KERN_INFO "Modulo lista de tarefas encerrado com sucesso!\n");
    return 0;
}

static ssize_t dev_read(struct file *filep, char *buffer, size_t len, loff_t *offset){
   int error_count = 0;
   lista_tarefas *tmp = (lista_tarefas *) vmalloc(sizeof(lista_tarefas));
   
   error_count = copy_to_user(buffer, lista->descricao, len);
   
 
   if (error_count==0){ 
	   list_for_each(head_list, &lista->list)
	   {
		   tmp = list_entry(head_list, lista_tarefas, list);
		   printk(KERN_INFO "Numero tarefa %d\n", lista->identificador);
		   printk(KERN_INFO "Descricao: %s\n\n",lista->descricao);
		}
   }
   else {
      printk(KERN_INFO "Falha ao enviar\n");
      return -EFAULT;              // Failed -- return a bad address message (i.e. -14)
   }
}

module_init(lista_tarefas_init);
module_exit(lista_tarefas_exit);
