#include"shell.h"

/**
*custom_strlen-returnsthelengthofastring
*@s:thestringwhoselengthtocheck
*
*Return:integerlengthofstring
*/
intcustom_strlen(char*s)
{
inti=0;

if(!s)
return(0);

while(*s++)
i++;
return(i);
}

/**
*custom_strcmp-performslexicographiccomparisonoftwostrings.
*@s1:thefirststring
*@s2:thesecondstring
*
*Return:negativeifs1<s2,positiveifs1>s2,zeroifs1==s2
*/
intcustom_strcmp(char*s1,char*s2)
{
while(*s1&&*s2)
{
if(*s1!=*s2)
return(*s1-*s2);
s1++;
s2++;
}
if(*s1==*s2)
return(0);
else
return(*s1<*s2?-1:1);
}

/**
*custom_starts_with-checksifneedlestartswithhaystack
*@haystack:stringtosearch
*@needle:thesubstringtofind
*
*Return:addressofnextcharofhaystackorNULL
*/
char*custom_starts_with(constchar*haystack,constchar*needle)
{
while(*needle)
if(*needle++!=*haystack++)
return(NULL);
return((char*)haystack);
}

/**
*custom_str_concat-concatenatestwostrings
*@dest:thedestinationbuffer
*@src:thesourcebuffer
*
*Return:pointertodestinationbuffer
*/
char*custom_str_concat(char*dest,char*src)
{
char*ret=dest;

while(*dest)
dest++;
while(*src)
*dest++=*src++;
*dest=*src;
return(ret);
}
