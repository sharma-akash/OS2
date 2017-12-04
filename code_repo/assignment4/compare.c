#include <linux/module.h>
#include <linux/slab.h>
#include <linux/random.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/syscall.h>

// Module for random memory allocation

static int __init malloc_init(void){

  int i, random_bytes, random_bytes2;

  for(i = 0; i < 10000; i++){
      get_random_bytes(&random_bytes, sizeof(random_bytes));
      get_random_bytes(&random_bytes2, sizeof(random_bytes2));

      void * temp = kmalloc(random_bytes, GFP_KERNEL);
      kfree(temp);
      temp = kmalloc(random_bytes2, GFP_KERNEL);
      kfree(temp);
  }

  long free_space = syscall(359);
  long used_space = syscall(360);
  printf("computed free space: %lu\n", free_space);
  printf("computed used space: %lu\n", used_space);
  printf("computed ratio: %f\n", (float)free_spade/(float)used_space);

  return 0;
}

static void __exit malloc_exit(void){
}

module_init(malloc_init);
module_exit(malloc_exit);

MODULE_AUTHOR("Rohit Chaudhary, Akash Sharma");
MODULE_LICENSE("GPL");
