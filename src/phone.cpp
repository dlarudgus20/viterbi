#include "phone.h"

#include <string.h>

using namespace std;

std::array<phoneType, N_PHONE> phones;

void readPhoneHMM(const std::string& path)
{
    std::array<phoneType, N_PHONE>& hmm = phones;
    FILE *hmmFile = fopen(path.c_str(), "r");

    char line[30], *token;
    char delimiter[] = "\" ";
    char dummyChar[30];
    int i, j, k, l, dummyInt;

    for (i = 0; i < N_PHONE; i++)
    {
        fgets(line, 30, hmmFile);

        token = strtok(line, delimiter);
        token = strtok(NULL, delimiter); // Read phone name

        hmm[i].name = token;

        fgets(line, 30, hmmFile); // Read <BEGINHMM>
        fgets(line, 30, hmmFile); // Read <NUMSTATES>

        for (j = 0; j < getNumberOfPhoneState(i); j++)
        {
            fgets(line, 30, hmmFile); // Read <STATE>
            fgets(line, 30, hmmFile); // Read <NUMMIXES>
            for (k = 0; k < N_PDF; k++)
            {
                fscanf(hmmFile, "%s", dummyChar);
                fscanf(hmmFile, "%d %lf", &dummyInt, &hmm[i].state[j].pdf[k].weight); // Read pdf weight
                //hmm[i].state[j].pdf[k].weight = log(hmm[i].state[j].pdf[k].weight);
                fgets(line, 30, hmmFile);

                fgets(line, 30, hmmFile);
                for (l = 0; l < N_DIMENSION; l++)
                { // Read mean
                    fscanf(hmmFile, "%lf", &hmm[i].state[j].pdf[k].mean[l]);
                }
                fgets(line, 30, hmmFile);

                fgets(line, 30, hmmFile);
                for (l = 0; l < N_DIMENSION; l++)
                { // Read variance
                    fscanf(hmmFile, "%lf", &hmm[i].state[j].pdf[k].var[l]);
                }
                fgets(line, 30, hmmFile);
            }
        }

        fgets(line, 30, hmmFile); // Read <TRAMSP>
        for (j = 0; j < getNumberOfPhoneState(i) + 2; j++)
        {
            for (k = 0; k < getNumberOfPhoneState(i) + 2; k++)
            {
                fscanf(hmmFile, "%lf", &hmm[i].tp[j][k]);
                //hmm[i].tp[j][k] = log(hmm[i].tp[j][k]);
            }
        }
        fgets(line, 30, hmmFile);
        fgets(line, 30, hmmFile); // Read <ENDHMM>
    }

    fclose(hmmFile);
}

int getPhoneIndex(string name) {
  for (int i = 0; i < N_PHONE; i++) {
    if(phones[i].name == name) return i;
  }
  return -1; // if there's no phone with given name
}

int getNumberOfPhoneState(int index) {
  if (index == 17) return 1; // "sp"
  return 3;
}
