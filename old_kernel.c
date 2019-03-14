/* ACADEMIC INTEGRITY PLEDGE                                              */
/*                                                                        */
/* - I have not used source code obtained from another student nor        */
/*   any other unauthorized source, either modified or unmodified.        */
/*                                                                        */
/* - All source code and documentation used in my program is either       */
/*   my original work or was derived by me from the source code           */
/*   published in the textbook for this course or presented in            */
/*   class.                                                               */
/*                                                                        */
/* - I have not discussed coding details about this project with          */
/*   anyone other than my instructor. I understand that I may discuss     */
/*   the concepts of this program with other students and that another    */
/*   student may help me debug my program so long as neither of us        */
/*   writes anything during the discussion or modifies any computer       */
/*   file during the discussion.                                          */
/*                                                                        */
/* - I have violated neither the spirit nor letter of these restrictions. */
/*                                                                        */
/*                                                                        */
/*                                                                        */
/* Signed:_____________________________________ Date:_____________        */
/*                                                                        */
/*                                                                        */
/* 3460:4/526 BlackDOS2020 kernel, Version 1.01, Spring 2018.             */

void handleInterrupt21(int,int,int,int);
/*void printString(char*,int);*/
void printLogo();
void readInt(int* n);
void writeInt(int n);
char* readString();

/* Mad Lib kernel.c - c. 2018 O'Neil */
void main()
{
   char food[25], adjective[25], color[25], animal[25];
   int temp;
   makeInterrupt21();
   printLogo();
   interrupt(33,0,"\r\nWelcome to the Mad Libs kernel.\r\n\0",0,0);
   interrupt(33,0,"Enter a food: \0",0,0);
   interrupt(33,1,food,0,0);
   temp = 0;
   while ((temp < 100) || (temp > 120)) {
      interrupt(33,0,"Enter a number between 100 and 120: \0",0,0);
      interrupt(33,14,&temp,0,0);
   }
   interrupt(33,0,"Enter an adjective: \0",0,0);
   interrupt(33,1,adjective,0,0);
   interrupt(33,0,"Enter a color: \0",0,0);
   interrupt(33,1,color,0,0);
   interrupt(33,0,"Enter an animal: \0",0,0);
   interrupt(33,1,animal,0,0);
   interrupt(33,0,"Your note is on the printer, go get it.\r\n\0",0,0);
   interrupt(33,0,"Dear Professor O\'Neil,\r\n\0",1,0);
   interrupt(33,0,"\r\nI am so sorry that I am unable to turn in my program at this time.\r\n\0",1,0);
   interrupt(33,0,"First, I ate a rotten \0",1,0);
   interrupt(33,0,food,1,0);
   interrupt(33,0,", which made me turn \0",1,0);
   interrupt(33,0,color,1,0);
   interrupt(33,0," and extremely ill.\r\n\0",1,0);
   interrupt(33,0,"I came down with a fever of \0",1,0);
   interrupt(33,13,temp,1,0);
   interrupt(33,0,". Next my \0",1,0);
   interrupt(33,0,adjective,1,0);
   interrupt(33,0," pet \0",1,0);
   interrupt(33,0,animal,1,0);
   interrupt(33,0," must have\r\nsmelled the remains of the \0",1,0);
   interrupt(33,0,food,1,0);
   interrupt(33,0," on my computer, because he ate it. I am\r\n\0",1,0);
   interrupt(33,0,"currently rewriting the program and hope you will accept it late.\r\n\0",1,0);
   interrupt(33,0,"\r\nSincerely,\r\n\0",1,0);
   interrupt(33,0,"(your name here)\r\n\0",1,0);
   while(1);
}  

/*
void main()
{
   makeInterrupt21();
   printLogo(); 
   interrupt(33,0,"Hello world from Mikyla Wilfred.\r\n\0",1,0); 
   int n = 0;
   readInt(&n);
   writeInt(n);
   while(1);
}
*/
void printString(char* c, int d)
{  
   if ( d == 1 ){
	   do {   
		interrupt(23, *c, 0, 0, 0);
		c++;
   	   } while (*(c) != '\0');
   }
   else { 
           do {   
		interrupt(16, 14*256+*c, 0, 0, 0);
		c++;
   	   } while (*(c) != '\0');
	   
   } 

   return;
}

void printLogo()
{
   printString("       ___   `._   ____  _            _    _____   ____   _____ \r\n\0",0);
   printString("      /   \\__/__> |  _ \\| |          | |  |  __ \\ / __ \\ / ____|\r\n\0",0);
   printString("     /_  \\  _/    | |_) | | __ _  ___| | _| |  | | |  | | (___ \r\n\0",0);
   printString("    // \\ /./      |  _ <| |/ _` |/ __| |/ / |  | | |  | |\\___ \\ \r\n\0",0);
   printString("   //   \\\\        | |_) | | (_| | (__|   <| |__| | |__| |____) |\r\n\0",0);
   printString("._/'     `\\.      |____/|_|\\__,_|\\___|_|\\_\\_____/ \\____/|_____/\r\n\0",0);
   printString(" BlackDOS2020 v. 1.01, c. 2018. Based on a project by M. Black. \r\n\0",0);
   printString(" Author(s): Mikyla Wilfred and Kevin Lewis.\r\n\r\n\0",0);
} 


int mod(int a, int b) {
	int x = a;
	while (x >= b) x = x - b;
	return x;
}

int div(int a, int b) {
	int q = 0;
	while (q * b <= a) q++;
	return (q - 1);
}

void writeInt (int x) {
    int i = 0;
    char stringFinal2[80];
    char* c3 = stringFinal2;

	char stringFinal_Final[80];
    char* c_Final = stringFinal_Final;   

    *c3 = '\0';
    c3++;

    if (x < 0) {
        x *= -1;
        *c3 = '-';
	c3++;
    }
      
  /*Makes 0 if int is 0*/  
	 if (x == 0) {
       *c_Final = '0';
	   c_Final++;
    } 
	
	
    while (x != 0) {
        *(c3) = (char) ((mod(x,10)) + '0');
        x = div(x, 10);
	c3++;
	i++;
    }

   *c3 = '\0';
  c3--;
 
 /* Return Null if string or empty */
  if (i == 0){
	  *c_Final = '\0';
  }
 
while (i > 0){
	*c_Final = *c3;
	c3--;
	c_Final++;
 	i--;
}
    *c_Final = '\0';


}

void readInt (int* n) {
    int num = 0;
    int isNegative = 0;
    char* c2 = readString();

    if (*c2 == '-') {
        isNegative = 1;
	c2++;
    }
 
    while (*(c2) != '\r') {
        num = num * 10;
        num = num + (*(c2) - '0');
	c2++;
    }
 
    if (isNegative) { 
        num *= -1; 
    }
    *n = num;

}

char* readString(){
	char stringFinal[80];
	char* c = stringFinal;

	while(1){
		*c = interrupt(22,0,0,0,0);
		if (*(c) == 13){
			*c = '\r';
			c++;
			*c = '\n';
			c++;
			*c = '\0';
			interrupt(16, 14*256+'\0', 0, 0, 0);
			interrupt(16, 14*256+'\r', 0, 0, 0);
			interrupt(16, 14*256+'\n', 0, 0, 0);

			interrupt(33,0,stringFinal,0,0); 
			return stringFinal;
		}


		interrupt(16, 14*256+*c, 0, 0, 0);
		 if (*(c) == 8){
				c--;
			} else { 
				c++;
			}  
	}
}




void handleInterrupt21(int ax, int bx, int cx, int dx)
{
   //return;
   switch(ax) {  
      case 0: printString(bx,cx); break; 
      case 1: readString(bx); break; 
/*      case 2: case 3: case 4: case 5: */
/*      case 6: case 7: case 8: case 9: case 10: */
/*      case 11: case 12: case 15: */
       case 13: writeInt(bx); break;
      case 14: readInt(bx); break;
      default: printString("General BlackDOS error.\r\n\0"); 
   }  
}
