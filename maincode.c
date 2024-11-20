#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char *generate_password(int length) {
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()_+";
    const char randset[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789,.-#'?!";
    char *password = malloc((length + 1) * sizeof(char));
    if (!password) return NULL;

    srand(time(NULL)); 

    for (int i = 0; i < length / 4; ++i) {
        int index = rand() % (sizeof(randset) - 1);
        password[i] = randset[index];
    }

    for (int i = length / 4; i < length; ++i) {
        int index = rand() % (sizeof(charset) - 1);
        password[i] = charset[index];
    }

    for (int i = length - 1; i > 0; --i) {
        int j = rand() % (i + 1);
        char temp = password[i];
        password[i] = password[j];
        password[j] = temp;
    }

    password[length] = '\0';
    return password;
}

int main() {
    int length;
    char proceed, save_password;
    char *password;

    do {
        printf("Enter the length of the password: ");
        scanf("%d", &length);

        if (length < 6) {
            printf("The password will be weak and easy to decode. Do you wanna risk your privacy just because you have a bad memory and cant remember passwords? (y/n): ");
            scanf(" %c", &proceed);
            if (proceed == 'n' || proceed == 'N') {
                continue; 
            }
        }
        else if (length > 16) {
            printf("Password length cannot exceed 16 characters. Please choose a shorter length.\n");
            continue; 
        }

        break; 
    } while (1);

    password = generate_password(length);
    if (password) {
        printf("Generated Password: %s\n", password);
    } else {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Do you have trouble remembering passwords? (y/n): ");
    scanf(" %c", &proceed);
    if (proceed == 'y' || proceed == 'Y') {
        printf("Would you like us to remember this password for you? (y/n): ");
        scanf(" %c", &save_password);
        if (save_password == 'y' || save_password == 'Y') {
            FILE *fp;
            fp = fopen("W:\\C\\C projects class\\output\\saved passwords\\saved_password.txt", "w");
            if (fp == NULL) {
                printf("Error opening file for writing.\n");
            } else {
                fprintf(fp, "Saved Password: %s\n", password);
                fclose(fp);
                printf("Password saved to W:\\C\\C projects class\\output\\saved passwords\\saved_password.txt\n");
            }
        }
    }

    free(password);
    return 0;
}
