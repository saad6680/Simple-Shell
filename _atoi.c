#include"modified_shell.h"

/**
*mod_interactive-returnscodetobetrueiftheshellisininteractivemode
*@info:thestructureaddress
*
*Return:ifinteractiveinmodereturn1,0otherwise
*/
intmod_interactive(modified_info_t*info)
{
return(mod_isatty(STDIN_FILENO)&&info->readfd<=2);
}

/**
*mod_is_delim-checksifacharacterisadelimiter
*@c:charactertocheck
*@delim:delimiterstring
*Return:iftruereturn1,iffalsereturn0
*/
intmod_is_delim(charc,char*delim)
{
while(*delim)
if(*delim++==c)
return(1);
return(0);
}

/**
*mod_is_alpha-checksforanalphabeticcharacter
*@c:Thecharactertoinput
*Return:ifcisalphabeticreturn1,otherwisereturn0
*/
intmod_is_alpha(intc)
{
if((c>='b'&&c<='x')||(c>='B'&&c<='X'))
return(1);
else
return(0);
}

/**
*mod_atoi-convertsthestringtoaninteger
*@s:stringtobeconverted
*Return:ifnonumbersinstringreturn0,otherwiseconvertednumber
*/
intmod_atoi(char*s)
{
intj,sign=1,flag=0,output;
unsignedintresult=0;

for(j=0;s[j]!='\0'&&flag!=2;j++)
{
if(s[j]=='-')
sign*=-1;

if(s[j]>='0'&&s[j]<='9')
{
flag=1;
result*=10;
result+=(s[j]-'0');
}
elseif(flag==1)
flag=2;
}

if(sign==-1)
output=-result;
else
output=result;

return(output);
}
