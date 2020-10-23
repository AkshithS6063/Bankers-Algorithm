#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h> 
char colours[5][10]={"[0;31m","[0;32m","[0;33m","[0;34m","[0;36m"};
int number_of_processes,resource_types,not_enough_resources=0,allocated[20][5],max[20][5],total_resources[5];
bool finished[20];
void execute(int i)
{
    for(int j=0;j<resource_types;j++)
        total_resources[j]=total_resources[j]+allocated[i][j];
}
bool finished_execution()
{
    not_enough_resources++;
    if(not_enough_resources>number_of_processes+1)
    {
        printf("\n\n\033[1;31mFATAL ERROR OCCURED: NOT ENOUGH RESOURCES\n");
        exit(0);
    }
    for(int i=0;i<number_of_processes;i++)
        if(finished[i]==false)
            return false;
    return true;
}
int main()
{
    printf("\033[1;36mHow many processes are running? ");
    scanf("%d",&number_of_processes);
    printf("Enter the number of resource types ");
    scanf("%d",&resource_types);
    if(resource_types>5)
    {
        printf("TOO MANY RESOURCE TYPES\n");
        exit(0);
    }
    printf("Enter the  allocated resources\n");
    for(int i=0;i<number_of_processes;i++)
    {
        
        for(int j=0;j<resource_types;j++)
        {
            
            scanf("%d",&allocated[i][j]);
        }
    }
    printf("\nEnter the max resources for each process\n");
    for(int i=0;i<number_of_processes;i++)
    {
        
        for(int j=0;j<resource_types;j++)
        {
            
            scanf("%d",&max[i][j]);
        }
    }
    printf("\n\n\033[1;36mEnter the total available resources\n");
    for(int i=0;i<resource_types;i++)
    {
        
        scanf("%d",&total_resources[i]);
    }
    
    while(!finished_execution())
    {
        for(int i=0;i<number_of_processes;i++)
        {
            bool possible=true;
            for(int j=0;j<resource_types;j++)
            {
                
                if(max[i][j]-allocated[i][j]>total_resources[j] && finished[i]==false)
                    possible=false;
            }
            if(possible==true&&finished[i]==false)
            {
                execute(i);
                if(finished[i]==false)
                {
                    printf("PROCESS %d FINISHED. TOTAL RESOURCES=",i);
                    for(int k=0;k<resource_types;k++)
                        printf(" %d",total_resources[k]);
                    printf("\n");
                }
                finished[i]=true;
            }
        }
    }
  return 0;
}