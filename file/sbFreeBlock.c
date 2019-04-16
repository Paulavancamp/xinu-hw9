/* sbFreeBlock.c - sbFreeBlock */
/* Copyright (C) 2008, Marquette University.  All rights reserved. */
/*                                                                 */
/* Modified by Alexander Kosla and Paula Van Camp                  */
/*                                                                 */
/*TA-BOT:MAILTO paula.vancamp@marquette.edu alexander.kosla@marquette.edu */

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
//Add the block back into the filesystem's list of free blocks.
//Use the superblock's locks to guarantee mutually exclusive access
//to the free list, and write the changed free list segment(s) back to disk.

    if ((psuper == NULL)||(block == NULL)){
	return SYSERR;//no block or pointer given
    }

    struct dentry *phw;
    phw = psuper->sb_disk;
    if(phw == NULL){
	return SYSERR;
    }

    //set up freeblock and others
    freeblock = (struct freeblock*) malloc(sizeof(struct freeblock));
    struct freeblock *newblock, *nextBlock;
    struct dirblock *swizzle;
    //enforce mutual exclusion	
    wait(psuper->sb_freelock);

/************************CRITICAL SECTION*******************************/

    //initialize freeblock to be the freeblock
    freeblock = psuper->sb_freelist;
    //CASE 3: if no freeblk
    if(freeblock == NULL){
	//create and add to head of sb freelist
	printf("FREEBLOCK IS NULL \r\n\t");
	newBlock->fr_count = 0;
	newBlock->fr_next = NULL;
	newBlock->fr_blocknum = block;
	/*swizzle*/
	swizzle = psuper->sb_dirlst;
	psuper->sb_dirlst = (struct dirblock *)swizzle->db_blocknum;
    	seek(diskfd, block);
	if(write(diskfd, freeblk, sizeof(struct freeblock))){
	    return SYSERR;
	}
	/*restore swizzle*/
	psuper->sb_dirlst = swizzle;
	signal(psuper->sb_freelist);
	return OK;
    }
    //**CASE 2: if block is full
    if(freeblock->fr_count==FREEBLOCKMAX){
	//add to end of freelist
	printf("BLOCK FULL\r\n\t");
	newBlock->fr_count = 0;
	newBlock->fr_next = NULL;
	newBlock->fr_blocknum = block;
	freeblock->fr_next = newBlock;
	}
	signal(psuper->sb_freelock);
	return OK;
    //**CASE 1: Basic Case  
    if(freelist->fr_count<MAXBLOCKCOUNT){
    	freeblock->fr_free[block];
    	freeblock->fr_count++;
    }

/***********************END CRITICAL SECTION*************************/
    signal(psuper->sb_freelock);

    return SYSERR;
}
