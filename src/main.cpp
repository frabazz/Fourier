#define MAX_SAMPLES_CHANNELL 1000
#define MAX_CHANNELLS 2
    /*
ex max 10, min 2
scale = (max-min)/2 = 4
maxAbs = max - scale = 6
2 3 4 5 || 6 7 8 9 10

 */
#include <endian.h>
#include <cstdint>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cinttypes>
#include <iostream>

using namespace std;

typedef struct waveHeader {
    char ChunkID[4];
    uint32_t ChunkSize;
    char Format[4];
    char Subchunk1ID[4];
    uint32_t Subchunk1size;
    uint16_t AudioFormat;
    uint16_t NumChannels;
    uint32_t SampleRate;
    uint32_t ByteRate;
    uint16_t BlockAlign;
    uint16_t BitsPerSample;
    uint16_t ExtraParamSize;
    char Subchunk2ID[4];
    uint32_t Subchunk2Size;
} __attribute__((__packed__)) WaveHeader_t;

//TODO -> check BE, LE on strings
void charArrToBE(char buff[], int size){
    int i, n = 1;
    char buff_copy[size];

    if(*(char *)&n == 1){//if it is LE, convert to BE
        for(i = 0; i < size; i++){
            buff_copy[i] = buff[i];
            printf("%c", buff[i]);
        }
        printf("\n");
        for(i = 0;i < size; i++)
            buff[i] = buff_copy[size-i-1];
    }
}

int halfStrcmp(char s[], char buff[], int size){
    int i, ris = 1;
    for(i = 0; ris && i < size;i++){
        ris = (s[i] == buff[i]);
        printf("%c == %c\n", s[i], buff[i]);
    }
    return ris;
}
/*
es : 2 3 4 5  6 7 8 9 10

es: 2 -> (2 - 4)/6

*/
double normalizeSample(int16_t sample, int16_t max, int16_t min){
    double scale = ((double)sample)/((double)(max-min))/2.0;
    //return (scale - 0.5);
    return (double)sample / (double)1;
}

int readHeader(FILE* fp, WaveHeader_t* header){
    fread(header, sizeof(WaveHeader_t), 1, fp);
    //LE conversion
    header -> ChunkSize = htole32(header -> ChunkSize);
    header -> Subchunk1size = htole32(header -> Subchunk1size);
    header -> AudioFormat = htole16(header -> AudioFormat);
    header -> NumChannels = htole16(header -> NumChannels);
    header -> SampleRate = htole32(header -> SampleRate);
    header -> ByteRate = htole32(header -> ByteRate);
    header -> BlockAlign = htole16(header -> BlockAlign);
    header -> BitsPerSample = htole16(header -> BitsPerSample);
    header -> Subchunk2Size = htole32(header -> Subchunk2Size);
    //BE conversion
    /*
    charArrToBE(header -> ChunkID, 4);
    charArrToBE(header -> Format, 4);
    charArrToBE(header -> Subchunk1ID, 4);
    charArrToBE(header -> Subchunk1ID, 4);
    */
    int ris = (
        header -> ByteRate == (header -> SampleRate * header -> NumChannels * ((header -> BitsPerSample)/8)) &&
        header -> BlockAlign == (header -> NumChannels * ((header -> BitsPerSample)/8)) &&
        header -> AudioFormat == 1 &&
        (header -> BitsPerSample == 8 || header -> BitsPerSample == 16 || header -> BitsPerSample == 32)
    );

    return ris;
}

int16_t sampleArr[2][MAX_SAMPLES_CHANNELL];
float sampleArrNorm[2][MAX_SAMPLES_CHANNELL];

int main(int argc, char* argv[]){
    FILE* fp;
    fp = fopen(argv[1], "rb");
    WaveHeader_t header;
    if(readHeader(fp, &header)){
        uint32_t samples = header.Subchunk2Size / header.NumChannels / (header.BitsPerSample/8);
        printf("no of samples: %" PRIu32 "\n", samples);
        uint32_t sampleOffset = samples/MAX_SAMPLES_CHANNELL;
        printf("bits per sample: %" PRIu16 "\n", header.BitsPerSample);
        printf("number of channells : %" PRIu16 "\n", header.NumChannels);
        printf("extra param size: %" PRIu16 "\n", header.ExtraParamSize);
        //uint32_t channels[header.NumChannels][samples];
        int k = 0;

        for(uint32_t i = 0;i < samples;i++){
            for(uint16_t j = 0;j < header.NumChannels;j++){
                int16_t sample;
                fread(&sample, sizeof(int16_t), 1, fp);
                int16_t notvalue = 0;
                if(k < MAX_SAMPLES_CHANNELL  && sampleOffset != 0 && i%sampleOffset == 0 && sample != notvalue){
                    sampleArr[j][k] = htole16(sample);
                    //printf("%d\n", (int)sampleArr[j][k]);
                    k++;
                }
            }
        }

        printf("read samples from file \n");
        for(uint16_t j = 0;j < header.NumChannels;j++){
            int16_t maxSample = sampleArr[j][0];
            int16_t minSample = sampleArr[j][0];

            for(int i = 0;i < MAX_SAMPLES_CHANNELL;i++){
                if(sampleArr[j][i] > maxSample)
                    maxSample = sampleArr[j][i];
                if(sampleArr[j][i] < minSample)
                    minSample = sampleArr[j][i];
            }
            for(int i = 0;i < MAX_SAMPLES_CHANNELL;i++){
                sampleArrNorm[j][i] = normalizeSample(sampleArr[j][i], maxSample, minSample);
            }
        }
        for(uint16_t j = 0;j < header.NumChannels;j++){
            char filename[100];
            sprintf(filename, "output%d.txt", (int)j);
            printf("printing %s...\n", filename);
            FILE* fpOut = fopen(filename, "w+");
            for(int i = 0;i < MAX_SAMPLES_CHANNELL;i++)
                fprintf(fpOut, "%f ", sampleArrNorm[j][i]);

            fclose(fpOut);
        }

    }
    else
        printf("ERROR! Invalid WAV file\n");
    fclose(fp);
    return 0;
}
