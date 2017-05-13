#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "queueint.h"
using namespace std;


/**
 * Do not change
 * Reads jobs from the input stream for an iteration.
 *
 * @param inf Input stream
 * @return Queue of jobs (represented by their size) 
 *         read from the line of the file
 */
QueueInt readLine(ifstream &inf)
{
    string line;
    getline(inf, line);
    QueueInt retval;
    if(inf.fail()) return retval;
    stringstream ss(line);
    int value;
    while(ss >> value) {
        retval.push(value);
    }
    return retval;
}

/**
 * Do not change
 * Prints a single job (item) scheduling and its iteration.
 *
 * @param iteration Current iteration number
 * @param value Number of required CPU cores to run the job (job value)
 * @param resourceIndex Array index of the resource the job has been scheduled
 */
void scheduleAndPrintJob(const int iteration,
                         const int value,
                         const int resourceIndex)
{

    cout << "Iteration: " << iteration
         << ", Scheduled: " << value
         << ", Resource: " << resourceIndex + 1
         << endl;

}

/**
 * Attempts to schedule jobs (from the jobs queue) in one of the resources (array).
 * If the job cannot be scheduled, it should be retained for the next iteration.
 *
 * @param resources Pointer to resources array
 * @param jobqueue Queue of all jobs from earlier iterations &  this iteration
 *              that still need to be scheduled
 * @param iteration Current iteration number
 * @param numResources Number of available resources
 */
void scheduleJobs(int *resources,
                  QueueInt& jobqueue,
                  const int iteration,
                  const int numResources) {

    // You complete.
    // Be sure to call scheduleAndPrintJob when you schedule a job
    //

    int job; QueueInt jobs;
    while(!jobqueue.empty())
    {
        job = jobqueue.front();
        bool inserted = false;
        for(int i = 0; i < numResources; i++)
        {
            if(resources[i] >= job)
            {
                resources[i] -= job;
                scheduleAndPrintJob(iteration, job, i);
                inserted = true;
                break;
            }
        }
        if(!inserted)
        {
            int temp = job;
            jobs.push(temp);
        }
        jobqueue.pop();
    }
    jobqueue.concatenate(jobs);
}

// Do not change
int main(int argc, char *argv[]) {


    ifstream inf(argv[1]);
    if (inf.fail()) {
        cout << "Error" << endl;
        return 1;
    }

    // read number of resources, work capacity per resource
    int numResources;
    int capacity;
    string firstLine;
    getline(inf, firstLine);
    stringstream ss(firstLine);
    ss >> numResources;
    ss >> capacity;

    QueueInt jobqueue;
    int iteration = 0;
    int *resources = new int[numResources];
    double loading = 0;

    while( (!inf.fail()) || (!jobqueue.empty()) ) {
        iteration++;
        // reset resources
        for (int i = 0; i < numResources; i++) {
            resources[i] = capacity;
        }

        /*************** Add your code here ****************/


        QueueInt temp = readLine(inf);
        jobqueue.concatenate(temp);

        scheduleJobs(resources, jobqueue, iteration, numResources);
        







        /*************** Stop your code here ***************/

        // Loading Computation
        double total = 0;
        for(int i=0; i < numResources; i++) {
            total += capacity-resources[i];
        }
        loading += total / (capacity*numResources);

    }
    cout << "Average loading: ";
    if(iteration == 0) {
        cout << 0.0 << endl;
    }
    else {
        cout << loading / (iteration) << endl;
    }
    inf.close();
    delete [] resources;
    return 0;
}
