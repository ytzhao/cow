[An Even Easier Introduction to CUDA](https://devblogs.nvidia.com/parallelforall/even-easier-introduction-cuda/)

- **kernel**
  Add the specifier ```__global__```  to the function, and the code that runs on the GPU is often call _device code_, the code that runs on the CPU is _host code_.
- **Memory allocation**
  To allocate data in unified memory, call ```cudaMallocManaged()```, which return a pointer that you can access from host (CPU) code or device (GPU) code. Call ```cudaFree()``` to free the data.
- **Launch the kernel**
  CUDA kernel launches are specified using the triple angle bracket syntax ```<<<>>>```
- **Synchronize data** 
  We need the CPU to wait until the kernel is done before it accesses the results (**CUDA kernel launches don't block the calling CPU thread**). To do this, just call ```cudaDeviceSynchronize()``` before doing the final error checking on the CPU.
- **Compile file and profile it**
  CUDA files have the file extension ```.cu``` , compile CUDA code with ```nvcc```.
```prompt
nvcc myCuda.cu -o my_cuda
nvprof ./my_cuda
```
- **Choose the threads**
  CUDA GPUs run kernels using **blocks of threads**, e.g:
```cpp
add<<<1, 256>>>(N, x, y);
```
```<<<1, 256>>>``` is the key! There are two parameters, ```<<<the number of thread blockes, the number of  threads in a thread block>>>```. Together, the blocks of parallel threads make up a _grid_. CUDA C++ provides keywords that let kernels get the indices of the running threads, ```threadIdx.x, blockDim.x``` etc. 
- **Out of the blocks**

- **Full code**
```cpp
#include <iostream>
#include <math.h>

// Kernel function to add the elements of two arrays
__global__
void add(int n, float *x, float *y) 
{
  int index = blockIdx.x * blockDim.x + threadIdx.x;
  int stride = blockDim.x * gridDim.x;
  for ( int i = index; i < n; i += stride ) {
    y[i]  = x[i] + y[i];
  }
}


int main(void)
{
  int N = 1 << 20;
  float *x, *y;

  // Allocate Unified Memory - accessible from CPU or GPU
  cudaMallocManaged(&x, N*sizeof(float));
  cudaMallocManaged(&y, N*sizeof(float));

  // Initialize x and y arrays on the host
  for ( int i=0; i<N; i++ ) {
    x[i] = 1.0f;
    y[i] = 2.0f;
  }

  // Run kernel on 1M elements on the GPU
  int blockSize = 256;
  int numBlocks = (N + blockSize - 1) / blockSize;
  add<<<numBlocks, blockSize>>>(N, x, y);

  // Wait for GPU to finish before accessing on host
  cudaDeviceSynchronize();

  // Check for errors (all values should be 3.0f)
  float maxError = 0.0f;
  for ( int i=0; i<N; i++ ) {
    maxError = fmax( maxError, fabs(y[i]-3.0f) );
  } 
  std::cout << "Max error: " << maxError << std::endl;

  // Free memory
  cudaFree(x);
  cudaFree(y);

  return 0;
}
```
- :tada: :tada: :tada: