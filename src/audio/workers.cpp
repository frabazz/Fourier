#include "workers.hpp"
#include <iostream>

using namespace audio_workers;


void audio_workers::sample_read_worker(sample_read_params params){
    if(params.range->first < 0){
        params.range->second += std::abs(params.range->first);
        params.range->first = 0;
        if(params.range->second > params.wav->sampleSize)
            params.range->second = params.wav->sampleSize;
        }

    if(params.range->second > params.wav->sampleSize){
        params.range->first -= (params.range->second - params.wav->sampleSize);
        params.range->second = params.wav->sampleSize;
        if(params.range->first < 0)
            params.range->first = 0;
    }

    double delta =  (params.range->second - params.range->first)/(double)(params.npoints);

    params.wav->seekStart();
    params.wav->seek(params.range->first);

    for(int i = 0; i < params.npoints - 1; ++i){
        double sample = 0.0;
        params.wav->readSample(&sample);
        //std::cout << "read sample index " << params.range->first + (i+1) * delta << " ";
        //std::cout << "position : " << _wav_file->tell() << std::endl;
        // std::cout << " of value " << sample << std::endl ;
        int cast_delta = i * delta;
        params.wav->seek((int)delta - 1);
        //_wav_file->seek((int)delta * (-1));
        params.data->push_back({(int)params.range->first + cast_delta, sample});
    }



    params.wav->seekStart(); // leave it as we got it!

    *params.min_y = -1.25;
    *params.max_y = 1.25;
    std::cout << "[SAMPLE READ WORKER] generated v of size: " << params.data->size() << std::endl;
/*     *_wav_file = Wave::WaveFile("../assets/sin.wav");
    if(!_wav_file->open())
        std::cout << "error opening file" << std::endl;
*/

}
