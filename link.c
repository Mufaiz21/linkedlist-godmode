#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};


struct Node* create_node(int data);
void insert_head(struct Node **head, int data);
void insert_tail(struct Node **head, int data);
void insert_at_position(struct Node **head, int data, int pos);
void delete_head(struct Node **head);
void delete_tail(struct Node **head);
void delete_value(struct Node **head, int value);
void print_list(struct Node *head);
int get_size(struct Node *head);
struct Node* reverse_list(struct Node *head);
int detect_cycle(struct Node *head);
void free_list(struct Node *head);



int main() {
    struct Node *head = NULL;

    insert_head(&head, 10);
    insert_head(&head, 20);
    insert_tail(&head, 30);
    insert_tail(&head, 40);
    insert_at_position(&head, 25, 3);

    printf("Initial List: ");
    print_list(head);

    delete_head(&head);
    printf("After deleting head: ");
    print_list(head);

    delete_tail(&head);
    printf("After deleting tail: ");
    print_list(head);

    delete_value(&head, 25);
    printf("After deleting num 25: ");
    print_list(head);

    printf("Size of list: %d\n", get_size(head));

    head = reverse_list(head);
    printf("Reversed list: ");
    print_list(head);

    printf("Cycle present or not: %s\n", detect_cycle(head) ? "YES" : "NO");

    free_list(head);

    return 0;
}




struct Node* create_node(int data) {
    struct Node *new_node = malloc(sizeof(struct Node));
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

void insert_head(struct Node **head, int data) {
    struct Node *new_node = create_node(data);
    new_node->next = *head;
    *head = new_node;
}

void insert_tail(struct Node **head, int data) {
    struct Node *new_node = create_node(data);

    if (*head == NULL) {
        *head = new_node;
        return;
    }

    struct Node *temp = *head;
    while (temp->next != NULL)
        temp = temp->next;

    temp->next = new_node;
}

void insert_at_position(struct Node **head, int data, int pos) {
    if (pos == 1) {
        insert_head(head, data);
        return;
    }

    struct Node *new_node = create_node(data);
    struct Node *temp = *head;

    for (int i = 1; i < pos - 1 && temp != NULL; i++)
        temp = temp->next;

    if (temp == NULL) {
        printf("Position out of range\n");
        free(new_node);
        return;
    }

    new_node->next = temp->next;
    temp->next = new_node;
}

void delete_head(struct Node **head) {
    if (*head == NULL) return;

    struct Node *temp = *head;
    *head = (*head)->next;
    free(temp);
}

void delete_tail(struct Node **head) {
    if (*head == NULL) return;

    if ((*head)->next == NULL) {
        free(*head);
        *head = NULL;
        return;
    }

    struct Node *temp = *head;
    while (temp->next->next != NULL)
        temp = temp->next;

    free(temp->next);
    temp->next = NULL;
}

void delete_value(struct Node **head, int value) {
    if (*head == NULL) return;

    if ((*head)->data == value) {
        delete_head(head);
        return;
    }

    struct Node *temp = *head;
    while (temp->next != NULL && temp->next->data != value)
        temp = temp->next;

    if (temp->next == NULL) {
        printf("Value %d not found\n", value);
        return;
    }

    struct Node *to_delete = temp->next;
    temp->next = temp->next->next;
    free(to_delete);
}

int get_size(struct Node *head) {
    int count = 0;
    while (head != NULL) {
        count++;
        head = head->next;
    }
    return count;
}

struct Node* reverse_list(struct Node *head) {
    struct Node *prev = NULL;
    struct Node *current = head;

    while (current != NULL) {
        struct Node *next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    return prev;
}

int detect_cycle(struct Node *head) {
    struct Node *slow = head;
    struct Node *fast = head;

    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;

        if (slow == fast)
            return 1; 
    }
    return 0; 
}

void print_list(struct Node *head) {
    while (head != NULL) {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

void free_list(struct Node *head) {
    while (head != NULL) {
        struct Node *temp = head;
        head = head->next;
        free(temp);
    }
}
