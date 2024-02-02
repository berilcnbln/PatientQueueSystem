class MaxHeap {
public:
    struct patient{
        int patient_id, patient_priority, arrival_time, service_time;
    };

    // Constructor
    MaxHeap();

    // Destructor
    ~MaxHeap();

    void push(patient value);

    patient top();

    patient pop();

    int size();

    bool isEmpty();


private:
    int currentSize; // for tracking size of the array

    patient *items; // array to keep the max-heap structure
    int MAX_SIZE = 10;

    void heapDelete(patient &rootItem);
    void heapRebuild(int root);
    static bool greater(patient &a, patient &b);
};


