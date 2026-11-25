#include "estructuras.h"

int main() {
    int count = 0;
    Record* master_array = load_and_validate("readings.txt", &count);
    
    if (master_array == NULL) {
        printf("Fallo al inicializar los datos.\n");
        return 1;
    }

    int opcion = -1;
    while (opcion != 0) {
        printf("\nPROYECTO ESTRUCTURAS\n");
        printf("1. Arreglo Dinamico (preview)\n");
        printf("2. Lista Ligada Simple (crear, mostrar y borrar por ID)\n");
        printf("3. Pila / Stack (push, peek, pop x2)\n");
        printf("4. Cola / Queue (enqueue, dequeue total, enqueue de nuevo)\n");
        
        printf("5. Lista Circular (vuelta completa + 1 paso)\n");
        printf("6. Lista Doble (recorrer y borrar nodo interior)\n");
        printf("0. Salir\n");
        printf("Selecciona: ");
        
        if (scanf("%d", &opcion) != 1) {
            printf("Entrada invalida.\n");
            while(getchar() != '\n'); 
            continue;
        }

        switch (opcion) {
            case 1:
                printf("\nPreview del Arreglo Original:\n");
                int limit = count < 5 ? count : 5;
                for (int i = 0; i < limit; i++) {
                    printf("ID: %d | Valor: %d\n", master_array[i].original_id, master_array[i].value);
                }
                break;
                
            case 2: {
                printf("\n-- Operando sobre Lista Ligada Simple --\n");
                Node* head = NULL;
                
                for (int i = 0; i < count; i++) {
                    head = append_to_list(head, master_array[i]);
                }
                
                printf("Lista creada. Mostrando primeros 5 elementos:\n");
                traverse_list(head, 5);
                
                int target;
                printf("\nIngresa el ID que deseas eliminar de esta lista temporal: ");
                scanf("%d", &target);
                
                head = remove_from_list(head, target);
                
                printf("\nMostrando lista despues de eliminacion:\n");
                traverse_list(head, 5);
                
                free_list(head);
                printf("\nMemoria de la lista temporal liberada.\n");
                break;
            }
            
            case 3: {
                printf("\n-- Operando sobre Pila Ligada (Stack) --\n");
                Node* top = NULL;
                
                // Push records in arrival order
                for (int i = 0; i < count; i++) {
                    top = push_stack(top, master_array[i]);
                }
                
                // Peek at the top
                peek_stack(top);
                
                // Pop twice when possible
                top = pop_stack(top);
                top = pop_stack(top);
                
                free_list(top); // Usamos free_list porque los nodos son de la misma estructura
                printf("\nMemoria de la pila temporal liberada.\n");
                break;
            }
            case 4: {
                printf("\n-- Operando sobre Cola Ligada (Queue) --\n");
                Node* front = NULL;
                Node* rear = NULL;
                
                // Enqueue records in arrival order
                for (int i = 0; i < count; i++) {
                    rear = enqueue(rear, &front, master_array[i]);
                }
                
                // Dequeue until empty
                printf("Vaciando la cola:\n");
                while (front != NULL) {
                    dequeue(&front);
                }
                rear = NULL; // Aseguramos que rear también sea NULL si la cola está vacía
                
                // Enqueue a record again (metemos el primer registro solo por cumplir la instrucción)
                printf("\nEncolando un registro nuevamente:\n");
                if (count > 0) {
                    rear = enqueue(rear, &front, master_array[0]);
                    printf("Encolado ID: %d\n", front->data.original_id);
                }
                
                free_list(front);
                printf("\nMemoria de la cola temporal liberada.\n");
                break;
            }
            
            case 5: {
                printf("\n-- Operando sobre Lista Circular --\n");
                Node* head_circ = NULL;
                for (int i = 0; i < count; i++) {
                    head_circ = append_to_circular(head_circ, master_array[i]);
                }
                
                traverse_circular_special(head_circ);
                
                free_circular(head_circ);
                printf("\nMemoria de la lista circular liberada.\n");
                break;
            }
            case 6: {
                printf("\n-- Operando sobre Lista Doblemente Ligada --\n");
                DoubleNode* head_double = NULL;
                for (int i = 0; i < count; i++) {
                    head_double = append_to_double(head_double, master_array[i]);
                }
                
                printf("Recorrido hacia ADELANTE (limitado a 5):\n");
                traverse_double_forward(head_double, 5);
                
                printf("\nRecorrido hacia ATRAS (limitado a 5):\n");
                traverse_double_backward(head_double, 5);
                
                int target;
                printf("\nIngresa el ID de un nodo INTERIOR que desees eliminar: ");
                scanf("%d", &target);
                
                head_double = remove_interior_double(head_double, target);
                
                printf("\nLista despues de la operacion (hacia adelante):\n");
                traverse_double_forward(head_double, 5);
                
                free_double_list(head_double);
                printf("\nMemoria de la lista doble liberada.\n");
                break;
            }
            case 0:
                printf("Saliendo...\n");
                break;
            default:
                printf("Opcion invalida\n");
        }
    }

    free(master_array);
    return 0;
}