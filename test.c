#include <stdio.h>

#define max 100

 struct process{

    int pid;
    int burstT;
    int remainingT;
    int priority;

};

typedef struct process process;

int S_q0=0;
int S_q1=0;
int S_q2=0;
int S_q3=0;

process q0[max];
process q1[max];
process q2[max];
process q3[max];

int SwitchTime=20;
int totaltime=0;

void enqueue(process *q ,int *size,process p){
    q[*size]=p;
    (*size)++;
}

process dequeue(process *q,int *size){

    process temporary = q[0];

    (*size)--;

    for(int i =0 ; i < (*size) ;i++){
        q[i] = q[i+1];
    }

    return temporary;

}

void RoundedRobin(process *q,int *size,int QT,int SwitchT){

    while((SwitchT > 0) &&( *size > 0)){

        if(SwitchT >= QT){

            process excecuting = dequeue(q,size);

            if(excecuting.remainingT > QT){

                excecuting.remainingT = excecuting.remainingT - QT;

                        SwitchT = SwitchT-QT;
                        enqueue(q,size,excecuting);

                        totaltime=totaltime+QT;


            }
            else if(excecuting.remainingT == QT){

                excecuting.remainingT = 0;
                printf("\n%d process  completed\n",excecuting.pid);
                SwitchT = SwitchT -QT;
                totaltime=totaltime+QT;
                int waitingtime=totaltime-excecuting.burstT;

                printf("%d process turnaroundtime: %d\n",excecuting.pid,totaltime);
                printf("%d process waitingtime: %d\n\n",excecuting.pid,waitingtime);

            }

            else{
                SwitchT = SwitchT- excecuting.remainingT;
                totaltime=totaltime+excecuting.remainingT;
                int waitingtime=totaltime-excecuting.burstT;
                excecuting.remainingT = 0 ;
                printf("\n%d process completed.\n",excecuting.pid);
                printf("%d process turnaroundtime: %d\n\n",excecuting.pid,totaltime);
                printf("%d process waitingtime: %d\n\n",excecuting.pid,waitingtime);
            }

        }
        else{
           
            
            if(q[0].remainingT > SwitchT){

                  q[0].remainingT = q[0].remainingT -SwitchT;
                  totaltime=totaltime+SwitchT;
                  SwitchT = 0;

            }
            else{
                process executing = dequeue(q,size);
                SwitchT=SwitchT-executing.remainingT;
                totaltime=totaltime+executing.remainingT;
                 int waitingtime=totaltime-executing.burstT;

                executing.remainingT =0;
                printf("\n%d process completed.\n",executing.pid);
                printf("%d process turnaroundtime: %d\n",executing.pid,totaltime);
                printf("%d process waitingtime: %d\n\n",executing.pid,waitingtime);
                

            }
        }
        

    }
    

}

void FCFS(process *q,int *size,int SwitchT){

    while((SwitchT >0) && (*size > 0)){

        if(q[0].remainingT > SwitchT){

            q[0].remainingT=q[0].remainingT-SwitchT;
            totaltime=totaltime+SwitchT;
            SwitchT=0;
            
        }

        else  if(q[0].remainingT == SwitchT){
            q[0].remainingT=0;
            totaltime=totaltime+SwitchT;
            int waitingtime=totaltime-q[0].burstT;
            SwitchT=0;

            printf("\n%d process  completed\n",q[0].pid);
            printf("%d process turnaroundtime: %d\n",q[0].pid,totaltime);
            printf("%d process waitingtime: %d\n\n",q[0].pid,waitingtime);
            dequeue(q,size);

            
        }

         if(q[0].remainingT < SwitchT){

            SwitchT=SwitchT-q[0].remainingT;
            totaltime=totaltime+q[0].remainingT;
            int waitingtime=totaltime-q[0].burstT;
            q[0].remainingT=0;

            printf("\n%d process  completed\n",q[0].pid);
            printf("%d process turnaroundtime: %d\n",q[0].pid,totaltime);
            printf("%d process waitingtime: %d\n\n",q[0].pid,waitingtime);
            dequeue(q,size);
        }
    }
}

void SJF(process *q,int *size,int SwitchT){

     while((SwitchT >0) && (*size > 0)){

        int shortest = 0;

        for(int i=1;i<(*size);i++){
            if(q[shortest].remainingT > q[i].remainingT){
                shortest =i;
            }
        }

        if(q[shortest].remainingT > SwitchT){

            q[shortest].remainingT = q[shortest].remainingT -SwitchT;
            totaltime=totaltime+SwitchT;
            SwitchT = 0;

           

        }

        else if(q[shortest].remainingT == SwitchT){

            q[shortest].remainingT =0;
            totaltime=totaltime+SwitchT;
            int waitingtime=totaltime-q[shortest].burstT;
            SwitchT = 0;

            printf("\n%d process  completed\n",q[shortest].pid);
            printf("%d process turnaroundtime: %d\n",q[shortest].pid,totaltime);
            printf("%d process waitingtime: %d\n\n",q[shortest].pid,waitingtime);
            dequeue(q+shortest,size);

        }
         else if(q[shortest].remainingT < SwitchT){

            SwitchT=SwitchT-q[shortest].remainingT;
            totaltime=totaltime+q[shortest].remainingT;
            int waitingtime=totaltime-q[shortest].burstT;
            q[shortest].remainingT=0;
            
            printf("\n%d process  completed\n",q[shortest].pid);
            printf("%d process turnaroundtime: %d\n",q[shortest].pid,totaltime);
            printf("%d process waitingtime: %d\n\n",q[shortest].pid,waitingtime);
            dequeue(q+shortest,size);
        }

     }
    
}

int main(){

    int m;
    printf("Enter number of proccesses you want to execute: ");
    scanf("%d",&m);

    for(int j=1;j<=m;j++){
        process NewP;
        NewP.pid=j;

        printf("\nEnter burst time of %d process: ",NewP.pid);
        scanf("%d",&NewP.burstT); 

        NewP.remainingT=NewP.burstT;  

        printf("\nEnter priority(0,1,2,3) of %d process: ",NewP.pid);
        scanf("%d",&NewP.priority);

        switch (NewP.priority)
        {
        case 0:
            enqueue(q0,&S_q0,NewP);
            break;

        case 1:
            enqueue(q1,&S_q1,NewP);
            break;

        case 2:
            enqueue(q2,&S_q2,NewP);
            break;

        case 3:
            enqueue(q3,&S_q3,NewP);
            break;
        
        default:
            break;
        }


    }
    int Qt;
    if(S_q0 >0){
    printf("\nEnter quantum time of Rounded Robin algorithm: ");
    scanf("%d",&Qt);
    }

    while(S_q0 >0 || S_q1 >0 || S_q2 > 0 || S_q3 > 0){

        if(S_q0 > 0){

            RoundedRobin(q0,&S_q0,Qt,SwitchTime);
        }

        if(S_q1 > 0){
            SJF(q1,&S_q1,SwitchTime);
        }

         if(S_q2 > 0){
            SJF(q2,&S_q2,SwitchTime);
        }

        if(S_q3>0){
            FCFS(q3,&S_q3,SwitchTime);
        }
    }
 
 printf("Total time all processes took: %d\n",totaltime);

    return 0;
}