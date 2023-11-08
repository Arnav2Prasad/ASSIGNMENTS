#include "List.h"

void init(struct node** head) {
    (*head) = NULL;
}


void append(struct node** head, int row, int col, int data) {
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    if (temp == NULL) {
        //printf("Memory allocation failed.\n");
        return;
    }
    temp->row = row;
    temp->col = col;
    temp->data = data;
    temp->next = NULL;
    if ((*head) == NULL) {
        (*head) = temp;
        return;
    } else {
        struct node* curr = (*head);
        while (curr->next != NULL) {
            curr = curr->next;
        }
        curr->next = temp;
    }
}

void display(struct node* head) {
    struct node* curr = head;
    while (curr != NULL) {
        printf("(%d, %d, %d)-->", curr->row, curr->col, curr->data);
        curr = curr->next;
    }
    printf("NULL\n");
}


void free_list(struct node* head) {
    struct node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int** read_file(char s[], int* row, int* col) {
    FILE* file_pointer;
    int rows, cols;

    // Open file in read mode
    file_pointer = fopen(s, "r");
    if (file_pointer == NULL) {
        printf("File could not be opened.\n");
        return NULL;
    }

    // Read the number of rows and columns from the file
    fscanf(file_pointer, "%d %d", &rows, &cols);

    // Allocate memory for the matrix
    int** matrix = (int**)malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int*)malloc(cols * sizeof(int));
        for (int j = 0; j < cols; j++) {
            fscanf(file_pointer, "%d", &matrix[i][j]);
        }
    }

    *row = rows;
    *col = cols;

    // Close the file
    fclose(file_pointer);
    return matrix;
}

struct node* addsparsematrix(struct node* head1, struct node* head2){
        if (head1==NULL && head2==NULL){
                return NULL;
        }
        if (head1==NULL){
                return head2;
        }
        if (head2==NULL){
                return head1;
        }
        struct node* p = head1;
        struct node* q=head2;
        struct node* ans;
        init(&ans);

        while (p&&q){
                if (p->row==q->row){
                        if (p->col==q->col){
                                append(&ans,p->row,p->col,p->data+q->data);
                                p=p->next;
                                q=q->next;
                        }
                        else if (p->col>q->col){
                                append(&ans,q->row,q->col,q->data);
                                q=q->next;
                        }
                        else{
                                append(&ans,p->row,p->col,p->data);
                                p=p->next;
                        }
                }
                else{
                        if (p->row > q->row){
                                append(&ans,q->row,q->col,q->data);
                                q=q->next;
                        }
                        else{
                                append(&ans,p->row,p->col,p->data);
                                p=p->next;
                        }
                }
        }
        while (p){
                append(&ans,p->row,p->col,p->data);
                p=p->next;
        }
        while (q){
                append(&ans,q->row,q->col,q->data);
                q=q->next;
        }
        return ans;
}

struct node* subtractsparsematrix(struct node* head1, struct node* head2){
        if (head1==NULL && head2==NULL){
                return NULL;
        }

        if (head2==NULL){
                return head1;
        }
        struct node* p = head1;
        struct node* q=head2;
        struct node* ans;
        init(&ans);

        if (head1==NULL){
                while (q!=NULL){
                        append(&ans,q->row,q->col,-(q->data));
                        q=q->next;
                }
                return ans;
        }

        while (p&&q){
                if (p->row==q->row){
                        if (p->col==q->col){
                                append(&ans,p->row,p->col,p->data-q->data);
                                p=p->next;
                                q=q->next;
                        }
                        else if (p->col>q->col){
                                append(&ans,q->row,q->col,-(q->data));
                                q=q->next;
                        }
                        else{
                                append(&ans,p->row,p->col,p->data);
                                p=p->next;
                        }
                }
                else{
                        if (p->row > q->row){
                                append(&ans,q->row,q->col,-(q->data));
                                q=q->next;
                        }
                        else{
                                append(&ans,p->row,p->col,p->data);
                                p=p->next;
                        }
                }
        }
        while (p){
                append(&ans,p->row,p->col,p->data);
                p=p->next;
        }
        while (q){
                append(&ans,q->row,q->col,-(q->data));
                q=q->next;
        }
      return ans;
}

void to_file(struct node* head, char s[], int row, int col) {
    FILE* fp = fopen(s, "w");
    if (fp == NULL) {
        printf("Error opening the file.\n");
        return;
    }

    fprintf(fp, "%d %d\n", row, col);

    struct node* curr = head;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (curr != NULL && curr->row == i && curr->col == j) {
                fprintf(fp, "%d ", curr->data);
                curr = curr->next;
            } else {
                fprintf(fp, "0 ");
            }
        }
        fprintf(fp, "\n");
    }

    fclose(fp);
}


