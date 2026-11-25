#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

#include <stdio.h>
#include <stdlib.h>

// Definición del registro principal
typedef struct {
    int original_id;
    int value;
} Record;

// Nodo para listas simples, pilas y colas
typedef struct Node {
    Record data;
    struct Node* next;
} Node;

// Nodo para listas doblemente ligadas
typedef struct DoubleNode {
    Record data;
    struct DoubleNode* next;
    struct DoubleNode* prev;
} DoubleNode;

// prototipos
Record* load_and_validate(const char* filename, int* out_count);
Node* append_to_list(Node* head, Record record);
void traverse_list(Node* head, int limit);
Node* remove_from_list(Node* head, int target_id);
void free_list(Node* head);

// prototipos pila
Node* push_stack(Node* top, Record record);
Node* pop_stack(Node* top);
void peek_stack(Node* top);

// prototipos cola
Node* enqueue(Node* rear, Node** front, Record record);
Node* dequeue(Node** front);


// propotipos lista circular
Node* append_to_circular(Node* head, Record record);
void traverse_circular_special(Node* head);
void free_circular(Node* head);

// prototipos lista doblemente ligada
DoubleNode* append_to_double(DoubleNode* head, Record record);
void traverse_double_forward(DoubleNode* head, int limit);
void traverse_double_backward(DoubleNode* head, int limit);
DoubleNode* remove_interior_double(DoubleNode* head, int target_id);
void free_double_list(DoubleNode* head);

#endif