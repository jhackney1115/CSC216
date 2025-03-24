#include <iostream>
#include <vector>
#include <climits>

using namespace std;

class Job
{
private:
  string name;
  int priority;

public:
  Job(string n, int p) : name(n), priority(p) {}

  void execute()
  {
    cout << "Running the job with name "
              << name
              << " and priority "
              << priority
              << endl;
  }

  string getName()
  {
    return name;
  }

  int getPriority()
  {
    return priority;
  }
  bool operator==(Job & otherJob) const{
    return priority==otherJob.getPriority();
  }
  bool operator>(Job & otherJob) const{
        return priority>otherJob.getPriority();
  }
  bool operator<(Job & otherJob) const{
        return priority<otherJob.getPriority();
  }
};

template <typename T>//, typename Compare=greater<T>> 
class PriorityQueue {
  protected:
    vector<T> data;
    //Compare greater_than;

    size_t parent(size_t j) { return (j-1) / 2; }
    size_t left(size_t j) { return 2 * j + 1; }
    size_t right(size_t j) { return 2 * j + 2; }
    bool has_left(size_t j) { return left(j) < data.size(); }
    bool has_right(size_t j) { return right(j) < data.size(); }
    
    void upheap(size_t j) {
        while (j > 0) {
            size_t p{parent(j)};
            if (data[j]>data[p]) {
                swap(data[j], data[p]);
                j = p;
            } else {
                break;
            }
    }
    }
    
    void downheap(size_t j) {
        while (has_left(j)) {                            
            size_t large_child{left(j)};
            if (has_right(j)) {
                if (data[right(j)] > data[left(j)])
                    large_child = right(j);
            }

            if (data[large_child] > data[j]) { 
                swap(data[j], data[large_child]);
                j = large_child;
            } else
                break;
        }
    }

  public:
    PriorityQueue() : data(vector<T>()){}

    int size() const { return data.size(); }
    bool empty() const { return data.empty(); }
    const T& max() const { return data.front(); }
    
    void insert(const T& e) {
        data.push_back(e);
        upheap(static_cast<unsigned>(data.size() - 1)); 
    }
    
    
    T remove_max() {
        swap(data[0], data[data.size() - 1]);
        T temp = data.back();
        data.pop_back();    
        downheap(0);
        return temp;
    }
};

class JobQueue {
    private:
    PriorityQueue<Job> jobQ;
    public:
    JobQueue() : jobQ(PriorityQueue<Job>()) {}  
    void insert(Job job){
        jobQ.insert(job);
    }
    void runHighestPriority(){
        jobQ.remove_max().execute();
    }
};

int main(){
    //Higher number = priority
    // i.e 1 != first priority
    JobQueue jobQueue;
 
    Job jobA("job a", 5);
    Job jobB("job b", 2);
    Job jobC("job c", 9);
    Job jobD("job d", 8);
    Job jobE("job e", 1);
    jobQueue.insert(jobA);
    jobQueue.insert(jobB);
    jobQueue.insert(jobC);
    jobQueue.insert(jobD);
    jobQueue.insert(jobE);

    jobQueue.runHighestPriority(); 
    // Calls jobC.execute() since job C has the highest priority

    jobQueue.runHighestPriority(); 
    // Calls jobD.execute() since job D has the next highest priority

    jobQueue.runHighestPriority(); 
    // Calls jobA.execute() since job A has the next highest priority

    jobQueue.runHighestPriority(); 
    // Calls jobB.execute() since job B has the next highest priority

    jobQueue.runHighestPriority();
    // Calls jobE.execute since it is last one

    return 0;
}
