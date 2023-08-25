#include"shell.h"

/**
*_eputs-Printsaninputstringtostderr.
*@str:Thestringtobeprinted.
*
*Return:Nothing.
*/
void_eputs(char*str)
{
	inti=0;

	if(!str)
		return;

	while(str[i]!='\0')
	{
		_eputchar(str[i]);
		i++;
	}
}

/**
*_eputchar-Writesthecharacterctostderr.
*@c:Thecharactertoprint.
*
*Return:Onsuccess1.
*Onerror,-1isreturned,anderrnoissetappropriately.
*/
int_eputchar(charc)
{
	staticinti;
	staticcharbuf[WRITE_BUF_SIZE];

	if(c==BUF_FLUSH||i>=WRITE_BUF_SIZE)
	{
		write(2,buf,i);
		i=0;
	}
	if(c!=BUF_FLUSH)
		buf[i++]=c;

	return(1);
}

/**
*_putfd-Writesthecharacterctothegivenfiledescriptor.
*@c:Thecharactertoprint.
*@fd:Thefiledescriptortowriteto.
*
*Return:Onsuccess1.
*Onerror,-1isreturned,anderrnoissetappropriately.
*/
int_putfd(charc,intfd)
{
	staticinti;
	staticcharbuf[WRITE_BUF_SIZE];

	if(c==BUF_FLUSH||i>=WRITE_BUF_SIZE)
	{
		write(fd,buf,i);
		i=0;
	}
	if(c!=BUF_FLUSH)
		buf[i++]=c;

	return(1);
}

/**
*_putsfd-Printsaninputstringtothegivenfiledescriptor.
*@str:Thestringtobeprinted.
*@fd:Thefiledescriptortowriteto.
*
*Return:Thenumberofcharactersput.
*/
int_putsfd(char*str,intfd)
{
	inti=0;

	if(!str)
		return(0);

	while(*str)
	{
	i+=_putfd(*str++,fd);
	}

	return(i);
}
