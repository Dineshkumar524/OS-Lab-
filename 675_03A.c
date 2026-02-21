#include<stdio.h>

int main()
{
    int at[5] = {0,1,2,3,4};
    int bt[5] = {5,7,6,2,4};
    
    int ct[5], tat[5], wt[5];
    int i;
    float avg_wt = 0, avg_tat = 0;

    // First process completion time
    ct[0] = at[0] + bt[0];

    // Remaining processes
    for(i = 1; i < 5; i++)
    {
        if(ct[i-1] > at[i])
            ct[i] = ct[i-1] + bt[i];
        else
            ct[i] = at[i] + bt[i];
    }

    // Calculate TAT and WT
    for(i = 0; i < 5; i++)
    {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];

        avg_wt += wt[i];
        avg_tat += tat[i];
    }

    printf("Process\tAT\tBT\tCT\tTAT\tWT\n");

    for(i = 0; i < 5; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
        i+1, at[i], bt[i], ct[i], tat[i], wt[i]);
    }

    printf("\nAverage Waiting Time = %.2f", avg_wt/5);
    printf("\nAverage Turnaround Time = %.2f", avg_tat/5);

    return 0;
}
