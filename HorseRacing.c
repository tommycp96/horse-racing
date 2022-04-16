#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SIZE(x) (sizeof(x) / sizeof((x)[0]));

struct horse {
  char name[100];
  int speed;
  int id;
};

char username[20] = "eric";
char npm[4] = "0987";
struct horse horses[3];

int login(char name[20], char userNpm[4]);
int generateHorseSpeed();
int generateHorseId();

void printHorses() {
  for (int i = 0; i < 3; i++) {
    strcpy(horses[i].name, "horse");
    horses[i].speed = generateHorseSpeed();
    horses[i].id = generateHorseId();
    printf("horse name: %s\n", horses[i].name);
    printf("horse speed: %d\n", horses[i].speed);
    printf("horse id: %d\n", horses[i].id);
  }
}

void inputHorses() {
  int len = (int) SIZE(horses);
  printf("len: %d\n", len);
  for (int i = 0; i < len; i++) {
    
  }
}

void racingMenu() {
  int option;
  printf("1. Input horses data\n");
  printf("2. Show horses data\n");
  printf("3. Racing simulation\n");
  printf("4. Back to main menu\n");
  printf("Enter your option: ");
  scanf("%d", &option);
  while(option != 4) {
    switch (option) {
    case 1:
      inputHorses();
      break;
    case 2:
      printHorses();
      break;

    default:
      break;
    }
  }
}

int main(void) {
  int option;
  char name[20];
  char password[4];

  printf("1. Login\n");
  printf("2. Exit\n");
  printf("Your input: ");
  scanf("%d", &option);
  while(option != 2) {
    switch (option) {
      case 1:
        printf("Username: ");
        scanf("%s", name);
        printf("Password: ");
        scanf("%s", password);
        int isLogin = login(name, password);
        while (isLogin >= 0) {
          if (isLogin == 0) {
            printf("Login success!\n");
            racingMenu();
            break;
          } 
          if (isLogin != 0) {
            printf("Login failed!\n");
            break;
          }
        }
        break;
      case 2:
        return 0;
        break;
      default:
        printf("1. Login\n");
        printf("2. Exit\n");
        printf("Your input: ");
        scanf("%d", &option);
        break;
    }
  }
  return 0;
}

int login(char name[20], char userNpm[4]) {
  int isUsername = strcmp(name, username);
  int isNpm = strcmp(userNpm, npm);
  return (isUsername == 0 && isNpm == 0) ? 0 : 1;
}

int generateHorseSpeed() {
  return rand() % (50 + 1 - 20) + 20;
}

int generateHorseId() {
  return rand() % (500 + 1 - 1) + 1;
}