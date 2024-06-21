#include "workers.hpp"
#include "wave.hpp"

#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

using namespace audio_workers;

namespace {

void fourew(std::vector<std::fstream *> &file, int &na, int &nb, int &nc,
            int &nd) {
  int i;
  for (i = 0; i < 4; i++)
    (*file[i]).seekp(0);
  for (i = 0; i < 4; i++)
    (*file[i]).seekg(0);
  std::swap(file[1], file[3]);
  std::swap(file[0], file[2]);
  na = 2;
  nb = 3;
  nc = 0;
  nd = 1;
}

/*
I have absolutely no clue of how this works internally. It's from Numerical
Recipes in C++(https://numerical.recipes/).

The parameters are:
- a vector of four data files (2 input and 2 output)
- a vector of dimensions size (yes it works also in multiple dimensions)
- isign = 1 for FFT, -1 for IFFT
*/
  
void fourfs(std::vector<std::fstream *> &file, std::vector<int> &nn,
            const int isign) {
  const int KBF = 128;
  static int mate[4] = {1, 0, 3, 2};
  int cc, cc0, j, j12, jk, k, kk, n = 1, mm, kc = 0, kd, ks, kr, na, nb, nc, nd,
                                  nr, ns, nv;
  double tempr, tempi, wr, wi, wpr, wpi, wtemp, theta;
  std::vector<double> afa(KBF), afb(KBF), afc(KBF);
  int ndim = nn.size();
  for (j = 0; j < ndim; j++) {
    n *= nn[j];
    if (nn[j] <= 1)
      std::cout << "invalid Doub or wrong ndim in fourfs" << std::endl;
  }
  nv = 0;
  jk = nn[nv];
  mm = n;
  ns = n / KBF;
  nr = ns >> 1;
  kd = KBF >> 1;
  ks = n;
  fourew(file, na, nb, nc, nd);
  for (;;) {
    theta = isign * 3.141592653589793 / (n / mm);
    wtemp = sin(0.5 * theta);
    wpr = -2.0 * wtemp * wtemp;
    wpi = sin(theta);
    wr = 1.0;
    wi = 0.0;
    mm >>= 1;
    for (j12 = 0; j12 < 2; j12++) {
      kr = 0;
      do {
        cc0 = (*file[na]).tellg() / sizeof(double);
        (*file[na]).read((char *)&afa[0], KBF * sizeof(double));
        cc = (*file[na]).tellg() / sizeof(double);
        if ((cc - cc0) != KBF)
	  std::cout << "read error 1 in fourfs" << std::endl;
        cc0 = (*file[nb]).tellg() / sizeof(double);
        (*file[nb]).read((char *)&afb[0], KBF * sizeof(double));
        cc = (*file[nb]).tellg() / sizeof(double);
        if ((cc - cc0) != KBF)
	  std::cout << "read error 2 in fourfs" << std::endl;
        for (j = 0; j < KBF; j += 2) {
          tempr = wr * afb[j] - wi * afb[j + 1];
          tempi = wi * afb[j] + wr * afb[j + 1];
          afb[j] = afa[j] - tempr;
          afa[j] += tempr;
          afb[j + 1] = afa[j + 1] - tempi;
          afa[j + 1] += tempi;
        }
        kc += kd;
        if (kc == mm) {
          kc = 0;
          wr = (wtemp = wr) * wpr - wi * wpi + wr;
          wi = wi * wpr + wtemp * wpi + wi;
        }
        cc0 = (*file[nc]).tellp() / sizeof(double);
        (*file[nc]).write((char *)&afa[0], KBF * sizeof(double));
        cc = (*file[nc]).tellp() / sizeof(double);
        if ((cc - cc0) != KBF)
	  std::cout << "write error 1 in fourfs" << std::endl;
        cc0 = (*file[nd]).tellp() / sizeof(double);
        (*file[nd]).write((char *)&afb[0], KBF * sizeof(double));
        cc = (*file[nd]).tellp() / sizeof(double);
        if ((cc - cc0) != KBF)
	  std::cout << "write error 2 in fourfs" << std::endl;
      } while (++kr < nr);
      if (j12 == 0 && ks != n && ks == KBF) {
        na = mate[na];
        nb = na;
      }
      if (nr == 0)
        break;
    }
    fourew(file, na, nb, nc, nd);
    jk >>= 1;
    while (jk == 1) {
      mm = n;
      jk = nn[++nv];
    }
    ks >>= 1;
    if (ks > KBF) {
      for (j12 = 0; j12 < 2; j12++) {
        for (kr = 0; kr < ns; kr += ks / KBF) {
          for (k = 0; k < ks; k += KBF) {
            cc0 = (*file[na]).tellg() / sizeof(double);
            (*file[na]).read((char *)&afa[0], KBF * sizeof(double));
            cc = (*file[na]).tellg() / sizeof(double);
            if ((cc - cc0) != KBF)
	      std::cout << "read error 3 in fourfs" << std::endl;
            cc0 = (*file[nc]).tellp() / sizeof(double);
            (*file[nc]).write((char *)&afa[0], KBF * sizeof(double));
            cc = (*file[nc]).tellp() / sizeof(double);
            if ((cc - cc0) != KBF)
	      std::cout <<  "write error 3 in fourfs" << std::endl;
          }
          nc = mate[nc];
        }
        na = mate[na];
      }
      fourew(file, na, nb, nc, nd);
    } else if (ks == KBF)
      nb = na;
    else
      break;
  }
  j = 0;
  for (;;) {
    theta = isign * 3.141592653589793 / (n / mm);
    wtemp = sin(0.5 * theta);
    wpr = -2.0 * wtemp * wtemp;
    wpi = sin(theta);
    wr = 1.0;
    wi = 0.0;
    mm >>= 1;
    ks = kd;
    kd >>= 1;
    for (j12 = 0; j12 < 2; j12++) {
      for (kr = 0; kr < ns; kr++) {
        cc0 = (*file[na]).tellg() / sizeof(double);
        (*file[na]).read((char *)&afc[0], KBF * sizeof(double));
        cc = (*file[na]).tellg() / sizeof(double);
        if ((cc - cc0) != KBF)
	  std::cout << "read error 4 in fourfs" << std::endl;
        kk = 0;
        k = ks;
        for (;;) {
          tempr = wr * afc[kk + ks] - wi * afc[kk + ks + 1];
          tempi = wi * afc[kk + ks] + wr * afc[kk + ks + 1];
          afa[j] = afc[kk] + tempr;
          afb[j] = afc[kk] - tempr;
          afa[++j] = afc[++kk] + tempi;
          afb[j++] = afc[kk++] - tempi;
          if (kk < k)
            continue;
          kc += kd;
          if (kc == mm) {
            kc = 0;
            wr = (wtemp = wr) * wpr - wi * wpi + wr;
            wi = wi * wpr + wtemp * wpi + wi;
          }
          kk += ks;
          if (kk > KBF - 1)
            break;
          else
            k = kk + ks;
        }
        if (j > KBF - 1) {
          cc0 = (*file[nc]).tellp() / sizeof(double);
          (*file[nc]).write((char *)&afa[0], KBF * sizeof(double));
          cc = (*file[nc]).tellp() / sizeof(double);
          if ((cc - cc0) != KBF)
	    std::cout << "write error 4 in fourfs" << std::endl;
          cc0 = (*file[nd]).tellp() / sizeof(double);
          (*file[nd]).write((char *)&afb[0], KBF * sizeof(double));
          cc = (*file[nd]).tellp() / sizeof(double);
          if ((cc - cc0) != KBF)
	    std::cout << "write error 5 in fourfs" << std::endl;
          j = 0;
        }
      }
      na = mate[na];
    }
    fourew(file, na, nb, nc, nd);
    jk >>= 1;
    if (jk > 1)
      continue;
    mm = n;
    do {
      if (nv < ndim - 1)
        jk = nn[++nv];
      else
        return;
    } while (jk == 1);
  }
}

} // namespace

void audio_workers::sample_read_worker(sample_read_params params) {
  if (params.range->first < 0) {
    params.range->second += std::abs(params.range->first);
    params.range->first = 0;
    if (params.range->second > params.wav->sampleSize)
      params.range->second = params.wav->sampleSize;
  }

  if (params.range->second > params.wav->sampleSize) {
    params.range->first -= (params.range->second - params.wav->sampleSize);
    params.range->second = params.wav->sampleSize;
    if (params.range->first < 0)
      params.range->first = 0;
  }

  double delta =
      (params.range->second - params.range->first) / (double)(params.npoints);

  params.wav->seekStart();
  params.wav->seek(params.range->first);

  for (int i = 0; i < params.npoints - 1; ++i) {
    double sample = 0.0;
    params.wav->readSample(&sample);
    // std::cout << "read sample index " << params.range->first + (i+1) * delta
    // << " "; std::cout << "position : " << _wav_file->tell() << std::endl;
    //  std::cout << " of value " << sample << std::endl ;
    int cast_delta = i * delta;
    params.wav->seek((int)delta - 1);
    //_wav_file->seek((int)delta * (-1));
    params.data->push_back({(int)params.range->first + cast_delta, sample});
  }

  params.wav->seekStart(); // leave it as we got it!

  *params.min_y = -1.25;
  *params.max_y = 1.25;
  std::cout << "[SAMPLE READ WORKER] generated v of size: "
            << params.data->size() << std::endl;
  /*     *_wav_file = Wave::WaveFile("../assets/sin.wav");
      if(!_wav_file->open())
          std::cout << "error opening file" << std::endl;
  */
}

void audio_workers::fft_worker(Wave::WaveFile *wav, std::vector<dpair>* data){
  wav->seekStart();
  std::fstream in1, in2;
  std::fstream out1, out2;

  
  in1 = std::fstream("in1_tmp", std::ios::binary | std::ios::out);
  in2 = std::fstream("in2_tmp", std::ios::binary | std::ios::out);  
  out1 = std::fstream("out1_tmp", std::ios::binary | std::ios::out | std::ios::in);
  out2 = std::fstream("out2_tmp", std::ios::binary | std::ios::out | std::ios::in);

  if(!in1 || !in2 || !out1 || !out2)
    std::cout << "tmp error" << std::endl;

  //TODO int32?
  int sample_size = wav->sampleSize;
  int fft_size = 1;
  
  while(fft_size < sample_size){
    fft_size <<= 1;
  }

  std::cout << "sample size : " << sample_size << " , fft_size: " << fft_size << std::endl; 
  
  double sample;
  double pad = 0.0;
  int i = 0;
  int h = fft_size >> 1;
  
  for(i = 0; i < h; i++){
    double j;
    if(i < sample_size)
      wav->readSample(&j);
    else
      j = 0;

    in1.write((char*)&j, sizeof(double));
  }

  
  for(i = 0; i < h; i++){
    double j;
    if(i + h < sample_size)
      wav->readSample(&j);
    else
      j = 0;

    in2.write((char*)&j, sizeof(double));
  }

  
  in1.close();
  in2.close();

  std::fstream in1_fft, in2_fft;
  in1_fft = std::fstream("in1_tmp", std::ios::binary | std::ios::out | std::ios::in);
  in2_fft = std::fstream("in2_tmp", std::ios::binary | std::ios::out | std::ios::in);

  std::vector<std::fstream*> fft_streams = {&in1_fft, &in2_fft, &out1, &out2};
  std::vector<int> dims = {fft_size};
  fourfs(fft_streams, dims, 1);
}
