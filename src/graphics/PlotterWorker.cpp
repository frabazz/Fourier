#include "PlotterWorker.hpp"
#include "wave.hpp"

#include <iostream>


SampleReadWorker::SampleReadWorker(Wave::WaveFile* file) : PlotterWorker(){
    _wav_file = file;
}

void SampleReadWorker::run(worker_params params){
    if(params.range->first < 0){
        params.range->second += std::abs(params.range->first);
        params.range->first = 0;
        if(params.range->second > _wav_file->sampleSize)
            params.range->second = _wav_file->sampleSize;
        }

    if(params.range->second > _wav_file->sampleSize){
        params.range->first -= (params.range->second - _wav_file->sampleSize);
        params.range->second = _wav_file->sampleSize;
        if(params.range->first < 0)
            params.range->first = 0;
    }

    double delta =  (params.range->second - params.range->first)/(double)(params.npoints);

    _wav_file->seekStart();
    _wav_file->seek(params.range->first);

    for(int i = 0; i < params.npoints - 1; ++i){
        double sample = 0.0;
        _wav_file->readSample(&sample);
        //std::cout << "read sample index " << params.range->first + (i+1) * delta << " ";
        //std::cout << "position : " << _wav_file->tell() << std::endl;
        // std::cout << " of value " << sample << std::endl ;
        int cast_delta = i * delta;
        _wav_file->seek((int)delta - 1);
        //_wav_file->seek((int)delta * (-1));
        params.data->push_back({(int)params.range->first + cast_delta, sample});
    }



    _wav_file->seekStart(); // leave it as we got it!

    *params.min_y = -1.25;
    *params.max_y = 1.25;
    std::cout << "generated v of size: " << params.data->size() << std::endl;
/*     *_wav_file = Wave::WaveFile("../assets/sin.wav");
    if(!_wav_file->open())
        std::cout << "error opening file" << std::endl;
*/

}
