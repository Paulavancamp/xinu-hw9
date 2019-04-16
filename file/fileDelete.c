/* fileDelete.c - fileDelete */
/* Copyright (C) 2008, Marquette University.  All rights reserved. */
/*                                                                 */
/* Modified by                                                     */
/*                                                                 */
/* and                                                             */
/*                                                                 */
/*                                                                 */

#include <kernel.h>
#include <memory.h>
#include <file.h>

/*------------------------------------------------------------------------
 * fileDelete - Delete a file.
 *------------------------------------------------------------------------
 */
devcall fileDelete(int fd)
{
    //  Unlink this file from the master directory index,
    //  and return its space to the free disk block list.
    //  Use the superblock's locks to guarantee mutually exclusive
    //  access to the directory index.

	//enforce mutual exclusion
	wait(dirlock);
	//call freeblock using the given location within the list
	sbFreeBlock(supertab, supertab->dirlist->db_fnodes[fd].blocknum);
	//set state to free
	fn_state = FREE;
	//idk...
	seek(DISK0, supertab->sb_dirlist->db_blocknum);
	write(DISK0, supertab->sb_dirlist, sizeof(struct dirblock));
	//end critical section
	signal(dirlock);

   return OK;
}
