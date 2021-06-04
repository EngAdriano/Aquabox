//-----------------------------------------------------------------------------
// Titulo: Firmware do sistema de caixas d'água
// Microcontrolador: PIC16F876A-I/SP
// Frequencia: Fclock = 4MHZ
// Compilador: MikroC Ver 7.2
// Data: 26/10/2019
// Autor: Eng. José Adriano Filho
// Cliente: Valderi Felipe
// Versão Firmware: 2.1.0
//-----------------------------------------------------------------------------
// ----  Mapeamento de Hardware  ----

// Configuração dos pinos do LCD
sbit LCD_RS at RB2_bit;
sbit LCD_EN at RB3_bit;
sbit LCD_D7 at RB7_bit;
sbit LCD_D6 at RB6_bit;
sbit LCD_D5 at RB5_bit;
sbit LCD_D4 at RB4_bit;

// Configuração da direção dos pinos do LCD
sbit LCD_RS_Direction at TRISB2_bit;
sbit LCD_EN_Direction at TRISB3_bit;
sbit LCD_D7_Direction at TRISB7_bit;
sbit LCD_D6_Direction at TRISB6_bit;
sbit LCD_D5_Direction at TRISB5_bit;
sbit LCD_D4_Direction at TRISB4_bit;

// Definições utilizadas
#define auto            RB1_bit
#define valvula1        RA1_bit
#define valvula2        RA2_bit
#define valvula3        RA3_bit
#define bomba           RA5_bit
#define caixa1_Vazia    RC0_bit
#define caixa1_Cheia    RC1_bit
#define caixa2_Vazia    RC2_bit
#define caixa2_Cheia    RC3_bit
#define caixa3_Vazia    RC4_bit
#define caixa3_Cheia    RC5_bit
#define habilita_V      RA0_bit
#define habilita_C      RA4_bit
#define habilita_H      RB0_bit

//Definição de booleanos - Mapeamento de binário sob uma var short
unsigned short FlagA;
#define  caixa1_L    FlagA.B0
#define  caixa1_H    FlagA.B1
#define  caixa2_L    FlagA.B2
#define  caixa2_H    FlagA.B3
#define  caixa3_L    FlagA.B4
#define  caixa3_H    FlagA.B5
#define  modo        FlagA.B6
#define  statusBomba FlagA.B7

unsigned short FlagB;
#define  enable_V    FlagB.B0
#define  enable_C    FlagB.B1
#define  enable_H    FlagB.B2

//===========================================================================
//  ----  Protótipo das Funções  ----
void habilitaCaixa();
void encherCaixa();
void modoManual();  //Não está sendo utilizada
void relogio(int lin, int col);
void delay_segundos(int valor);
void texto_lcd(int lin, int col, char txt[]);
void sensores();
void erroVazao(char caixa);
void erroSesoresFechados(char caixa);
void mostraErro();
void transmite();
void atualizaPay();
void atualizaVariaveisPay();
void enviaParaEsp();
void ligaManual();
void limpaErroVazao();

//Protótipo das Mensagens
void cxValderi(int lin, int col);
void cxCristiano(int lin, int col);
void cxHenrique(int lin, int col);
void cxProcessando(int lin, int col);
void cxTempo(int lin, int col);
void aquabox(int lin, int col);
void sejaBemVindo(int lin, int col);
void falha(int lin, int col);
void msgsensores(int lin, int col);

//===========================================================================
//  ----  Variáveis Globais  ----
static char payload[] = "1000000000000000200000000000000030000000000000000000\n";
char habilita_caixa = 0x00;
char contadorSensor = 0x00;
char segundos       = 0x00;
char minutos        = 0x00;
char horas          = 0x00;
char clk_cont       = 0x00;
char intervaloTX    = 0x00;
char temp_envio     = 0x00;
unsigned short tempoErroV[12];
unsigned short tempoErroC[12];
unsigned short tempoErroH[12];
char  erro_V        = 0x00;
char  erro_C        = 0x00;
char  erro_H        = 0x00;
char ligado         = 0;
char minutosVazao   = 0;

//Variáveis para atualizar o payload
char statusVPay        = '0';
char erroVpay          = '0';
char statusOnOffVpay   = '0';
char statusCPay        = '0';
char erroCpay          = '0';
char statusOnOffCpay   = '0';
char statusHPay        = '0';
char erroHpay          = '0';
char statusOnOffHpay   = '0';
char statusModoPay     = '0';


//===========================================================================
//  ----  Função de Interrupção

void interrupt()
{
  //Timer2
  if (TMR2IF_bit){
    TMR2IF_bit     = 0;                      //Limpa flag de int timer2

    contadorSensor++;
    
    if(auto == 0x01) modo = 0x01;
    else             modo = 0x00;
    
    if(habilita_V == 1) enable_V = 0x01;
    else                enable_V = 0x00;
    if(habilita_C == 1) enable_C = 0x01;
    else                enable_C = 0x00;
    if(habilita_H == 1) enable_H = 0x01;
    else                enable_H = 0x00;
    
    if(modo)                                   //Modo automático
    {                                          //sim...
       if(contadorSensor >= 3)                 //Já passou 30ms
       {                                       //sim...
          if (~caixa1_Vazia) caixa1_L = 0x00;  //Caixa vazia? Se sim...
          else               caixa1_L = 0x01;  //Se não...
          if (~caixa1_Cheia) caixa1_H = 0x00;  //Caixa não cheia? Se sim...
          else               caixa1_H = 0x01;  //Se não...
          
          if (~caixa2_Vazia) caixa2_L = 0x00;  //Caixa vazia? Se sim...
          else               caixa2_L = 0x01;  //Se não
          if (~caixa2_Cheia) caixa2_H = 0x00;  //Caixa não cheia? Se sim...
          else               caixa2_H = 0x01;  //Se não
          
          if (~caixa3_Vazia) caixa3_L = 0x00;  //Caixa vazia? Se sim...
           else              caixa3_L = 0x01;  //Se não...
          if (~caixa3_Cheia) caixa3_H = 0x00;  //Caixa não cheia? Se sim...
          else               caixa3_H = 0x01;  //Se não...
          
          contadorSensor = 0x00;
       }//fim de contador
    }//Fim de modo
    else 
    {
       //bomba             = 0x00;          //Desliga bomba
       contadorSensor    = 0x00;
       statusBomba       = 0x00;
    }//Fim de else modo
  }//Fim de teste da flag TMR0IF_bit interrupção do Timer0
  
  if (TMR1IF_bit){
      TMR1IF_bit = 0;
      TMR1H         = 0x0B;
      TMR1L         = 0xDC;
      
      asm clrwdt;                       //Limpa watchdog
      
      clk_cont++;
      intervaloTX++;
      
      if(clk_cont == 0x02)
      {
         clk_cont = 0x00;
         
         segundos++;
         temp_envio++;
         
         if(segundos > 59)
         {
            segundos = 0x00;
            minutos++;
            
            minutosVazao++;     //Variavel para zerar erro vazão
            if(minutosVazao > 59)
            {
               minutosVazao = 0x00;
            }
            
            if(minutos > 59)
            {
               minutos = 0x00;
               horas++;
               if(horas > 23)
               {
                 horas = 0x00;
               }//Fim do if horas
            }//Fim do if minutos
         }//Fim do if segundos
         
      }//Fim do if clk_cont
  }//Fim de teste da flag TMR1IF_bit interrupção do Timer1
}//Fim da interrupt

//===========================================================================
//  ---- Função de Inicialização  ----

void setup()
{
  CMCON          = 0x07;                  //Desativa os camparadores
  ADCON1         = 0x06;                  //Todas os pinos digitais
  
  //Watchdog timer - Por isso não uso Timer0
  //Prescaler 1:64; Desabilita resistores de pull-up internos
  OPTION_REG     = 0x8E;
  
  //Timer1
  //Prescaler 1:8; TMR1 Preload = 3036; Tempo Atual de interrupções: 500 ms
  T1CON          = 0x31;
  TMR1IF_bit     = 0x00;
  TMR1H          = 0x0B;
  TMR1L          = 0xDC;
  TMR1IE_bit     = 0x01;
  INTCON         = 0xC0;
  
  //Timer2
  //Prescaler 1:4; Postscaler 1:10; TMR2 Preload = 250; Tempo = 10,01 ms
  T2CON          = 0x4D;
  PR2            = 250;
  TMR2IE_bit     = 1;
  
  //Configurações dos Ports

  TRISA          = 0x11;                  //Como saída
  TRISC          = 0xBF;                  //PortC como entrada e tx como saída

  PORTA          = 0x11;                  //0b1111 1111

  modo           = 0x01;                  //Inicia no modo manual
  statusBomba    = 0x00;               //bomba: ligada = 1, deslidaga = 0
  
  //Inicialização das variáveis de erro
  
  erro_V         = 0x00;
  erro_C         = 0x00;
  erro_H         = 0x00;
  
}//Fim do setup

//===========================================================================
//  ----  Função Principal

void main() {

  setup();                          // Configuração inicial do sistema
  asm clrwdt;                       //Limpa watchdog
  
  Lcd_Init();                        // Inicializa o LCD
  Lcd_Cmd(_LCD_CLEAR);               // Limpa o display
  Lcd_Cmd(_LCD_CURSOR_OFF);          // Desliga o cursor
  aquabox(1, 5);
  sejaBemVindo(2, 2);
  
  segundos = 0x00;                   //Inicializando cronômetro
  minutos  = 0x00;
  horas    = 0x00;
  minutosVazao = 0x00;
  delay_segundos(2);                  //Delay de 2s
  Lcd_Cmd(_LCD_CLEAR);               //Limpa o display
  
  UART1_Init(9600);               // Initialize UART module at 9600 bps
  Delay_ms(100);
  
  while(1)
  {
    aquabox(1, 1);
    falha(2,2);
    relogio(1,9);                         //Chama rotina relógio
    limpaErroVazao();
    erroSesoresFechados(1);               //Checa caixa 1
    erroSesoresFechados(2);               //Checa caixa 2
    erroSesoresFechados(3);               //Checa caixa 3
    mostraErro();                         //Mostra erros durante o processo

    enviaParaEsp();

    if(modo == 0x01)
    {
      habilitaCaixa();
      encherCaixa();
    }else
    {
      //modoManual();
      sensores();
    }//Fim do else if modo
    
  }//Fim do while
}//Fim do main

//===========================================================================
//  ----  Desenvolvimento das Funções  ----

void enviaParaEsp()
{
  atualizaVariaveisPay();
  atualizaPay();
  
  if(intervaloTX > 3)  //10 segundos para enviar o payload
    {
       transmite();
       intervaloTX = 0;                          //teste de transmissão
    }
}

void transmite()
{
  UART1_Write_Text(payload);
  UART1_Write(10);
  UART1_Write(13);
}

void atualizaVariaveisPay()
{
  //Status das caixas
  //Caixa Valderi
  if((caixa1_L == 1) && (caixa1_H == 0))
  {
    statusVPay = '0';
  }

  if((caixa1_L == 0) && (caixa1_H == 1))
  {
       statusVPay = '1';
  }

  if((caixa1_L == 1) && (caixa1_H == 1))
  {
         statusVPay = '2';
  }
  if((statusBomba == 1) && (habilita_caixa == 1 ))
  {
           statusVPay = '3';
  }

  //Caixa Cristiano
  if((caixa2_L == 1) && (caixa2_H == 0))
  {
    statusCPay = '0';
  }

  if((caixa2_L == 0) && (caixa2_H == 1))
  {
    statusCPay = '1';
  }
  if((caixa2_L == 1) && (caixa2_H == 1))
  {
    statusCPay = '2';
  }
  if((statusBomba == 1) && (habilita_caixa == 2 ))
  {
    statusCPay = '3';
  }
  //Caixa Henrique
  if((caixa3_L == 1) && (caixa3_H == 0))
  {
    statusHPay = '0';
  }
  if((caixa3_L == 0) && (caixa3_H == 1))
  {
    statusHPay = '1';
  }
  if((caixa3_L == 1) && (caixa3_H == 1))
  {
    statusHPay = '2';
  }
  if((statusBomba == 1) && (habilita_caixa == 3 ))
  {
    statusHPay = '3';
  }
  
  // Erro da caixa
  //Erro Caixa Valderi
  if(erro_V == 0)
  {
     erroVpay = '0';
  }
  else
  {
     if(erro_V == 1)
     {
       erroVpay = '2';
     }
     else
     {
       erroVpay = '1';
     }
  }
  
 //Erro Caixa Cristiano
  if(erro_C == 0)
  {
     erroCpay = '0';
  }
  else
  {
     if(erro_C == 1)
     {
       erroCpay = '2';
     }
     else
     {
       erroCpay = '1';
     }
  }
  
  //Erro Caixa Henrique
  if(erro_H == 0)
  {
     erroHpay = '0';
  }
  else
  {
     if(erro_H == 1)
     {
       erroHpay = '2';
     }
     else
     {
       erroHpay = '1';
     }
  }

  // StatusOnOff da caixa
  //Chave On/Off Caixa Valderi
  if(enable_V == 1)
  {
     statusOnOffVpay = '0';
  }
  else
  {
     statusOnOffVpay = '1';
  }
  
  //Chave On/Off Caixa Cristiano
  if(enable_C == 1)
  {
     statusOnOffCpay = '0';
  }
  else
  {
     statusOnOffCpay = '1';
  }
  
  //Chave On/Off Caixa Henrique
  if(enable_H == 1)
  {
     statusOnOffHpay = '0';
  }
  else
  {
     statusOnOffHpay = '1';
  }

   // StatusModo da caixa
  if(modo == 1)
  {
     statusModoPay = '0';
  }
  else
  {
     statusModoPay = '1';
  }
}

void atualizaPay()
{
  payload[1] = statusVPay;
  payload[14] = erroVpay;
  payload[15] = statusOnOffVpay;
  payload[17] = statusCPay;
  payload[30] = erroCpay;
  payload[31] = statusOnOffCpay;
  payload[33] = statusHPay;
  payload[46] = erroHpay;
  payload[47] = statusOnOffHpay;
  payload[48] = statusModoPay;
}

void habilitaCaixa()
{
  if (enable_V == 0x01 && erro_V == 0x00 && caixa1_L == 0x00 && caixa1_H == 0x01)
  {
     habilita_caixa = 1;
  }
  else
  {
     if (enable_C == 0x01 && erro_C == 0x00 && caixa2_L == 0x00 && caixa2_H == 0x01)
     {
        habilita_caixa = 2;
     }
     else
     {
        if (enable_H == 0x01 && erro_H == 0x00 && caixa3_L == 0x00 && caixa3_H == 0x01)
        {
           habilita_caixa = 3;
        }
        else
        {
            habilita_caixa = 0;
        }
     }
  }
}

void encherCaixa()
{
  switch (habilita_caixa)
  {
    case 1:
    {
       if(statusBomba == 0x00)
          {
            
            Lcd_Init();                        // Inicializa o LCD
            Lcd_Cmd(_LCD_CLEAR);               // Limpa o display
            Lcd_Cmd(_LCD_CURSOR_OFF);          // Desliga o cursor
            //Lcd_Cmd(_LCD_CLEAR);            // Limpa o display
            cxProcessando(1, 4);
            cxValderi(2,4);

            delay_segundos(1);              //Delay de 1 segundo
            valvula1        = 0x01;         //Liga válvula da caixa 1
            delay_segundos(3);              //delay de 3 segundos
            bomba           = 0x01;         //Liga a bomba
            statusBomba     = 0x01;         //Altera status da bomba para 1

            Lcd_Cmd(_LCD_CLEAR);               // Limpa o display
            cxValderi(1,4);
            cxTempo(2, 1);

            segundos = 0x00;
            minutos  = 0x00;
            horas    = 0x00;

            while(statusBomba)
            {
               relogio(2,9);                   //Chama rotina relógio
               
               if(caixa1_L == 0x00)
               {
                  tempoErroV[0] = (segundos/10) + 48; //dezena seg
                  tempoErroV[1] = (segundos%10) + 48; //unidade seg
                  tempoErroV[2] = (minutos/10) + 48;  //dezena min
                  tempoErroV[3] = (minutos%10) + 48;  //unidade min
                  tempoErroV[4] = (horas/10) + 48;    //dezena hor
                  tempoErroV[5] = (horas%10) + 48;    //unidade hor
                  
                  payload[2] = tempoErroV[4];  //dezena hor
                  payload[3] = tempoErroV[5];  //unidade hor
                  payload[4] = tempoErroV[2];  //dezena min
                  payload[5] = tempoErroV[3];  //unidade min
                  payload[6] = tempoErroV[0];  //dezena seg
                  payload[7] = tempoErroV[1];  //unidade seg
                  
               }
               
               //if(caixa1_H == 0x00)
               //{
                  tempoErroV[6] = (segundos/10) + 48; //dezena seg
                  tempoErroV[7] = (segundos%10) + 48; //unidade seg
                  tempoErroV[8] = (minutos/10) + 48;  //dezena min
                  tempoErroV[9] = (minutos%10) + 48;  //unidade min
                  tempoErroV[10] = (horas/10) + 48;   //dezena hor
                  tempoErroV[11] = (horas%10) + 48;   //unidade hor

                  payload[8] = tempoErroV[10];   //dezena hor
                  payload[9] = tempoErroV[11];   //unidade hor
                  payload[10] = tempoErroV[8];    //dezena min
                  payload[11] = tempoErroV[9];    //unidade min
                  payload[12] = tempoErroV[6];     //dezena seg
                  payload[13] = tempoErroV[7];    //unidade seg
               //}

               erroVazao(1);
               
               enviaParaEsp();

               if(caixa1_H == 0x00 || erro_V == 0x01)
               {
                  bomba               = 0x00;   //Desliga bomba
                  delay_segundos(3);
                  valvula1            = 0x00;   //Desliga válvula da caixa 1
                  statusBomba         = 0x00;   //Muda status da bomba para 0
                  segundos            = 0x00;
                  minutos             = 0x00;
                  horas               = 0x00;
                  habilita_caixa      = 0x00;
                  Lcd_Cmd(_LCD_CLEAR);                // Limpa o display
               }//Fim do if caixa1_L && caixa1_H
            }//Fim do while statusBomba
          }//Fim do if bombaStatus
       break;
    };
    case 2:
    {
       if(statusBomba == 0x00)
       {
         Lcd_Init();                        // Inicializa o LCD
         Lcd_Cmd(_LCD_CLEAR);               // Limpa o display
         Lcd_Cmd(_LCD_CURSOR_OFF);          // Desliga o cursor
         //Lcd_Cmd(_LCD_CLEAR);            //Limpa o display
         cxProcessando(1, 4);
         cxCristiano(2, 3);

         delay_segundos(1);
         valvula2        = 0x01;         //Liga válvula da caixa 2
         delay_segundos(3);              //delay de 3 segundos
         bomba           = 0x01;         //Liga a bomba
         statusBomba     = 0x01;         //Altera status da bomba para 1

         segundos = 0x00;
         minutos  = 0x00;
         horas    = 0x00;

          Lcd_Cmd(_LCD_CLEAR);           // Limpa o display
          cxCristiano(1, 3);
          cxTempo(2, 1);

         while(statusBomba)
         {
            relogio(2,9);                  //Chama rotina relógio
            
            if(caixa2_L == 0x00)
               {
                  tempoErroC[0] = (segundos/10) + 48; //dezena seg
                  tempoErroC[1] = (segundos%10) + 48; //unidade seg
                  tempoErroC[2] = (minutos/10) + 48;  //dezena min
                  tempoErroC[3] = (minutos%10) + 48;  //unidade min
                  tempoErroC[4] = (horas/10) + 48;    //dezena hor
                  tempoErroC[5] = (horas%10) + 48;    //unidade hor

                  payload[18] = tempoErroC[4];  //dezena hor
                  payload[19] = tempoErroC[5];  //unidade hor
                  payload[20] = tempoErroC[2];  //dezena min
                  payload[21] = tempoErroC[3];  //unidade min
                  payload[22] = tempoErroC[0];  //dezena seg
                  payload[23] = tempoErroC[1];  //unidade seg
                  
               }

               //if(caixa2_H == 0x00)
               //{
                  tempoErroC[6] = (segundos/10) + 48; //dezena seg
                  tempoErroC[7] = (segundos%10) + 48; //unidade seg
                  tempoErroC[8] = (minutos/10) + 48;  //dezena min
                  tempoErroC[9] = (minutos%10) + 48;  //unidade min
                  tempoErroC[10] = (horas/10) + 48;   //dezena hor
                  tempoErroC[11] = (horas%10) + 48;   //unidade hor

                  payload[24] = tempoErroC[10];   //dezena hor
                  payload[25] = tempoErroC[11];   //unidade hor
                  payload[26] = tempoErroC[8];    //dezena min
                  payload[27] = tempoErroC[9];    //unidade min
                  payload[28] = tempoErroC[6];     //dezena seg
                  payload[29] = tempoErroC[7];    //unidade seg
               //}

             erroVazao(2);
             
             enviaParaEsp();

            if(caixa2_H == 0x00 || erro_C == 0x01)
            {
               bomba           = 0x00;  //Desliga bomba
               delay_segundos(3);       //delay de 3 segundos
               valvula2        = 0x00;  //Desliga válvula da caixa 2
               statusBomba = 0x00;      //Muda status da bomba para 0
               segundos = 0x00;
               minutos  = 0x00;
               horas    = 0x00;
               habilita_caixa      = 0x00;
               Lcd_Cmd(_LCD_CLEAR);               // Limpa o display
            }//Fim do if caixa1_L && caixa1_H
          }//Fim do while statusBomba
       }//Fim do if bombaStatus
       break;
    };
    case 3:
    {
      if(statusBomba == 0x00)
       {
         Lcd_Init();                        // Inicializa o LCD
         Lcd_Cmd(_LCD_CLEAR);               // Limpa o display
         Lcd_Cmd(_LCD_CURSOR_OFF);          // Desliga o cursor
         //Lcd_Cmd(_LCD_CLEAR);                  // Limpa o display
         cxProcessando(1, 4);
         cxHenrique(2, 3);

         delay_segundos(1);
         valvula3        = 0x01;               //Liga válvula da caixa 3
         delay_segundos(3);                       //delay de 3 segundos
         bomba           = 0x01;               //Liga a bomba
         statusBomba     = 0x01;               //Altera status da bomba para 1

         segundos = 0x00;
         minutos  = 0x00;
         horas    = 0x00;

         Lcd_Cmd(_LCD_CLEAR);                  // Limpa o display
         cxHenrique(1, 3);
         cxTempo(2, 1);

         while(statusBomba)
         {
            relogio(2,9);                         //Chama rotina relógio
            
            if(caixa3_L == 0x00)
               {
                  tempoErroH[0] = (segundos/10) + 48; //dezena seg
                  tempoErroH[1] = (segundos%10) + 48; //unidade seg
                  tempoErroH[2] = (minutos/10) + 48;  //dezena min
                  tempoErroH[3] = (minutos%10) + 48;  //unidade min
                  tempoErroH[4] = (horas/10) + 48;    //dezena hor
                  tempoErroH[5] = (horas%10) + 48;    //unidade hor

                  payload[34] = tempoErroH[4];  //dezena hor
                  payload[35] = tempoErroH[5];  //unidade hor
                  payload[36] = tempoErroH[2];  //dezena min
                  payload[37] = tempoErroH[3];  //unidade min
                  payload[38] = tempoErroH[0];  //dezena seg
                  payload[39] = tempoErroH[1];  //unidade seg
                  
               }

               //if(caixa3_H == 0x00)
               //{
                  tempoErroH[6] = (segundos/10) + 48; //dezena seg
                  tempoErroH[7] = (segundos%10) + 48; //unidade seg
                  tempoErroH[8] = (minutos/10) + 48;  //dezena min
                  tempoErroH[9] = (minutos%10) + 48;  //unidade min
                  tempoErroH[10] = (horas/10) + 48;   //dezena hor
                  tempoErroH[11] = (horas%10) + 48;   //unidade hor

                  payload[40] = tempoErroH[10];   //dezena hor
                  payload[41] = tempoErroH[11];   //unidade hor
                  payload[42] = tempoErroH[8];    //dezena min
                  payload[43] = tempoErroH[9];    //unidade min
                  payload[44] = tempoErroH[6];     //dezena seg
                  payload[45] = tempoErroH[7];    //unidade seg
               //}

            erroVazao(3);
            
            enviaParaEsp();

            if(caixa3_H == 0x00 || erro_H == 0x01)
            {
               bomba           = 0x00;          //Desliga bomba
               delay_segundos(3);                  //delay de 3 segundos
               valvula3        = 0x00;          //Liga válvula da caixa 3
               statusBomba = 0x00;              //Muda status da bomba para 0
               segundos = 0x00;
               minutos  = 0x00;
               horas    = 0x00;
               habilita_caixa      = 0x00;
               Lcd_Cmd(_LCD_CLEAR);               // Limpa o display
            }//Fim do if caixa1_L && caixa1_H
          }//Fim do while statusBomba
       }//Fim do if bombaStatus
    }
  }
}

/*
void modoManual() // Não esta em uso.
{
   Lcd_Cmd(_LCD_CLEAR);               //Limpa o display
   while(!modo)                       //Repete enquanto em modo manual
   {
     //texto_lcd(1, 1, txt7);         //Texto "Sistema em Modo"
     //texto_lcd(2, 6, txt8);          //Texto "Manual"
     
     delay_segundos(2);                  //delay de 2 segundos
     valvula1          = 0x00;
     valvula2          = 0x00;
     valvula3          = 0x00;
     
   }//Fim do while modo
   Lcd_Cmd(_LCD_CLEAR);               // Limpa o display
}//Fim do modoManual
*/

void relogio(int lin, int col)
{
   unsigned short time[6];
  /*
   if(segundos > 59)
   {
      segundos = 0x00;
      minutos++;

      if(minutos > 59)
      {
         minutos = 0x00;
         horas++;

         if(horas > 23)
         {
            horas = 0x00;
         }//Fim do if horas
      }//Fim do if minutos
   }//Fim do if segundos
   */
    //Horas
    time[0] = horas/10;
    time[1] = horas%10;
    
    //Minutos
    time[2] = minutos/10;
    time[3] = minutos%10;
    
    //Segundos
    time[4] = segundos/10;
    time[5] = segundos%10;
    
    lcd_chr(lin,col,TIME[0]+48);          //Imprime dezena minuto
    lcd_chr_cp(TIME[1]+48);               //imprime unidade minuto
    lcd_chr_cp(':');                      //Separador
    lcd_chr_cp(TIME[2]+48);               //imprime dezena segundo
    lcd_chr_cp(TIME[3]+48);               //imprime unidade segundo
    lcd_chr_cp(':');                      //Separador
    lcd_chr_cp(TIME[4]+48);               //imprime dezena segundo
    lcd_chr_cp(TIME[5]+48);               //imprime unidade segundo
}//Fim do relogio

void delay_segundos(int valor)
{
    int duracao = valor;
    segundos = 0;
    
    while(duracao >= segundos)
    {
    
    }//Fim do while
}//Fim de delay_segundos

void texto_lcd(int lin, int col, char txt[])
{
   char textoLcd[16];
   int res;
   int i;
   int tamanho;
   
   tamanho = strlen(txt);     //Tamanho da string do texto
   
   res = strcpy(textoLcd,txt);
   
   lcd_chr(lin,col,textoLcd[0]);
   
   for (i = 1; i < tamanho; i++ )
   {
       lcd_chr_cp(textoLcd[i]);
   }
} //Fim de texto_lcd

void sensores()
{
   unsigned short sensor[6];
   
   bomba             = 0x00;     //Liga a bomba
   statusBomba       = 0x00;     //Altera status da bomba para 1
   valvula1          = 0x00;
   valvula2          = 0x00;
   valvula3          = 0x00;
   
   Lcd_Init();                        // Inicializa o LCD
   Lcd_Cmd(_LCD_CLEAR);               // Limpa o display
   Lcd_Cmd(_LCD_CURSOR_OFF);          // Desliga o cursor

   //Lcd_Cmd(_LCD_CLEAR);               //Limpa o display
   while(!modo)                       //Repete enquanto em modo manual
   {
     sensor[0] = ~caixa1_Cheia;
     sensor[1] = ~caixa1_Vazia;
     sensor[2] = ~caixa2_Cheia;
     sensor[3] = ~caixa2_Vazia;
     sensor[4] = ~caixa3_Cheia;
     sensor[5] = ~caixa3_Vazia;

     msgsensores(1,2);
     
     lcd_chr(2,2,'V');                         //Imprime sensores de
     lcd_chr_cp('=');                           //Valderi
     lcd_chr_cp(sensor[0] + 48);               //imprime sensor Caixa cheia
     lcd_chr_cp(sensor[1] + 48);               //imprime sensor Caixa vazia
     lcd_chr_cp(' ');
     lcd_chr_cp('C');                          //imprime sensores de
     lcd_chr_cp('=');                          //Cristiano
     lcd_chr_cp(sensor[2] + 48);               //imprime sensor Caixa cheia
     lcd_chr_cp(sensor[3] + 48);               //imprime sensor Caixa vazia
     lcd_chr_cp(' ');
     lcd_chr_cp('H');                          //imprime sensores de
     lcd_chr_cp('=');                          //Henrique
     lcd_chr_cp(sensor[4] + 48);               //imprime sensor Caixa cheia
     lcd_chr_cp(sensor[5] + 48);               //imprime sensor Caixa vazia
     lcd_chr_cp(' ');
     
     //Fazer executar o acionamento da bomba e solenóides aqui
     ligaManual();

     //delay_segundos(1);                        //delay de 1 segundos
    // valvula1          = 0x00;
    // valvula2          = 0x00;
     //valvula3          = 0x00;
     
     erro_V            = 0x00;
     erro_C            = 0x00;
     erro_H            = 0x00;

     enviaParaEsp();

   }//Fim do while modo
   Lcd_Cmd(_LCD_CLEAR);               // Limpa o display
   bomba               = 0x00;   //Desliga bomba
   valvula1            = 0x00;   //Desliga válvula da caixa 1
   valvula2            = 0x00;
   valvula3            = 0x00;
   statusBomba         = 0x00;   //Muda status da bomba para 0
   habilita_caixa      = 0x00;
   
}//fim de sensores

void ligaManual()
{

   if(enable_V == 0x00 && ligado == 0 && enable_C == 0x01 && enable_H == 0x001)
     {
        ligado = 1;
        //delay_segundos(1);            //Delay de 1 segundo
        valvula1            = 0x01;     //Liga válvula da caixa 1
        delay_segundos(3);              //delay de 3 segundos
        bomba               = 0x01;     //Liga a bomba
        statusBomba         = 0x01;     //Altera status da bomba para 1
     }
     
   if(enable_C == 0x00 && ligado == 0 && enable_V == 0x01 && enable_H == 0x01)
     {
        ligado = 1;
        //delay_segundos(1);            //Delay de 1 segundo
        valvula2            = 0x01;     //Liga válvula da caixa 1
        delay_segundos(3);              //delay de 3 segundos
        bomba               = 0x01;     //Liga a bomba
        statusBomba         = 0x01;     //Altera status da bomba para 1
     }
     
     if(enable_H == 0x00 && ligado == 0 && enable_V == 0x01 && enable_C == 0x01)
     {
        ligado = 1;
        //delay_segundos(1);            //Delay de 1 segundo
        valvula3            = 0x01;     //Liga válvula da caixa 1
        delay_segundos(3);              //delay de 3 segundos
        bomba               = 0x01;     //Liga a bomba
        statusBomba         = 0x01;     //Altera status da bomba para 1
     }


    if(enable_V == 0x01 && enable_C == 0x01 && enable_H == 0x01)
     {

          bomba               = 0x00;   //Desliga bomba
          delay_segundos(3);
          valvula1            = 0x00;   //Desliga válvula da caixa 1
          valvula2            = 0x00;
          valvula3            = 0x00;
          statusBomba         = 0x00;   //Muda status da bomba para 0
          habilita_caixa      = 0x00;
          ligado = 0;
     }
     
     if(enable_V == 0x01 && enable_C == 0x00 && enable_H == 0x00)
     {

          bomba               = 0x00;   //Desliga bomba
          valvula1            = 0x00;   //Desliga válvula da caixa 1
          valvula2            = 0x00;
          valvula3            = 0x00;
          statusBomba         = 0x00;   //Muda status da bomba para 0
          habilita_caixa      = 0x00;
     }
     
     if(enable_V == 0x00 && enable_C == 0x00 && enable_H == 0x00)
     {
          bomba               = 0x01;   //liga bomba
          valvula1            = 0x00;   //Desliga válvula da caixa 1
          valvula2            = 0x00;
          valvula3            = 0x00;
          statusBomba         = 0x01;   //Muda status da bomba para 0
          habilita_caixa      = 0x00;
     }
}

void erroVazao(char caixa)
{
  switch (caixa) 
  {
    case 1:
    {
      //if((segundos >= 10 && caixa1_L == 0) || (horas >= 0 && segundos >= 15 && caixa1_H == 1)) //Para teste
      if((minutos >= 10 && caixa1_L == 0) || (horas >= 1 && minutos >= 10 && caixa1_H == 1))
       {
          erro_V = 0x01;
          minutosVazao = 0;
       }
      else
       {
          erro_V = 0x00;
       }
      break;
    };
    case 2:
    {
      if((minutos >= 10 && caixa2_L == 0)|| (minutos >= 50 && caixa2_H == 1))
       {
          erro_C = 0x01;
          minutosVazao = 0;
       } 
       else
       {
          erro_C = 0x00;
       }
      break;
    };
    case 3:
    {
      if((minutos >= 10 && caixa3_L == 0) || (horas >= 1 && minutos >= 10 && caixa3_H == 1))
       {
          erro_H = 0x01;
          minutosVazao = 0;
       } 
       else
       {
          erro_H = 0x00;
       }
      break;
    };
  }
}

void limpaErroVazao()
{
   if((minutosVazao > 30)&&((erro_V == 0x01)||(erro_C == 0x01)||(erro_H == 0x01)))
   {
      erro_V            = 0x00;
      erro_C            = 0x00;
      erro_H            = 0x00;
      minutosVazao      = 0x00;
   }
}

void erroSesoresFechados(char caixa)
{
     switch (caixa)
  {
    case 1:
    {
         if(caixa1_L == 0 && caixa1_H == 0)
         {
            erro_V = 0x02;
         }
         break;
    };
    case 2:
    {
         if(caixa2_L == 0 && caixa2_H == 0)
         {
            erro_C = 0x02;
         }
         break;
    };
    case 3:
    {
         if(caixa3_L == 0 && caixa3_H == 0)
         {
            erro_H = 0x02;
         }
         break;
    };
  }
}

void mostraErro()
{
   if((erro_V == 0x01) || (erro_V == 0x02))
   {
     lcd_chr(2,9,'V');
   }
   else
   {
     lcd_chr(2,9,'0');
   }
   
    if(erro_C == 0x01 || erro_C == 0x02)
   {
     lcd_chr(2,12,'C');
   }
   else
   {
     lcd_chr(2,12,'0');
   }
   
     if(erro_H == 0x01 || erro_H == 0x02)
   {
     lcd_chr(2,15,'H');
   }
   else
   {
     lcd_chr(2,15,'0');
   }
}

//Mensagens
void aquabox(int lin, int col)
{
    lcd_chr(lin,col,'A');          //AQUABOX
    lcd_chr_cp('Q');
    lcd_chr_cp('U');
    lcd_chr_cp('A');
    lcd_chr_cp('B');
    lcd_chr_cp('O');
    lcd_chr_cp('X');
}

void cxValderi(int lin, int col)
{
  lcd_chr(lin,col,'C');          //Cx. Valderi
    lcd_chr_cp('x');
    lcd_chr_cp('.');
    lcd_chr_cp(' ');
    lcd_chr_cp('V');
    lcd_chr_cp('a');
    lcd_chr_cp('l');
    lcd_chr_cp('d');
    lcd_chr_cp('e');
    lcd_chr_cp('r');
    lcd_chr_cp('i');
}

void cxCristiano(int lin, int col)
{
    lcd_chr(lin,col,'C');          //Cx. Cristiano
    lcd_chr_cp('x');
    lcd_chr_cp('.');
    lcd_chr_cp(' ');
    lcd_chr_cp('C');
    lcd_chr_cp('r');
    lcd_chr_cp('i');
    lcd_chr_cp('s');
    lcd_chr_cp('t');
    lcd_chr_cp('i');
    lcd_chr_cp('a');
    lcd_chr_cp('n');
    lcd_chr_cp('o');
}

void cxHenrique(int lin, int col)
{
    lcd_chr(lin,col,'C');          //Cx. Henrique
    lcd_chr_cp('x');
    lcd_chr_cp('.');
    lcd_chr_cp(' ');
    lcd_chr_cp('H');
    lcd_chr_cp('e');
    lcd_chr_cp('n');
    lcd_chr_cp('r');
    lcd_chr_cp('i');
    lcd_chr_cp('q');
    lcd_chr_cp('u');
    lcd_chr_cp('e');
}

void cxProcessando(int lin, int col)
{
    lcd_chr(lin,col,'P');          //Processando
    lcd_chr_cp('r');
    lcd_chr_cp('o');
    lcd_chr_cp('c');
    lcd_chr_cp('e');
    lcd_chr_cp('s');
    lcd_chr_cp('s');
    lcd_chr_cp('a');
    lcd_chr_cp('n');
    lcd_chr_cp('d');
    lcd_chr_cp('o');
}

void cxTempo(int lin, int col)
{
    lcd_chr(lin,col,'T');          //Tempo:
    lcd_chr_cp('e');
    lcd_chr_cp('m');
    lcd_chr_cp('p');
    lcd_chr_cp('o');
    lcd_chr_cp(':');
    lcd_chr_cp(' ');
}

void sejaBemVindo(int lin, int col)
{
    lcd_chr(lin,col,'S');          //SEJA BEM VINDO
    lcd_chr_cp('E');
    lcd_chr_cp('J');
    lcd_chr_cp('A');
    lcd_chr_cp(' ');
    lcd_chr_cp('B');
    lcd_chr_cp('E');
    lcd_chr_cp('M');
    lcd_chr_cp('-');
    lcd_chr_cp('V');
    lcd_chr_cp('I');
    lcd_chr_cp('N');
    lcd_chr_cp('D');
    lcd_chr_cp('O');
}

void falha(int lin, int col)
{
    lcd_chr(lin,col,'F');          //Falha
    lcd_chr_cp('a');
    lcd_chr_cp('l');
    lcd_chr_cp('h');
    lcd_chr_cp('a');
}

void msgsensores(int lin, int col)
{
    lcd_chr(lin,col,'S');          //Sensores-Manual
    lcd_chr_cp('e');
    lcd_chr_cp('n');
    lcd_chr_cp('s');
    lcd_chr_cp('o');
    lcd_chr_cp('r');
    lcd_chr_cp('e');
    lcd_chr_cp('s');
    lcd_chr_cp('-');
    lcd_chr_cp('M');
    lcd_chr_cp('a');
    lcd_chr_cp('n');
    lcd_chr_cp('u');
    lcd_chr_cp('a');
    lcd_chr_cp('l');
}