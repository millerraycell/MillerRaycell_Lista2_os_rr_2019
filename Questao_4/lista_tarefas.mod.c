#include <linux/build-salt.h>
#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0xacec71ed, "module_layout" },
	{ 0x57556533, "class_unregister" },
	{ 0x2525597, "device_destroy" },
	{ 0xab16269d, "class_destroy" },
	{ 0x1d779a88, "device_create" },
	{ 0x6bc3fbc0, "__unregister_chrdev" },
	{ 0xe64ee30b, "__class_create" },
	{ 0xb807186, "__register_chrdev" },
	{ 0xb44ad4b3, "_copy_to_user" },
	{ 0x88db9f48, "__check_object_size" },
	{ 0x68f31cbd, "__list_add_valid" },
	{ 0x91715312, "sprintf" },
	{ 0xe1537255, "__list_del_entry_valid" },
	{ 0xd6ee688f, "vmalloc" },
	{ 0x7c32d0f0, "printk" },
	{ 0xbdfb6dbb, "__fentry__" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "3617034758C76E2E4CE7936");
