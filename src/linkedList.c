#include <stddef.h> // required for NULL
#include <stdio.h>
#include <stdlib.h>
#include <linkedList.h>


struct list_node *list_get_tail(struct list_node **head)
{
    struct list_node *current_node = *head;
    struct list_node *last_node = NULL;
    while (current_node)
    {
        last_node = current_node;
        current_node = current_node->next;
    }
    return last_node;
}

struct list_node *list_append(struct list_node **head, struct list_node *item)
{
    struct list_node *tail = list_get_tail(head);
    if (!tail)
    {
        *head = item;
    }
    else
    {
        tail->next = item;
    }
    item->next = NULL;
    return item;
}
struct list_node *list_pop(struct list_node **head)
{
    struct list_node *current_head = *head;
    if (!current_head)
    {
        return NULL;
    }
    *head = (*head)->next;
    current_head->next = NULL;
    return current_head;
}

struct string_item *string_item_new(const char *string)
{
    struct string_item *item = malloc(sizeof(struct string_item));
    if (!item)
    {
        return NULL;
    }
    item->string = string;
    return item;
}
struct list_node *list_remove(struct list_node **head, struct list_node *item)
{
    struct list_node *current_node = *head;
    struct list_node *tmp_node = NULL;

    if(!current_node)
    {
        return NULL;
    }

    if(current_node == item)
    {
        list_pop(head);
        return 0;
    }

    while(current_node->next != item)
    {
        current_node = current_node->next;

        if(!current_node->next)
        {
            return NULL;
        }
    }

    tmp_node = current_node->next;  //node to remove
    current_node->next = tmp_node->next;  //the next of the current node is the next of the one i have to remove
    current_node = tmp_node;  //current node become the node i have to remove
    current_node->next = NULL;

    return current_node;
}
struct string_item *reverse_unit (struct string_item **list, struct string_item **reversed_list)
{
    struct string_item *item_removed = (struct string_item*)list_remove((struct list_node**)&list,(struct list_node*)list_get_tail(list));
    list_append((struct list_node **)&reversed_list, (struct list_node *)string_item_new(item_removed->string));

   return *reversed_list;

}
int list_counter(struct string_item **list)   // sembra giusto ma devo settare counter a -1 se no ne conta 1 in piu'.
{
    int counter = -1;
    struct list_node *current_node = (struct list_node *)&list;
    while (current_node->next != NULL)
    {
        counter++;
        current_node = current_node->next;
    }
    return counter;
}
struct string_item *reverse_complete (struct string_item **list, struct string_item **reversed_list)  //da capire perche' non funziona
{
    struct string_item* item_removed = (struct string_item*)list_remove((struct list_node**)&list,(struct list_node*)list_get_tail(list));

    while(item_removed)
    {
        list_append((struct list_node **)&reversed_list, (struct list_node *)string_item_new(item_removed->string));

        struct list_node *tail = (struct list_node*)list_get_tail(list);

        if(!tail)
        {
            item_removed = NULL;
        }
        else
        {
            item_removed = (struct string_item*)list_remove((struct list_node**)&list,(struct list_node*)list_get_tail(list));
        }
    }
    return *reversed_list;
    
}
int main()
{

    struct string_item *item1 = string_item_new("element 1");
    struct string_item *item2 = string_item_new("element 2");
    struct string_item *item3 = string_item_new("element 3");
    struct string_item *item4 = string_item_new("element 4");


    struct string_item *my_linked_list = NULL;
    // list_append((struct list_node **)&my_linked_list, (struct list_node *)string_item_new("Hello World"));
    // list_append((struct list_node **)&my_linked_list, (struct list_node *)string_item_new("Test001"));
    // list_append((struct list_node **)&my_linked_list, (struct list_node *)string_item_new("Test002"));
    // list_append((struct list_node **)&my_linked_list, (struct list_node *)string_item_new("1"));
    // list_append((struct list_node **)&my_linked_list, (struct list_node *)string_item_new("2"));
    // list_append((struct list_node **)&my_linked_list, (struct list_node *)string_item_new("3"));
    // list_append((struct list_node **)&my_linked_list, (struct list_node *)string_item_new("4"));
    // list_append((struct list_node **)&my_linked_list, (struct list_node *)string_item_new("5"));


    list_append_cast(&my_linked_list,item1);
    list_append_cast(&my_linked_list,item2);
    list_append_cast(&my_linked_list,item3);
    list_append_cast(&my_linked_list,item4);


    int count = list_counter(&my_linked_list);
    printf("%d\n", count);

    struct string_item *reversed = NULL;
    
    struct string_item *string_item = reverse_complete(&my_linked_list, &reversed);
    


    while (string_item)
    {
        printf("%s\n", string_item->string);
        string_item = (struct string_item *)string_item->node.next;
    }
    return 0;
}