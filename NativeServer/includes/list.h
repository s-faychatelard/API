//
//  list.h
//  NativeServer
//
//  Created by Sylvain Fay-Châtelard, Baptiste Burles on 08/01/14.
//  Copyright (c) 2013 Dviance, Kliplab. All rights reserved.
//

#ifndef NativeServer_list_h
#define NativeServer_list_h

#ifdef __cplusplus
extern "C" {
#endif
    
    /* how to use list
     
     ListNode *n = list->first;
     while (n != NULL)
     {
     void * data = n->data;
     
     ...
     
     
     n = n->next;
     }
     */
    
    typedef struct _list_node_
    {
        struct _list_node_ *next;
        struct _list_node_ *prev;
        void *data;
    } ListNode;
    
    typedef struct _list_
    {
        ListNode *first;
        ListNode *last;
        int size;
    } List;
    
    extern void listInit(List * l);
    
    extern ListNode * listAddElement(List *l, void *e);
    
    extern void * listRemoveNode(List *l, ListNode* node);
    
    extern void * listRemoveLastNode(List *l);
    
    /** Use with caution */
    extern void * listGetElementAt(List* l, int index);
    
    extern void listRemoveElementAt(List* l, int index);
    
#ifdef __cplusplus
}
#endif

#endif
