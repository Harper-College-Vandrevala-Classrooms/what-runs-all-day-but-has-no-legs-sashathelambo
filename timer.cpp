#include <chrono>
#include <iostream>
using namespace std;

class CPlusPlusTime {
public:
    virtual chrono::high_resolution_clock::time_point now() const {
        return chrono::high_resolution_clock::now();
    }
};

class Timer {
public:
    Timer(CPlusPlusTime* time_provider = nullptr) 
        : started_(false), start_time_(), elapsed_time_(0), time_provider_(time_provider) {
        if (!time_provider_) {
            time_provider_ = new CPlusPlusTime();
        }
    }
    Timer(long long elapsed_time, CPlusPlusTime* time_provider = nullptr) 
        : started_(false), start_time_(), elapsed_time_(elapsed_time), time_provider_(time_provider) {
        if (!time_provider_) {
            time_provider_ = new CPlusPlusTime();
        }
    }

    void start() {
        if (!started_) {
            start_time_ = time_provider_->now();
            started_ = true;
        } else {
            cerr << "Warning: Timer already started. Continuing from current time." << endl;
        }
    }

    void stop() {
        if (started_) {
            auto end_time = time_provider_->now();
            auto duration = chrono::duration_cast<chrono::seconds>(end_time - start_time_);
            elapsed_time_ = duration.count();
            started_ = false;
        } else {
            cerr << "Warning: Timer not started. Cannot stop." << endl;
        }
    }

    long long elapsed() const {
        if (!started_) {
            return elapsed_time_;
        } else {
            auto end_time = time_provider_->now();
            auto duration = chrono::duration_cast<chrono::seconds>(end_time - start_time_);
            return duration.count();
        }
    }

    void pretty_print() const {
        long long seconds = elapsed_time_;
        if (seconds == 0) {
            cout << "No time has passed." << endl;
        } else {
            long long hours = seconds / 3600;
            seconds %= 3600;
            long long minutes = seconds / 60;
            seconds %= 60;
            cout << hours << " hour" << (hours == 1 ? "" : "s") << ", "
                 << minutes << " minute" << (minutes == 1 ? "" : "s") << ", and "
                 << seconds << " second" << (seconds == 1 ? "" : "s") << " has passed." << endl;
        }
    }

    Timer add(const Timer& other) const {
        return Timer(elapsed_time_ + other.elapsed_time_, time_provider_);
    }

    Timer subtract(const Timer& other) const {
        return Timer(elapsed_time_ - other.elapsed_time_, time_provider_);
    }

private:
    bool started_;
    chrono::high_resolution_clock::time_point start_time_;
    long long elapsed_time_;
    CPlusPlusTime* time_provider_;
};
