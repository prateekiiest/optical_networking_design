#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<strings.h>
 int main()
 {
    int path[50];     // declaring path
    int traffic[50];   // declaring traffic
    int i,j;
    int a[14];                              // ALL INITIAL DECLARATIONS PRESENT HERE
    
 
    for(i=0;i<14;i++){


    a[i]=i+1;   // INITIALIZING THE ARRAY OF 14 POINTS

    }
 
 
    char buff[255];

   FILE *fp;
   fp=fopen("one.txt","r");      // OPENING THE MAIN FILE ONE.TXT  WHERE INFO ON TRAFFIC AND PATH CONNECTION IS GIVEN
        if(!fp)  // If File cannot be opened
        return 1;
 
while(fgets(buff, 255 , fp))
  {
     printf("%s",buff);
  }  
 



for(j=0;j<100;j++){
	
}


 
  fclose(fp);

return 0;


}


