#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/module.h>

struct family
{
	struct person *father;
	struct person *mother;
	int number_of_sons;
	int family_id;
};

struct person {
	int age;
	int salary;
	char *name;
};

static int __init hello_world_init(void)
{
	struct person somebody;
	struct person somebody2;
	struct family my_fam;
	int *fam_id_ptr;
	struct family *fam_ptr;

	somebody.age = 21;
	somebody.salary = 850;
	somebody.name = "Alice";
	
	somebody2.age = 25;
	somebody2.salary = 1050;
	somebody2.name = "Jhon";
	
	/* * Fill and initialise f somewhere */
	my_fam.mother = &somebody;
	my_fam.father = &somebody2;
	my_fam.number_of_sons = 12;
	my_fam.family_id = 5;
	
	pr_info("Jonathan DEBUG: Kernel Module Inserted Successfully...\n");
	pr_info(" &my_fam = %p (direct access)\n", &my_fam);
	/* * pointer to a field of the structure
	 * (could be any (non-pointer) member in the structure)
	 */
    fam_id_ptr = &my_fam.family_id;
	
	/* now let us retrieve back its family */
	fam_ptr = container_of(fam_id_ptr, struct family, family_id);
	pr_info("&fam_ptr = %p (indirect access)\n", fam_ptr);
    return 0;
}

static void __exit hello_world_exit(void)
{
    pr_info("Jonathan DEBUG: Kernel Module Removed Successfully...\n");
}

module_init(hello_world_init);
module_exit(hello_world_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("JC<jonathan.cagua@gmail.com>");
MODULE_DESCRIPTION("ptr to parent struct");
MODULE_VERSION("1:1.0");