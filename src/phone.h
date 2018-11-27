#ifndef PHONE_H_
#define PHONE_H_

#define N_PHONE 21
#define N_STATE		3
#define N_PDF		2
#define N_DIMENSION	39

#include <string>
#include <array>

using namespace std;

typedef struct {
  double weight;
  double mean[N_DIMENSION];
  double var[N_DIMENSION];
} pdfType;

typedef struct {
  pdfType pdf[N_PDF];
} stateType;

typedef struct {
  string name;
  double tp[N_STATE+2][N_STATE+2];
  stateType state[N_STATE];
} phoneType;

extern std::array<phoneType, N_PHONE> phones;

void readPhoneHMM(const std::string& path);
void writePhoneHMM(const std::string& path);

int getPhoneIndex(string name);
int getNumberOfPhoneState(int index);

#endif
