/*
 * Copyright (C) 2018 Koen Zandberg
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */
/**
 * @ingroup     sys_auto_init
 * @{
 * @file
 * @brief       initializes USBUS, usb devices and handlers
 *
 * This auto initialization for USBUS is designed to cover the common use case
 * of a single usb peripheral. An USBUS instance is started with USB function
 * handlers based on which module is compiled in.
 *
 * If this doesn't suit your use case, a different intialization function can
 * to be created based on this initialization sequence.
 *
 * @author  Koen Zandberg <koen@bergzand.net>
 * @}
 */

#include "usb/usbus.h"

static char _stack[USBUS_STACKSIZE];
static usbus_t usbus;

void auto_init_usb(void)
{
    /* Get driver context */
    usbdev_t *usbdev = usbdev_get_ctx(0);
    assert(usbdev);

    /* Initialize basic usbus struct, don't start the thread yet */
    usbus_init(&usbus, usbdev);


    /* Finally initialize USBUS thread */
    usbus_create(_stack, USBUS_STACKSIZE, USBUS_PRIO, USBUS_TNAME, &usbus);
}
