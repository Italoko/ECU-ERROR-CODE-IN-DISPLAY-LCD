#include <LiquidCrystal.h>

                  //Pinos de conexão LCD
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); 

//definição do pino de entrada
#define input 13
//definição em ms bounce do btn
#define bounce 50

/*
    TABELA DE ERROS
    INDICE  = QUANTIDADE DE PULSOS
*/
char *tabError[] = 
{
  "ERROR 01", 
  "ERROR 02", 
  "ERROR 03",                   
  "ERROR 04", 
  "ERROR 05", 
  "ERROR 06"
};

//Variável contadora de pulsos
int count;

//Config Botão
bool stateBtn = false;
bool stateBtnAnt = false;
unsigned long delayBtn;

//Config tela inicial
void initScreen()
{
  lcd.clear();
  lcd.setCursor(2,0);
  lcd.print("PIOVAN MOTOS");
}

void printError(int err)
{
  lcd.clear();
  lcd.print(tabError[err]);
  delay(2500);
  count = 0 ;
  initScreen();
}

void setup() 
{
  //Config pino de entrada
  pinMode(input, INPUT_PULLUP);
  
  //Config LCD DYSPLAY (16COL X 2LIN)
  lcd.begin(16, 2);
  
  count = 0;
  initScreen();
}

void loop() 
{
  stateBtn = !digitalRead(input);
  if ((millis() - delayBtn) > bounce) 
  {
      if (stateBtn && !stateBtnAnt) 
      {
          count++;
          if (count > 3) err = count;
          delayBtn = millis();
      }
      else if (!stateBtn && stateBtnAnt) delayBtn = millis();
  }
  stateBtnAnt = stateBtn;
  if(count > 1)
    printError(err);
}
 
 
 
