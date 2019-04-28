/* taken from
 "PlayStation 2" Programmer Tool Runtime Library Release 2.3
 */
/*
 *              Emotion Engine Library Sample Program
 *
 *                       - mpeg streaming -
 *
 *                         Version 0.10
 *                           Shift-JIS
 *
 *      Copyright (C) 2000 Sony Computer Entertainment Inc.
 *                        All Rights Reserved.
 *
 *                           readbuf.c
 *                   functions for read buffer
 *
 *       Version        Date            Design      Log
 *  --------------------------------------------------------------------
 *       0.10           12.17.1999      umemura     the first version
 */
#include "defs.h"
#include "readbuf.h"

#if (!(defined(__cplusplus) || defined(__MWERKS__) || defined(__UNUSED__)))
#define __UNUSED__ __attribute__ ((unused))
#endif /* (!(defined(__cplusplus) || defined(__MWERKS__) || defined(__UNUSED__))) */


#if (!defined(__UNUSED__))
# define __UNUSED__ /* No op */
#endif /* (!defined(__UNUSED__)) */

#define BUFF_SIZE (N_READ_UNIT * READ_UNIT_SIZE)

/* //////////////////////////////////////////////////////////////// */
/* */
/* Create read buffer */
/* */
void
readBufCreate(ReadBuf * b)
{
    b->put = b->count = 0;
    b->size = BUFF_SIZE;
}

/* //////////////////////////////////////////////////////////////// */
/* */
/* Delete read buffer */
/* */
void
readBufDelete(ReadBuf * b __UNUSED__)
{
}

/* //////////////////////////////////////////////////////////////// */
/* */
/* Get empty area */
/* */
int
readBufBeginPut(ReadBuf * b, u_char ** ptr)
{
    int                 size = b->size - b->count;

    if (size)
    {
        *ptr = b->data + b->put;
    }
    return size;
}

/* //////////////////////////////////////////////////////////////// */
/* */
/* Proceed 'write' pointer */
/* */
int
readBufEndPut(ReadBuf * b, int size)
{
    int                 size_ok = min(b->size - b->count, size);

    b->put = (b->put + size_ok) % b->size;
    b->count += size_ok;

    return size_ok;
}

/* //////////////////////////////////////////////////////////////// */
/* */
/* Get data area */
/* */
int
readBufBeginGet(ReadBuf * b, u_char ** ptr)
{
    if (b->count)
    {
        *ptr = b->data + (b->put - b->count + b->size) % b->size;
    }
    return b->count;
}

/* //////////////////////////////////////////////////////////////// */
/* */
/* Proceed 'read' pointer */
/* */
int
readBufEndGet(ReadBuf * b, int size)
{
    int                 size_ok = min(b->count, size);

    b->count -= size_ok;

    return size_ok;
}
