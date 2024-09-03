// parameters

/* 
Neural Network Description: 
INPUT: (1, 28, 28, 1)
CONVOLUTION: (1, 28, 28, 4) 
FC: (1, 20) 
FC: (1, 20)
*/

#define B1_CONV1_IN_DIM_X 28				
#define B1_CONV1_IN_DIM_Y 28				
#define B1_CONV1_IN_CH 1					
#define B1_CONV1_KER_DIM_X 3				
#define B1_CONV1_KER_DIM_Y 3				
#define B1_CONV1_PAD_X 1					// padding = same
#define B1_CONV1_PAD_Y 1					// padding = same
#define B1_CONV1_STRIDE_X 1					
#define B1_CONV1_STRIDE_Y 1					
#define B1_CONV1_OUT_DIM_X 28				
#define B1_CONV1_OUT_DIM_Y 28				
#define B1_CONV1_OUT_CH 4					

#define B1_CONV1_RELU_OUT_CH 4			
#define B1_CONV1_RELU_OUT_DIM_X 28		
#define B1_CONV1_RELU_OUT_DIM_Y 28   		 

#define B1_POOL_IN_DIM_X 28
#define B1_POOL_IN_DIM_Y 28
#define B1_POOL_IN_CH 4
#define B1_POOL_KER_DIM_X 2
#define B1_POOL_KER_DIM_Y 2
#define B1_POOL_PAD_X 0
#define B1_POOL_PAD_Y 0
#define B1_POOL_STRIDE_X 2
#define B1_POOL_STRIDE_Y 2
#define B1_POOL_OUT_DIM_X 14
#define B1_POOL_OUT_DIM_Y 14

#define FC1_IN_DIM 784
#define FC1_OUT_DIM 20

#define FC2_IN_DIM 20
#define FC2_OUT_DIM 10





