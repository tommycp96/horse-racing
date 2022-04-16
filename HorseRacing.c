#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>

#define USERNAME "eric"
#define NPM "0987"
#define SIZE(x) (sizeof(x) / sizeof((x)[0]))
#define YELLOW "\033[1;33m"

const int defaultRaceLength = 500 / 10;

struct horse
{
  char name[100];
  int speed;
  int id;
  int position;
};

struct horse horses[3];

int login(char name[], char userNpm[]);
int generateHorseSpeed();
int generateHorseId();
void makeColor(char color[]);
void resetColor();
void printHorses();
void inputHorses();
void printRaceBoard(int horseNum);
void raceStart();
void racingMenu();

int main(void)
{
  int option;
  char name[20];
  char password[4];

  printf("1. Login\n");
  printf("2. Exit\n");
  printf("Your input: ");
  scanf("%d", &option);
  while (option != 2)
  {
    switch (option)
    {
    case 1:
      printf("Username: ");
      scanf("%s", name);
      printf("Password: ");
      scanf("%s", password);
      int isLogin = login(name, password);
      while (isLogin >= 0)
      {
        if (isLogin == 0)
        {
          printf("Login success!\n");
          racingMenu();
          break;
        }
        if (isLogin != 0)
        {
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

int login(char name[], char userNpm[])
{
  int isUsername = strcmp(name, USERNAME);
  int isNpm = strcmp(userNpm, NPM);
  return (isUsername == 0 && isNpm == 0) ? 0 : 1;
}

int generateHorseSpeed()
{
  return rand() % (50 + 1 - 20) + 20;
}

int generateHorseId()
{
  return rand() % (500 + 1 - 1) + 1;
}

void makeColor(char color[])
{
  printf("%s", color);
}

void resetColor()
{
  printf("\033[0m");
}

void printHorses()
{
  int len = (int)SIZE(horses);
  if (len != 0)
  {
    for (int i = 0; i < len; i++)
    {
      makeColor(YELLOW);
      printf("Horse data %d\n", i + 1);
      resetColor();
      printf("Horse name: %s\n", horses[i].name);
      printf("Horse speed: %d(m/s)\n", horses[i].speed);
      printf("Horse id: %d\n", horses[i].id);
    }
  }
}

void inputHorses()
{
  int len = (int)SIZE(horses);
  char horseName[100];
  for (int i = 0; i < len; i++)
  {
    printf("Input horse data %d:\n", i + 1);
    printf("Horse name: ");
    scanf("%s", horseName);
    strcpy(horses[i].name, horseName);
    horses[i].speed = generateHorseSpeed();
    horses[i].id = generateHorseId();
    horses[i].position = 0;
  }
}

void printRaceBoard(int horseNum)
{
  for (int i = 0; i < defaultRaceLength; i++)
  {
    int loc = horses[horseNum].position;
    if (i == loc)
    {
      printf("%s", horses[horseNum].name);
    }
    else
    {
      printf(".");
    }
  }
  printf("\n");
}

void raceStart()
{
  bool continueon = true;
  for (int n = 0; n < 3; n++)
  {
    printRaceBoard(n);
  }

  while (continueon)
  {
    system("clear");
    printHorses();
    for (int number = 0; number < 3; number++)
    {
      horses[number].position += (horses[number].speed / 10);
      printRaceBoard(number);
      if (horses[number].position >= (defaultRaceLength))
      {
        continueon = false;
        if (horses[0].position < horses[number].position)
        {
          horses[0].position = horses[number].position;
          printf("Horse %s is the winner\n", horses[number].name);
        }
      }
    }
    sleep(1);
  }
}

void racingMenu()
{
  int option;
  printf("1. Input horses data\n");
  printf("2. Show horses data\n");
  printf("3. Racing simulation\n");
  printf("4. Back to main menu\n");
  printf("Enter your option: ");
  scanf("%d", &option);
  while (option <= 3)
  {
    if (option == 1)
    {
      inputHorses();
      break;
    }
    else if (option == 2)
    {
      int isEmpty = strcmp(horses[0].name, "");
      if (isEmpty == 0)
      {
        printf("Horses data are empty, please input the data first.\n");
        break;
      }
      else
      {
        printHorses();
        break;
      }
    }
    else if (option == 3)
    {
      int isEmpty = strcmp(horses[0].name, "");
      if (isEmpty == 0)
      {
        printf("Horses data are empty, please input the data first.\n");
        break;
      }
      else
      {
        raceStart();
        break;
      }
    }
  }
}