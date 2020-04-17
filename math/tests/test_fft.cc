/* -------------------------------------------------------------------
* A very simple FFT test. 
* Alexander Karlsson, begun 2015-08-12
* -------------------------------------------------------------------- */
#include "../fast_fourier_transform.cc"

/* Test */
int main()
{
  comp_array data{0.0, 1.0, 0.0, 1.0};
  data = FFT(data);

  cout << "fft" << endl;
  for (int i = 0; i < 8; ++i) {
    cout << data[i] << endl;
  }

  iFFT(data);

  data = iFFT(data);

  cout << endl << "ifft" << endl;
  for (int i = 0; i < 8; ++i) {
    cout << data[i] << endl;
  }

  return 0;
}
