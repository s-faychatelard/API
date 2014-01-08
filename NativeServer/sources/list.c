//
//  list.c
//  NativeServer
//
//  Created by Sylvain Fay-Châtelard, Baptiste Burles on 08/01/14.
//  Copyright (c) 2013 Dviance, Kliplab. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#include "../includes/list.h"

void listInit(List * l)
{
    l->first = NULL;
    l->last = NULL;
    l->size = 0;
}

ListNode* listAddElement(List *l, void *e)
{
    if (l == NULL) return NULL;
    
    ListNode *node = (ListNode*)calloc(1, sizeof(ListNode));
    
    node->next = NULL;
    node->prev = l->last;
    node->data = e;
    
    if (l->last != NULL)
        l->last->next = node;
    
    if (l->first == NULL)
        l->first = node;
    
    l->last = node;
    
    l->size++;
    
    return node;
}

void *listRemoveNode(List *l, ListNode* node)
{
    if (node == NULL) return NULL;
    
    ListNode * prev = node->prev;
    ListNode * next = node->next;
    
    if (prev != NULL)
        prev->next = next;
    else
        l->first = next;
    
    if (next != NULL)
        next->prev = prev;
    else
        l->last = prev;
    
    node->prev = NULL;
    node->next = NULL;
    
    l->size--;
    
    return next;
}

void *listRemoveLastNode(List *l)
{
    ListNode *node = l->last;
    
    if (node == NULL) return NULL;
    
    listRemoveNode(l, l->last);
    
    return node->data;
}

void *listGetElementAt(List* l, int index)
{
    int i=0;
    ListNode *n = l->first;
    while (n != NULL)
    {
        if (i == index)
            return n->data;
        
        n = n->next;
        i++;
    }
    return NULL;
}

void listRemoveElementAt(List* l, int index)
{
    int i=0;
    ListNode *n = l->first;
    while (n != NULL)
    {
        if (i == index)
        {
            listRemoveNode(l, n);
            return;
        }
        
        n = n->next;
        i++;
    }
}
