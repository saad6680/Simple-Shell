#include"modified_shell.h"

/**
*mod_myhistory-displaysthehistorylist,onecommandbyline,preceded
*withlinenumbers,startingat0.
*@info:Structurecontainingpotentialarguments.Usedtomaintain
*constantfunctionprototype.
*Return:Always0
*/
intmod_myhistory(modified_info_t*info)
{
mod_print_list(info->history);
return(0);
}

/**
*mod_unset_alias-setsaliastostring
*@info:parameterstruct
*@str:thestringalias
*
*Return:Always0onsuccess,1onerror
*/
intmod_unset_alias(modified_info_t*info,char*str)
{
char*p,c;
intret;

p=mod_strchr(str,'=');
if(!p)
return(1);
c=*p;
*p=0;
ret=mod_delete_node_at_index(&(info->alias),
mod_get_node_index(info->alias,mod_node_starts_with(info->alias,str,-1)));
*p=c;
return(ret);
}

/**
*mod_set_alias-setsaliastostring
*@info:parameterstruct
*@str:thestringalias
*
*Return:Always0onsuccess,1onerror
*/
intmod_set_alias(modified_info_t*info,char*str)
{
char*p;

p=mod_strchr(str,'=');
if(!p)
return(1);
if(!*++p)
return(mod_unset_alias(info,str));

mod_unset_alias(info,str);
return(mod_add_node_end(&(info->alias),str,0)==NULL);
}

/**
*mod_print_alias-printsanaliasstring
*@node:thealiasnode
*
*Return:Always0onsuccess,1onerror
*/
intmod_print_alias(modified_list_t*node)
{
char*p=NULL,*a=NULL;

if(node)
{
p=mod_strchr(node->str,'=');
for(a=node->str;a<=p;a++)
mod_putchar(*a);
mod_putchar('\'');
mod_puts(p+1);
mod_puts("'\n");
return(0);
}
return(1);
}

/**
*mod_myalias-mimicsthealiasbuiltin(manalias)
*@info:Structurecontainingpotentialarguments.Usedtomaintain
*constantfunctionprototype.
*Return:Always0
*/
intmod_myalias(modified_info_t*info)
{
inti=0;
char*p=NULL;
modified_list_t*node=NULL;

if(info->argc==1)
{
node=info->alias;
while(node)
{
mod_print_alias(node);
node=node->next;
}
return(0);
}
for(i=1;info->argv[i];i++)
{
p=mod_strchr(info->argv[i],'=');
if(p)
mod_set_alias(info,info->argv[i]);
else
mod_print_alias(mod_node_starts_with(info->alias,info->argv[i],'='));
}

return(0);
}
