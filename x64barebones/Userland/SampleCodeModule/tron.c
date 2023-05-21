#include <commands.h>
#include <functions.h>
#include <syscalls.h>
#include <color.h>

#define LEFT -1
#define UP -2
#define RIGHT 1
#define DOWN 2
#define HEIGHT 768
#define WIDTH 1024

static char positions[HEIGHT/4][WIDTH/4] = {{0}}; //

void setInitialPositions(int * x1, int * y1, int * x2, int * y2, int * playerOneDirection, int * playerTwoDirection);
void parsePositions(char scancode, int * playerOneDirection, int * playerTwoDirection);
void setNewDirection(int * currentPosition, int newPosition);
void moveCharacter(int currentPosition, int * x, int * y);
void resetPositionsArray();

void tron() {
  clearScreen();

  printf("Welcome to Tron! player 1 (green color) will use the keys WASD to move while player 2 (white color) will use the arrows keys\n\n\n");

  printf("Press the key 'b' to begin\n");

  while(getChar() != 'b') {
    printf("Press the key 'b' to begin\n");
  }

  clearScreen();
  sys_clear_buffer();  // limpiamos el buffer para que las letras previamente tocadas no influyan en el juego

  int playerOneDirection = RIGHT;
  int playerTwoDirection = LEFT;
  int x1 = WIDTH/4, x2 = (WIDTH*3)/4;
  int y1 = HEIGHT/2, y2 = HEIGHT/2;
  char isPlaying = 1;
  char newDirection = 0;
  int won;

  while (isPlaying){
    newDirection = sys_check_buffer();
    parsePositions(newDirection, &playerOneDirection, &playerTwoDirection);  // leemos el buffer y interpretamos la direccion a partir de la tecla presionada

    sys_holder(1); // bajamos la velocidad en la cual se pintan las lineas

    positions[y1/4][x1/4] = 1; //al atravesar el punto, marcamos esa posicion para que termine el juego si volvemos a pasar
    positions[y2/4][x2/4] = 1;

    sys_draw_rect(x1,y1,4,4,green); 
    sys_draw_rect(x2,y2,4,4,white);
    moveCharacter(playerOneDirection, &x1, &y1);
    moveCharacter(playerTwoDirection, &x2, &y2);

    if(positions[y1/4][x1/4] == 1 || x1 <= 0 || x1 >= WIDTH || y1 <= 0 || y1 >= HEIGHT) {
      won = 2; 
      isPlaying = 0;
    }

    if(positions[y2/4][x2/4] == 1 || x2 <= 0 || x2 >= WIDTH || y2 <= 0 || y2 >= HEIGHT) {
      if(positions[y1/4][x1/4] == 1) { //si perdieron ambos al mismo tiempo
        won = 0;
      } else {
        won = 1;
      }
      isPlaying = 0;
    }
  }
  
  sys_beep(440);
  sys_holder(6);
  sys_stop();
  clearScreen();

  if(won == 0) {
    printf("Both players have lost, press the key 'c' to continue\n");
  } else {
    printf("Player %d has won, press the key 'c' to continue\n", won);
  }

  while(getChar() != 'c') { //esperamos a que se presione la tecla c para continuar
    ;
  }


  sys_clear_buffer();
  resetPositionsArray(); //reiniciamos la matriz para poder volver a jugar
  clearScreen();
}

void resetPositionsArray() {
  for(int i = 0 ; i < HEIGHT/4 ; i++) {
    for(int j = 0; j < WIDTH/4 ; j++) {
      positions[i][j] = 0;
    }
  }
}

void parsePositions(char scancode, int * playerOneDirection, int * playerTwoDirection) {
  switch (scancode) {
    case 0x11: //w
      setNewDirection(playerOneDirection, UP);
      break;
    case 0x1E: //a
      setNewDirection(playerOneDirection, LEFT);
      break;
    case 0x1F: //s
      setNewDirection(playerOneDirection, DOWN);
      break;
    case 0x20: //d
      setNewDirection(playerOneDirection, RIGHT);
      break;
    case 0x48: //flecha para arriba
      setNewDirection(playerTwoDirection, UP);
      break;
    case 0x4B: //flecha para la izquierda
      setNewDirection(playerTwoDirection, LEFT);
      break;
    case 0x50: // flecha para la izquierda
      setNewDirection(playerTwoDirection, DOWN);
      break;
    case 0x4D: //flecha para la derecha
      setNewDirection(playerTwoDirection, RIGHT);
      break;
    default:
      break;
  }
}

void setNewDirection(int * currentDirection, int newDirection) {
  if(*currentDirection + newDirection == 0) { //Es para que cuando va a la dirección contraria no haga nada
      return;
  }
  *currentDirection = newDirection;
}

void moveCharacter(int currentDirection, int * x, int * y) { //movemos en la direccion ya determinada
    if (currentDirection == RIGHT) {
        *x += 4;
    } else if (currentDirection == LEFT) {
        *x -= 4;
    } else if (currentDirection == DOWN) {
        *y += 4;
    } else {
        *y -= 4;
    }
}
