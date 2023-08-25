#include"shell.h"

/**
*str_length-returnsthelengthofastring
*@s:thestringwhoselengthtocheck
*
*Return:integerlengthofstring
*/
intstr_length(char*s)
{
inti=0;

if(!s)
return(0);

while(*s++)
i++;
return(i);
}

/**
*str_compare-performslexicographiccomparisonoftwostrings.
*@s1:thefirststring
*@s2:thesecondstring
*
*Return:negativeifs1<s2,positiveifs1>s2,zeroifs1==s2
*/
intstr_compare(char*s1,char*s2)
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
*starts_with-checksifneedlestartswithhaystack
*@haystack:stringtosearch
*@needle:thesubstringtofind
*
*Return:addressofnextcharofhaystackorNULL
*/
char*starts_with(constchar*haystack,constchar*needle)
{
while(*needle)
if(*needle++!=*haystack++)
return(NULL);
return((char*)haystack);
}

/**
*str_concatenate-concatenatestwostrings
*@dest:thedestinationbuffer
*@src:thesourcebuffer
*
*Return:pointertodestinationbuffer
*/
char*str_concatenate(char*dest,char*src)
{
char*ret=dest;

while(*dest)
dest++;
while(*src)
*dest++=*src++;
*dest=*src;
return(ret);
}
