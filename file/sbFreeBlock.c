/* sbFreeBlock.c - sbFreeBlock */
/* Copyright (C) 2008, Marquette University.  All rights reserved. */
/*                                                                 */
/* Modified by Alexander Kosla and Paula Van Camp                  */
/*                                                                 */
/* TA-BOT:MAILTO paula.vancamp@marquette.edu alexander.kosla@marquette.edu */
/*                                                                 */

#include <kernel.h>
#include <device.h>
#include <memory.h>
#include <disk.h>
#include <file.h>

/*------------------------------------------------------------------------
 * sbFreeBlock - Add a block back into the free list of disk blocks.
 *------------------------------------------------------------------------
 */
devcall sbFreeBlock(struct superblock *psuper, int block)
{
    // TODO: Add the block back into the filesystem's list of free blocks.
    //  Use the superblock's locks to guarantee mutually exclusive access to the free list, and write the changed free list segment(s) back to disk.
    struct freeblock *frisbee, *prevblock;
    if (psuper == NULL){
	return SYSERR; //no pointer to super
    }
    if(block == NULL){
	return SYSERR;//no block given
    }

    //enforce mutual exclusion	
    wait(psuper->sb_freelock);
   
    //find poisition in list
    frisbee.fr_blocknum = block;
    frisbee.fr_count++;
    
    //insert into list of free blocks
    prevblock.fr_blocknum = block-1;
    frisbee.fr_next = prevblock.fr_next;
    prevblock.fr_next = frisbee;
 

    //release lock
    signal(psuper->sb_freelock);
    return SYSERR;
}
