#include <stdlib.h>
#include <gmp.h>

const char* p_str = "93450983094850938450983409623";     // 97 bits
const char* g_str = "93450983094850938450983409621";
const char* gg_str = "-2";                               // g = gg mod p
const char *A = "45416776270485369791375944998";		 // A = g^a mod p
const char *B = "15048074151770884271824225393";		 // B = g^b mod p

void bsgs(mpz_t x,mpz_t g,mpz_t y,mpz_t p){
	mpz_t r,t,temp_a,temp_b;
	mpz_inits(r,t,temp_a,temp_b,NULL);
	int flag = 0;
	mpz_set_ui(t,1);
	
	
	unsigned long long s = 305697535310396;
	unsigned long long i,j;
	i = 0;
	j = 0;						
	unsigned long long len = 305697535310400;
				 
	mpz_t baby[len];
	mpz_t giant[len];
	
	while(1){	
		
		mpz_powm(temp_a,g,r,p);
		mpz_mul(temp_a,y,temp_a);
		mpz_powm_ui(temp_a,temp_a,1,p);    			//mod p 保持封闭性 
		mpz_mul_ui(temp_b,t,s);
		mpz_powm(temp_b,g,temp_b,p);
		//temp_a = y*(g^r) % p , temp_b = g^(t*s) % p 
		
		mpz_init2(baby[i],128);       					//初始化 128 bits 
		mpz_init2(giant[i],128);	  	
		
		mpz_set(baby[i],temp_a);
		mpz_set(giant[i],temp_a); 
		
		i++;
		mpz_add_ui(r,r,1);
		mpz_add_ui(t,t,1);
		if( mpz_cmp_ui(r,s) > 0){     						// r>s 时 break 
			break;
		}
	}
	
	mpz_set_ui(r,0);
	mpz_set_ui(t,0);
	
	/*
	i = 0;
	j = 0;
	while(1){
		while(1){
			if(mpz_cmp(baby[i],giant[j]) == 0){
				flag = 1;
				mpz_set_ui(r,i);
				mpz_set_ui(t,j);
				break;
			}
			j++;
		}
		
		if(flag == 1){
			break;
		}
		i++;
	}
	
	mpz_add_ui(t,t,1);
	mpz_mul_ui(x,t,s);
	mpz_sub(x,x,r);
	mpz_powm_ui(x,x,1,p);
	*/
	
	
	/*for(i = 0;i<len;i++){
		mpz_clear(baby[i]);
		mpz_clear(giant[i]);
	}
	mpz_clears(r,t,temp_a,temp_b);
	
	mpz_set_ui(x,1);
} 

int main(){
	mpz_t x,g,y,p;
	mpz_inits(x,g,y,p,NULL);
	mpz_set_str(g,g_str,10);
	mpz_set_str(p,p_str,10);
	//mpz_set_str(y,B,10);
	mpz_set_str(y,A,10);
	
	bsgs(x,g,y,p);
	
	gmp_printf("%Zd\n",x);
	mpz_clears(x,g,y,p);
	
	return 0;
}
