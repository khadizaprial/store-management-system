
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Product {
    int productId;
    char name[50];
    double price;
    int quantity;
    struct Product* next;
};

// Function to add a product to the linked list
void addProduct(struct Product** head, int productId, const char* name, double price, int quantity) {
    struct Product* newProduct = (struct Product*)malloc(sizeof(struct Product));
    if (newProduct == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    newProduct->productId = productId;
    strcpy(newProduct->name, name);
    newProduct->price = price;
    newProduct->quantity = quantity;
    newProduct->next = NULL;

    // If the list is empty, make the new product the head
    if (*head == NULL) {
        *head = newProduct;
    } else {
        // Otherwise, add the new product to the end of the list
        struct Product* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newProduct;
    }

    printf("Product added successfully.\n");
}

// Function to display all products in the linked list
void displayProducts(struct Product* head) {
    if (head == NULL) {
        printf("No products to display.\n");
        return;
    }

    printf("Products in the store:\n");
    struct Product* current = head;
    while (current != NULL) {
        printf("Product ID: %d, Name: %s, Price: %.2f, Quantity: %d\n",
               current->productId, current->name, current->price, current->quantity);
        current = current->next;
    }
}

// Function to search for a product by name in the linked list
void searchProduct(struct Product* head, const char* searchName) {
    if (head == NULL) {
        printf("No products to search.\n");
        return;
    }

    struct Product* current = head;
    int found = 0;

    printf("Search results for products with name '%s':\n", searchName);
    while (current != NULL) {
        if (strcmp(current->name, searchName) == 0) {
            printf("Product ID: %d, Name: %s, Price: %.2f, Quantity: %d\n",
                   current->productId, current->name, current->price, current->quantity);
            found = 1;
        }
        current = current->next;
    }

    if (!found) {
        printf("No matching products found.\n");
    }
}

// Function to search for a product by ID in the linked list
struct Product* searchProductById(struct Product* head, int productId) {
    struct Product* current = head;
    while (current != NULL) {
        if (current->productId == productId) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// Function to update product information by ID
void updateProduct(struct Product* head, int updateId) {
    struct Product* current = head;
    while (current != NULL) {
        if (current->productId == updateId) {
            printf("Enter updated information for Product ID %d:\n", updateId);
            printf("Enter Product Name: ");
            scanf("%s", current->name);
            printf("Enter Price: ");
            scanf("%f", &current->price);
            printf("Enter Quantity: ");
            scanf("%d", &current->quantity);
            printf("Product information updated successfully.\n");
            return;
        }
        current = current->next;
    }
    printf("Product with ID %d not found.\n", updateId);
}

// Function to delete a product by ID
void deleteProduct(struct Product** head, int productId) {
    struct Product* current = *head;
    struct Product* prev = NULL;

    while (current != NULL) {
        if (current->productId == productId) {
            if (prev == NULL) {
                // If the product to be deleted is the first in the list
                *head = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            printf("Product with ID %d deleted successfully.\n", productId);
            return;
        }

        prev = current;
        current = current->next;
    }

    printf("Product with ID %d not found.\n", productId);
}

// Function to free the allocated memory for the linked list
void freeList(struct Product* head) {
    while (head != NULL) {
        struct Product* temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    struct Product* store = NULL;
    int choice;

    do {
        printf("\nStore Management System\n");
        printf("1. Add Product\n");
        printf("2. Display Products\n");
        printf("3. Search Product by Name\n");
        printf("4. Search Product by ID\n");
        printf("5. Update Product\n");
        printf("6. Delete Product\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                int productId, quantity;
                char name[50];
                float price;

                printf("Enter Product ID: ");
                scanf("%d", &productId);
                printf("Enter Product Name: ");
                scanf("%s", name);
                printf("Enter Price: ");
                scanf("%f", &price);
                printf("Enter Quantity: ");
                scanf("%d", &quantity);

                addProduct(&store, productId, name, price, quantity);
                break;
            }
            case 2:
                displayProducts(store);
                break;
            case 3: {
                char searchName[50];
                printf("Enter Product Name to search: ");
                scanf("%s", searchName);
                searchProduct(store, searchName);
                break;
            }
            case 4: {
                int searchId;
                printf("Enter Product ID to search: ");
                scanf("%d", &searchId);
                struct Product* foundProduct = searchProductById(store, searchId);
                if (foundProduct != NULL) {
                    printf("\nProduct found:\n");
                    printf("Product ID: %d\n", foundProduct->productId);
                    printf("Name: %s\n", foundProduct->name);
                    printf("Price: %.2f\n", foundProduct->price);
                    printf("Quantity: %d\n", foundProduct->quantity);
                } else {
                    printf("Product not found.\n");
                }
                break;
            }
            case 5: {
                int updateId;
                printf("Enter Product ID to update: ");
                scanf("%d", &updateId);
                updateProduct(store, updateId);
                break;
            }
            case 6: {
                int deleteId;
                printf("Enter Product ID to delete: ");
                scanf("%d", &deleteId);
                deleteProduct(&store, deleteId);
                break;
            }
            case 7:
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    } while (choice != 7);

    // Free allocated memory before exiting
    freeList(store);

    return 0;
}
