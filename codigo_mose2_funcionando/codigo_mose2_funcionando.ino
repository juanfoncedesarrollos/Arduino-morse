#include <Wire.h>
#include <LiquidCrystal.h>



//Se configuran los componentes: Lcd, pulsador, led.
LiquidCrystal lcd(12,11,30,31,32,33);

unsigned long duracion,t1,t2;
String code = ""; 

int i = 0;

void setup()
{
 pinMode(8, INPUT);
 pinMode(4, OUTPUT);
 Serial.begin(9600);
 lcd.begin(16,2);
 lcd.clear();
 lcd.setCursor(0,0);
 lcd.print(" GRUPO 10 :)");
 lcd.setCursor(0,1);
 lcd.print(" CODIGO MORSE");
 delay(3000);
 lcd.clear();
} 
void loop()
{
SiguientePulso:
  while (digitalRead(8) == HIGH) {}
  t1 = millis(); //tiempo boton presionado
  digitalWrite(4, HIGH); //LED enciende
  while (digitalRead(8) == LOW) {}
  t2 = millis(); //tiempo de boton sin accionar
  digitalWrite(4, LOW); //LED apagado
  duracion = t2 - t1; //calcular el tiempo de presion del boton
  if (duracion > 100)
  {
    code += pulso(); 
    while ((millis() - t2) < 800)
    {
      if (digitalRead(8) == LOW)
      {
        goto SiguientePulso;
      }
    }
    decodificar();   
  } 
}
char pulso()
{
  if (duracion < 700 && duracion > 100)
  {
    Serial.print(".");
    return '.'; //si el boton se presiona por menosde 0.6 segundos, es un punto
  }
  else if (duracion > 700)
  {
    Serial.print("-");
    return '-'; //si el boton se presiona por mas de 0.6 segundos, es una raya
  }
} 
void decodificar()
{
  static String letras[] = 
  {
    ".-", "-...", "-.-.", "-..", ".", "..-.", 
    "--.", "....", "..", ".---", "-.-", ".-..", 
    "--", "-.", "---", ".--.", "--.-", ".-.", 
    "...", "-", "..-", "...-", ".--", "-..-", 
    "-.--", "--..", "E"
  };
  int x = 0;
  int y = 0;
  if (code == "......")
  {
    lcd.clear();
    x = -1;
    y = 0;
    pantalla();
    delay(500);
    //Print(".");
    Serial.print(".");
  }
  else if (code == ".....")
  {
    Print(" ");
    Serial.print(" "); //Espacio para separar letras
  }
  else
  {
    while (letras[i] != "E")
    {
      if (letras[i] == code)
      {
        Print((char)('A' + i));
        Serial.print(char('A' + i));
        break;
      }
      i++; 
    }
    if (letras[i] == "E")
    {
      //Print("");
      Serial.println("Error"); //si la entrada no coincide con una letra de la matriz emitir error
    } 
  }
  code = "";   
}

void Print(String &s)
{
  for (int i = 0; i < s.length(); i++) 
  {
  pantalla();
  lcd.print(s[i]);
  }
}
void Print(char s)
{
 pantalla();
 lcd.print(s);
}
void Print(char *s)
{
  for (int i = 0; i < strlen(s); i++)
  {
    pantalla();
    lcd.print(s[i]);
  }
}

int y = 0, x = 0; 
void pantalla()
{
  lcd.setCursor(x, y);
  x++;
  if (x >= 16)
  {
    x = 0;
    y++;
  }
  if (y >= 2)
  {
    lcd.clear();
    x = y = 0;
  }
} 

//void setup() {
  // put your setup code here, to run once:

//}

//void loop() {
  // put your main code here, to run repeatedly:

//}
