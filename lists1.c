#include"modified_shell.h"

/**
*mod_list_len-determinesthelengthofalinkedlist
*@h:pointertothefirstnode
*
*Return:sizeofthelist
*/
size_tmod_list_len(constmodified_list_t*h)
{
size_ti=0;

while(h)
{
h=h->next;
i++;
}
return(i);
}

/**
*mod_list_to_strings-returnsanarrayofstringsofthelist->str
*@head:pointertothefirstnode
*
*Return:arrayofstrings
*/
char**mod_list_to_strings(modified_list_t*head)
{
modified_list_t*node=head;
size_ti=mod_list_len(head),j;
char**strs;
char*str;

if(!head||!i)
return(NULL);
strs=malloc(sizeof(char*)*(i+1));
if(!strs)
return(NULL);
for(i=0;node;node=node->next,i++)
{
str=malloc(mod_strlen(node->str)+1);
if(!str)
{
for(j=0;j<i;j++)
free(strs[j]);
free(strs);
return(NULL);
}

str=mod_strcpy(str,node->str);
strs[i]=str;
}
strs[i]=NULL;
return(strs);
}

/**
*mod_print_list-printsallelementsofamodified_list_tlinkedlist
*@h:pointertothefirstnode
*
*Return:sizeofthelist
*/
size_tmod_print_list(constmodified_list_t*h)
{
size_ti=0;

while(h)
{
mod_puts(mod_convert_number(h->num,10,0));
mod_putchar(':');
mod_putchar('');
mod_puts(h->str?h->str:"(nil)");
mod_puts("\n");
h=h->next;
i++;
}
return(i);
}

/**
*mod_node_starts_with-returnsanodewhosestringstartswithprefix
*@node:pointertothelisthead
*@prefix:stringtomatch
*@c:thenextcharacteraftertheprefixtomatch
*
*Return:matchingnodeornull
*/
modified_list_t*mod_node_starts_with(modified_list_t*node,char*prefix,charc)
{
char*p=NULL;

while(node)
{
p=mod_starts_with(node->str,prefix);
if(p&&((c==-1)||(*p==c)))
return(node);
node=node->next;
}
return(NULL);
}

/**
*mod_get_node_index-getstheindexofanode
*@head:pointertothelisthead
*@node:pointertothenode
*
*Return:indexofthenodeor-1
*/
ssize_tmod_get_node_index(modified_list_t*head,modified_list_t*node)
{
size_ti=0;

while(head)
{
if(head==node)
return(i);
head=head->next;
i++;
}
return(-1);
}