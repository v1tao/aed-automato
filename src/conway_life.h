#include <random>
//tamanho maximo para matriz
#define M 50
#define N 50
//matriz globais usadas 
int mat[M][N];
int temp_mat[M][N];

//funcao que salva a matriz em um arquivo
void save_matrix_file(int m, int n){
	FILE *arquivo;
    arquivo = fopen ("matrix.txt", "w");
  
   	fprintf(arquivo, "%d %d\n", m, n);   
    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++) 
        	fprintf(arquivo, "%d ", mat[i][j]);
  		
  		fprintf(arquivo, "\n"); 
    }
    fclose(arquivo);
}
//funcao para carregar a matriz previamente salva na maquina
void load_matrix_file(int *m, int *n){
	int temp_m = *m;
	int temp_n = *n;	
	
	FILE *arquivo;
	arquivo = fopen ("matrix.txt", "r");
	if ((arquivo = fopen("matrix.txt", "r")) == NULL) {
        printf("Erro! Abrir Arquivo");
    }
    else{
	    fscanf(arquivo, "%d %d", &temp_m, &temp_n);

	   	while(!feof(arquivo)){	
		   	for (int i = 0; i < temp_m; i++){
		   		for (int j = 0; j < temp_n; j++)
		   			fscanf(arquivo, "%d", &mat[i][j]);
		  		fscanf(arquivo, "\n"); 
		   	} 
		}
	    fclose(arquivo);
	}
	*m = temp_m;
	*n = temp_n;
}
//funcao responsavel por mostrar a matriz principal
void print_mat(int m, int n){
	std::cout << "\n";	
	for(int i = 0; i < m; i++){
		std::cout << "|";
		for (int j = 0; j < n; j++){
			if(mat[i][j] == 1)	
				std::cout << "\033[1;32m" << mat[i][j] << "\033[0m ";
			else
				std::cout << "\033[1;31m" << mat[i][j] << "\033[0m ";	
		}
		std::cout << "\b|\n";
	}
	std::cout << "\n";
}
//funcao responsavel por preencher a matriz de forma pseudo aleatoria
void rand_mat(int m, int n){
	std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist1(0, 1); // distribution in range [1, 6]	

	for(int i = 0; i < m; i++){
		for (int j = 0; j < n; j++)
			mat[i][j] = dist1(rng);
	}
}

//funcao responsavel por preencher a matrix de forma manual
void manual_mat(int m, int n){
	std::cout << "|";	
	for(int i = 0; i < m; i++){
		for(int j = 0; j < n; j++){
			std::cin >> mat[i][j];
			std::cout << " ";	
		}
		std::cout << "\b|";	
	}
}
//matriz responsavel para copiar a matriz temporaria e armazena-la na principal
void copy_matrix(int m, int n){
	for(int i = 0; i < m; i++){
		for(int j = 0; j < n; j++)
			temp_mat[i][j] = mat[i][j];
	}
}
//funcao responsavel por copiar a matriz principal e armazena-la na temporaria
void copy_matrix_inverse(int m, int n){
	for(int i = 0; i < m; i++){
		for(int j = 0; j < n; j++)
			mat[i][j] = temp_mat[i][j];
	}
}
/*
funcao responsavel por checar os possiveis arredores de cada celula em posicoes especificas
tambem responsavel por trocar a o estado da celula de acordo com os arredores
*/
void check_surrounding_elements(int pos_i, int pos_j, int m, int n){
	int count_live = 0;
	if(pos_i == 0 && pos_j == 0){
		if(mat[pos_i][pos_j + 1] == 1)	
			count_live++;
		if(mat[pos_i + 1][pos_j] == 1)	
			count_live++;
		if(mat[pos_i + 1][pos_j + 1] == 1)
			count_live++;		
	}
	else if(pos_i == 0 && pos_j == n - 1){
		if(mat[pos_i][pos_j - 1] == 1)	
			count_live++;
		if(mat[pos_i + 1][pos_j] == 1)	
			count_live++;
		if(mat[pos_i + 1][pos_j - 1] == 1)
			count_live++;
	}
	else if(pos_i == m - 1 && pos_j == 0){
		if(mat[pos_i][pos_j + 1] == 1)	
			count_live++;
		if(mat[pos_i - 1][pos_j] == 1)	
			count_live++;
		if(mat[pos_i - 1][pos_j + 1] == 1)
			count_live++;	
	}
	else if(pos_i == m - 1 && pos_j == n - 1){
		if(mat[pos_i][pos_j - 1] == 1)	
			count_live++;
		if(mat[pos_i - 1][pos_j] == 1)	
			count_live++;
		if(mat[pos_i - 1][pos_j - 1] == 1)
			count_live++;
	}
	else{
		for (int j = pos_j - 1; j <= pos_j + 1; j++){
			if (mat[pos_i - 1][j] == 1)
				count_live++;
		}
		for (int j = pos_j - 1; j <= pos_j + 1; j++){
			if (mat[pos_i + 1][j] == 1)
				count_live++;
		}	
		if(mat[pos_i][pos_j - 1] == 1)
			count_live++;
		if(mat[pos_i][pos_j + 1] == 1)
			count_live++;
	}

	if (mat[pos_i][pos_j] == 1){
		if(count_live > 3 || count_live < 2)
			temp_mat[pos_i][pos_j] = 0;
	}	
	if (mat[pos_i][pos_j] == 0 && count_live == 3)
		temp_mat[pos_i][pos_j] = 1;

}
//funcao responsavel pelo menu, e contar o numero de mortos e vivos em volta da celula selecionada mat[i][j]
void life_loop(int m, int n){
	int lives = 0;	
	int dead = 0;
	
	/*
	loop inicialmente criado com intuito de parar o funcionamento do conway life	
	caso a matriz fique morta(completa de 0) ou entao 100% viva ( completa de 1)	
	*/
	for(int i = 0; i < m; i++){
		for(int j = 0; j < n; j++){
			if(mat[i][j] == 0)
				dead++;
			else
				lives++;
		}
	}

	/*
	loop responsavel por controlar o menu	
	durante o processamento da matriz	
	*/
	int life_loop_menu_option; 
	while(dead != 0 || dead != (m * n)){
		system("clear");	
		print_mat(m, n);
		for(int i = 0; i < m; i++){
			for(int j = 0; j < n; j++)
				check_surrounding_elements(i, j, m, n);
		}
		copy_matrix_inverse(m, n);	

		std::cout << "\033[0;34m|1|\033[0m \033[0;33mProxima configuracao\033[0m" << std::endl;
		std::cout << "\033[0;34m|2|\033[0m \033[0;33mSalvar matriz\033[0m" << std::endl; 
		std::cout << "\033[0;34m|0|\033[0m \033[0;33mVoltar ao Menu Principal\033[0m" << std::endl;	
		std::cout << "\n\033[0;33mDigite a operacao desejada: \033[0m";	
		std::cin  >> life_loop_menu_option;	
		if(life_loop_menu_option == 1)
			continue;
		else if(life_loop_menu_option == 2){
			save_matrix_file(m, n);	
			std::cout << "Matriz Salva!" << std::endl;
		}
		else if(life_loop_menu_option == 0)
			break;
		else
			std::cout << "Opcao nao existente" << std::endl;	
		estetica1();	
	}
}
//funcao responsavel pelo menu principal do jogo da vida (conway life)
void menu_conway_life(){
	int m = 0;	
	int n = 0;  
	int opcao_menu_conway;

	

	do
    {
    	system("clear");	
    	azul();
   		std::cout << "\t\t############################" << std::endl;
   		std::cout << "----------------## \033[0;33m   ---CONWAY LIFE---   \033[0m\033[0;34m##----------------" << std::endl;
   		std::cout << "\t\t############################\n" << std::endl;
    	reset();	    

        std::cout << "\033[0;34m|1|\033[0m \033[0;33mPreencher matriz inicial automaticamente\033[0m" << std::endl;
		std::cout << "\033[0;34m|2|\033[0m \033[0;33mPreencher matriz inicial manualmente\033[0m" << std::endl; 
		std::cout << "\033[0;34m|3|\033[0m \033[0;33mCarregar matriz salva\033[0m" << std::endl;	
		std::cout << "\033[0;34m|0|\033[0m \033[0;33mVoltar ao Menu Principal\033[0m" << std::endl;
        amarelo();
        std::cout << "\nDigite a operacao desejada: ";reset();
        std::cin >> opcao_menu_conway;
        estetica1();
       	system("clear"); 
      
            switch (opcao_menu_conway) {
                case 1:
                {
                    azul();
			   		std::cout << "\t\t############################" << std::endl;
			   		std::cout << "----------------## \033[0;33m   ---CONWAY LIFE---   \033[0m\033[0;34m##----------------" << std::endl;
			   		std::cout << "\t\t############################\n" << std::endl;
			    	reset(); 
                    std::cout << "\033[0;34m_-||\033[0m \033[0;33mPreenchimento de matriz inicial automatica\033[0m \033[0;34m||-_\033[0m\n" << std::endl;
                    std::cout << "\033[0;33mDigite o tamanho da matriz desejada mat[\033[0;35mm\033[0m\033[0;33m][\033[0m\033[0;35mn\033[0m\033\033[0;33m]\033[0m" << std::endl;
					std::cout << "\033[0;35mM\033[0;35m \033[0;33m-->\033[0;35m ";
					std::cin  >> m;
					std::cout << "\033[0;35mN\033[0;35m \033[0;33m-->\033[0;35m ";
					std::cin  >> n;
				   	std::cout << "\033[0m"; 
				    rand_mat(m, n);
					copy_matrix(m, n);	
					life_loop(m, n); 
                    break;
               		system("clear"); 
                }
                case 2:
                {
                    std::cout << "\033[0;34m_-||\033[0m \033[0;33mPreenchimento de matriz inicial manual\033[0m \033[0;34m||-_\033[0m\n" << std::endl;
                    std::cout << "\033[0;33mDigite o tamanho da matriz desejada mat[\033[0;35mm\033[0m\033[0;33m][\033[0m\033[0;35mn\033[0m\033\033[0;33m]\033[0m" << std::endl;
					std::cout << "\033[0;35mM\033[0;35m \033[0;33m-->\033[0;35m ";
					std::cin  >> m;
					std::cout << "\033[0;35mN\033[0;35m \033[0;33m-->\033[0;35m ";
					std::cin  >> n;
					std::cout << "\033[0m\n";	
					
					manual_mat(m, n);                    
                   	copy_matrix(m, n); 
                   	life_loop(m, n);
                    break;
                }
               	case 3:
               	{
                    std::cout << "\033[0;34m_-||\033[0m \033[0;33mCarregar matriz salva\033[0m \033[0;34m||-_\033[0m\n" << std::endl;
                    
                    load_matrix_file(&m, &n);
               		copy_matrix(m, n);
               		life_loop(m, n);
               		break;
               	} 
                case 0:
                {
                    break;
                }
                default:
                   printf("ERRO!! Opcao nao existente!\n");
            }
            estetica1();
        }while (opcao_menu_conway != 0);

}