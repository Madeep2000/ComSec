#include <iostream>
#include <cstdlib>
#include <math.h>
#include <fstream>
#include <gmpxx.h>
#include <gmp.h>
using namespace std;

int rep = 15;   //素数测试用值 


//output:两个512比特的素数p,q 
void gender(mpz_t p,mpz_t q){
	
	gmp_randstate_t state;
	gmp_randinit_default(state);


	while(1){
		mpz_urandomb(p,state,512);		
		if( mpz_probab_prime_p(p,rep) == 1 ){
			while(1){
				mpz_urandomb(q,state,512);
				if( mpz_probab_prime_p(q,rep) == 1 ){
					break;
				}
			}
			break;
		}		
	}
	return;
}

//input：两个素数 p，q 
//output:p*q的欧拉函数值euler
void euler_func(mpz_t euler,mpz_t p,mpz_t q){
	mpz_t one,pp,qq;          //1,(p-1),(q-1)
	
	mpz_inits(one,pp,qq,NULL);
	mpz_set_str(one,"1",10);
	mpz_sub(pp,p,one);
	mpz_sub(qq,q,one);
	
	mpz_mul(euler,pp,qq);
	
	return;
} 



int main(){
	

	

	mpz_t p,q,n,euler;
	mpz_inits(p,q,n,euler,NULL);
	

	gender(p,q);
	mpz_mul(n,p,q);
	euler_func(euler,p,q);
	
	
	mpz_out_str(stdout,10,p);
	cout<<endl<<endl;
	mpz_out_str(stdout,10,q);
	cout<<endl<<endl;
	mpz_out_str(stdout,10,n);
	cout<<endl<<endl;
	mpz_out_str(stdout,10,euler);
	cout<<endl<<endl;
	
	
	return 0;
 }  

