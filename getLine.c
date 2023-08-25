#include"modified_shell.h"

/**
*input_buffer-bufferschainedcommands
*@info:parameterstruct
*@buffer:addressofbuffer
*@length:addressoflengthvar
*
*Return:bytesread
*/
ssize_tinput_buffer(modified_info_t*info,char**buffer,size_t*length)
{
ssize_tread_bytes=0;
size_tlength_p=0;

if(!*length)/*ifnothingleftinthebuffer,fillit*/
{
/*bfree((void**)info->cmd_buffer);*/
free(*buffer);
*buffer=NULL;
signal(SIGINT,sigint_handler);
#ifUSE_GETLINE
read_bytes=getline(buffer,&length_p,stdin);
#else
read_bytes=_get_line(info,buffer,&length_p);
#endif
if(read_bytes>0)
{
if((*buffer)[read_bytes-1]=='\n')
{
(*buffer)[read_bytes-1]='\0';/*removetrailingnewline*/
read_bytes--;
}
info->linecount_flag=1;
remove_comments(*buffer);
build_history_list(info,*buffer,info->histcount++);
/*if(_strchr(*buffer,';'))isthisacommandchain?*/
{
*length=read_bytes;
info->cmd_buffer=buffer;
}
}
}
return(read_bytes);
}

/**
*get_input-getsalineminusthenewline
*@info:parameterstruct
*
*Return:bytesread
*/
ssize_tget_input(modified_info_t*info)
{
staticchar*buffer;/*the';'commandchainbuffer*/
staticsize_ti,j,length;
ssize_tread_bytes=0;
char**buffer_p=&(info->arg),*p;

mod_putchar(BUF_FLUSH);
read_bytes=input_buffer(info,&buffer,&length);
if(read_bytes==-1)/*EOF*/
return(-1);
if(length)	/*wehavecommandsleftinthechainbuffer*/
{
j=i;/*initnewiteratortocurrentbufferposition*/
p=buffer+i;/*getpointerforreturn*/

check_chain(info,buffer,&j,i,length);
while(j<length)/*iteratetosemicolonorend*/
{
if(is_chain(info,buffer,&j))
break;
j++;
}

i=j+1;/*incrementpastnulled';''*/
if(i>=length)/*reachedendofbuffer?*/
{
i=length=0;/*resetpositionandlength*/
info->cmd_buffer_type=CMD_NORMAL;
}

*buffer_p=p;/*passbackpointertocurrentcommandposition*/
return(_str_len(p));/*returnlengthofcurrentcommand*/
}

*buffer_p=buffer;/*elsenotachain,passbackbufferfrom_get_line()*/
return(read_bytes);/*returnlengthofbufferfrom_get_line()*/
}

/**
*read_buffer-readsabuffer
*@info:parameterstruct
*@buffer:buffer
*@i:size
*
*Return:r
*/
ssize_tread_buffer(modified_info_t*info,char*buffer,size_t*i)
{
ssize_tread_bytes=0;

if(*i)
return(0);
read_bytes=read(info->readfd,buffer,READ_BUF_SIZE);
if(read_bytes>=0)
*i=(size_t)read_bytes;
return(read_bytes);
}

/**
*_get_line-getsthenextlineofinputfromSTDIN
*@info:parameterstruct
*@ptr:addressofpointertobuffer,preallocatedorNULL
*@length:sizeofpreallocatedptrbufferifnotNULL
*
*Return:s
*/
int_get_line(modified_info_t*info,char**ptr,size_t*length)
{
staticcharbuffer[READ_BUF_SIZE];
staticsize_ti,len;
size_tk;
ssize_tread_bytes=0,s=0;
char*p=NULL,*new_p=NULL,*c;

p=*ptr;
if(p&&length)
s=*length;
if(i==len)
i=len=0;

read_bytes=read_buffer(info,buffer,&len);
if(read_bytes==-1||(read_bytes==0&&len==0))
return(-1);

c=_strchr(buffer+i,'\n');
k=c?1+(size_t)(c-buffer):len;
new_p=_reallocate(p,s,s?s+k:k+1);
if(!new_p)/*MALLOCFAILURE!*/
return(p?free(p),-1:-1);

if(s)
_str_n_cat(new_p,buffer+i,k-i);
else
_str_n_cpy(new_p,buffer+i,k-i+1);

s+=k-i;
i=k;
p=new_p;

if(length)
*length=s;
*ptr=p;
return(s);
}

/**
*sigint_handler-blocksctrl-C
*@sig_num:thesignalnumber
*
*Return:void
*/
voidsigint_handler(__attribute__((unused))intsig_num)
{
mod_puts("\n");
mod_puts("$");
mod_putchar(BUF_FLUSH);
}
