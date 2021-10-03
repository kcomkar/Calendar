#include<stdio.h>
#include<signal.h>
#include<string.h>
#include<conio.h>

// To return the number of days in a given month of a particular year i.e., if it is leap year or not 
int getNumberOfDays(int month,int year)
{
   switch(month)
   {
      case 1 : return(31);
      case 2 : if(year%4==0)
		 return(29);
	       else
		 return(28);
      case 3 : return(31);
      case 4 : return(30);
      case 5 : return(31);
      case 6 : return(30);
      case 7 : return(31);
      case 8 : return(31);
      case 9 : return(30);
      case 10: return(31);
      case 11: return(30);
      case 12: return(31);
      default: return(-1);
   }
}

// To return the name of a week
char *getName(int odd)
{
   switch(odd)
   {
      case 0 :return("Sunday");
      case 1 :return("Monday");
      case 2 :return("Tuesday");
      case 3 :return("Wednesday");
      case 4 :return("Thursday");
      case 5 :return("Friday");
      case 6 :return("Saturday");
      default:return("Error in getName\(\) module.Invalid argument passed");
   }
}

// To fetch the name of the week of a particular date in the form of an integer
int getOddNumber(int day,int mon,int year)
{
   int res=0,t1,t2,y=year;
   year = year-1600;
   while(year>=100)
   {
       res=res+5;
       year=year-100;
   }
   res=(res%7);
   t1=((year-1)/4);
   t2=(year-1)-t1;
   t1=(t1*2)+t2;
   t1=(t1%7);
   res = res+t1;
   res=res%7;
   t2=0;
   for(t1=1;t1<mon;t1++)
   {
      t2+=getNumberOfDays(t1,y);
   }
   t2 = t2+day;
   t2 = t2%7;
   res = res+t2;
   res = res%7;
   if(y>2000)
     res=res+1;
   res = res%7;
   res = res%7;
   return res;
}

char *getWeek(int dd,int mm,int yy)
{
   int odd;
   if(!(mm>=1 && mm<=12))
   {
      return("Invalid month value");
   }
   if(!(dd>=1 && dd<=getNumberOfDays(mm,yy)))
   {
      return("Invalid date");
   }
   if(yy>=1600)
   {
     odd = getOddNumber(dd,mm,yy);
     odd=odd%7;
     return(getName(odd));
   }
   else
   {
      return("\nPlease give year more than 1600");
   }
}

// To print the calendar of a particular month of an year at starting from the given coordinates of a week 
void printMonth(int mon,int year,int x,int y)
{
   int nod,odd,cnt,d=1,x1=x,time=1;
   gotoxy(x,y);
   clreol();
   if(!(mon>=1 && mon<=12))
   {
       printf("\nINVALID MONTH");
       getch();
       return;
   }
   if(!(year>=1600))
   {
      printf("\nINVALID YEAR");
      getch();
      return;
   }
   if(x<=0)
     x=wherex();
   if(y<=0)
     y=wherey();
   gotoxy(x,y);
   textcolor(RED);
   cprintf("S");
   textcolor(YELLOW);
   cprintf("   M   T   W   T   F   S");
   textcolor(7);
   cprintf("");
   y++;
   nod=getNumberOfDays(mon,year);
   odd=getOddNumber(d,mon,year);
   repeat : printf("");
   switch(odd)
   {
     case 0 : x=x;
	      cnt=1;
	      break;
     case 1 : x=x+4;
	      cnt=2;
	      break;
     case 2 : x=x+8;
	      cnt=3;
	      break;
     case 3 : x=x+12;
	      cnt=4;
	      break;
     case 4 : x=x+16;
	      cnt=5;
	      break;
     case 5 : x=x+20;
	      cnt=6;
	      break;
     case 6 : x=x+24;
	      cnt=7;
	      break;
     default : if(time==1)
	       {
		  odd = odd%7;
		  time++;
		  goto repeat;
	       }
	       else if(time==2)
	       {
		  odd = odd - 7;
		  time++;
		  goto repeat;
	       }
	       else
	       {
		 printf("\n\nINVALID DATA FROM THE getOddNumber() MODULE");
		 return;
	       }
   }
   gotoxy(25,25);
   gotoxy(x,y);
   printf("%02d",d);
   for(d=2;d<=nod;d++)
   {
      if(cnt%7==0)
      {
	y++;
	cnt=0;
	x=x1-4;
      }
      x = x+4;
      cnt++;
      gotoxy(x,y);
      printf("%02d",d);
   }
}

void han(void)
{
   FILE *fp;
   fp = fopen("STAT","rw");
   fprintf(fp,"1");
   fcloseall();
   main();
}

int checkForErrors()
{
   FILE *fp;
   int stat;
   fp = fopen("STAT","r");
   if(fp!=NULL)
   {
      fscanf(fp,"%d",&stat);
      return stat;
   }
   else
   {
      return -1;
   }
}

void printLogo(int col,int x,int y)
{
    int x1=wherex(),y1=wherey();
    gotoxy(x,y);
    textcolor(col);
    cprintf("Mini Calendar");
    textcolor(7);
    cprintf("");
    gotoxy(x1,y1);
}

main()
{
   char ch='\0',ch1,x,y,x1=1,y1=1;
   int dd,mm,yy;
   signal(SIGTERM,han);
   signal(SIGINT,han);
   signal(SIGABRT,han);
   signal(SIGFPE,han);
   signal(SIGILL,han);
   dd = checkForErrors();
   if(dd==1)
   {
      clrscr();
      gotoxy(25,25);
      printf("An signal to close the program was caught in the previous run.");
      gotoxy(25,27);
      printf("Press any key to continue...");
      unlink("STAT");
      flushall(); fflush(stdin);
      getch();
   }
   while(ch!='0')
   {
      flushall();
      fflush(stdout);
      clrscr();
      printLogo(-3,1,25);
      printf("\n\n\n\n\n\t\t\t\t1.Know the day");
      printf("\n\t\t\t\t2.Print the month");
      printf("\n\t\t\t\t0.EXIT");
      printf("\n\n\t\t\t\tENTER YOUR CHOICE : ");
      flushall();
      fflush(stdin);
      ch=getche();
      clrscr();
      switch(ch)
      {
	case '1': x=1;y=1;x1=x;y1=y;
		  ch1='Y';
		  clrscr();
		  while(toupper(ch1)=='Y')
		  {
		    printLogo(-2,1,25);
		    gotoxy(x1,y1);
		    clreol();
		    printf("\nEnter date (DD MM YYYY) : ");
		    clreol();
		    scanf("%d %d %d",&dd,&mm,&yy);
		    printf("\nDay is : %s\n",getWeek(dd,mm,yy));
		    flushall();
		    fflush(stdin);
		    cprintf("");
		    x1=wherex();
		    y1=wherey();
		    printf("\nDo you want to check another (Y/N) : ");
		    x = wherex();
		    y = wherey();
		    do
		    {
		      gotoxy(x,y);
		      clreol();
		      ch1=toupper(getche());
		    }while(ch1!='Y' && ch1!='N');
		  }
		  break;
	case '2' : again : gotoxy(1,1);
		   printLogo(-10,1,25);
		   printf("Enter month and year (MM YYYY) : ");
		   clreol();
		   scanf("%d %d",&mm,&yy);
		   printf("\n\n");
		   textcolor(LIGHTBLUE);
		   gotoxy(30,10);
		   clreol();
		   if(mm==1)
		      cprintf("January");
		   else if(mm==2)
		      cprintf("February");
		   else if(mm==3)
		      cprintf("March");
		   else if(mm==4)
		      cprintf("April");
		   else if(mm==5)
		      cprintf("May");
		   else if(mm==6)
		      cprintf("June");
		   else if(mm==7)
		      cprintf("July");
		   else if(mm==8)
		      cprintf("August");
		   else if(mm==9)
		      cprintf("September");
		   else if(mm==10)
		      cprintf("October");
		   else if(mm==11)
		      cprintf("November");
		   else if(mm==12)
		      cprintf("December");
		   else
		   {
		      textcolor(-4);
		      cprintf("ERROR");
		      textcolor(7);
		      cprintf("");
		   }
		   if(yy<1600)
		   {
		     printf(",");
		     textcolor(-5);
		     cprintf("ERROR");
		     textcolor(7);
		     cprintf("");
		     printf("\n\nInvalid year");
		     getch();
		     gotoxy(wherex()-12,wherey());
		     clreol();
		     goto hell;
		   }
		   clreol();
		   cprintf(",%d",yy);
		   textcolor(7);
		   cprintf("");
		   printMonth(mm,yy,30,wherey()+1);
		   hell : flushall();
		   gotoxy(22,25);
		   printf("Do you want to see another calendar(Y/N) : ");
		   ch1='';
		   x = wherex();
		   y = wherey();
		   while(ch1!='Y' && ch1!='N')
		   {
		     flushall();
		     fflush(stdin);
		     gotoxy(x,y);
		     ch1 = toupper(getche());
		     gotoxy(x,y);
		     clreol();
		   }
		   if(ch1=='Y')
		   {
		      clrscr();
		      goto again;
		   }
		   else
		   {
		     gotoxy(x,y);
		     printf("%c",ch1);
		     printf("\n                            ");
		     textcolor(-3);
		     cprintf("Press any key to continue...");
		     textcolor(7);
		     cprintf("");
		     getch();
		     clrscr();
		   }
		   break;
	case '0' : exit(0);
      }
   }
}
