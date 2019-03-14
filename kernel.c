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
/* Signed:____________Mikyla Wilfred__________ Date:__2/16/2018___        */
/*                                                                        */
/*                                                                        */
/* 3460:4/526 BlackDOS2020 kernel, Version 1.01, Spring 2018.             */

void handleInterrupt21(int,int,int,int);
void printLogo();
char* readString(char str[]);
void readInt(int* n);
void writeInt(int x);

int mod(int a, int b);
int div(int a, int b);

//variables
char str[80];
int* x;
char* c;
void main()
{
 char buffer[12288]; int size;
 makeInterrupt21();
 /* Step 0 – config file */
 interrupt(33,2,buffer,258,0);
 interrupt(33,12,buffer[0]+1,buffer[1]+1,0);
 printLogo();
 /* Step 1 – load/edit/print file  */
 interrupt(33,3,"spc02\0",buffer,&size);
  buffer[7] = '2'; buffer[8] = '0';
 buffer[9] = '1'; buffer[10] = '8';
 interrupt(33,0,buffer,0,0); 
 /* Step 2 – write revised file */ 
 interrupt(33,8,"spr18\0",buffer,size); 
 /* Step 3 – delete original file 
 interrupt(33,7,"spc02\0",0,0);*/
 while (1) ;
}
/* more stuff follows */

void printString(char* c, int d)
{

	if( d == 0){
		do{
			interrupt(16, 14*256 + *c, 0, 0, 0);
			c++;
		} while(*(c) != '\0');
		*c = '\0';
	}
	else if (d == 1){
		do{
			interrupt(23, *c, 0, 0, 0);
			c++;
		} while(*(c) != '\0');
		*c = '\0';
	}

   return;
}

char* readString(char str[]){
	char* c = str;
	char* start = c;
	while(1){
		*c = interrupt(22, 0, 0, 0);
		if(*c == 13){ //if enter is pressed

			//append null terminator to string
			*c = '\0';

			//output string on new line
			interrupt(16, 14*256 + '\0', 0, 0, 0);
			interrupt(16, 14*256 + '\r', 0, 0, 0);
			interrupt(16, 14*256 + '\n', 0, 0, 0);
			return str;	
		}
		if(*c == 8 && start != c){interrupt(16, 14*256 + *c, 0, 0, 0); c--;} //if backspace is pressed
		else if(c != 8) {interrupt(16, 14*256 + *c, 0, 0, 0); c++;} //print to screen
	}
}

void printLogo()
{
   interrupt(33,0,"       ___   `._   ____  _            _    _____   ____   _____ \r\n\0",0,0);
   interrupt(33,0,"      /   \\__/__> |  _ \\| |          | |  |  __ \\ / __ \\ / ____|\r\n\0",0,0);
   interrupt(33,0,"     /_  \\  _/    | |_) | | __ _  ___| | _| |  | | |  | | (___ \r\n\0",0,0);
   interrupt(33,0,"    // \\ /./      |  _ <| |/ _` |/ __| |/ / |  | | |  | |\\___ \\ \r\n\0",0,0);
   interrupt(33,0,"   //   \\\\        | |_) | | (_| | (__|   <| |__| | |__| |____) |\r\n\0",0,0);
   interrupt(33,0,"._/'     `\\.      |____/|_|\\__,_|\\___|_|\\_\\_____/ \\____/|_____/\r\n\0",0,0);
   interrupt(33,0," BlackDOS2020 v. 1.01, c. 2018. Based on a project by M. Black. \r\n\0",0,0);
   interrupt(33,0," Author:  Mikyla Wilfred and Kevin Lewis\r\n\r\n\0",0,0);
}

/* MAKE FUTURE UPDATES HERE */
/* VVVVVVVVVVVVVVVVVVVVVVVV */

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

void readInt(int* n){
	int num = 0;
    char str[80];
    char* c = readString(str);
    char* d = c;
   
    if(*d != '0'){
      while (*d != '\0') {
          num = num * 10;
          num = num + (*d - '0');
          d++;
      }
    }
    else{num = 0;}

    *n = num;

    writeInt(*n);
    
}

void writeInt(int x){
    int len = 0;
 
    char tmp[80];
    char* c = tmp;
    char tmp2[80];
    char* c2 = tmp2;

 
    // Check for zero
    if(x==0){interrupt(33,0,"0\0\r\n",1,0); return;}

    // Fill buffer with digit characters in reverse order.
    if(x != 0){
      while (x != 0) {
          *c = (char) (mod(x,10) + '0');
          x = div(x,10);
          c++;
          len++;
      }

      *c = '\0';

      c--;

      while(len > 0){
      	*c2 = *c;
      	c--;
      	c2++;
      	len--;
      }
      *c2 = '\0'; c2++; c2 = '\r'; c2++; c2 = '\n';
    }
    interrupt(33,0,tmp2,1,0);


}


void readSector(char* buffer, int sector){
	int relSecNo  = mod(sector, 18) + 1;
	int headNo = mod (div(sector,18) , 2);
	int trackNo = div (sector, 36) ;
	interrupt(19,513, buffer ,(trackNo*256)+relSecNo,headNo * 256);
}

void writeSector(char* buffer, int sector){
	int relSecNo  = mod(sector, 18) + 1;
	int headNo = mod (div(sector,18) , 2);
	int trackNo = div (sector, 36) ;
	interrupt(19,769, buffer ,(trackNo*256)+relSecNo,headNo * 256);
}
	
void clearScreen(int background, int foreground){
	int i = 0;
	for (i; i < 24; i++){
		 interrupt(33,0,"\r\n",0,0);
	}

 	interrupt(16,512,0,0,0);

	if (background > 0 && background < 9 && foreground > 0 && foreground < 17){
			interrupt(16, 1536, 4096 * (background -1) + 256 * (foreground - 1), 0, 6223);
	}
}

void error(int bx){
switch(bx) { 
      case 0: printString("File not found.\r\n\0",0); break;
      case 1: printString("Duplicate or Invalid file name.\r\n\0",0); break; 
      case 2:  printString("Disk full.\r\n\0",0); break;
      default: printString("General error.\r\n\0",0); break;
   }  
}

void readFile(char* name, char* buffer, int* size){
	char* sector[512];
	char* c; char* f; char* b; char* p;
	int length = 0; int nameMatch = 0; int location = 0;
	int i, j, k, l = 0;
	int address;

	readSector(sector, 257);

	c = name;
	f = name;
	b = sector;

	length = 0;
	nameMatch = 0;
	location = 0;

	while(*c != '\0'){c++; length = length + 1;}

	for(i = 0; i < 16; i++){
		if(nameMatch == 0){	
			f = name;
			nameMatch = 1;
			
			if(*b == 0){nameMatch = 0;}
			else{	
				for(j = 0; j < length; j++){	
					if(*b == *f){b++; f++;}	
					else{nameMatch = 0; b++;}
				}

				for(k = 0; k < (8 - length); k++){b++;}
			}
		}

		if(nameMatch == 0){b = b + 24;}				
		else{	
			size = 0;	
			while(*b != 0){							
				readSector(buffer + address, *b);
				address = address + 512;
				b++;
				size++;
			}
			writeInt (size);
		
		}
	}
	if(nameMatch == 0){interrupt(33,15,0,0,0);}
}


void writeFile(char* name, char* buffer, int numberOfSectors){
	char* sector[512];
	char* map[512];
	char* y;
	char* c; char* f; char* b; char* p; char* fileLocation; char* a;
	int length = 0; int nameMatch = 0; int location = 0; int m = 0; 
	int i, j, k, l, isFound = 0;
	int isEmpty, numberOfSectorsTemp; 

	readSector(map, 256);
	readSector(sector, 257);

	c = name;
	f = name;
	b = sector;
	a = map;
	y = name;

	length = 0;
	nameMatch = 0;
	location = 0;

	while(*c != '\0'){c++; length = length + 1;}
	for(i = 0; i < 16; i++){
		if(nameMatch == 0){
	
			f = name;		
			nameMatch = 1;							
	
			if(*b == 0 && isFound == 0){isFound = 1; fileLocation = b; nameMatch = 0; }				
			else if(*b == 0){nameMatch = 0;}	
			else{				
				for(j = 0; j < length; j++){	
					if(*b == *f){b++; f++;}		
					else{nameMatch = 0; b++;}		
				}
				for(k = 0; k < (8 - length); k++){b++;}
			} 
			if(nameMatch == 1){interrupt(33,15,1,0,0); return;}
			else {b = b + 24;}	
		}
	}
	if(isFound == 0){interrupt(33,15,2,0,0); return;}	

	for (m = 0; m < 6; m++){
		if (m > length){
			fileLocation = 0;  			
		} else {
			fileLocation = y; 			
		}
		fileLocation++;
		y++;
	}

// find empty sector
// Write Sector
// Save Sector # in fileLocaion++
// find next empty sector
	isEmpty = 1;
	numberOfSectorsTemp = 1;
	
	for(i = 0; i < 256; i++){
		if (*a != 0) {
			isEmpty = 0;
		} 
		
		if (isEmpty == 1 && numberOfSectorsTemp < numberOfSectors){
			a = a + 24;
			fileLocation = i; 
			fileLocation++;
		}else if (isEmpty == 1){
			fileLocation = i; 
			break;
		} else {
			a = a + 24;
		}
	}


	for(k = 0; k < (24 - numberOfSectors); k++){
		fileLocation = 0; 
		fileLocation++; 
	}

	writeSector(map, 256);
	writeSector(sector, 257);

	
}

/* deleteFile(bx){} */
/* ^^^^^^^^^^^^^^^^^^^^^^^^ */
/* MAKE FUTURE UPDATES HERE */

void handleInterrupt21(int ax, int bx, int cx, int dx)
{
   switch(ax) { 
      	case 0: printString(bx,cx); break;
      	case 1: readString(bx); break;
	case 2: readSector(bx,cx); break;
  	case 3: readFile(bx,cx,dx); break;
	case 6: writeSector(bx,cx);
	/*case 7: deleteFile(bx); break;*/
	case 8: writeFile(bx,cx,dx); break;  
	case 12: clearScreen(bx,cx); break;
      	case 13: writeInt(bx); break;
      	case 14: readInt(bx); break;
 	case 15: error(bx); break;
/*    case 4: case 5: */
/*         case 9: case 10: */
/*      case 11: */
	  default: printString("General BlackDOS error.\r\n\0");
   }  
}
