#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

// the struct to simulate the event
struct Event {
    int serverNumber;
    double eventTime;
    double serviceTime;
};
// suppose the server number is 10
Event event[11];

double queue[500];
double enqueueTime[500];
int record_id[11];

int totalServer = 0;
int busyServer = 0;

// record how many people served
int totalServed = 0;
double currentTime = 0;
double totalServiceTime;
int queueSize = 0;
double serviceTime = 0;
double nextServiceTime = 0;
double totalQueueTime = 0;
double maxQueueTime = 0;
double lastEventTime = 0;
int maxQueueLength = 0;
int totalMultiQueueLength = 0;
double queueTime[500];

// for the second strategy
double multiQueue[11][500];
double enterMultiQueueTime[11][500];
int multiQueueSize[11];

void swap(Event &e1, Event &e2) {
    Event tmp = e2;
    e2 = e1;
    e1 = tmp;
}

void filterUp() {
    int child = busyServer;
    while (child > 0) {
        if (event[(child - 1) / 2].eventTime > event[child].eventTime) {
            swap(event[child], event[(child - 1) / 2]);
            child /= 2;
        } else
            return;
    }
}

void filterDown() {
    if (busyServer == 0) {
        return;
    }

    int i = 0;
    while (i < busyServer) {
        int children = i * 2 + 1;
        if (children > busyServer)
            return;
        if ((children + 1) <= busyServer) {
            if (event[children].eventTime > event[children + 1].eventTime)
                children += 1;
        }

        if (event[i].eventTime > event[children].eventTime) {
            swap(event[children], event[i]);
        }
        i = children;
    }

}

void enqueue(double sevTime, int StSimulationRound) {
    // this means the first strategy, only single queue
    if (StSimulationRound == 1) {
        queue[queueSize] = sevTime;
        enqueueTime[queueSize] = currentTime;
        queueSize++;
        if (queueSize > maxQueueLength)
            maxQueueLength = queueSize;
    }
        // this is the second strategy, every server use a queue
    else {
        int flag = multiQueueSize[1];
        int queueIndex = 1;
        for (int i = 2; i < totalServer + 1; ++i) {
            if (multiQueueSize[i] < flag) {
                flag = multiQueueSize[i];
                queueIndex = i;
            }
        }
        multiQueue[queueIndex][flag] = sevTime;
        enterMultiQueueTime[queueIndex][flag] = currentTime;
        multiQueueSize[queueIndex]++;
        int totalQuelength = 0;
        for (int i = 1; i < totalServer + 1; ++i) {
            totalQuelength += multiQueueSize[i];
        }
        if (totalQuelength > totalMultiQueueLength)
            totalMultiQueueLength = totalQuelength;

        for (int i = 1; i < totalServer + 1; ++i) {
            if (multiQueueSize[i] > maxQueueLength)
                maxQueueLength = multiQueueSize[i];
        }
    }
}

double dequeue(int StSimulationRound, int serverId) {
    double tmp;
    if (StSimulationRound == 1) {
        totalQueueTime += (currentTime - enqueueTime[0]);
        if ((currentTime - enqueueTime[0]) > maxQueueTime) {
            maxQueueTime = currentTime - enqueueTime[0];
        }
        tmp = queue[0];
        for (int i = 0; i < queueSize - 1; ++i) {
            queue[i] = queue[i + 1];
            enqueueTime[i] = enqueueTime[i + 1];
        }
        queueSize--;
    } else {
        int queueLength = multiQueueSize[serverId];
        tmp = multiQueue[serverId][queueLength];
        totalQueueTime += ((currentTime - enterMultiQueueTime[serverId][0]));
        if ((currentTime - enterMultiQueueTime[serverId][queueLength - 1]) > maxQueueTime)
            maxQueueTime = ((currentTime - enterMultiQueueTime[serverId][0]));
        for (int i = 0; i < queueLength - 1; ++i) {
            multiQueue[serverId][i] = multiQueue[serverId][i + 1];
            enterMultiQueueTime[serverId][i] = enterMultiQueueTime[serverId][i + 1];
        }

        queueLength--;
        multiQueueSize[serverId] = queueLength;
    }
    return tmp;
}

void handleArrival(ifstream &readIntoHeap, int StSimulationRound) {
    lastEventTime = currentTime;
    currentTime = event[0].eventTime;
    readIntoHeap >> event[0].eventTime >> nextServiceTime;
    totalServiceTime += nextServiceTime;
    filterDown();
    if (busyServer < totalServer) {
        busyServer++;
        event[busyServer].eventTime = currentTime + serviceTime;
        event[busyServer].serviceTime += serviceTime;
        filterUp();
    } else
        enqueue(serviceTime, StSimulationRound);
    serviceTime = nextServiceTime;
}

void handleLastArrival(int StSimulationRound) {
    lastEventTime = currentTime;
    currentTime = event[0].eventTime;
    if (busyServer < totalServer) {
        busyServer++;
        //make one free server busy
        event[busyServer].eventTime = currentTime + serviceTime;
        event[busyServer].serviceTime += serviceTime;

        filterUp();
    } else
        enqueue(serviceTime, StSimulationRound);

    Event tmp = event[busyServer];
    event[busyServer] = event[0];
    event[0] = tmp;
    busyServer--;
    filterDown();
}

void processEndService(int StSimulationRound) {
    lastEventTime = currentTime;
    currentTime = event[0].eventTime;
    double actualServiceTime = 0;
    if (StSimulationRound == 1) {
        if (queueSize == 0) {
            Event tmp = event[busyServer];
            event[busyServer] = event[0];
            event[0] = tmp;
            busyServer -= 1;
        } else {
            actualServiceTime = dequeue(StSimulationRound, event[0].serverNumber);
            event[0].eventTime = currentTime + actualServiceTime;
            event[0].serviceTime += actualServiceTime;
        }
    } else {
        int id = event[0].serverNumber;
        if (multiQueueSize[event[0].serverNumber] == 0) {
            Event tmp = event[busyServer];
            event[busyServer] = event[0];
            event[0] = tmp;
            busyServer -= 1;
        } else {
            actualServiceTime = dequeue(StSimulationRound, id);
            event[0].eventTime = currentTime + actualServiceTime;
            event[0].serviceTime += actualServiceTime;
        }
    }
    totalServed++;
    filterDown();
}

void setStSimulation(ifstream &fileIn, int StSimulationRound) {

    currentTime = 0;
    busyServer = 0;
    queueSize = 0;
    totalServed = 0;
    totalServiceTime = 0;
    totalQueueTime = 0;
    maxQueueLength = 0;

    fileIn >> totalServer;
    fileIn >> event[0].eventTime >> serviceTime;

    for (int i = 0; i < totalServer + 1; ++i) {
        record_id[i] = i;
    }
    for (int i = 0; i < totalServer + 1; ++i) {
        event[i].serverNumber = i;
        event[i].serviceTime = 0;
    }
    if (StSimulationRound == 2) {
        for (int i = 0; i < totalServer + 1; ++i) {
            multiQueueSize[i] = 0;
        }
    }
    totalServiceTime += serviceTime;
}

void simulate(ifstream &fileIn, int StSimulationRound) {
    if (StSimulationRound == 1) {
        cout << "===========The first strategy===========" << endl;
        cout << "Make the first simulation, " << totalServer << " servers and 1 queue in total." << endl;
    }else {
        cout << endl;
        cout << "===========The second strategy===========" << endl;
        cout << "Make the second simulation, " << totalServer << " servers and " << totalServer
             << " queue in total." << endl;
    }
    while(!fileIn.eof() || busyServer >= 0){
        long int currentFilePos = fileIn.tellg();
        char nextChar;
        fileIn >> nextChar;
        if(!fileIn.fail()) {
            fileIn.seekg(currentFilePos);
            if (event[0].serverNumber == 0)
                handleArrival(fileIn, StSimulationRound);
            else
                processEndService(StSimulationRound);
        }else{
            if (event[0].serverNumber == 0)
                handleLastArrival(StSimulationRound);
            else
                processEndService(StSimulationRound);
        }
    }
}

void printResults(int StSimulationRound){
    cout << "The total number of served people is: " << totalServed << endl;
    cout << "The total service time is: " << currentTime << endl;
    cout << "The average service time is: " << totalServiceTime / totalServed << endl;
    cout << "The average time a customer spend in queue is: " << totalQueueTime / totalServed << endl;
    cout << "The max time a customer spend in queue is: " << maxQueueTime << endl;
    cout << "The average length of queue in any give seconds is: " << totalQueueTime / currentTime << endl;
    cout << "The max queue length is: " << maxQueueLength << endl;
    if(StSimulationRound == 2)
        cout << "The multi queue length in total is: " << totalMultiQueueLength << endl;
    cout << "The total idle time for each server is: " << endl;
    for(int i = 0; i < totalServer + 1; ++i){
        if(event[i].serverNumber != 0)
            cout << "The idle for server " << event[i].serverNumber << " is: " << currentTime - event[i].serviceTime << endl;
    }

}


int main() {
    char fileName[256];
    cout << "please input the file: " << endl;
    cin >> fileName;

    ifstream fin;
    fin.open(fileName);
    while(!fin.good()){
        cout << "file can't open, please enter agian: " << endl;
        cin >> fileName;
        fin.open(fileName);
    }
    // run the first strategy simulation
    setStSimulation(fin, 1);
    simulate(fin, 1);
    fin.close();
    printResults(1);

    fin.open(fileName);
    // run the second strategy simulation
    setStSimulation(fin, 2);
    simulate(fin, 2);
    fin.close();
    printResults(2);

    return 0;
}

