#include"shell.h"

/**
*_strncpy-Copiesastring.
*@dest:Thedestinationstringtobecopiedto.
*@src:Thesourcestring.
*@n:Thenumberofcharacterstobecopied.
*
*Return:Theconcatenatedstring.
*/
char*_strncpy(char*dest,char*src,intn)
{
inti,j;
char*s=dest;

i=0;
while(src[i]!='\0'&&i<n-1)
{
dest[i]=src[i];
i++;
}
if(i<n)
{
j=i;
while(j<n)
{
dest[j]='\0';
j++;
}
}
return(s);
}

/**
*_strncat-Concatenatestwostrings.
*@dest:Thefirststring.
*@src:Thesecondstring.
*@n:Thenumberofbytestobemaximallyused.
*
*Return:Theconcatenatedstring.
*/
char*_strncat(char*dest,char*src,intn)
{
inti,j;
char*s=dest;

i=0;
j=0;
while(dest[i]!='\0')
i++;
while(src[j]!='\0'&&j<n)
{
dest[i]=src[j];
i++;
j++;
}
if(j<n)
dest[i]='\0';
return(s);
}

/**
*_strchr-Locatesacharacterinastring.
*@s:Thestringtobeparsed.
*@c:Thecharactertolookfor.
*
*Return:Apointertothefirstoccurrenceofthecharactercinthestrings,
*orNULLifthecharacterisnotfound.
*/
char*_strchr(char*s,charc)
{
do
{
if(*s==c)
return(s);
}while(*s++!='\0');

return(NULL);
}
