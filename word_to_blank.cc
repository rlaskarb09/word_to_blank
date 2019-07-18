// The MIT License (MIT)

// Copyright (c) 2019 Namkyu Kim

//  Permission is hereby granted, free of charge, to any person obtaining a
//  copy of this software and associated documentation files (the "Software"),
//  to deal in the Software without restriction, including without limitation
//  the rights to use, copy, modify, merge, publish, distribute, sublicense,
//  and/or sell copies of the Software, and to permit persons to whom the
//  Software is furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
//  OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
//  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
//  DEALINGS IN THE SOFTWARE.

/* code */


#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <random>
#include <chrono>


#define MAX_LENGTH 100000
#define BLANK_PROBABILITY 0.2

using namespace std;

template<typename Out>
void split (const string &s, char delim, Out result)
{
  stringstream ss(s);
  string item;

  while (getline (ss, item, delim))
    *(result++) = item;
}

vector<string> split(const string &s, const char delim)
{
  vector<string> elems;
  split(s, delim, back_inserter(elems));

  return elems;
}

int main (int argc, char *argv[])
{
  string input_file;
  if (argc != 2)
  { 
    cout << "How to use :" << endl;
    cout << "./word_to_blank input.txt" << endl;
    return 0;
  }
  else
  {
    input_file = string(argv[1]);
  }
  char input_buffer[MAX_LENGTH];

  ifstream input_stream (input_file);

  if (input_stream.is_open())
  {
    input_stream.readsome(input_buffer, MAX_LENGTH);
    // cout << input_buffer << endl;
    input_stream.close();

    string blank("[        ]");

    string input_text (input_buffer);
    

    vector<string> x = split(input_text, ' ');
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine gen(seed);
    uniform_real_distribution<double> distribution(0.0, 1.0);

    string output("");



    for (auto i = x.begin(); i != x.end(); i++)
    {
      if (i != x.begin() && (distribution(gen) < BLANK_PROBABILITY) && (*i).compare("\n") != 0)
      {
        *i = blank;
      }
      output.append(*i);
      if (i + 1 != x.end())
        output.append(" ");
    }

    cout << output;
  }

  return 0;
}