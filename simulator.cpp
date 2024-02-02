#include<bits/stdc++.h>
#include "maxHeap1.h"
//#include "maxHeap2.h"
using namespace std;

const int N = 1e8 + 9;

MaxHeap::patient patients[N];
int max_avg_wait_time, n;
MaxHeap *heap;
double wait_time = 0;

struct output{
    int doc_no, patient_id, currentTime, wait_time;
};

vector<output> ret;

bool patientComparator(const MaxHeap::patient &p1, const MaxHeap::patient &p2){
    return (p1.arrival_time < p2.arrival_time || (p1.arrival_time == p2.arrival_time && p1.patient_priority > p2.patient_priority));
}

void print(vector<output> ret){
    for(int i = 0; i < ret.size(); i++){
        printf("Doctor %d takes patient %d at minute %d (wait: %d mins)\n", ret[i].doc_no, ret[i].patient_id,
                ret[i].currentTime, ret[i].wait_time);
    }
    return ;
}

void readerInput(char *textName){
    FILE *fp = fopen(textName, "r");

    fscanf(fp, "%d", &n);

    int id, priority, arrival_time, service_time;
    for(int i = 0; i < n; i++){
        id = priority = arrival_time = service_time = 0;
        fscanf(fp, "%d %d %d %d", &id, &priority, &arrival_time, &service_time);
        patients[i] = {id, priority, arrival_time, service_time};
    }

    fclose(fp);
}

bool f(int number_of_doctors){
    int earliestFinishTime = 1, doctors[number_of_doctors], observedPatients = 0, i = 0, temp;
    ret.clear();
    wait_time = 0;

    for(int j = 0; j < number_of_doctors; j++)
        doctors[j] = 1;

    int freeDoctors = number_of_doctors;

    while(observedPatients < n){
        int countBusyDoctors = number_of_doctors - freeDoctors;

        while(i < n && ((freeDoctors > 0) ||
             (freeDoctors == 0 && (patients[i].arrival_time <= earliestFinishTime || heap -> isEmpty())))) {

            if(freeDoctors > 0)
                freeDoctors--;

            heap->push(patients[i]);
            i++;
            countBusyDoctors++;
        }

        for(int j = 0; j < number_of_doctors; j++){
            if(!heap->isEmpty() && doctors[j] <= earliestFinishTime){
                MaxHeap::patient top = heap -> pop();

                int currentTime = max(earliestFinishTime, top.arrival_time);
                int currentWaitTime = currentTime - top.arrival_time;

                ret.push_back({j, top.patient_id, currentTime, currentWaitTime});

                wait_time += currentWaitTime;

                doctors[j] = currentTime + top.service_time;

                observedPatients++;
            }
        }
        earliestFinishTime = doctors[0];
        for(int j = 1; j < number_of_doctors; j++)
            earliestFinishTime = min(earliestFinishTime, doctors[j]);
    }

    wait_time /= n;
    return (wait_time <= (1.0 * max_avg_wait_time));
}

int main(int argc, char *argv[]){

    char inputTextName[109] = "\0";
    strcpy(inputTextName, argv[1]);
    max_avg_wait_time = atoi(argv[2]);

//    char inputTextName[] = "patients.txt";
//    max_avg_wait_time = 5;

    readerInput(inputTextName);

    heap = new MaxHeap();

    sort(patients, patients + n, patientComparator);

    for(int i = 1; i <= N; i++){
        if(f(i)){
            printf("Minimum number of doctors required: %d\n\n", i);
            printf("Simulation with %d doctors:\n\n", i);
            print(ret);
            printf("\nAverage waiting time: %f minutes\n", wait_time);
            break;
        }
    }
    return 0;
}
