#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/xarray.h>
#include <linux/slab.h>


DEFINE_XARRAY(xarray_test);

struct my_data {
	int id;
	char name[20];
};

static void insert_data(int id, const char *name)
{
	struct my_data *data = kmalloc(sizeof(*data), GFP_KERNEL);
	data->id = id;
	strncpy(data->name, name, sizeof(data->name));
	xa_store(&xarray_test, id, data, GFP_KERNEL);
}

static void remove_data(int id)
{
	struct my_data *data = xa_erase(&xarray_test, id);
	if (data)
		kfree(data);
}

static struct my_data *get_data(int id)
{
	return xa_load(&xarray_test, id);
}

static int __init xarray_test_init(void)
{
	unsigned long index;
	struct my_data *data = get_data(2);

	printk("xarray example: init xarray example module\n");

	insert_data(1, "John");
	insert_data(2, "Alice");
	insert_data(3, "Bon");
	insert_data(4, "Steve");

	if (data)
		printk("xarray example: ID: %d, Name: %s\n",
				data->id, data->name);

	printk("xarray example: before remove data 3\n");
	xa_for_each(&xarray_test, index, data) {
		printk("index %ld, data %p: id %d, name %s\n",
				index, data, data->id, data->name);
	}

	remove_data(3);
	xa_for_each(&xarray_test, index, data) {
		printk("index %ld, data %p: id %d, name %s\n",
				index, data, data->id, data->name);
	}

	return 0;
}

static void __exit xarray_test_exit(void)
{
	struct my_data *data;
	unsigned long index = 0;

	printk("xarray example: cleaning up xarray example module\n");

	xa_for_each(&xarray_test, index, data) {
		xa_erase(&xarray_test, index);
		kfree(data);
	}
}

module_init(xarray_test_init);
module_exit(xarray_test_exit);


MODULE_AUTHOR("Jack");
MODULE_LICENSE("GPL");
