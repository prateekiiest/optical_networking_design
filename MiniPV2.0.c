#include<stdio.h>
#include<stdlib.h>
#define MAX 14
#define TEMP 0
#define PERM 1
#define infinity 9999

struct node
{
int predecessor;
int dist; /*minimum distance of node from source*/
int status;
};

int adj[MAX][MAX];
int n;
void main()
{
int i,j,ch,k=1;
int source,dest;
int path[MAX];
int shortdist,count;
FILE *fp;
int choice;
printf("Enter \n 1 to input network as per you wish \n 2 To work with a pre defined network");
scanf("%d",&choice);
if(choice==1)
create_graph();
else
network();
printf("\n Now writing to file......\n");
fp = fopen("Network1.txt","w");
    if(fp==NULL)
    printf("\n Cannot open file");
    else
    {
        fprintf(fp,"\n N1\t N2 \t\t CONNECTED");
        for(i=0;i<MAX;i++)
    {
        for(j=0;j<MAX;j++)
        {
            if(adj[i][j]!=0)
            fprintf(fp,"\n %d\t %d \t\t %d",(i+1),(j+1),adj[i][j]);
        }
    }
    fclose(fp);
    }
printf("The adjacency matrix is :\n");
display();

while(k==1)
{
/*printf("Enter source node(0 to quit) : ");
scanf("%d",&source);*/
source=rand()%n +1; printf("\nsrc  :%d",source);
/*printf("Enter destination node(0 to quit) : ");
scanf("%d",&dest);*/
dest=rand()%n +1;  printf("\ndest  :%d",dest);
//if(source==0 || dest==0)
//exit(1);

count = findpath(source,dest,path,&shortdist);
if(shortdist!=0)
{
//printf("Wavelength assigned to the request is : %d\n", shortdist);
printf("\nRequest routed as : ");
for(i=count;i>1;i--)
printf("%d->",path[i]);
printf("%d",path[i]);
printf("\n");
}
else
printf("\nThere is no path from source to destination node\n");
printf("\n Press 1 to generate more request and 0 t quit\n");
scanf("%d",&k);
}

}
create_graph()
{
int i,max_edges,origin,destin,wt;

printf("Enter number of vertices : ");
scanf("%d",&n);
max_edges=n*(n-1);

for(i=1;i<=max_edges;i++)
{
printf("Enter edge %d(0 0 to quit) : ",i);
scanf("%d %d",&origin,&destin);
if((origin==0) && (destin==0))
break;
//printf("Enter weight for this edge : ");
//scanf("%d",&wt);
if( origin > n || destin > n || origin<=0 || destin<=0)
{
printf("Invalid edge!\n");
i--;
}
else
adj[origin][destin]=1;//wt
}/*End of for*/
}/*End of create_graph()*/
network()
{  //Inputs the given network(pre-decided)
adj[1][2]=1;    adj[5][4]=1 ;  adj[5][10]=1;    adj[11][13]=1;
adj[1][3]=1;    adj[6][7]=1 ;  adj[12][14]=1;
adj[1][9]=1;    adj[6][11]=1;  adj[12][11]=1;
adj[2][1]=1;    adj[6][2]=1 ;  adj[12][10]=1;
adj[2][3]=1;    adj[7][8]=1 ;  adj[7][4]=1;  adj[7][6]=1;
adj[2][6]=1;    adj[8][9]=1 ;  adj[13][11]=1;
adj[3][1]=1;    adj[8][7]=1 ;  adj[13][10]=1;
adj[3][2]=1;    adj[9][8]=1 ;  adj[14][4]=1;
adj[3][4]=1;    adj[9][10]=1;   adj[14][12]=1;
adj[4][3]=1;    adj[9][1]=1 ;
adj[4][5]=1;    adj[10][12]=1;  adj[10][9]=1;
adj[4][7]=1;    adj[10][13]=1;
adj[4][14]=1;   adj[11][12]=1;  adj[11][6]=1;

n=14;
}
display()
{
int i,j;
for(i=1;i<=n;i++)
{
for(j=1;j<=n;j++)
printf("%3d",adj[i][j]);
printf("\n");
}

}/*End of display()*/

int findpath(int s,int d,int path[MAX],int *sdist)
{
struct node state[MAX];
int i,min,count=0,current,newdist,u,v;
*sdist=0;
/* Make all nodes temporary */
for(i=1;i<=n;i++)
{
state[i].predecessor=0;
state[i].dist = infinity;
state[i].status = TEMP;
}

/*Source node should be permanent*/
state[s].predecessor=0;
state[s].dist = 0;
state[s].status = PERM;

/*Starting from source node until destination is found*/
current=s;
while(current!=d)
{
for(i=1;i<=n;i++)
{
/*Checks for adjacent temporary nodes */
if ( adj[current][i] > 0 && state[i].status == TEMP )
{
newdist=state[current].dist + adj[current][i];
/*Checks for Relabeling*/
if( newdist < state[i].dist )
{
state[i].predecessor = current;
state[i].dist = newdist;
}
}
}/*End of for*/

/*Search for temporary node with minimum distand make it current
node*/
min=infinity;
current=0;
for(i=1;i<=n;i++)
{
if(state[i].status == TEMP && state[i].dist < min)
{
min = state[i].dist;
current=i;
}
}/*End of for*/

if(current==0) /*If Source or Sink node is isolated*/
return 0;
state[current].status=PERM;
}/*End of while*/

/* Getting full path in array from destination to source */
while( current!=0 )
{
count++;
path[count]=current;
current=state[current].predecessor;
}

/*Getting distance from source to destination*/
for(i=count;i>1;i--)
{
u=path[i];
v=path[i-1];
*sdist+= adj[u][v];
}
return (count);
}/*End of findpath()*/
