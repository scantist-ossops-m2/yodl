#ifndef _INCLUDED_MEDIA_H_
#define _INCLUDED_MEDIA_H_

#include <stdio.h>
#include "../queue/queue.h"

/*
    the Media struct is used only by the lexical scanner (Lexer). Pointers to
    Media structs are passed via the Stack
*/

typedef struct Media
{
    FILE       *d_file;         /* current input file if reading files  */
    size_t    d_lineno;       /* linenumber at push-point             */
    long        d_offset;       /* offset at push-point                 */
    char       *d_filename;     /* name of the file being processed     */
    Queue       d_queue;        /* queue of chars to process            */
    bool        d_isfile;       /* true if file media                   */
    bool        d_fgetc;        /* true if retreived char from file     */
}
Media;

    /*
        All _media_ functions may only be called when the Media * points
        to actual Media
    */
void            l_media_destructor(void *mp);
bool            l_media_fgetc(Media *mp);       /* true if char returned by */
char const     *l_media_filename(Media *mp);    /* returns filename         */
int             l_media_get(Media *mp);         /* gets next char fm media  */
bool            l_media_isFile(Media *mp);      /* true: media refers to a  */
                                                /* file, false: to memory   */
                                                /* or no media              */
size_t          l_media_lineno(Media *mp);      /* 0 (no media) or linenr   */
void            l_media_push_front(Media *mp, char const *str);
void            l_media_restore_state(Media *mp);
void            l_media_save_state(Media *mp);  /* info about current media */
                                                /* if it's a file, save its */
                                                /* info and close it        */

                                                /* unget_memory() assumes   */
                                                /* enough room in d_memory  */
void            l_media_unget_memory(Media *mp, int ch);

#endif
