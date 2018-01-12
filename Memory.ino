long randNumber;
int Tableau[6];
int Tableau2[6];
int y,z,saisie;
byte flag;

void setup()
  {
      randomSeed(analogRead(0));      
      DDRB  = 0b100000;   /* Port B bits 0 à 4  en entrée  ( Boutons poussoir  ) */
      DDRC  = 0b00011111;   /* Port C bits 0 à 4  en sortie  ( Leds Jaune) */
      DDRD  = 0b00001100;     /* Port D bits 2 et 3  en sortie  ( Led verte et rouge )*/
     }

void loop()
{
  y=0;z=0;
  saisie=0;
  flag=true;
  Tableau[0,0,0,0,0];
  Tableau2[0,0,0,0,0];
  
       PORTD = 0b1000;      /* Bit 3 mis à 1 (Led rouge allumée, Led verte éteinte ) */
       for (int x=0; x<3; x++)
       { PORTC = 0b11111; delay(300); /* les 5 Leds jaune  */
         PORTC = 0; delay(300);       /* clignote 3 fois   */
       }      
  
       
/******* acquisition aléatoire **************/
/* Range dans tableau, un nombre aleatoire et allume la Led correspondante (5 fois ) */
       do
       {          
          randNumber = random(0,5);Tableau[y]= (1<<randNumber); 
          PORTC |= (1<<randNumber);delay(400);
          PORTC &= ~(1<<randNumber);delay(200);
          y++;          
       }
       while(y<5);
                  
 /******** acquisition des 5 saisies **********/       
    do
      {
        while(!PINB);              /* attend l'appuie d'une touche */
        delay(80);                /* tempo anti_rebond du contact */
        saisie=(PINB);
        Tableau2[z]=saisie;      /* numéro de touche dans tableau2 */
        PORTC |= saisie;         /* puis allummage led correspondante */
        while(PINB);delay(50);  /* attendre relachement bouton */
        PORTC &= ~(saisie);              /* extinction led */
        z++;                     
      }
      while(z<5);               /* boucle pour les 5 saisies */
         
      /**************Comparaison **************/
      for (int x=0 ; x<5; x++)    /* vérification égalite de chaque élement du tableau */
      {          if (Tableau[x] != Tableau2[x]) /* si différence mettre Flag à 0 */
                    flag= false;
                         
       }                          
       if (flag)  PORTD =0b0100;  /* Led verte allumée, Led rouge éteinte */
       else { for (int x=0 ; x<4; x++)  /* Si flag = false, led rouge clignote 3 fois*/
                  { PORTD &= ~( PORTD );
                   delay(200);
                   PORTD = 0b1000;
                   delay(200); 
                   }
            }
       delay(500);
       while(!PINB);
}
