#include <LiquidCrystal.h>

byte arrowDown[8]={ B00100,B00100,B00100,B00100,B00100,B10101,B01110,B00100}; // Seta p/ baixo

// *** INPUT SETTINGS ***

#define pinPulse 2
//or #define pinPulse 1

//**********************************

// *** LCD KEYPAD SHIELD SETTINGS ***

#define pinButtons A0
#define pinBackLight 10
              // RS,EN,D4,D5,D6,D7
LiquidCrystal lcd(8,9,4,5,6,7);

//**********************************

// ******* BUTTON SETTINGS *********

#define btnNONE   0
#define btnSELECT 1
#define btnLEFT   2
#define btnUP     3
#define btnDOWN   4
#define btnRIGHT  5
#define tempBounce 50

unsigned long delayBtn;
int estBtnAnt = btnNONE;
//**********************************

// ***** DIAGNOSIS SETTINGS ********

#define TL 15 // Qtd de diagnosticos 
int count = 0; //Variável contadora de pulsos

int codeError[TL]   = {0,12,13,14,15,16,22,28,30,33,39,41,44,46,50}; //Codigo do erro

String msgError[TL] = {"ERRO NAO IDENTIFICADO",
"Nenhum sinal recebido do sensor de posicao do virabrequim",
"Sensor da pressao do ar de admissao:circuito aberto ou curto circuito detectado",
"Sensor de pressao do ar de admissao defeituoso",
"Sensor de posicao do acelerador TPS aberto ou curto-circuito",
"TPS esta preso agarrado",
"Sensor da temperatura do ar de admissao - circuito aberto ou curto circuito detectado",
"Sensor da temperatura do motor - circuito aberto ou curto circuito detectado"
"A motocicleta caiu",
"Circuito aberto detectado no enrolamento primario da bobina de ignicao",
"Circuito aberto ou curto circuito detectado no injetor de combustivel",
"Sensor de inclinacao com o circuito aberto ou curto circuito",
"Erro detectado durante a leitura ou gravacao E2PROM",
"Fornecimento de energia para o sistema FI nao esta normal",
"Memoria da ECU defeituosa",
};//Msg sintoma do erro

//**********************************

//Config tela inicial
void initScreen()
{
  lcd.clear();
  lcd.setCursor(2,0);
  lcd.print("PIOVAN MOTOS");
}

void init()
{
  lcd.begin(16, 2);
  lcd.createChar(1,arrowDown);
  pinMode(pinBackLight, OUTPUT);
  digitalWrite(pinBackLight, HIGH);
  
  pinMode(pinPulse, INPUT);
  count = 0;
  initScreen();
}

int opButtons(int btnValue)
{
  if ((btnValue < 800) && (btnValue >= 600)) 
     return btnSELECT;
   else if ((btnValue < 600) && (btnValue >= 400)) 
     return btnLEFT;
   else if ((btnValue < 400) && (btnValue >= 200)) 
     return btnUP;
   else if ((btnValue < 200) && (btnValue >= 60))
     return btnDOWN;
   else if  (btnValue < 60)
     return btnRIGHT;
   else 
     return btnNONE;
}

void actionBtn(int btn)
{
  if ((millis() - delayBtn) > tempBounce)
   if ((btn == btnNONE) && (estBtnAnt != btnNONE)) 
   {
      //******* ACTION HERE ( PRINT OR OTHER FUNCTION )  ******
      delayBtn = millis();
   }
  estBtnAnt = btn;
}

int searchCodeError(int cod)
{
  int i=0;
  while(i < TL && cod < codeError[i]) 
    i++;
    
  if(cod == codeError[i])
    return i;
  return 0;  
}

void printError(int i)
{
  int btn;
  String msg = msgError[i];
  String line1,line2;
  lcd.clear();
  for(int i = 0 ; i < msg.length(); i++)
  {
    if(line1.length() < 16)
      line1 += msg.charAt(i);
    else
      if(line2.length() < 14)
        line2 += msg.charAt(i);  
        
    if(line1.length() < 16 && line2.length() < 14 || i >= msg.length())
    {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(line1);

      lcd.setCursor(0,1);
      lcd.print(line2);

      if(i < msg.length())
      {
        lcd.setCursor(15,1);
        lcd.write(1);
  
        line1 = line2 = "";
        delay(30000);
        btn = analogRead(pinButtons);
        while(btn == btnNONE)
          btn = analogRead(pinButtons);
        actionBtn(opButtons(btn));
        btn = btnNONE;
      }
    }
  }
}

void readError()
{
  
}

void setup() 
{
  init();
}

void loop() 
{
  readError();
}
 
 
 
