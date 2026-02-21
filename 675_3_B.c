#include <stdio.h>

int main() {
    int n = 5;
    int pid[] = {0,1,2,3,4};
    int at[]  = {0,0,0,0,0};
    int bt1[] = {5,7,6,8,5};
    int io[]  = {2,2,3,1,2};
    int bt2[] = {3,2,4,2,5};

    int pct[5], ct[5];  // PCT = completion after first burst, CT = final completion
    int tat[5], wt[5];
    int t = 0;

    // First CPU burst
    for(int i=0;i<n;i++){
        if(t<at[i]) t=at[i];
        t += bt1[i];
        pct[i] = t;
    }

    // Second CPU burst after I/O
    for(int i=0;i<n;i++){
        int ready = pct[i]+io[i];
        if(t<ready) t=ready;
        t += bt2[i];
        ct[i] = t;
    }

    // Calculate TAT and WT
    double totalTAT=0, totalWT=0;
    for(int i=0;i<n;i++){
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - (bt1[i]+bt2[i]);
        totalTAT += tat[i];
        totalWT += wt[i];
    }

    printf("PID\tAT\tBT1\tI/O\tBT2\tPCT\tCT\tTAT\tWT\n");
    for(int i=0;i<n;i++){
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               pid[i], at[i], bt1[i], io[i], bt2[i], pct[i], ct[i], tat[i], wt[i]);
    }

    printf("\nAverage TAT = %.2f\n", totalTAT/n);
    printf("Average WT  = %.2f\n", totalWT/n);

    return 0;
}
