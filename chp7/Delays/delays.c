#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/jiffies.h>
#include <linux/timer.h>
#include <linux/delay.h>
#include <linux/wait.h>
#include <linux/sched.h>



unsigned long timeout = 10000;
unsigned long js, je, tet ,tot,jf;
int netblock_init_module(void){
    js = jiffies;
    msleep(10000);
    printk("\n[Jiffies start Time : %lu]\nModule Started.\n", js);
    mdelay(timeout);    //Short Delays
    jf= jiffies;
    printk("\n[Jiffies  Timeout End time : %lu]",jf);  //TIME CALCULATIONS
    printk("\nCOMPLETED THE TIMEOUT MODE");
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
