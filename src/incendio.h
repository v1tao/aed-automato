#include <stdlib.h>
#include <cstdlib>
#include <random>
#include <chrono>
#define M 50
#define N 50
//estados
#define VAZIO 0
#define VEGETACAO 1
#define FOGO 2
#define AGUA 3
//clima
#define CHUVA  -1
#define SECO   -2
#define NORMAL -3


struct Estado{
	int valor;
	int idade;
};

struct Estado mat_incendio[M][N];
struct Estado mat_incendio_temp[M][N];

//declaracoes das funcoes
void save_matrix_file_incendio(int m, int n);
void load_matrix_file_incendio(int *m, int *n);
int check_surrounding_empty(int pos_i, int pos_j, int m, int n);
int check_surrounding_forest(int pos_i, int pos_j, int m, int n);
int check_surrounding_fire(int pos_i, int pos_j, int m, int n);
int check_surrounding_water(int pos_i, int pos_j, int m, int n);

typedef std::mt19937 rng_type;
std::uniform_int_distribution<rng_type::result_type> udist(0, 7);

rng_type rng;

int rand_generator_incendio()
{
 	using namespace std;	
 	// seed rng first:
 	unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator(seed);
    normal_distribution<double> distribution(0.0, 100.0);
    
    double random_num = distribution(generator);
    if(random_num < 0)
 		return (int)random_num % 100 * -1;
 	return (int)random_num % 100;
}


/*
	criacao do ecossistema
	-------------------------
	| ESTADO    |	CHANCE  |
	-------------------------	
	| VAZIO		|	 18 %   |
	| VEGETACAO	|	 32 %   |	
	| FOGO		|    30 %   |
	| AGUA 		|	 20 %   |
	-------------------------
 */
void rand_mat_incendio(int m, int n){
	int count_empty;
	int count_forest;
	int count_fire;
	int count_water;	
	/*
	std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist10(0, 10); 	
	*/
	
	
   	//preenchimento temporario 
    for(int i = 0; i < m; i++){
    	for(int j = 0; j < n; j ++)
    		mat_incendio[i][j].valor = 9;
    }

	for(int i = 0; i < m; i++){
		for(int j = 0; j < n; j++){
			
			int dice_roll = rand_generator_incendio();	
			std::cout << dice_roll;	
			//zerar o contador para cada celula	
			count_empty  = 0;
			count_forest = 0;	
			count_fire   = 0;	
			count_water  = 0;
			
			count_empty  = check_surrounding_empty(i, j, m, n);	
			count_forest = check_surrounding_forest(i, j, m, n);	
			count_fire   = check_surrounding_fire(i, j, m, n);	
			count_water  = check_surrounding_water(i, j, m, n);	
			//Chance de ser AGUA no ecossistema 30% 
			if(dice_roll >= 0 && dice_roll < 27){
				mat_incendio[i][j].valor = AGUA;
				mat_incendio[i][j].idade = 0;	
			
			}	
			//Chance de ser VEGETACAO no ecossistema 37%	
			else if(dice_roll >= 37 && dice_roll < 60){
				mat_incendio[i][j].valor = VEGETACAO;
				mat_incendio[i][j].idade = 0;
			}	
			//Chance de ser VAZIO no ecossistema 18%	
			else if(dice_roll >= 60 && dice_roll < 97){ 
				mat_incendio[i][j].valor = VAZIO;
				mat_incendio[i][j].idade = 0;	
			}	
			//Chance de ser FOGO no ecossistema 13%	
			else{
				mat_incendio[i][j].valor = FOGO;
				mat_incendio[i][j].idade = 0;	
			}	
		}
	}	
} 

void manual_mat_incendio(int m, int n){
	std::cout << "|";	
	for(int i = 0; i < m; i++){
		for(int j = 0; j < n; j++){
			std::cin >> mat_incendio[i][j].valor;
			mat_incendio[i][j].valor = 0;	
			std::cout << " ";	
		}
		std::cout << "\b|";		
	}
}
void copy_mat_incendio(int m, int n){
	for(int i = 0; i < m; i++){
		for(int j = 0; j < n; j++){
			mat_incendio_temp[i][j].idade = mat_incendio[i][j].idade;
			mat_incendio_temp[i][j].valor = mat_incendio[i][j].valor;
		}
	}
}

void copy_mat_incendio_inverse(int m, int n){
	for(int i = 0; i < m; i++){
		for(int j = 0; j < n; j++){
			mat_incendio_temp[i][j].idade = mat_incendio[i][j].idade;
			mat_incendio[i][j].valor = mat_incendio_temp[i][j].valor;
		}
	}
}

int clima_rand(){
	int clima_atual = 0;	

	
	int dice_roll = rand_generator_incendio();	
  /*  
	 0 = normal
    -1 = chuva
	-2 = seca    */
    if(dice_roll < 13)
    	clima_atual = CHUVA;
    
    else if(dice_roll > 24 && dice_roll <= 34)
    	clima_atual = SECO;
   	 
    else
    	clima_atual = NORMAL;
    std::cout << dice_roll << "gerado " << clima_atual << std::endl;
    return clima_atual;
}


void print_mat_incendio(int m, int n){
	std::cout << "\n";	
	for(int i = 0; i < m; i++){
		std::cout << "\x1B[37m|\033[0m";
		for (int j = 0; j < n; j++){
			if(mat_incendio[i][j].valor == 0)	
				std::cout << "\033[1;37m" << mat_incendio[i][j].valor << "\033[0m ";
			else if(mat_incendio[i][j].valor == 1)
				std::cout << "\033[1;32m" << mat_incendio[i][j].valor << "\033[0m ";	
			else if(mat_incendio[i][j].valor == 2)
				std::cout << "\033[1;31m" << mat_incendio[i][j].valor << "\033[0m ";	
			else
				std::cout << "\033[1;36m" << mat_incendio[i][j].valor << "\033[0m ";
		}
		std::cout << "\b\x1B[37m|\033[0m\n";
	}
	std::cout << "\n";
}	

int check_surrounding_fire(int pos_i, int pos_j, int m, int n){
	int count_fire = 0;
	if(pos_i == 0 && pos_j == 0){
		if(mat_incendio[pos_i][pos_j + 1].valor == FOGO)	
			count_fire++;
		if(mat_incendio[pos_i + 1][pos_j].valor == FOGO)	
			count_fire++;
		if(mat_incendio[pos_i + 1][pos_j + 1].valor == FOGO)
			count_fire++;		
	}
	else if(pos_i == 0 && pos_j == n - 1){
		if(mat_incendio[pos_i][pos_j - 1].valor == FOGO)	
			count_fire++;
		if(mat_incendio[pos_i + 1][pos_j].valor == FOGO)	
			count_fire++;
		if(mat_incendio[pos_i + 1][pos_j - 1].valor == FOGO)
			count_fire++;
	}
	else if(pos_i == m - 1 && pos_j == 0){
		if(mat_incendio[pos_i][pos_j + 1].valor == FOGO)	
			count_fire++;
		if(mat_incendio[pos_i - 1][pos_j].valor == FOGO)	
			count_fire++;
		if(mat_incendio[pos_i - 1][pos_j + 1].valor == FOGO)
			count_fire++;	
	}
	else if(pos_i == m - 1 && pos_j == n - 1){
		if(mat_incendio[pos_i][pos_j - 1].valor == FOGO)	
			count_fire++;
		if(mat_incendio[pos_i - 1][pos_j].valor == FOGO)	
			count_fire++;
		if(mat_incendio[pos_i - 1][pos_j - 1].valor == FOGO)
			count_fire++;
	}
	else{
		for (int j = pos_j - 1; j <= pos_j + 1; j++){
			if (mat_incendio[pos_i - 1][j].valor == FOGO)
				count_fire++;
		}
		for (int j = pos_j - 1; j <= pos_j + 1; j++){
			if (mat_incendio[pos_i + 1][j].valor == FOGO)
				count_fire++;
		}	
		if(mat_incendio[pos_i][pos_j - 1].valor == FOGO)
			count_fire++;
		if(mat_incendio[pos_i][pos_j + 1].valor == FOGO)
			count_fire++;
	}
	return count_fire;
}

int check_surrounding_empty(int pos_i, int pos_j, int m, int n){
	int count_empty = 0;
	if(pos_i == 0 && pos_j == 0){
		if(mat_incendio[pos_i][pos_j + 1].valor == VAZIO)	
			count_empty++;
		if(mat_incendio[pos_i + 1][pos_j].valor == VAZIO)	
			count_empty++;
		if(mat_incendio[pos_i + 1][pos_j + 1].valor == VAZIO)
			count_empty++;		
	}
	else if(pos_i == 0 && pos_j == n - 1){
		if(mat_incendio[pos_i][pos_j - 1].valor == VAZIO)	
			count_empty++;
		if(mat_incendio[pos_i + 1][pos_j].valor == VAZIO)	
			count_empty++;
		if(mat_incendio[pos_i + 1][pos_j - 1].valor == VAZIO)
			count_empty++;
	}
	else if(pos_i == m - 1 && pos_j == 0){
		if(mat_incendio[pos_i][pos_j + 1].valor == VAZIO)	
			count_empty++;
		if(mat_incendio[pos_i - 1][pos_j].valor == VAZIO)	
			count_empty++;
		if(mat_incendio[pos_i - 1][pos_j + 1].valor == VAZIO)
			count_empty++;	
	}
	else if(pos_i == m - 1 && pos_j == n - 1){
		if(mat_incendio[pos_i][pos_j - 1].valor == VAZIO)	
			count_empty++;
		if(mat_incendio[pos_i - 1][pos_j].valor == VAZIO)	
			count_empty++;
		if(mat_incendio[pos_i - 1][pos_j - 1].valor == VAZIO)
			count_empty++;
	}
	else{
		for (int j = pos_j - 1; j <= pos_j + 1; j++){
			if (mat_incendio[pos_i - 1][j].valor == VAZIO)
				count_empty++;
		}
		for (int j = pos_j - 1; j <= pos_j + 1; j++){
			if (mat_incendio[pos_i + 1][j].valor == VAZIO)
				count_empty++;
		}	
		if(mat_incendio[pos_i][pos_j - 1].valor == VAZIO)
			count_empty++;
		if(mat_incendio[pos_i][pos_j + 1].valor == VAZIO)
			count_empty++;
	}
	return count_empty;
}
int check_surrounding_water(int pos_i, int pos_j, int m, int n){
	int count_water = 0;
	if(pos_i == 0 && pos_j == 0){
		if(mat_incendio[pos_i][pos_j + 1].valor == AGUA)	
			count_water++;	
		if(mat_incendio[pos_i + 1][pos_j].valor == AGUA)	
			count_water++;
		if(mat_incendio[pos_i + 1][pos_j + 1].valor == AGUA)
			count_water++;		
	}
	else if(pos_i == 0 && pos_j == n - 1){
		if(mat_incendio[pos_i][pos_j - 1].valor == AGUA)	
			count_water++;
		if(mat_incendio[pos_i + 1][pos_j].valor == AGUA)	
			count_water++;
		if(mat_incendio[pos_i + 1][pos_j - 1].valor == AGUA)
			count_water++;
	}
	else if(pos_i == m - 1 && pos_j == 0){
		if(mat_incendio[pos_i][pos_j + 1].valor == AGUA)	
			count_water++;
		if(mat_incendio[pos_i - 1][pos_j].valor == AGUA)	
			count_water++;
		if(mat_incendio[pos_i - 1][pos_j + 1].valor == AGUA)
			count_water++;	
	}
	else if(pos_i == m - 1 && pos_j == n - 1){
		if(mat_incendio[pos_i][pos_j - 1].valor == AGUA)	
			count_water++;
		if(mat_incendio[pos_i - 1][pos_j].valor == AGUA)	
			count_water++;
		if(mat_incendio[pos_i - 1][pos_j - 1].valor == AGUA)
			count_water++;
	}
	else{
		for (int j = pos_j - 1; j <= pos_j + 1; j++){
			if (mat_incendio[pos_i - 1][j].valor == AGUA)
				count_water++;
		}
		for (int j = pos_j - 1; j <= pos_j + 1; j++){
			if (mat_incendio[pos_i + 1][j].valor == AGUA)
				count_water++;
		}	
		if(mat_incendio[pos_i][pos_j - 1].valor == AGUA)
			count_water++;
		if(mat_incendio[pos_i][pos_j + 1].valor == AGUA)
			count_water++;
	}
	return count_water;
}

int check_surrounding_forest(int pos_i, int pos_j, int m, int n){
	int count_forest = 0;
	if(pos_i == 0 && pos_j == 0){
		if(mat_incendio[pos_i][pos_j + 1].valor == VEGETACAO)	
			count_forest++;
		if(mat_incendio[pos_i + 1][pos_j].valor == VEGETACAO)	
			count_forest++;
		if(mat_incendio[pos_i + 1][pos_j + 1].valor == VEGETACAO)
			count_forest++;		
	}
	else if(pos_i == 0 && pos_j == n - 1){
		if(mat_incendio[pos_i][pos_j - 1].valor == VEGETACAO)	
			count_forest++;
		if(mat_incendio[pos_i + 1][pos_j].valor == VEGETACAO)	
			count_forest++;
		if(mat_incendio[pos_i + 1][pos_j - 1].valor == VEGETACAO)
			count_forest++;
	}
	else if(pos_i == m - 1 && pos_j == 0){
		if(mat_incendio[pos_i][pos_j + 1].valor == VEGETACAO)	
			count_forest++;
		if(mat_incendio[pos_i - 1][pos_j].valor == VEGETACAO)	
			count_forest++;
		if(mat_incendio[pos_i - 1][pos_j + 1].valor == VEGETACAO)
			count_forest++;	
	}
	else if(pos_i == m - 1 && pos_j == n - 1){
		if(mat_incendio[pos_i][pos_j - 1].valor == VEGETACAO)	
			count_forest++;
		if(mat_incendio[pos_i - 1][pos_j].valor == VEGETACAO)	
			count_forest++;
		if(mat_incendio[pos_i - 1][pos_j - 1].valor == VEGETACAO)
			count_forest++;
	}
	else{
		for (int j = pos_j - 1; j <= pos_j + 1; j++){
			if (mat_incendio[pos_i - 1][j].valor == VEGETACAO)
				count_forest++;
		}
		for (int j = pos_j - 1; j <= pos_j + 1; j++){
			if (mat_incendio[pos_i + 1][j].valor == VEGETACAO)
				count_forest++;
		}	
		if(mat_incendio[pos_i][pos_j - 1].valor == VEGETACAO)
			count_forest++;
		if(mat_incendio[pos_i][pos_j + 1].valor == VEGETACAO)
			count_forest++;
	}
	return count_forest;
}

void state_change(int m, int n){
	int clima = clima_rand();	
	
	for(int i = 0; i < m; i++){
		for(int j = 0; j < n; j++){
			mat_incendio_temp[i][j].idade++;	
			int count_forest = 0;	
			int count_water  = 0;
			int count_empty  = 0;
			int count_fire   = 0;
	
			count_forest = check_surrounding_forest(i, j, m, n);
			count_water  = check_surrounding_water(i, j, m, n);
			count_empty  = check_surrounding_empty(i, j, m, n);
			count_fire   = check_surrounding_fire(i, j, m, n);	
			switch(mat_incendio[i][j].valor){			
				case VAZIO:
				{				
					if(clima == CHUVA){
						if(count_water > 3)
							mat_incendio_temp[i][j].valor = AGUA;
						else{
							if(count_water >= 1 && count_forest >= 2)
								mat_incendio_temp[i][j].valor = VEGETACAO;
								mat_incendio_temp[i][j].idade = 0;	
						}
					}
					else if(clima == SECO){
						if(count_water >= 2 && count_forest >= 2){
							mat_incendio_temp[i][j].valor = VEGETACAO;
							mat_incendio_temp[i][j].idade = 0;	
						}
					}
					else{
						if(count_water >= 1 && count_forest >= 2)
							mat_incendio_temp[i][j].valor = VEGETACAO;
					}	
					break;
				}
				case VEGETACAO:
				{
					if(clima == CHUVA){
						mat_incendio_temp[i][j].idade == 0;	
						if(count_water > 4)
							mat_incendio_temp[i][j].valor = AGUA;
						else if(count_fire > 4){
							mat_incendio_temp[i][j].valor = FOGO;
							mat_incendio_temp[i][j].idade = 0;	
						}
					}	
					else if(clima == SECO){
						if(count_fire > 2){
							mat_incendio_temp[i][j].valor = FOGO; 
							mat_incendio_temp[i][j].idade = 0;	
						}
						else if(mat_incendio[i][j].idade > 7){
							mat_incendio_temp[i][j].valor = VAZIO;
						}
					}	
					else{
						if(count_fire > 3){
							mat_incendio_temp[i][j].valor = FOGO; 
							mat_incendio_temp[i][j].idade = 0;	
						}
						else if(mat_incendio[i][j].idade > 10){
							mat_incendio_temp[i][j].valor = VAZIO;
						}	
					}	
					break;
				}
				case FOGO:
				{
					if(clima == CHUVA){
						if(count_fire <= 2){
							mat_incendio_temp[i][j].valor = VAZIO;
						}
						else if(count_water > 3){
							mat_incendio_temp[i][j].valor = AGUA;
						}	
						else if(mat_incendio[i][j].idade >= 5)
							mat_incendio_temp[i][j].valor = VAZIO;	
					}	
					else if(clima == SECO){
						if(mat_incendio[i][j].idade > 7)
							mat_incendio_temp[i][j].valor = VAZIO;
					}	
					else{
						if(mat_incendio[i][j].idade > 7)
							mat_incendio_temp[i][j].valor = VAZIO;	
					}	
					break;
				}
				case AGUA:
				{
					if(clima == CHUVA){
						mat_incendio_temp[i][j].idade = 0;
					}	
					else if(clima == SECO){
						if(count_water <= 1 && mat_incendio[i][j].idade >= 4)
							mat_incendio_temp[i][j].valor = VAZIO;
					}	
					else{
						if(count_water <= 1 && mat_incendio[i][j].idade >= 7)
							mat_incendio_temp[i][j].valor = VAZIO;	
					}	
					break;
				}	
				default:
					std::cout << "tem algum bug cabuloso";	
			}
		}
		
	}
	copy_mat_incendio_inverse(m, n);	
	std::cout << "Clima Atual: ";
	if(clima == CHUVA)
		std::cout << "\x1B[34mCHOVENDO\033[0m" << std::endl;
	else if(clima == SECO)
		std::cout << "\x1B[93mSECO\033[0m\n" << std::endl;
	else
		std::cout << "\x1B[37mNORMAL\033[0m" << std::endl;
}
void incendio_loop(int m, int n){
	for(;;){	
		int incendio_loop_menu_option;			
	
		state_change(m, n);	
		print_mat_incendio(m, n);
		std::cout << "\033[0;34m|1|\033[0m \033[0;33mProxima configuracao\033[0m" << std::endl;
		std::cout << "\033[0;34m|2|\033[0m \033[0;33mPular 10 configuracoes\033[0m" << std::endl;
		std::cout << "\033[0;34m|3|\033[0m \033[0;33mSalvar matriz\033[0m" << std::endl; 
		std::cout << "\033[0;34m|0|\033[0m \033[0;33mVoltar ao Menu Principal\033[0m" << std::endl;	
		std::cout << "\n\033[0;33mDigite a operacao desejada: \033[0m";	
		std::cin  >> incendio_loop_menu_option;	
		
		if(incendio_loop_menu_option == 1)
			continue;
		else if(incendio_loop_menu_option == 2){
			continue;	
		}
		else if(incendio_loop_menu_option == 3){
			save_matrix_file_incendio(m, n);	
			std::cout << "Matriz Salva!" << std::endl;
		}
		else if(incendio_loop_menu_option == 0)
			break;
		else 
			std::cout << "Opcao nao existente" << std::endl;	
		
		estetica1();	
	}
}


void save_matrix_file_incendio(int m, int n){
	FILE *arquivo;
    arquivo = fopen ("matrix_incendio.txt", "w");
  
   	fprintf(arquivo, "%d %d\n", m, n);   
    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++) 
        	fprintf(arquivo, "%d ", mat_incendio[i][j].valor);
  		
  		fprintf(arquivo, "\n"); 
    }
    fclose(arquivo);
}

void load_matrix_file_incendio(int *m, int *n){
	int temp_m = *m;
	int temp_n = *n;	
	
	FILE *arquivo;
	arquivo = fopen ("matrix_incendio.txt", "r");
	if ((arquivo = fopen("matrix_incendio.txt", "r")) == NULL) {
        printf("Erro! Abrir Arquivo");
    }
    else{
	    fscanf(arquivo, "%d %d", &temp_m, &temp_n);

	   	while(!feof(arquivo)){	
		   	for (int i = 0; i < temp_m; i++){
		   		for (int j = 0; j < temp_n; j++)
		   			fscanf(arquivo, "%d", &mat_incendio[i][j].valor);
		  		fscanf(arquivo, "\n"); 
		   	} 
		}
	    fclose(arquivo);
	}
	*m = temp_m;
	*n = temp_n;
}
void menu_incendio(){
	int m = 0;	
	int n = 0;  
	int opcao_menu_incendio;

	

	do
    {
    	system("clear");	
    	azul();
   		std::cout << "\t\t###################################" << std::endl;
   		std::cout << "----------------## \033[0;33m   ---SIMULACAO INCENDIO---   \033[0m\033[0;34m##----------------" << std::endl;
   		std::cout << "\t\t###################################\n" << std::endl;
    	reset();	    

        std::cout << "\033[0;34m|1|\033[0m \033[0;33mPreencher matriz inicial automaticamente\033[0m" << std::endl;
		std::cout << "\033[0;34m|2|\033[0m \033[0;33mPreencher matriz inicial manualmente\033[0m" << std::endl; 
		std::cout << "\033[0;34m|3|\033[0m \033[0;33mCarregar matriz salva\033[0m" << std::endl;	
		std::cout << "\033[0;34m|0|\033[0m \033[0;33mVoltar ao Menu Principal\033[0m" << std::endl;
        amarelo();
        std::cout << "\nDigite a operacao desejada: ";reset();
        std::cin >> opcao_menu_incendio;
        estetica1();
       	system("clear"); 
      
            switch (opcao_menu_incendio) {
                case 1:
                {
                    azul();
			   		std::cout << "\t\t###################################" << std::endl;
			   		std::cout << "----------------## \033[0;33m   ---SIMULACAO INCENDIO---   \033[0m\033[0;34m##----------------" << std::endl;
			   		std::cout << "\t\t###################################\n" << std::endl;
			    	reset(); 
                    std::cout << "\033[0;34m_-||\033[0m \033[0;33mPreenchimento de matriz inicial automatica\033[0m \033[0;34m||-_\033[0m\n" << std::endl;
                    std::cout << "\033[0;33mDigite o tamanho da matriz desejada mat[\033[0;35mm\033[0m\033[0;33m][\033[0m\033[0;35mn\033[0m\033\033[0;33m]\033[0m" << std::endl;
					std::cout << "\033[0;35mM\033[0;35m \033[0;33m-->\033[0;35m ";
					std::cin  >> m;
					std::cout << "\033[0;35mN\033[0;35m \033[0;33m-->\033[0;35m ";
					std::cin  >> n;
				   	std::cout << "\033[0m"; 
				    
				    rand_mat_incendio(m, n);
					copy_mat_incendio(m, n);	
                   	print_mat_incendio(m, n);	
                   	incendio_loop(m, n);
                  	system("clear"); 
                    break;
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
					
					manual_mat_incendio(m, n);                    
                   	copy_mat_incendio(m, n); 
                   	incendio_loop(m, n); 
                   	system("clear"); 
                    break;
                }
               	case 3:
               	{
                    std::cout << "\033[0;34m_-||\033[0m \033[0;33mCarregar matriz salva\033[0m \033[0;34m||-_\033[0m\n" << std::endl;
                    
                    load_matrix_file_incendio(&m, &n);
               		copy_mat_incendio(m, n);
               		incendio_loop(m, n);
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
        }while (opcao_menu_incendio != 0);

}