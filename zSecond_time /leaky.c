#include<stdio.h>
int main(){
    int bucket=0,bucketcapacity,numberofpacket,leakrate;
    printf("Enter bucket capacity : ");
    scanf("%d",&bucketcapacity);
    printf("Enter leak rate : ");
    scanf("%d",&leakrate);
    printf("Enter number of packet : ");
    scanf("%d",&numberofpacket);

    int packet[numberofpacket];
    for(int i =0 ; i<numberofpacket ; i++){
        scanf("%d",&packet[i]);
    }
    printf("Time\tIncomming\tBucket\t\tLeak_rate\tRemaining\n");
    for(int i=0;i<numberofpacket;i++){
        printf("%d\t%d\t",i+1,packet[i]);
        bucket += packet[i];
        if(bucket > bucketcapacity){
            printf("%d(dropped %d)\t\t",bucketcapacity,bucket-bucketcapacity);
            bucket = bucketcapacity;
        }else{
            printf("%d\t",bucket);
        }

        int leaked;
        if(leakrate < bucket)
            leaked = leakrate;
        else
            leaked = bucket;
        printf("%d\t",leaked);
        bucket -= leaked;
        printf("%d\n",bucket);
    }
        //remaining bucket 
        int time = numberofpacket+1;
        while(bucket>0){
            int leaked;
            if(leakrate < bucket)
                leaked = leakrate;
            else
                leaked = bucket;
            printf("%d\t0\t%d\t\t%d\t%d\n",time,bucket,leaked,bucket-leaked);
            bucket -= leaked;
            time ++;
        }
}