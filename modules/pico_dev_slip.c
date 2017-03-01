#include "pico_dev_slip.h"
#include "pico_stack.h"

#define MAX_SLIP_PKTSIZE    1500

/* SLIP functions*/
extern void SLIP_send(uint8_t *buf, int len);
extern uint32_t SLIP_poll(uint8_t *buf, int len);
//extern int slip_packet_received();
extern uint32_t sl_poll(uint8_t *buf, uint32_t len);

static int pico_slip_send(struct pico_device *dev, void *buf, int len){
    (void) dev;
    SLIP_send(buf, len);
    return 0;
}

static int pico_slip_poll(struct pico_device *dev, int loop_score){
    //(void) dev;
    //uint8_t *buf=NULL;
    uint8_t buf[MAX_SLIP_PKTSIZE];
    uint32_t len;
    while (loop_score > 0){
        len = SLIP_poll(buf, MAX_SLIP_PKTSIZE);
        if(!len) break;

        pico_stack_recv(dev, buf, len); // this will copy the frame into the stack
        loop_score--;

    }
    /*
    while (loop_score > 0) {
        //if (!slip_packet_received()){
        //    break;
        //}
        //len = BSP_ethernet_packet_get(ETH_BASE, &buf);
        //dbg("pico slip poll.\r\n");
        len = SLIP_poll(buf, MAX_SLIP_PKTSIZE);
        if (len == 0) {
            break;
        }
        pico_stack_recv(dev, buf, len); // this will copy the frame into the stack
        loop_score--;
    }
    */
    return loop_score;
}


struct pico_device *pico_slip_create(const char *name){
    //uint8_t mac[6];
    /* Create device struct */
    struct pico_device *slip_dev = PICO_ZALLOC(sizeof(struct pico_device));
    if(!slip_dev) {
        return NULL;
    }



    //mac[0]=0x98; mac[1]=0x4F; mac[2]=0xEE; mac[3]=0x05; mac[4]=0x64; mac[5]=0xED;

    
    /* Register the device in picoTCP */
    if( 0 != pico_device_init(slip_dev, name, NULL)) {
        dbg("Device init failed.\r\n");
        PICO_FREE(slip_dev);
        return NULL;
    }   

    /* Attach function pointers */
    slip_dev->send = pico_slip_send;
    slip_dev->poll = pico_slip_poll; 

    slip_dev->overhead=0;

    dbg("Device %s created\r\n", slip_dev->name);

    /* Return a pointer to the device struct */ 
    return slip_dev;
}
