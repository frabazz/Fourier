#ifndef PLOTTER_WORKER_H
#define PLOTTER_WORKER_H

#include <mutex>

#include "../audio/wave.hpp"
#include "../common.hpp"

struct worker_params {
    dpair* range;
    double* min_y;
    double* max_y;
    int npoints;
    std::vector<dpair>* data;
};

class PlotterWorker{
    public:
        PlotterWorker(){};
        virtual void run(worker_params params) = 0;
};

class AsyncPlotterWorker{
    public:
        virtual void run(worker_params params, std::mutex* vecmtx) = 0;
        virtual bool finished() = 0;
        AsyncPlotterWorker(){};
};

class SampleReadWorker : public PlotterWorker{
    public:
        SampleReadWorker(Wave::WaveFile* file);
        void run(worker_params params) override;

    private:
        Wave::WaveFile* _wav_file;

};

class SpectrumWorker : public AsyncPlotterWorker{
    public:
        SpectrumWorker(Wave::WaveFile* file);
        void run(worker_params params, std::mutex* mutex) override;

    private:
        Wave::WaveFile* _wav_file;
};


#endif
