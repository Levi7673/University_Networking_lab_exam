#include <stdio.h>
int main(){
    int bucketcapacity,leakRate,numberofpacket,bucket=0;
    printf("Enter the number of packets : ");
    scanf("%d",&numberofpacket);
    printf("Enter the bucket capacity : ");
    scanf("%d",&bucketcapacity);
    printf("Enter the leak rate : ");
    scanf("%d",&leakRate);
    int packet[numberofpacket];

    for(int i=0;i<numberofpacket;i++){
        scanf("%d",&packet[i]);
    }

    printf("Time\tIncoming\tBucket\tLeaked\tRemaining\n");
    for(int i=0;i<numberofpacket;i++){
        printf("%d\t%d\t",i+1,packet[i]);

        bucket += packet[i];
        if(bucket > bucketcapacity){
            printf("%d(droped %d)\t\t", bucketcapacity,bucket-bucketcapacity);
            bucket = bucketcapacity;
        }else{
            printf("%d\t\t",bucket);
        }

        int leaked;
        if(bucket>leakRate)
            leaked=leakRate;
        else
            leaked=bucket;
        printf("%d\t",leaked);
        bucket -= leaked;
        printf("%d\n",bucket);
    }
    int time=numberofpacket+1;
    while(bucket>0){
        int leaked;
        if(bucket>leakRate)
            leaked=leakRate;
        else
            leaked=bucket;
        printf("%d\t0\t%d\t\t%d\t%d\n",time,bucket,leaked,bucket-leaked);
        bucket -= leaked;
        time ++;
    }
}