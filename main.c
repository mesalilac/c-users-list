#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define COMMAND_L(NAME) strcmp(NAME, line) == 0
#define COMMAND_LS(SHORT, LONG)                                                \
    strcmp(SHORT, line) == 0 || strcmp(LONG, line) == 0

typedef struct
{
    char *name;
    int age;
    char *email;
} User;

typedef struct
{
    User *list;
    int count;
} Users;

void users_push(Users *users, User user)
{
    users->list[users->count] = user;
    users->count++;
}

/// Remove user by index in list
///
/// returns `true` if element is removed false if index is out of bound
bool users_remove(Users *users, int index)
{
    if (index < 0 || index > users->count)
        return false;

    // int i = index - 1;
    for (int i = index; i < users->count; ++i)
        users->list[i] = users->list[i + 1];

    users->count -= 1;

    return true;
}

int main()
{
    bool is_running = true;
    char *indent    = "    ";

    Users users = {
        .list  = malloc(100 * sizeof(User)),
        .count = 0,
    };

    User user1 = {.name = "mike", .age = 34, .email = "example@email.com"};
    users.list[users.count] = user1;
    users.count++;

    while (is_running)
    {
        char *line = malloc(100 * sizeof(char));
        printf("> ");
        scanf("%s", line);

        if (COMMAND_LS("l", "list"))
        {
            if (users.count == 0)
                printf("List is empty\n");

            for (int i = 0; i < users.count; ++i)
            {
                printf(
                    "[%i]: name: %s, age: %i, email: %s\n",
                    i,
                    users.list[i].name,
                    users.list[i].age,
                    users.list[i].email
                );
            }
        }
        else if (COMMAND_LS("a", "add"))
        {
            User user = {
                .name  = malloc(100 * sizeof(char)),
                .email = malloc(100 * sizeof(char)),
                .age   = 0,
            };

            printf("name: ");
            scanf("%s", user.name);
            printf("email: ");
            scanf("%s", user.email);
            printf("age: ");
            scanf("%i", &user.age);

            users_push(&users, user);
        }
        else if (COMMAND_LS("r", "remove"))
        {
            int index = 0;
            printf("index: ");
            scanf("%i", &index);

            if (users_remove(&users, index) == true)
                printf("User removed\n");
            else
                printf("User does not exists\n");
        }
        else if (COMMAND_LS("e", "edit"))
        {
        }
        else if (COMMAND_LS("q", "quit"))
            is_running = false;
        else if (COMMAND_LS("h", "help"))
        {
            printf("Commands:\n");
            printf("------------------------\n");
            printf("%sl, list\n", indent);
            printf("%sa, add\n", indent);
            printf("%sr, remove\n", indent);
            printf("%se, edit\n", indent);
            printf("%sh, help\n", indent);
            printf("%sq, quit\n", indent);
        }

        free(line);
    }

    free(users.list);
}
