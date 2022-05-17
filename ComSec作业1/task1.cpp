#include <iostream>
#include <cstdlib>
#include <math.h>
#include <fstream>
#include <gmpxx.h>
#include <gmp.h>
using namespace std;

int times = 15;


bool MillerTest(mpz_t a,mpz_t q,mpz_t n){
	mpz_t x,nn;
	mpz_inits(x,nn,NULL);
	mpz_powm(x,a,q,n);
	mpz_sub_ui(nn,n,1);
	
	if(  mpz_cmp_ui(x,1) == 0  ||  mpz_cmp(x,nn) == 0  ){
		return 1;
	}
	
	
	while(mpz_cmp(nn,q)!=0){
		
		mpz_powm(x,x,x,n);
		mpz_mul_ui(q,q,2);
		
		if( mpz_cmp(x,nn) == 0 ){
			return 1;
		}
	}
	
	return 0;
}

bool IsPrime(mpz_t n,int k){
	
	gmp_randstate_t state;
	gmp_randinit_default(state);
	

	
	mpz_t q,a,remin;
	mpz_inits(q,a,remin,NULL);
	mpz_sub_ui(q,n,1);
	
	
	while(mpz_cdiv_r_ui(remin,q,2) == 0){
		mpz_cdiv_q_ui(q,q,2);
	}
	
	
	//output: 2 ~ n-1 µÄËæ»úÊý a 
	for(int i = 0;i < k;i++){
		mpz_urandomm(a,state,n);  
		
		while(mpz_cmp_ui(a,2) <= 0){
			mpz_urandomm(a,state,n);						  
		}	
			
	}
	
	if(!MillerTest(a,q,n)){
		return 0;
	}
	
	return 1;
} 

int main(){
	
	mpz_t n;
	mpz_inits(n,NULL);

		
	gmp_randstate_t state;
	gmp_randinit_default(state);

	
	mpz_urandomb(n,state,256);


	if(IsPrime(n,times)){
		mpz_out_str(stdout,10,n);
		cout<<endl<<"is Prime"<<endl;	
	}
	else{
		mpz_out_str(stdout,10,n);
		cout<<endl<<"is not Prime"<<endl;
	}
/*	
	if(mpz_probab_prime_p(n,times) == 1){
		cout<<endl<<"is Prime"<<endl;
	}
	else{
		cout<<endl<<"is not Prime"<<endl;
	}
*/	
	
	return 0;
	
}
