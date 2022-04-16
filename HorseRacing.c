#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>

#define USERNAME "eric"
#define NPM "1082"
#define CLASS "A"
#define SIZE(x) (sizeof(x) / sizeof((x)[0]))
#define YELLOW "\033[1;33m"
#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define CYAN "\033[1;36m"

const int defaultRaceLength = 500 / 10;

struct horse
{
  char name[100];
  int speed;
  int id;
  float position;
  int winPercentage;
};

struct horse horses[3];
int choosenHorse = -1;

int login(char name[], char userNpm[]);
int generateHorseSpeed();
int generateHorseId();
int generateHorseWinPercentage();
void makeColor(char color[]);
void resetColor();
void printHorses();
void inputHorses();
void printRaceBoard(int horseNum);
void raceStart();
void betting();
void resetHorsesPosition();
void racingMenu();
void printBonus();

int main(void)
{
  int option;
  char name[20];
  char password[4];

  printf("1. Login\n");
  printf("2. Exit\n");
  printf("Your input: ");
  scanf("%d", &option);
  while (option <= 2)
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
          makeColor(GREEN);
          printf("Login success!\n");
          resetColor();
          racingMenu();
          break;
        }
        if (isLogin != 0)
        {
          makeColor(RED);
          printf("Login failed!\n");
          resetColor();
          break;
        }
      }
      break;
    case 2:
      printBonus();
      exit(0);
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

int generateHorseWinPercentage()
{
  return rand() % (100 + 1 - 20) + 20;
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
      printf("Horse win percentage: %d%%\n", horses[i].winPercentage);
    }
    if (choosenHorse != -1)
    {
      makeColor(GREEN);
      printf("You choose horse %d: %s\n", choosenHorse + 1, horses[choosenHorse].name);
      resetColor();
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
    horses[i].winPercentage = generateHorseWinPercentage();
  }
}

void printRaceBoard(int horseNum)
{
  for (int i = 0; i < defaultRaceLength; i++)
  {
    int loc = horses[horseNum].position;
    if (i == loc)
    {
      makeColor(CYAN);
      printf("%s", horses[horseNum].name);
      resetColor();
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
      horses[number].position += (float)horses[number].speed / 10;
      printRaceBoard(number);
      if (horses[number].position >= ((float)defaultRaceLength))
      {
        continueon = false;
        if (choosenHorse >= 0)
        {
          struct horse yourHorse;
          strcpy(yourHorse.name, horses[choosenHorse].name);
          struct horse winHorse;
          strcpy(winHorse.name, horses[number].name);
          int isYourHorseWin = strcmp(yourHorse.name, winHorse.name);
          if (isYourHorseWin == 0)
          {
            makeColor(GREEN);
            printf("Your horse %s is the winner\n", yourHorse.name);
            resetColor();
          }
          else
          {
            makeColor(RED);
            printf("Your horse %s is lose from %s\n", yourHorse.name, winHorse.name);
            resetColor();
          }
        }
        else
        {
          makeColor(GREEN);
          printf("Horse %s is the winner\n", horses[number].name);
          resetColor();
        }
      }
    }
    sleep(1);
  }
}

void betting()
{
  int n;
  printHorses();
  printf("Choose your horse: ");
  scanf("%d", &n);
  printf("n value: %d\n", n);
  printf("choosen before: %d\n", choosenHorse);
  choosenHorse = n - 1;
  printf("choosen after: %d\n", choosenHorse);
}

void resetHorsesPosition()
{
  for (int i = 0; i < 3; i++)
  {
    horses[i].position = 0;
  }
}

void racingMenu()
{
  int option;
  printf("1. Input horses data\n");
  printf("2. Show horses data\n");
  printf("3. Racing simulation\n");
  printf("4. Bet the horse\n");
  printf("5. Back to main menu\n");
  printf("Enter your option: ");
  scanf("%d", &option);
  while (option <= 4)
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
        makeColor(RED);
        printf("Horses data are empty, please input the data first.\n");
        resetColor();
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
        makeColor(RED);
        printf("Horses data are empty, please input the data first.\n");
        resetColor();
        break;
      }
      else
      {
        resetHorsesPosition();
        raceStart();
        break;
      }
    }
    else if (option == 4)
    {
      int isEmpty = strcmp(horses[0].name, "");
      if (isEmpty == 0)
      {
        makeColor(RED);
        printf("Horses data are empty, please input the data first.\n");
        resetColor();
        break;
      }
      else
      {
        betting();
        resetHorsesPosition();
        raceStart();
        break;
      }
    }
  }
}

void printBonus()
{
  makeColor(GREEN);
  printf("Name: %s\n", USERNAME);
  printf("NPM: 210711082\n");
  printf("Class: %s\n", CLASS);
  printf("Bonuses has been taken: 1, 2, 3, All of it!\n");
  resetColor();
}