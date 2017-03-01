/*********************************************************************
   PicoTCP. Copyright (c) 2012-2015 Altran Intelligent Systems. Some rights reserved.
   See LICENSE and COPYING for usage.

   Authors: Daniele Lacamera
 *********************************************************************/


#include "pico_device.h"
#include "pico_dev_galileo.h"
#include "pico_stack.h"

/* GALILEO functions*/
extern void quarkX1000_eth_init(void);
extern void send(uint8_t * buf, int len);
extern void poll(uint8_t * buf, uint32_t loop_score);
extern uint8_t *get_MAC_addr();

static int pico_eth_send(struct pico_device *dev, void *buf, int len)
{
    (void) dev;

    send(buf, len);
    return 0;
}

static int pico_eth_poll(struct pico_device *dev, int loop_score)
{
    //redo this function
    uint8_t *buf;
    uint32_t len = 0;
    IGNORE_PARAMETER(dev);
    IGNORE_PARAMETER(loop_score);
    //poll()

    /*while (loop_score > 0) {
        if (!BSP_ethernet_packet_available(ETH_BASE)) {
            break;
        }
        len = BSP_ethernet_packet_get(ETH_BASE, &buf);
        if (len == 0) {
            break;
        }
        pico_stack_recv(dev, buf, len); // this will copy the frame into the stack
        loop_score--;
    }*/

    return loop_score;
}


struct pico_device *pico_eth_create(const char *name){
    uint8_t *mac;
    /* Create device struct */
    struct pico_device* eth_dev = PICO_ZALLOC(sizeof(struct pico_device));
    if(!eth_dev) {
        return NULL;
    }

    /* Initialize hardware */
        quarkX1000_eth_init();
        mac=get_MAC_addr();
        dbg("MAC addr:::  %02x:%02x:%02x:%02x:%02x:%02x.\r\n", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5] );


    /* Attach function pointers */
    //send and poll are GALILEO functions
    eth_dev->send = pico_eth_send;
    eth_dev->poll = pico_eth_poll;
    
    /* Register the device in picoTCP */
    if( 0 != pico_device_init(eth_dev, name, mac)) {
        dbg("Device init failed.\r\n");
        PICO_FREE(eth_dev);
        return NULL;
    }



    /* Return a pointer to the device struct */ 
    return eth_dev;
}
