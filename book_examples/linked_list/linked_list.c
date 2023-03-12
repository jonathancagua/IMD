/* Typical includes to work with Linux kernel*/
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

#include <linux/list.h> /* For list_head */
#include <linux/slab.h> /* For kmalloc */

struct car {
  int door_number;
  char *color;
  char *model;
  struct list_head list; /* kernel's list structure */
};

/* struct listhead carlist; */
static LIST_HEAD(carlist);

static int __init hello_world_init(void) {
  pr_info("Jonathan DEBUG: Kernel Module Inserted Successfully...\n");
  
  struct car *redcar = kmalloc(sizeof(struct car), GFP_KERNEL);
  struct car *bluecar = kmalloc(sizeof(struct car), GFP_KERNEL);

  /* Initialize each node's list entry with define from linux/list.h */
  INIT_LIST_HEAD(&bluecar->list);
  INIT_LIST_HEAD(&redcar->list);

  /* allocate memory for color and model field and fill every field */
  redcar->door_number = 5;
  redcar->color = "red";
  redcar->model = "toyota";

  redcar->door_number = 4;
  bluecar->color = "blue";
  bluecar->model = "ford";

  list_add(&redcar->list, &carlist);
  pr_info("This is a double linked list, where\n");
  pr_info("carlist and redcar point to each other\n");

  pr_info("Carlist next and prev now point to &redcar.list\n");
  pr_info("    &redcar->list: %p\n", &redcar->list);
  pr_info("     carlist.next: %p\n", carlist.next);
  pr_info("     carlist.prev: %p\n", carlist.prev);

  pr_info("And redcar.list next and prev point to &carlist\n");
  pr_info("         &carlist: %p\n", &carlist);
  pr_info("redcar->list.next: %p\n", redcar->list.next);
  pr_info("redcar->list.prev: %p\n", redcar->list.prev);

  pr_info("carlist -> redcar\n");

  pr_info("What if we add bluecar to carlist?\n");
  list_add(&bluecar->list, &carlist);
  pr_info("    &bluecar->list: %p\n", &bluecar->list);
  pr_info("      carlist.next: %p\n", carlist.next);
  pr_info("bluecar->list.next: %p\n", bluecar->list.next);
  pr_info(" redcar->list.next: %p\n", redcar->list.next);
  
  pr_info("carlist -> bluecar -> redcar\n");
  return 0;
}

static void __exit hello_world_exit(void) {
  pr_info("Jonathan DEBUG: Kernel Module Removed Successfully...\n");
}

module_init(hello_world_init);
module_exit(hello_world_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("JC<jonathan.cagua@gmail.com>");
MODULE_DESCRIPTION("linked list 1st example");
MODULE_VERSION("1:1.0");
