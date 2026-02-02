#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Book {
    long long isbn;
    char title[100];
    struct Book *left;
    struct Book *right;
};

struct Book *root = NULL;

struct Book* createBook() {
    struct Book *newBook = (struct Book*)malloc(sizeof(struct Book));

    printf("Enter Book Details:\n");

    printf("ISBN Number: ");
    scanf("%lld", &newBook->isbn);

    printf("Book Title: ");
    getchar();
    fgets(newBook->title, sizeof(newBook->title), stdin);
    newBook->title[strcspn(newBook->title, "\n")] = 0;

    newBook->left = NULL;
    newBook->right = NULL;

    return newBook;
}

struct Book* insertBook(struct Book *node, struct Book *newBook) {
    if (node == NULL) {
        printf("Book '%s' with ISBN %lld inserted successfully!\n",
               newBook->title, newBook->isbn);
        return newBook;
    }

    if (newBook->isbn < node->isbn) {
        node->left = insertBook(node->left, newBook);
    } else if (newBook->isbn > node->isbn) {
        node->right = insertBook(node->right, newBook);
    } else {
        printf("Book with ISBN %lld already exists!\n", newBook->isbn);
        free(newBook);
    }

    return node;
}

void insert() {
    struct Book *newBook = createBook();
    root = insertBook(root, newBook);
}

void inorderTraversal(struct Book *node) {
    if (node != NULL) {
        inorderTraversal(node->left);
        printf("ISBN: %-15lld Title: %s\n", node->isbn, node->title);
        inorderTraversal(node->right);
    }
}

void preorderTraversal(struct Book *node) {
    if (node != NULL) {
        printf("ISBN: %-15lld Title: %s\n", node->isbn, node->title);
        preorderTraversal(node->left);
        preorderTraversal(node->right);
    }
}

void postorderTraversal(struct Book *node) {
    if (node != NULL) {
        postorderTraversal(node->left);
        postorderTraversal(node->right);
        printf("ISBN: %-15lld Title: %s\n", node->isbn, node->title);
    }
}

void traverse() {
    if (root == NULL) {
        printf("Library is empty! No books to display.\n");
        return;
    }

    int choice;
    printf("\nSelect Traversal Method:\n");
    printf("1. Inorder (Sorted by ISBN)\n");
    printf("2. Preorder (Root-Left-Right)\n");
    printf("3. Postorder (Left-Right-Root)\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    printf("\n=== LIBRARY BOOK DATABASE ===\n");

    switch (choice) {
        case 1:
            printf("Inorder Traversal (Ascending ISBN order):\n");
            printf("----------------------------------------\n");
            inorderTraversal(root);
            break;
        case 2:
            printf("Preorder Traversal:\n");
            printf("-------------------\n");
            preorderTraversal(root);
            break;
        case 3:
            printf("Postorder Traversal:\n");
            printf("--------------------\n");
            postorderTraversal(root);
            break;
        default:
            printf("Invalid choice! Displaying inorder by default.\n");
            inorderTraversal(root);
    }

    printf("==============================\n");
}

struct Book* searchBook(struct Book *node, long long isbn) {
    if (node == NULL || node->isbn == isbn)
        return node;

    if (isbn < node->isbn)
        return searchBook(node->left, isbn);
    else
        return searchBook(node->right, isbn);
}

void search() {
    long long isbn;
    printf("Enter ISBN number to search: ");
    scanf("%lld", &isbn);

    struct Book *result = searchBook(root, isbn);

    if (result != NULL) {
        printf("\n=== BOOK FOUND ===\n");
        printf("ISBN: %lld\n", result->isbn);
        printf("Title: %s\n", result->title);
        printf("==================\n");
    } else {
        printf("\nBook with ISBN %lld not found in the library!\n", isbn);
    }
}

int countBooks(struct Book *node) {
    if (node == NULL)
        return 0;
    return 1 + countBooks(node->left) + countBooks(node->right);
}

int getHeight(struct Book *node) {
    if (node == NULL)
        return -1;

    int leftHeight = getHeight(node->left);
    int rightHeight = getHeight(node->right);

    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

void displayStatistics() {
    if (root == NULL) {
        printf("Library is empty!\n");
        return;
    }

    printf("\n=== LIBRARY STATISTICS ===\n");
    printf("Total books in library: %d\n", countBooks(root));
    printf("BST height: %d\n", getHeight(root));
    printf("Root book ISBN: %lld\n", root->isbn);
    printf("Root book title: %s\n", root->title);
    printf("===========================\n");
}

void demonstrateBST() {
    printf("\n=== BST PROPERTIES DEMONSTRATION ===\n");
    printf("1. All nodes in left subtree have ISBN < root ISBN\n");
    printf("2. All nodes in right subtree have ISBN > root ISBN\n");
    printf("3. Inorder traversal gives sorted sequence\n");
    printf("4. Search operation has O(log n) average time complexity\n");
    printf("=====================================\n");

    if (root != NULL) {
        printf("\nCurrent BST structure (conceptual):\n");
        printf("Root: %lld (%s)\n", root->isbn, root->title);

        if (root->left != NULL)
            printf("├── Left: %lld (%s)\n", root->left->isbn, root->left->title);

        if (root->right != NULL)
            printf("└── Right: %lld (%s)\n", root->right->isbn, root->right->title);
    }
}

int main() {
    int choice;

    printf("=== LIBRARY BOOK MANAGEMENT SYSTEM ===\n");
    printf("Using Binary Search Tree (BST)\n");

    while (1) {
        printf("\n--- MAIN MENU ---\n");
        printf("1. Insert New Book\n");
        printf("2. Traverse Books (Inorder/Preorder/Postorder)\n");
        printf("3. Search Book by ISBN\n");
        printf("4. Display Library Statistics\n");
        printf("5. Demonstrate BST Properties\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: insert(); break;
            case 2: traverse(); break;
            case 3: search(); break;
            case 4: displayStatistics(); break;
            case 5: demonstrateBST(); break;
            case 6:
                printf("Thank you for using Library Management System!\n");
                return 0;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
}
