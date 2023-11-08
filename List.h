struct node {
    int row;
    int col;
    int data;
    struct node* next;
};


void init(struct node** head);
void append(struct node** head, int row, int col, int data);
void display(struct node* head);
void free_list(struct node* head);
int** read_file(char s[], int* row, int* col);
struct node* addsparsematrix(struct node* head1, struct node* head2);
struct node* subtractsparsematrix(struct node* head1, struct node* head2);
void to_file(struct node* head, char s[], int row, int col);
