
class EqSolver{

 public:

  EqSolver();//construtor

  void SwapRows(int,int,double**,int);
  void GaussElimination(double**,double*,int);
  double* GaussEliminationSolver();
  double* FindRowMax(double**,int,int);
  void LUdecomposition3(float*,float*,float*,int);
  static void LUdecomposition3(double*,double*,double*,int);
  float* LUsolve3(float*,float*,float*,float*,int);
  static double* LUsolve3(double*,double*,double*,double*,int);
  

  ~EqSolver();//destrutor


 private:
  double** m;
  double** L;
  double** U;
  double *b;
  int decision; //variavel que contem a informacao sobre quais dos ponteiros foram instanciados e permite fazer a decisao de quais vao ser, portanto, apagados
  int mexist, bexist, Uexist, Lexist;//variavel que contem a informacao sobre se ja foi ou nao alocado espaco para a matriz m. E importante caso se queira obter a resolucao de varios sistemas utilizando o mesmo objeto EqSolver - a matriz m nao e fixa (nem o vetor b)
  int dim;

};
