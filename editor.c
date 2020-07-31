#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef unsigned char ed_byte;

typedef struct{
	ed_byte *pos;
	ed_byte *gap_start,*gap_end;
	ed_byte *buffer,*buf_end;
	int len;
}ed_buffer;

ed_buffer *ed_cur_buffer=NULL;
const int ed_gap=64;

void EdSwap(ed_buffer *buf)
{
	ed_cur_buffer=buf;
}

void EdInit()
{
	if (ed_cur_buffer!=NULL){
		free(ed_cur_buffer->buffer);
		free(ed_cur_buffer);
	}
	ed_buffer *buf=malloc(sizeof(ed_buffer));
	buf->buffer=malloc(ed_gap*sizeof(ed_byte));
	buf->len=ed_gap;
	buf->gap_start=buf->buffer;
	buf->gap_end=buf->buffer+ed_gap;
	buf->buf_end=buf->gap_end;
	buf->pos=buf->gap_start;
	EdSwap(buf);	
}

void EdInsert(ed_byte c)
{
	ed_buffer *buf=ed_cur_buffer;
	if (buf->pos==buf->gap_end)
		buf->pos=buf->gap_start;	
	if (buf->pos<buf->gap_start){
		buf->gap_end-=buf->gap_start-buf->pos;
		buf->gap_start=buf->pos;
		memcpy(buf->gap_end,buf->gap_start,buf->gap_start-buf->pos);
	}else if (buf->pos>buf->gap_end){
		memcpy(buf->gap_start,buf->gap_end,buf->pos-buf->gap_end);
		buf->gap_start+=buf->pos-buf->gap_end;
		buf->gap_end=buf->pos;
	}
	if (buf->gap_start==buf->gap_end){
		buf->len+=ed_gap;
		buf->buffer=realloc(buf->buffer,buf->len);
		buf->gap_end+=ed_gap;
		memcpy(buf->gap_end,buf->gap_start,buf->buf_end-buf->gap_start);
		buf->buf_end=buf->buffer+buf->len;
	}
	*buf->pos=c;
	buf->gap_start++;
	buf->pos=buf->gap_start;
}

void EdMove(int x)
{
	ed_buffer *buf=ed_cur_buffer;
	if (buf->pos==buf->gap_start){
		if (buf->gap_end==buf->buf_end)
			return;
		buf->pos=buf->gap_end;
	}
	
}

void EdDelete()
{


}

void EdNewline()
{

}

int main()
{
	EdInit();

	return 0;
}