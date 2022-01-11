#include "matrix.h"

//probably works
void realref(float **p, int rowc, int colc) {
	int lead = 0; 
	for(int r = 0; r < rowc; r++) {
		if(colc <= lead)
			return;
		int i = r;
		while(p[i][lead] == 0) {
			i++;
			if(rowc == i) {
				i = r;
				lead++; 
				if(colc == lead) 
					return;	
				
			}
		}

		if(i != r) {
			for(int j = 0; j < colc; j++) {
				float temp = p[i][j];
				p[i][j] = p[r][j];
				p[r][j] = temp; 
			}
		}
		for(int h = 0; h < rowc; h++) {
			if(h != r) {
				float treason = p[h][lead]; 
				for(int j = 0; j < colc; j++) 
					if(j == lead)
						p[h][j] = 0; 
					else 
						p[h][j] -= (p[r][j]/p[r][lead])*treason;
					
			}
		}

		lead++; 
	}
}
//needs to be fixed, especially the allocation checks;
void ref(struct matrix *m) {
	int rowc = m->rows, colc = m->cols;
	float **p; 
	p = (float **) malloc(rowc * sizeof(float)); 
	for(int row = 0; row < rowc; row++) 
		p[row] = (float *) malloc(colc * sizeof(float)); 
	
	for(int i = 0; i < rowc; i++) 
		for(int j = 0; j < colc; j++) 
			p[i][j] = m->pin[i*colc + j]; 

	realref(p, rowc, colc); 	
	
	for(int i = 0; i < rowc; i++)
		for(int j = 0; j < colc; j++) 
			m->pin[i*colc + j] = p[i][j]; 

	for(int row = 0; row < rowc; row++)
		free(p[row]); 
	free(p); 
} 

int main() {
	struct matrix *m = NULL;
	int r = 3, c = 3;
	char name[mxid]; 
	scanf("%s", name);  
	init_matrix(&m, r, c, name); 
	query_values(m); 
/*	query_id(name); 
	initmatrix(&ref, r, c, name);	
*/
	show_matrix(m);
	putchar('\n'); 
	ref(m); 
	show_matrix(m);  
}


