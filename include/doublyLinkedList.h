#pragma once

struct doubly_list_node
{
    struct doubly_list_node *prev;
    struct doubly_list_node *next;
};

struct doubly_string_item
{
    struct doubly_list_node node;
    const char *string;
};

struct doubly_list_node *list_get_tail(struct doubly_list_node **head);
struct doubly_list_node *list_append(struct doubly_list_node **head, struct doubly_list_node *item);
struct doubly_list_node *list_pop(struct doubly_list_node **head);

struct doubly_list_node *list_remove(struct doubly_list_node **head, struct doubly_list_node *item);
int  *list_insert_afther(struct doubly_list_node *item, struct doubly_list_node *item_to_insert);
int  *list_insert_before(struct doubly_list_node **head, struct doubly_list_node *item, struct doubly_list_node *item_to_insert);


struct doubly_string_item *string_item_new(const char *string);

#define doubleptr_doubly_list(obj) (struct doubly_list_node **)obj
#define singleptr_doubly_list(obj) (struct doubly_list_node *)obj
#define list_append_cast_doubly(list,item_to_append) list_append(doubleptr_doubly_list(list),singleptr_doubly_list(item_to_append))
#define list_remove_cast_doubly(list,item_to_remove) list_remove(doubleptr_doubly_list(list),singleptr_doubly_list(item_to_remove))
#define list_insert_afther_doubly(position_to_insert,item_to_insert) list_insert_afther(singleptr_doubly_list(position_to_insert),singleptr_doubly_list(item_to_insert))
#define list_insert_before_doubly(head,position_to_insert,item_to_insert) list_insert_before(doubleptr_doubly_list(head),singleptr_doubly_list(position_to_insert),singleptr_doubly_list(item_to_insert))



