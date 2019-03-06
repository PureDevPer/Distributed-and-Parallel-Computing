typedef struct {
        int row;
        int col;
        double **mat_data;
} mat_struct;

mat_struct *getMatInfo(char mat[], int matSize);
void print_mat(mat_struct *matPrint, int matrixSize);
void free_mat(mat_struct *makeFreeMat, int matrixSize);
void write_mat(mat_struct *matWrite, int matrixSize);
double *matLinear(mat_struct *m, int matrixSize, int numMatrix);
void print_mat_mpi(double *output, int matrixSize, int numMatrix);
void write_mat_mpi(double *output, int matrixSize, int numMatrix);