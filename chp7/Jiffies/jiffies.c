#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/jiffies.h>
#include <linux/timer.h>


unsigned long j, stamp_1, stamp_half, stamp_n;
unsigned long js, je, tet ,tot;
int netblock_init_module(void){
    js = jiffies;
    printk("\n[Jiffies start Time : %lu]\nModule Started.\n", js);
    


    j = jiffies;                      
    stamp_1    = j + HZ;              
    stamp_half = j + HZ/2;            
    printk("\nstamp1_1:[%lu]\n ",stamp_1);
    printk("\nstamp_half:[%lu]\n ",stamp_half);
    return 0;
}

void netblock_cleanup_module(void) {
    je = jiffies;
    printk("\n[Jiffies End Time : %lu]\nModule Removed.\n", je);
    tet = je - js;
    printk("\nEnd Time [%lu] - Start Time [%lu]: \nTotal elapsed Time [%lu]\n",js,je, tet);
    tot= tet * 1000 / HZ;
    printk("\n Total Elapsed time in seconds: [%lu]\n: ",tot);

}

module_init(netblock_init_module);
module_exit(netblock_cleanup_module);
