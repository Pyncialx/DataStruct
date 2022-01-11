#include <stddef.h> // required for NULL
#include <stdio.h>
#include <stdlib.h>
#include <doublyLinkedList.h>

struct doubly_list_node *list_append(struct doubly_list_node **head, struct doubly_list_node *item)
{
    struct doubly_list_node *tail = list_get_tail(head);
    if (!tail)
    {
        *head = item;
    }
    else
    {
        tail->next = item;
    }
    item->prev = tail;
    item->next = NULL;
    return item;
}

struct doubly_list_node *list_get_tail(struct doubly_list_node **head)
{
    struct doubly_list_node *current_node = *head;
    struct doubly_list_node *last_node = NULL;
    while (current_node)
    {
        last_node = current_node;
        current_node = current_node->next;
    }
    return last_node;
}

struct doubly_list_node *list_pop(struct doubly_list_node **head)
{
    struct doubly_list_node *current_head = *head;
    if (!current_head)
    {
        return NULL;
    }
    *head = (*head)->next;
    current_head->next = NULL;
    current_head->prev = NULL;

    return current_head;
}
struct doubly_string_item *string_item_new(const char *string)
{
    struct doubly_string_item *item = malloc(sizeof(struct doubly_string_item));
    if (!item)
    {
        return NULL;
    }
    item->string = string;
    return item;
}
struct doubly_list_node *list_remove(struct doubly_list_node **head, struct doubly_list_node *item)
{

    struct doubly_list_node *prev_node = item->prev;
    struct doubly_list_node *next_node = item->next;

    if (!item->prev)
    {
        list_pop(head);
        return 0;
    }

    prev_node->next = item->next; //the next of the previous node to remove become the next node of the node to remove
    next_node->prev = item->prev; // the previous of the next node to remove become the previous node of the node to remove
     //node to remove

    item->next = NULL; //removing the reference at the other node
    item->prev = NULL;

    return item;
}
int *list_insert_afther(struct doubly_list_node *item, struct doubly_list_node *item_to_insert) 
{
    //need control if the item exist in a list
    if (item->next)
    {
        item_to_insert->next = item->next; //set the next of the item i have to insert
        (item->next)->prev = item_to_insert; //set the previous of the next item to the item i have to insert
    }
    else
    {
        item_to_insert->next = NULL; //if there is nothing afther the item i want to insert afther
    }
    item_to_insert->prev = item;  //set the previous
    item->next = item_to_insert;  //set the item_to_insert as the next of the previous item

    return 0;

}

int *list_insert_before(struct doubly_list_node **head,struct doubly_list_node *item, struct doubly_list_node *item_to_insert)
{       
                                                                                                                
    if(item->prev)
    {
        item_to_insert->prev = item->prev;
        (item->prev)->next = item_to_insert;
    }
    else
    {
        *head = item_to_insert;
        item_to_insert->prev = NULL;
    }
    item_to_insert->next= item;
    item->prev = item_to_insert;

    return 0;
}

int main()
{
    struct doubly_list_node *mylist = NULL;

    struct doubly_string_item *item1 = string_item_new("element 1");
    struct doubly_string_item *item2 = string_item_new("element 2");
    struct doubly_string_item *item3 = string_item_new("element 3");
    struct doubly_string_item *item4 = string_item_new("element 4");

    struct doubly_string_item *item5 = string_item_new("element 5");
    struct doubly_string_item *item6 = string_item_new("LUIGI");
    struct doubly_string_item *item7 = string_item_new("MARIO");
    struct doubly_string_item *item8 = string_item_new("INMEZZO");




    list_append_cast_doubly(&mylist,item1);
    list_append_cast_doubly(&mylist,item2);
    list_append_cast_doubly(&mylist,item3);
    list_append_cast_doubly(&mylist,item4);
    list_append_cast_doubly(&mylist,item5);
    list_append_cast_doubly(&mylist,item6);

    
    //list_remove((struct doubly_list_node **)&mylist,(struct doubly_list_node *)item2);
    list_remove_cast_doubly(&mylist,item2);


    //list_insert_afther((struct doubly_list_node *)item3,(struct doubly_list_node *)item7);
    list_insert_afther_doubly(item3,item7);

    //list_insert_before((struct doubly_list_node **)&mylist,(struct doubly_list_node *)item7,(struct doubly_list_node *)item8);
    list_insert_before_doubly(&mylist,item7,item8);

    struct doubly_string_item *string_item = mylist;

    while (string_item)
    {
        printf("%s\n", string_item->string);
        string_item = (struct doubly_string_item *)string_item->node.next;
    }


    return 0;
}