#include "estructuras.h"

Record* load_and_validate(const char* filename, int* out_count) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Error: No se pudo abrir '%s'.\n", filename);
        return NULL;
    }

    int count;
    if (fscanf(file, "%d", &count) != 1 || count < 0 || count > 1000000) {
        fprintf(stderr, "Error: Conteo inicial invalido.\n");
        fclose(file);
        return NULL;
    }
    *out_count = count;
    if (count == 0) {
        fclose(file);
        return NULL; 
    }

    Record* array = (Record*)malloc(count * sizeof(Record));
    if (array == NULL) return NULL;

    int value;
    for (int i = 0; i < count; i++) {
        if (fscanf(file, "%d", &value) != 1) {
            free(array);
            fclose(file);
            return NULL;
        }
        array[i].original_id = i;
        array[i].value = value;
    }
    fclose(file);
    return array;
}

Node* append_to_list(Node* head, Record record) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = record;
    new_node->next = NULL;

    if (head == NULL) return new_node;

    Node* current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = new_node;
    return head;
}

void traverse_list(Node* head, int limit) {
    Node* current = head;
    int count = 0;
    while (current != NULL && count < limit) {
        printf("ID: %d | Valor: %d\n", current->data.original_id, current->data.value);
        current = current->next;
        count++;
    }
}

Node* remove_from_list(Node* head, int target_id) {
    if (head == NULL) return NULL;

    if (head->data.original_id == target_id) {
        Node* temp = head;
        head = head->next;
        free(temp);
        printf("Registro con ID %d eliminado.\n", target_id);
        return head;
    }

    Node* current = head;
    while (current->next != NULL && current->next->data.original_id != target_id) {
        current = current->next;
    }

    if (current->next != NULL) {
        Node* temp = current->next;
        current->next = current->next->next;
        free(temp);
        printf("Registro con ID %d eliminado.\n", target_id);
    } else {
        printf("ID %d no encontrado en la lista.\n", target_id);
    }
    return head;
}

void free_list(Node* head) {
    Node* current = head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
}

// implementacion pila lifo
// Las instrucciones piden: Push in arrival order, peek top, pop twice.
Node* push_stack(Node* top, Record record) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = record;
    new_node->next = top; // El nuevo nodo apunta al que antes era el top
    return new_node;      // El nuevo nodo es el nuevo top
}

void peek_stack(Node* top) {
    if (top != NULL) {
        printf("Top de la pila -> ID: %d | Valor: %d\n", top->data.original_id, top->data.value);
    } else {
        printf("La pila esta vacia.\n");
    }
}

Node* pop_stack(Node* top) {
    if (top == NULL) {
        printf("Error: Pila vacia, no se puede hacer pop.\n");
        return NULL;
    }
    Node* temp = top;
    top = top->next;
    printf("Pop ejecutado -> ID sacado: %d\n", temp->data.original_id);
    free(temp);
    return top;
}

// implementacion cola
// Las instrucciones piden: Enqueue arrival order, dequeue until empty, enqueue again.
Node* enqueue(Node* rear, Node** front, Record record) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = record;
    new_node->next = NULL;

    if (rear != NULL) {
        rear->next = new_node;
    }
    if (*front == NULL) {
        *front = new_node;
    }
    return new_node; // retorna el nuevo rear
}

Node* dequeue(Node** front) {
    if (*front == NULL) return NULL;
    
    Node* temp = *front;
    *front = (*front)->next;
    
    printf("Dequeue ejecutado -> ID sacado: %d\n", temp->data.original_id);
    free(temp);
    return *front; // retorna el nuevo front
}

// implementacion lsita ligada circular
Node* append_to_circular(Node* head, Record record) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = record;
    
    if (head == NULL) {
        new_node->next = new_node; // apunta a si mismo
        return new_node;
    }
    
    Node* current = head;
    while (current->next != head) {
        current = current->next;
    }
    current->next = new_node;
    new_node->next = head; // cierra el círculo
    return head;
}

// Instrucción: "Advance through one complete round and then one more step."
void traverse_circular_special(Node* head) {
    if (head == NULL) {
        printf("Lista circular vacia.\n");
        return;
    }
    
    Node* current = head;
    printf("Dando una vuelta completa:\n");
    do {
        printf("ID: %d | Valor: %d\n", current->data.original_id, current->data.value);
        current = current->next;
    } while (current != head);
    
    printf("\nY un paso mas:\n");
    printf("ID: %d | Valor: %d\n", current->data.original_id, current->data.value);
}

void free_circular(Node* head) {
    if (head == NULL) return;
    Node* current = head->next;
    while (current != head) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
    free(head); // libera el head al final
}

// implementacion lista doblemente ligada
DoubleNode* append_to_double(DoubleNode* head, Record record) {
    DoubleNode* new_node = (DoubleNode*)malloc(sizeof(DoubleNode));
    new_node->data = record;
    new_node->next = NULL;
    new_node->prev = NULL;

    if (head == NULL) return new_node;

    DoubleNode* current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = new_node;
    new_node->prev = current; // apunta hacia atrás
    return head;
}

void traverse_double_forward(DoubleNode* head, int limit) {
    DoubleNode* current = head;
    int count = 0;
    while (current != NULL && count < limit) {
        printf("ID: %d | Valor: %d\n", current->data.original_id, current->data.value);
        current = current->next;
        count++;
    }
}

void traverse_double_backward(DoubleNode* head, int limit) {
    if (head == NULL) return;
    DoubleNode* current = head;
    // ir hasta el final
    while (current->next != NULL) {
        current = current->next;
    }
    // recorrer hacia atrás
    int count = 0;
    while (current != NULL && count < limit) {
        printf("ID: %d | Valor: %d\n", current->data.original_id, current->data.value);
        current = current->prev;
        count++;
    }
}

// Instrucción: "Remove an interior node by ID when one exists."
// Un nodo interior es aquel que tiene un nodo antes y un nodo después (no es ni el primero ni el último).
DoubleNode* remove_interior_double(DoubleNode* head, int target_id) {
    if (head == NULL) return NULL;

    DoubleNode* current = head;
    while (current != NULL) {
        if (current->data.original_id == target_id) {
            // verificar si es un nodo interior
            if (current->prev != NULL && current->next != NULL) {
                current->prev->next = current->next;
                current->next->prev = current->prev;
                free(current);
                printf("Nodo INTERIOR con ID %d eliminado correctamente.\n", target_id);
                return head;
            } else {
                printf("El ID %d existe, pero NO es un nodo interior (es el head o el tail).\n", target_id);
                return head;
            }
        }
        current = current->next;
    }
    printf("ID %d no encontrado en la lista doble.\n", target_id);
    return head;
}

void free_double_list(DoubleNode* head) {
    DoubleNode* current = head;
    while (current != NULL) {
        DoubleNode* temp = current;
        current = current->next;
        free(temp);
    }
}