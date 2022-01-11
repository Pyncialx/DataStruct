#pragma once

struct list_node
{
    struct list_node *next;
};

struct string_item
{
    struct list_node node;
    const char *string;
};

struct list_node *list_get_tail(struct list_node **head);
struct list_node *list_append(struct list_node **head, struct list_node *item);
struct list_node *list_pop(struct list_node **head);

struct list_node *list_remove(struct list_node **head, struct list_node *item);



struct string_item *string_item_new(const char *string);

#define doubleptr_list(obj) (struct list_node **)obj
#define singleptr_list(obj) (struct list_node *)obj
#define list_append_cast(list,item_to_append) list_append(doubleptr_list(list),singleptr_list(item_to_append))
#define list_remove_cast(list,item_to_remove) list_remove(doubleptr_list(list),singleptr_list(item_to_remove))



