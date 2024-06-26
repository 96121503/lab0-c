#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"
#include "queue.h"
/* Notice: sometimes, Cppcheck would find the potential NULL pointer bugs,
 * but some of them cannot occur. You can suppress them by adding the
 * following line.
 *   cppcheck-suppress nullPointer
 */


/* Create an empty queue */
struct list_head *q_new()
{
    struct list_head *head = malloc(sizeof(struct list_head));
    if (head)
        INIT_LIST_HEAD(head);
    return head;
}

/* Free all storage used by queue */
void q_free(struct list_head *head)
{
    if (!head)
        return;

    element_t *entry, *safe;
    list_for_each_entry_safe (entry, safe, head, list) {
        list_del(&entry->list);
        q_release_element(entry);
    }
    free(head);
}

/* Insert an element at head of queue */
bool q_insert_head(struct list_head *head, char *s)
{
    element_t *node = malloc(sizeof(element_t));
    if (!head || !node)
        return false;
    int str_size = (strlen(s) + 1) * sizeof(char);
    node->value = malloc(str_size);
    if (!node->value) {
        free(node);
        return false;
    }
    memcpy(node->value, s, str_size - 1);
    node->value[str_size - 1] = '\0';
    list_add(&node->list, head);
    return true;
}

/* Insert an element at tail of queue */
bool q_insert_tail(struct list_head *head, char *s)
{
    element_t *node = malloc(sizeof(element_t));
    if (!head || !node)
        return false;
    int str_size = (strlen(s) + 1) * sizeof(char);
    node->value = malloc(str_size);
    if (!node->value) {
        free(node);
        return false;
    }
    memcpy(node->value, s, str_size - 1);
    node->value[str_size - 1] = '\0';
    list_add_tail(&node->list, head);
    return true;
}

/* Remove an element from head of queue */
element_t *q_remove_head(struct list_head *head, char *sp, size_t bufsize)
{
    if (!head || list_empty(head))
        return NULL;
    element_t *remove_node = list_entry(head->next, element_t, list);
    if (bufsize) {
        strncpy(sp, remove_node->value, bufsize - 1);
        sp[bufsize - 1] = '\0';
    }
    list_del(&remove_node->list);
    return remove_node;
}

/* Remove an element from tail of queue */
element_t *q_remove_tail(struct list_head *head, char *sp, size_t bufsize)
{
    if (!head || list_empty(head))
        return NULL;
    element_t *remove_node = list_entry(head->prev, element_t, list);
    if (bufsize) {
        strncpy(sp, remove_node->value, bufsize - 1);
        sp[bufsize - 1] = '\0';
    }
    list_del(&remove_node->list);
    return remove_node;
}

/* Return number of elements in queue */
int q_size(struct list_head *head)
{
    if (!head) {
        return 0;
    }
    int len = 0;
    struct list_head *node;

    list_for_each (node, head)
        len++;
    return len;
}

/* Delete the middle node in queue */
bool q_delete_mid(struct list_head *head)
{
    if (!head || list_empty(head))
        return false;
    struct list_head *left = head->next, *right = head->prev;
    if (left == right)
        return false;
    while (left != right && left->next != right) {
        right = right->prev;
        if (left == right || left->next == right)
            break;
    }
    return true;
}
/* Delete all nodes that have duplicate string */
bool q_delete_dup(struct list_head *head)
{
    if (!head)
        return false;
    if (list_empty(head) || list_is_singular(head))
        return true;
    element_t *node, *safe;
    bool flag = 0;
    list_for_each_entry_safe (node, safe, head, list) {
        char *str = list_entry(node->list.next, element_t, list)->value;
        if (node->list.next != head && !strcmp(str, node->value)) {
            list_del(&node->list);
            q_release_element(node);
            flag = 1;
        } else if (flag) {
            list_del(&node->list);
            q_release_element(node);
            flag = 0;
        }
    }
    return true;
}

/* Swap every two adjacent nodes */
void q_swap(struct list_head *head)
{
    struct list_head *node1, *node2, *safe;
    for (node1 = head->next, node2 = node1->next, safe = node2->next;
         node1 != head && node2 != head;
         node1 = safe, node2 = node1->next, safe = node2->next) {
        list_del(node1);
        list_add(node1, node2);
    }
}

/* Reverse elements in queue */
void q_reverse(struct list_head *head) {}

/* Reverse the nodes of the list k at a time */
void q_reverseK(struct list_head *head, int k)
{
    // https://leetcode.com/problems/reverse-nodes-in-k-group/
}

/* Sort elements of queue in ascending/descending order */
void q_sort(struct list_head *head, bool descend) {}

/* Remove every node which has a node with a strictly less value anywhere to
 * the right side of it */
int q_ascend(struct list_head *head)
{
    // https://leetcode.com/problems/remove-nodes-from-linked-list/
    return 0;
}

/* Remove every node which has a node with a strictly greater value anywhere to
 * the right side of it */
int q_descend(struct list_head *head)
{
    // https://leetcode.com/problems/remove-nodes-from-linked-list/
    return 0;
}

/* Merge all the queues into one sorted queue, which is in ascending/descending
 * order */
int q_merge(struct list_head *head, bool descend)
{
    // https://leetcode.com/problems/merge-k-sorted-lists/
    return 0;
}
