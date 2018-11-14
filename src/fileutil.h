#ifndef FILEUTIL_H_
#define FILEUTIL_H_

#include <vector>
#include <string>

using namespace std;

int listFilePaths (string prefix, string dir, vector<string> &paths);
int listAllInputPaths (string prefix, vector<string> &paths);

#endif
